#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sstream>

#define SYMBOL_LENGTH   20      // Maximum length of a variable name (identifier)
#define INT             0       // Integer type
#define CHAR            1       // Character string type
#define BST             2       // Binary search tree type
#define STRTERM         '\0'    // String termination character

using namespace std;

#pragma warning(disable: 4996)

struct symbolTableEntry{
    char symbol[ SYMBOL_LENGTH ]; // Variable identifier
    int type;       // The type of the variable: one of INT, CHAR, or BST
    int offset;     // Start address of variable in physical memory given as offset
    int length;    // Size in bytes used to store variable in physical memory
};

struct heapEntry{
    int blockSize;  // Size of free block in bytes
    int offset;     // Start address of free block given as offset into memory block
};

struct overlayTableEntry{
    char charValue[ SYMBOL_LENGTH ];
    int intValue;
    int type;
    int offset;
};

struct bstTable{
    string symbol = "";
    bstNode  bstName;
};

struct bstNode{
    int key; //A node of a binary search tree ordered on this key value.
    int left; //Left child
    int right; //Right child
};

//Forward Declaration of methods


int counter = 0;
int offsetCounter = 0;

bool is_digits(const std::string &valueCheck){
    return valueCheck.find_first_not_of("0123456789") == std::string::npos;
}

bool isnot_alpha(const std::string &stringCheck){
    return stringCheck.find_first_not_of("\"") == std::string::npos;
}

void allocate( struct symbolTableEntry *x, struct overlayTableEntry *y, string type, string var, int valength, string value ) {

    if (type.compare("INT") == 0) {
        strcpy(x->symbol, var.c_str());
        x->type = INT;
        x->offset = offsetCounter;
        x->length = 4;

        y->intValue = valength;
        y->type = INT;
        y->offset = 0;
    }
    if (type.compare("CHAR") == 0){
        strcpy(x->symbol, var.c_str());
        x->type = CHAR;
        x->offset = offsetCounter;
        x->length = valength;

        strcpy(y->charValue, value.c_str());
        y->type = CHAR;
        y->offset = 0;
    }
    offsetCounter = offsetCounter + 4;
}

void allocate_free( struct heapEntry *h, int offsetCounter, int blockSize ){
    h->offset = offsetCounter;
    h->blockSize = blockSize;
}

void add(symbolTableEntry *symbol, overlayTableEntry *overlay, string var, string value){
    int scalar;

    for (int i = 0; i < counter; i++) {
        if (strcmp(symbol[i].symbol, var.c_str()) == 0){
            if (overlay[i].type == INT){
                if (is_digits(value)){
                    scalar = atoi (value.c_str());
                    overlay[i].intValue = overlay[i].intValue + scalar; //update offset?
                }
                else{
                    for (int k = 0; k < counter; k++) {
                        if (strcmp(symbol[k].symbol, value.c_str()) == 0){
                            if (overlay[k].type == INT)
                                overlay[i].intValue = overlay[i].intValue + overlay[k].intValue;
                            else
                                cout << "Error: RHS of add command must be type INT." << endl;
                        }
                    }

                }
            }
            else
                cout << "Error: LHS of add must be type INT." << endl;
        }
    }

}

void strcat(symbolTableEntry *symbol, overlayTableEntry *overlay, string var, string value){
    for(int i = 0; i < counter; i++){
        if (strcmp(symbol[i].symbol, var.c_str()) == 0){
            if (isnot_alpha(value)){
                for(int k = 0; k < counter; k++){
                    if (strcmp(overlay[k].charValue, value.c_str()) == 0){
                        if (overlay[k].type == CHAR){
                            strncat(overlay[k].charValue, value.c_str(), sizeof(overlay[k].charValue) + value.length());
                            strncat(overlay[k].charValue, STRTERM, sizeof(overlay[k].charValue) + 1);
                        }
                        else
                            cout << "Error: RHS of strcat must be type CHAR." << endl;
                    }
                }
            }
            else if (symbol[i].type == CHAR){
                if (symbol[i].length < var.length()){
                    cout << "Error: LHS insufficient length to perform strcat." << endl;
                }
                else{
                    strncat(overlay[i].charValue, value.c_str(), sizeof(overlay[i].charValue) + value.length());
                    strncat(overlay[i].charValue, STRTERM, sizeof(overlay[i].charValue) + 1);
                }
            }
            else
                cout << "Error: LHS of strcat must be type CHAR." << endl;
        }
    }
}

void print(symbolTableEntry *symbolTable, overlayTableEntry *overlayTable, string var) {
    for (int i = 0; i < counter; i++) {
        if (strcmp(symbolTable[i].symbol, var.c_str()) == 0 && symbolTable[i].type == INT)
            cout << "The variable " << symbolTable[i].symbol << " has a value of " << overlayTable[i].intValue <<
            " ." << endl;
        else if (strcmp(symbolTable[i].symbol, var.c_str()) == 0 && symbolTable[i].type == CHAR)
            cout << "The variable " << symbolTable[i].symbol << " has a value of " << overlayTable[i].charValue <<
            " ." << endl;
    }
}

void free(symbolTableEntry *s, heapEntry *h, overlayTableEntry *o, string var){
    for(int i = 0; i < counter; i++){
        if (strcmp(s[i].symbol, var.c_str()) == 0){
            h[i].offset = 0;
            h[i].blockSize = 0;

            strcpy(o[i].charValue, "");
            o[i].intValue = 0;
            o[i].offset = 0;

            strcpy(s[i].symbol, "");
            s[i].offset = 0;
            s[i].length = 0;
        }
    }
}

void map(symbolTableEntry *s){
    cout << "Memory map:" << endl;
    for (int i = 0; i < counter; i++){
        printf( "Integer i=%d (decimal), i=0x%x (hexadecimal)\n", s[i].length, s[i].length );
    }
}

void compact(heapEntry *h, symbolTableEntry *s){
    cout << "A list of free blocks" << endl;
    for (int i = 0; i < counter; i++){
        if (s->offset == h->offset){}
        else
            cout << "Offset: " << h->offset << ",\t" << "Size: " << h->blockSize << "\n" << endl;

    }
}

void allocateBST(bstTable *T, string nodeName, int key){
    for(int i =0; i < sizeof(T); i++){
        if (T[i].symbol.compare("") == 0) {
            struct bstNode *root = new bstNode;
            root->key = key;
            root->left = NULL;
            root->right = NULL;
            T[i].symbol = nodeName;
            memcpy(&T[i].bstName, &root, sizeof(root));
        }
    }
}

void insert(string nodeInsert, string insertKey){
    cout << "Inserting into BST..." << endl;

}

int main(){
    int numAlloc;
    int numCommand;
    int numInput;
    char cinChar;
    string cinTemp;
    string cinCommand;
    string cinVar;

    cout << "Welcome to Memory Management!" << endl;
    cout << "Enter number for n for 2^n blocks to allocate: " << endl;
    cin >> numAlloc;

    char *symBytes = (char *) malloc(sizeof(symbolTableEntry));
    char *overBytes = (char *) malloc(sizeof(overlayTableEntry));
    char *heapBytes = (char *) malloc(sizeof(heapEntry));

    struct heapEntry *freeSpace = new heapEntry[2^numAlloc];
    allocate_free((struct heapEntry *) heapBytes, offsetCounter, 2^numAlloc );
    memcpy(&freeSpace[counter], symBytes, sizeof(freeSpace));

    cout << "Enter size of hash table: " << endl;
    cin >> numAlloc;

    struct symbolTableEntry *symTab = new symbolTableEntry[numAlloc]; //Hash table implementation
    struct overlayTableEntry *mallocTab = new overlayTableEntry[numAlloc];
    struct bstTable *bstTab = new bstTable[numAlloc];

    cout << "Input number of commands: " << endl;
    cin >> numCommand;

    for (int i = 0; i < numCommand; i++){
        cin >> cinCommand;

        if (cinCommand.compare("allocate") == 0){
            cin >> cinTemp;
            if (cinTemp.compare("INT") == 0){
                cin >> cinVar;

                cin >> numInput;

                allocate((struct symbolTableEntry *) symBytes, (struct overlayTableEntry *) overBytes, cinTemp, cinVar, numInput, "");
                memcpy(&symTab[counter], symBytes, sizeof(symTab));
                memcpy(&mallocTab[counter], overBytes, sizeof(mallocTab));

                counter++;
                allocate_free((struct heapEntry *) heapBytes, offsetCounter, 2^numAlloc );
                memcpy(&freeSpace[counter], symBytes, sizeof(freeSpace));
            }
            else if (cinTemp.compare("CHAR") == 0){
                cin >> cinVar;

                cin >> numInput;

                cin >> cinTemp;

                allocate((struct symbolTableEntry *) symBytes, (struct overlayTableEntry *) overBytes, cinTemp, cinVar, numInput, cinTemp);
                memcpy(&symTab[counter], symBytes, sizeof(symTab));
                memcpy(&mallocTab[counter], overBytes, sizeof(mallocTab));


                counter++;
                allocate_free((struct heapEntry *) heapBytes, offsetCounter, 2^numAlloc );
                memcpy(&freeSpace[counter], symBytes, sizeof(freeSpace));
            }
            else if (cinTemp.compare("BST") == 0){
                cin >> cinVar;

                cin >> numInput;

                struct bstNode *bstEntry = new bstNode;
                allocateBST(bstTab, cinVar, numInput);
            }
        }
        if (cinCommand.compare("add") == 0 ){
            cin >> cinVar;

            cin >> cinTemp;
            add(symTab, mallocTab, cinVar, cinTemp);
        }
        if (cinCommand.compare("strcat") == 0){
            cin >> cinVar;
            cin >> cinTemp;
            strcat(symTab, mallocTab, cinVar, cinTemp);
        }
        if (cinCommand.compare("print") == 0){
            cin >> cinVar;
            print(symTab, mallocTab, cinVar);

        }
        if (cinCommand.compare("map") == 0){
            map(symTab);
        }
        if (cinCommand.compare("free") == 0){
            cin >> cinVar;

            free(symTab, freeSpace, mallocTab, cinVar);
        }
        if (cinCommand.compare("compact") == 0){
            compact(freeSpace, symTab);
        }
        if (cinCommand.compare("insert") == 0){
            cin >> cinVar;
            cin >> cinTemp;
            insert(cinVar, cinTemp);
        }
    }
}