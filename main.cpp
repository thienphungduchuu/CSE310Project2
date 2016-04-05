#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sstream>

using namespace std;

#pragma warning(disable: 4996)

#define NO_TEAMS      32 // Number of NFL teams
#define TEAM_NAME_LEN 25 // Maximum team name string length
#define TOP_LEN        6 // Maximum time of possession string length

struct team_stats{
    char team_name[ TEAM_NAME_LEN ]; // Name of NFL team
    int games; // Number of games played in the season
    float pts_per_game; // Points per game
    int total_points; // Total points
    int scrimmage_plays; // Scrimmage plays
    float yds_per_game; // Yards per game
    float yds_per_play; // Yards per play
    float first_per_game; // First downs per game
    int third_md; // Third down conversions
    int third_att; // Third down attempts
    int third_pct; // Third down percentage
    int fourth_md; // Fourth down conversions
    int fourth_att; // Fourth down attempts
    int fourth_pct; // Fourth down percentage
    int penalties; // Number of penalties
    int pen_yds; // Penalty yards
    char top_per_game[ TOP_LEN ]; // Time of possession per game
    int fum; // Number of fumbles
    int lost; // Fumbles lost
    int to; // Turnover ratio
};

struct annual_stats{
    int year;
    struct team_stats teams[ NO_TEAMS ];
};

struct sortInt {
    int year;
    char team_name[ TEAM_NAME_LEN ];
    int stat;
};

struct sortFloat{
    int year;
    char team_name[ TEAM_NAME_LEN ];
    float stat;
};

int counter = 0; //Counts number of teams in array.
struct annual_stats footballSeason[NO_TEAMS]; //Initialize annual_stats


//Forward declaration of functions
void menuSelect(char);
void addTeam();
void bSort(int, string, string);
void bFind(int, string, string);
void bSortRange(int, int, string, string);
bool checkYear(int);
bool checkField(string);
bool checkOrder(string);
bool checkItem(string);
int selectYear(int);
void printList(int, string, string);
void printRangeInt(sortInt*, string);
void printRangeFloat(sortFloat*, string);
void flush();

int main() {

    int max = NO_TEAMS;
    int startNum = 0;
    int numSort;
    string cinTemp;
    string pickSort;
    int pickYear;
    string pickStat;
    string pickOrder;

    char choice = 'i';

    cout << "Welcome to Superbowl 50 Database" << endl;
    addTeam();
    while (true){
        cout << "Enter the number of sorts: " << endl;
        getline(cin, cinTemp);
        cout << cinTemp << endl;
        stringstream myStream(cinTemp);
        if (myStream >> numSort) //number of sorts
            break;
    }

    while (startNum < numSort){
        cout << "\nPick sorting method: " << endl;
        cin >> pickSort;
        cout << pickSort << endl;
        if(pickSort.compare("bsort") == 0) {
            cout << "Enter the season year: " << endl;
            cin >> pickYear;
            cout << pickYear << endl;
            cout << "Enter stat: " << endl;
            cin >> pickStat;
            cout << pickStat << endl;
            cout << "Enter order: " << endl;
            cin >> pickOrder;
            cout << pickOrder << endl;
            printList(pickYear, pickStat, pickOrder);
        }
        if(pickSort.compare("bfind") == 0){
            cout << "Enter the season year: " << endl;
            cin >> pickYear;
            cout << pickYear << endl;
            cout << "Enter stat: " << endl;
            cin >> pickStat;
            cout << pickStat << endl;
            cout << "Enter order: " << endl;
            cin >> pickOrder;
            cout << pickOrder << endl;
            bFind(pickYear, pickStat, pickOrder);
        }
        startNum++;
    }

    /*

    do {
        printf("Please enter selection:\n");
        printf("\ta: Add a football season to the list.\n");
        printf("\tb: Run bubble sort on the list.\n");
        printf("\tc: Find a team on the list using bubble or quick sort.\n");
        printf("\tq: Save and quit the list.\n");

        //flush(); //flush input buffer
        choice = tolower(getchar());
        menuSelect(choice);
    }while(choice != 113); //CHANGE LATER
     */
    return 0;
}

void menuSelect(char input){
    string choice;
    int sortYear;
    int startYear;
    int endYear;
    string findName;
    string findMethod;
    string sortName;
    string sortField;
    string sortOrder;

    switch(input){
        case 'a':
            addTeam();
            break;
        case 'b':
            printf("Which type of sort would you like to perform? (bsort or qsort)\n");
            cin >> sortName;
            if(sortName.compare("bsort") == 0){
                printf("Sort method: (enter 'range' or enter sort year\n");
                cin >> choice;
                if (choice.compare("range") == 0){
                    printf("Enter start year:\n");
                    cin >> startYear;
                    printf("Enter end year:\n");
                    cin >> endYear;
                    printf("Enter field:\n");
                    cin >> sortField;
                    printf("Choose sorting order: (incr or decr)\n");
                    cin >> sortOrder;
                    bSortRange(startYear, endYear, sortField, sortOrder);
                }
                else {
                    printf("Enter category:\n");
                    cin >> sortField;
                    printf("Choose sorting order: (incr or decr)\n");
                    cin >> sortOrder;
                    printList(sortYear, sortField, sortOrder);
                }
            }
            else if(sortName.compare("qsort") == 0){
            }
            else{
                printf("Invalid input!\n");
            }
            break;
        case 'c':
            printf("Which sorting method? (bfind or qfind)\n");
            cin >> findName;
            if(findName.compare("bfind") == 0){
                printf("Enter year:\n");
                cin >> sortYear;
                printf("Enter field:\n");
                cin >> sortField;
                printf("Choose find method: (max, min, average, or median)\n");
                cin >> findMethod;
                bFind(sortYear, sortField, findMethod);
            }
            break;
        case 'q':
            break;
        default:
            printf("Invalid input!\n");
    }
}

void addTeam(){

    string teamInput = "";
    int statInput;
    float decStat;


    int temp = 0;
    int loc = 0;

    while (true){
        cout << "Enter the number of football seasons to add: ";
        getline(cin, teamInput);
        stringstream myStream(teamInput);
        if (myStream >> statInput)
            break;
    }
    temp = statInput;

    while (true){
        cout << "Please enter season year: " << endl;
        getline(cin, teamInput);
        stringstream myStream(teamInput);
        if (myStream >> statInput)
            break;
    }
    footballSeason[counter].year = statInput;

    while (loc < temp){
        for (int index = 0; index < 32; index++) {
            printf("Please enter team name:\n");
            cin.getline(footballSeason[counter].teams[index].team_name,TEAM_NAME_LEN,'\t');
            cout << footballSeason[counter].teams[index].team_name << endl;
            printf("Please enter games played in the season:\n");
            cin >> footballSeason[counter].teams[index].games;
            cout << footballSeason[counter].teams[index].games << endl;
            printf("Please enter points per game:\n");
            cin >> footballSeason[counter].teams[index].pts_per_game;
            cout << footballSeason[counter].teams[index].pts_per_game << endl;
            printf("Please enter total points:\n");
            cin >> footballSeason[counter].teams[index].total_points;
            cout << footballSeason[counter].teams[index].total_points << endl;
            printf("Please enter scrimmage plays:\n");
            cin >> footballSeason[counter].teams[index].scrimmage_plays;
            cout << footballSeason[counter].teams[index].scrimmage_plays << endl;
            printf("Please enter yards per game:\n");
            cin >> footballSeason[counter].teams[index].yds_per_game;
            cout << footballSeason[counter].teams[index].yds_per_game << endl;
            printf("Please enter yards per play:\n");
            cin >> footballSeason[counter].teams[index].yds_per_play;
            cout << footballSeason[counter].teams[index].yds_per_play << endl;
            printf("Please enter first downs per game:\n");
            cin >> footballSeason[counter].teams[index].first_per_game;
            cout << footballSeason[counter].teams[index].first_per_game << endl;
            printf("Please enter third down conversions:\n");
            cin >> footballSeason[counter].teams[index].third_md;
            cout << footballSeason[counter].teams[index].third_md << endl;
            printf("Please enter third down attempts:\n");
            cin >> footballSeason[counter].teams[index].third_att;
            cout << footballSeason[counter].teams[index].third_att << endl;
            printf("Please enter third down percentage:\n");
            cin >> footballSeason[counter].teams[index].third_pct;
            cout << footballSeason[counter].teams[index].third_pct << endl;
            printf("Please enter fourth down conversions:\n");
            cin >> footballSeason[counter].teams[index].fourth_md;
            cout << footballSeason[counter].teams[index].fourth_md << endl;
            printf("Please enter fourth down attempts:\n");
            cin >> footballSeason[counter].teams[index].fourth_att;
            cout << footballSeason[counter].teams[index].fourth_att << endl;
            printf("Please enter fourth down percentage:\n");
            cin >> footballSeason[counter].teams[index].fourth_pct;
            cout << footballSeason[counter].teams[index].fourth_pct << endl;
            printf("Please enter number of penalties:\n");
            cin >> footballSeason[counter].teams[index].penalties;
            cout << footballSeason[counter].teams[index].penalties << endl;
            printf("Please enter penalty yards:\n");
            cin >> footballSeason[counter].teams[index].pen_yds;
            cout << footballSeason[counter].teams[index].penalties << endl;
            printf("Please enter time of possession per game:\n");
            cin >> footballSeason[counter].teams[index].top_per_game;
            cout << footballSeason[counter].teams[index].top_per_game << endl;
            printf("Please enter number of fumbles:\n");
            cin >> footballSeason[counter].teams[index].fum;
            cout << footballSeason[counter].teams[index].fum << endl;
            printf("Please enter fumbles lost:\n");
            cin >> footballSeason[counter].teams[index].lost;
            cout << footballSeason[counter].teams[index].lost << endl;
            printf("Please enter turnover ratio:\n");
            cin >> footballSeason[counter].teams[index].to;
            cout << footballSeason[counter].teams[index].to << endl;
            std::cin.ignore(3, '\n');
        }
        counter++;
        loc++;
    }
}

void bSort(int year, string field, string order){
    int loc, temp;
    int swap = 0;
    float swapf = 0;
    int chooseYear = selectYear(year);

    if (checkYear(year) && checkField(field) && checkOrder(order)){
        if(field.compare("games") == 0) {
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].games >
                            footballSeason[chooseYear].teams[loc + 1].games) {
                            swap = footballSeason[chooseYear].teams[loc].games;
                            footballSeason[chooseYear].teams[loc].games = footballSeason[chooseYear].teams[loc + 1].games;
                            footballSeason[chooseYear].teams[loc + 1].games = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].games <
                            footballSeason[chooseYear].teams[loc + 1].games) {
                            swap = footballSeason[chooseYear].teams[loc].games;
                            footballSeason[chooseYear].teams[loc].games = footballSeason[chooseYear].teams[loc + 1].games;
                            footballSeason[chooseYear].teams[loc + 1].games = swap;
                        }
                    }
                }
            }
        }
        else if(field.compare("pts_per_game") == 0) {
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].pts_per_game >
                            footballSeason[chooseYear].teams[loc + 1].pts_per_game) {
                            swapf = footballSeason[chooseYear].teams[loc].pts_per_game;
                            footballSeason[chooseYear].teams[loc].pts_per_game = footballSeason[chooseYear].teams[loc + 1].pts_per_game;
                            footballSeason[chooseYear].teams[loc + 1].pts_per_game = swapf;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].pts_per_game <
                            footballSeason[chooseYear].teams[loc + 1].pts_per_game) {
                            swapf = footballSeason[chooseYear].teams[loc].pts_per_game;
                            footballSeason[chooseYear].teams[loc].pts_per_game = footballSeason[chooseYear].teams[loc + 1].pts_per_game;
                            footballSeason[chooseYear].teams[loc + 1].pts_per_game = swapf;
                        }
                    }
                }
            }
        }
        else if(field.compare("total_points") == 0) {
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].total_points >
                            footballSeason[chooseYear].teams[loc + 1].total_points) {
                            swap = footballSeason[chooseYear].teams[loc].total_points;
                            footballSeason[chooseYear].teams[loc].total_points = footballSeason[chooseYear].teams[loc + 1].total_points;
                            footballSeason[chooseYear].teams[loc + 1].total_points = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].total_points <
                            footballSeason[chooseYear].teams[loc + 1].total_points) {
                            swap = footballSeason[chooseYear].teams[loc].total_points;
                            footballSeason[chooseYear].teams[loc].total_points = footballSeason[chooseYear].teams[loc + 1].total_points;
                            footballSeason[chooseYear].teams[loc + 1].total_points = swap;
                        }
                    }
                }
            }
        }
        else if(field.compare("scrimmage_plays") == 0) {
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].scrimmage_plays >
                            footballSeason[chooseYear].teams[loc + 1].scrimmage_plays) {
                            swap = footballSeason[chooseYear].teams[loc].scrimmage_plays;
                            footballSeason[chooseYear].teams[loc].scrimmage_plays = footballSeason[chooseYear].teams[loc + 1].scrimmage_plays;
                            footballSeason[chooseYear].teams[loc + 1].scrimmage_plays = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].scrimmage_plays <
                            footballSeason[chooseYear].teams[loc + 1].scrimmage_plays) {
                            swap = footballSeason[chooseYear].teams[loc].scrimmage_plays;
                            footballSeason[chooseYear].teams[loc].scrimmage_plays = footballSeason[chooseYear].teams[loc + 1].scrimmage_plays;
                            footballSeason[chooseYear].teams[loc + 1].scrimmage_plays = swap;
                        }
                    }
                }
            }
        }
        else if(field.compare("yds_per_game") == 0) {
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].yds_per_game >
                            footballSeason[chooseYear].teams[loc + 1].yds_per_game) {
                            swapf = footballSeason[chooseYear].teams[loc].yds_per_game;
                            footballSeason[chooseYear].teams[loc].yds_per_game = footballSeason[chooseYear].teams[loc + 1].yds_per_game;
                            footballSeason[chooseYear].teams[loc + 1].yds_per_game = swapf;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].yds_per_game <
                            footballSeason[chooseYear].teams[loc + 1].yds_per_game) {
                            swapf = footballSeason[chooseYear].teams[loc].yds_per_game;
                            footballSeason[chooseYear].teams[loc].yds_per_game = footballSeason[chooseYear].teams[loc + 1].yds_per_game;
                            footballSeason[chooseYear].teams[loc + 1].yds_per_game = swapf;
                        }
                    }
                }
            }
        }
        else if(field.compare("first_per_game") == 0) {
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].first_per_game >
                            footballSeason[chooseYear].teams[loc + 1].first_per_game) {
                            swapf = footballSeason[chooseYear].teams[loc].first_per_game;
                            footballSeason[chooseYear].teams[loc].first_per_game = footballSeason[chooseYear].teams[loc + 1].first_per_game;
                            footballSeason[chooseYear].teams[loc + 1].first_per_game = swapf;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].first_per_game <
                            footballSeason[chooseYear].teams[loc + 1].first_per_game) {
                            swapf = footballSeason[chooseYear].teams[loc].first_per_game;
                            footballSeason[chooseYear].teams[loc].first_per_game = footballSeason[chooseYear].teams[loc + 1].first_per_game;
                            footballSeason[chooseYear].teams[loc + 1].first_per_game = swapf;
                        }
                    }
                }
            }
        }
        else if(field.compare("third_md") == 0) {
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].third_md >
                            footballSeason[chooseYear].teams[loc + 1].third_md) {
                            swap = footballSeason[chooseYear].teams[loc].third_md;
                            footballSeason[chooseYear].teams[loc].third_md = footballSeason[chooseYear].teams[loc + 1].third_md;
                            footballSeason[chooseYear].teams[loc + 1].third_md = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].third_md <
                            footballSeason[chooseYear].teams[loc + 1].third_md) {
                            swap = footballSeason[chooseYear].teams[loc].third_md;
                            footballSeason[chooseYear].teams[loc].third_md = footballSeason[chooseYear].teams[loc + 1].third_md;
                            footballSeason[chooseYear].teams[loc + 1].third_md = swap;
                        }
                    }
                }
            }
        }
        else if(field.compare("third_att") == 0) {
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].third_att >
                            footballSeason[chooseYear].teams[loc + 1].third_att) {
                            swap = footballSeason[chooseYear].teams[loc].third_att;
                            footballSeason[chooseYear].teams[loc].third_att = footballSeason[chooseYear].teams[loc + 1].third_att;
                            footballSeason[chooseYear].teams[loc + 1].third_att = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].third_att <
                            footballSeason[chooseYear].teams[loc + 1].third_att) {
                            swap = footballSeason[chooseYear].teams[loc].third_att;
                            footballSeason[chooseYear].teams[loc].third_att = footballSeason[chooseYear].teams[loc + 1].third_att;
                            footballSeason[chooseYear].teams[loc + 1].third_att = swap;
                        }
                    }
                }
            }
        }
        else if(field.compare("third_pct") == 0) {
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].third_pct >
                            footballSeason[chooseYear].teams[loc + 1].third_pct) {
                            swap = footballSeason[chooseYear].teams[loc].third_pct;
                            footballSeason[chooseYear].teams[loc].third_pct = footballSeason[chooseYear].teams[loc + 1].third_pct;
                            footballSeason[chooseYear].teams[loc + 1].third_pct = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].third_pct <
                            footballSeason[chooseYear].teams[loc + 1].third_pct) {
                            swap = footballSeason[chooseYear].teams[loc].third_pct;
                            footballSeason[chooseYear].teams[loc].third_pct = footballSeason[chooseYear].teams[loc + 1].third_pct;
                            footballSeason[chooseYear].teams[loc + 1].third_pct = swap;
                        }
                    }
                }
            }
        }
        else if(field.compare("fourth_md") == 0) {
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].fourth_md >
                            footballSeason[chooseYear].teams[loc + 1].fourth_md) {
                            swap = footballSeason[chooseYear].teams[loc].fourth_md;
                            footballSeason[chooseYear].teams[loc].fourth_md = footballSeason[chooseYear].teams[loc + 1].fourth_md;
                            footballSeason[chooseYear].teams[loc + 1].fourth_md = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].fourth_md <
                            footballSeason[chooseYear].teams[loc + 1].fourth_md) {
                            swap = footballSeason[chooseYear].teams[loc].fourth_md;
                            footballSeason[chooseYear].teams[loc].fourth_md = footballSeason[chooseYear].teams[loc + 1].fourth_md;
                            footballSeason[chooseYear].teams[loc + 1].fourth_md = swap;
                        }
                    }
                }
            }
        }
        else if(field.compare("fourth_att") == 0) {
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].fourth_att >
                            footballSeason[chooseYear].teams[loc + 1].fourth_att) {
                            swap = footballSeason[chooseYear].teams[loc].fourth_att;
                            footballSeason[chooseYear].teams[loc].fourth_att = footballSeason[chooseYear].teams[loc + 1].fourth_att;
                            footballSeason[chooseYear].teams[loc + 1].fourth_att = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].fourth_att <
                            footballSeason[chooseYear].teams[loc + 1].fourth_att) {
                            swap = footballSeason[chooseYear].teams[loc].fourth_att;
                            footballSeason[chooseYear].teams[loc].fourth_att = footballSeason[chooseYear].teams[loc + 1].fourth_att;
                            footballSeason[chooseYear].teams[loc + 1].fourth_att = swap;
                        }
                    }
                }
            }
        }
        else if(field.compare("fourth_pct") == 0) {
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].fourth_pct >
                            footballSeason[chooseYear].teams[loc + 1].fourth_pct) {
                            swap = footballSeason[chooseYear].teams[loc].fourth_pct;
                            footballSeason[chooseYear].teams[loc].fourth_pct = footballSeason[chooseYear].teams[loc + 1].fourth_pct;
                            footballSeason[chooseYear].teams[loc + 1].fourth_pct = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].fourth_pct <
                            footballSeason[chooseYear].teams[loc + 1].fourth_pct) {
                            swap = footballSeason[chooseYear].teams[loc].fourth_pct;
                            footballSeason[chooseYear].teams[loc].fourth_pct = footballSeason[chooseYear].teams[loc + 1].fourth_pct;
                            footballSeason[chooseYear].teams[loc + 1].fourth_pct = swap;
                        }
                    }
                }
            }
        }
        else if(field.compare("penalties") == 0) {
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].penalties >
                            footballSeason[chooseYear].teams[loc + 1].penalties) {
                            swap = footballSeason[chooseYear].teams[loc].penalties;
                            footballSeason[chooseYear].teams[loc].penalties = footballSeason[chooseYear].teams[loc + 1].penalties;
                            footballSeason[chooseYear].teams[loc + 1].penalties = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].penalties <
                            footballSeason[chooseYear].teams[loc + 1].penalties) {
                            swap = footballSeason[chooseYear].teams[loc].penalties;
                            footballSeason[chooseYear].teams[loc].penalties = footballSeason[chooseYear].teams[loc + 1].penalties;
                            footballSeason[chooseYear].teams[loc + 1].penalties = swap;
                        }
                    }
                }
            }
        }
        else if(field.compare("pen_yds") == 0) {
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].pen_yds >
                            footballSeason[chooseYear].teams[loc + 1].pen_yds) {
                            swap = footballSeason[chooseYear].teams[loc].pen_yds;
                            footballSeason[chooseYear].teams[loc].pen_yds = footballSeason[chooseYear].teams[loc + 1].pen_yds;
                            footballSeason[chooseYear].teams[loc + 1].pen_yds = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].pen_yds <
                            footballSeason[chooseYear].teams[loc + 1].pen_yds) {
                            swap = footballSeason[chooseYear].teams[loc].pen_yds;
                            footballSeason[chooseYear].teams[loc].pen_yds = footballSeason[chooseYear].teams[loc + 1].pen_yds;
                            footballSeason[chooseYear].teams[loc + 1].pen_yds = swap;
                        }
                    }
                }
            }
        }
        else if(field.compare("fum") == 0) {
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].fum >
                            footballSeason[chooseYear].teams[loc + 1].fum) {
                            swap = footballSeason[chooseYear].teams[loc].fum;
                            footballSeason[chooseYear].teams[loc].fum = footballSeason[chooseYear].teams[loc + 1].fum;
                            footballSeason[chooseYear].teams[loc + 1].fum = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].fum <
                            footballSeason[chooseYear].teams[loc + 1].fum) {
                            swap = footballSeason[chooseYear].teams[loc].fum;
                            footballSeason[chooseYear].teams[loc].fum = footballSeason[chooseYear].teams[loc + 1].fum;
                            footballSeason[chooseYear].teams[loc + 1].fum = swap;
                        }
                    }
                }
            }
        }
        else if(field.compare("lost") == 0) {
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].lost >
                            footballSeason[chooseYear].teams[loc + 1].lost) {
                            swap = footballSeason[chooseYear].teams[loc].lost;
                            footballSeason[chooseYear].teams[loc].lost = footballSeason[chooseYear].teams[loc + 1].lost;
                            footballSeason[chooseYear].teams[loc + 1].lost = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].lost <
                            footballSeason[chooseYear].teams[loc + 1].lost) {
                            swap = footballSeason[chooseYear].teams[loc].lost;
                            footballSeason[chooseYear].teams[loc].lost = footballSeason[chooseYear].teams[loc + 1].lost;
                            footballSeason[chooseYear].teams[loc + 1].lost = swap;
                        }
                    }
                }
            }
        }
        else if(field.compare("to") == 0) {
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].to >
                            footballSeason[chooseYear].teams[loc + 1].to) {
                            swap = footballSeason[chooseYear].teams[loc].to;
                            footballSeason[chooseYear].teams[loc].to = footballSeason[chooseYear].teams[loc + 1].to;
                            footballSeason[chooseYear].teams[loc + 1].to = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (footballSeason[chooseYear].teams[loc].to <
                            footballSeason[chooseYear].teams[loc + 1].to) {
                            swap = footballSeason[chooseYear].teams[loc].to;
                            footballSeason[chooseYear].teams[loc].to = footballSeason[chooseYear].teams[loc + 1].to;
                            footballSeason[chooseYear].teams[loc + 1].to = swap;
                        }
                    }
                }
            }
        }
    }
}

void bFind(int year, string field, string item){
    int loc;
    float temp = 0;
    int index = 0; //store index of max
    int chooseYear = selectYear(year);


    bSort(year, field, "incr");

    if(checkYear(year) && checkField(field) && checkItem(item)){
        if(field.compare("games") == 0){
            if(item.compare("max") == 0){
                for(loc = 0; loc < NO_TEAMS; loc++){
                    if (temp < footballSeason[chooseYear].teams[loc].games) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].games;
                    }
                }
                cout << "Team\n" << field;
                for(index = 0; index < NO_TEAMS; index++)
                    cout << footballSeason[chooseYear].teams[index].team_name << "\t" << footballSeason[chooseYear].teams[index].games;
            }
            else if(item.compare("min") == 0){
                for(loc = 0; loc < NO_TEAMS; loc++){
                    if(temp > footballSeason[chooseYear].teams[loc].games){
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].games;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].team_name << "\t" << footballSeason[chooseYear].teams[index].games;
            }
            else if (item.compare("average") == 0){
                for(loc = 0; loc < NO_TEAMS; loc++)
                    temp = temp + footballSeason[chooseYear].teams[loc].games;
                temp = temp / NO_TEAMS;
                cout << field << "\n";
                cout << temp;
            }
            else if (item.compare("median") == 0){
                index = NO_TEAMS/2;
                cout << field << "\n";
                cout << footballSeason[chooseYear].teams[index].games;
            }
        }
        else if(field.compare("pts_per_game") == 0) {
            if (item.compare("max") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp < footballSeason[chooseYear].teams[loc].pts_per_game) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].pts_per_game;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].pts_per_game << "\t" << footballSeason[chooseYear].teams[index].pts_per_game;
            }
            else if (item.compare("min") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp > footballSeason[chooseYear].teams[loc].games) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].games;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].pts_per_game << "\t" << footballSeason[chooseYear].teams[index].pts_per_game;
            }
            else if (item.compare("average") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++)
                    temp = temp + footballSeason[chooseYear].teams[loc].pts_per_game;
                temp = temp / NO_TEAMS;
                cout << field << "\n";
                cout << temp;
            }
            else if (item.compare("median") == 0) {
                index = NO_TEAMS / 2;
                cout << field << "\n";
                cout << footballSeason[chooseYear].teams[index].pts_per_game;
            }
        }
        else if(field.compare("total_points") == 0) {
            if (item.compare("max") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp < footballSeason[chooseYear].teams[loc].total_points) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].total_points;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].total_points << "\t" << footballSeason[chooseYear].teams[index].total_points;
            }
            else if (item.compare("min") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp > footballSeason[chooseYear].teams[loc].total_points) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].total_points;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; index++)
                    cout << footballSeason[chooseYear].teams[index].total_points << "\t" << footballSeason[chooseYear].teams[index].total_points;
            }
            else if (item.compare("average") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++)
                    temp = temp + footballSeason[chooseYear].teams[loc].total_points;
                temp = temp / NO_TEAMS;
                cout << field << "\n";
                cout << temp;
            }
            else if (item.compare("median") == 0) {
                index = NO_TEAMS / 2;
                cout << field << "\n";
                cout << footballSeason[chooseYear].teams[index].total_points;
            }
        }
        else if(field.compare("tsccrimmage_plays") == 0) {
            if (item.compare("max") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp < footballSeason[chooseYear].teams[loc].scrimmage_plays) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].scrimmage_plays;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].scrimmage_plays << "\t" << footballSeason[chooseYear].teams[index].scrimmage_plays;
            }
            else if (item.compare("min") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp > footballSeason[chooseYear].teams[loc].scrimmage_plays) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].scrimmage_plays;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].scrimmage_plays << "\t" << footballSeason[chooseYear].teams[index].scrimmage_plays;
            }
            else if (item.compare("average") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++)
                    temp = temp + footballSeason[chooseYear].teams[loc].scrimmage_plays;
                temp = temp / NO_TEAMS;
                cout << field << "\n";
                cout << temp;
            }
            else if (item.compare("median") == 0) {
                index = NO_TEAMS / 2;
                cout << field << "\n";
                cout << footballSeason[chooseYear].teams[index].scrimmage_plays;
            }
        }
        else if(field.compare("yds_per_game") == 0) {
            if (item.compare("max") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp < footballSeason[chooseYear].teams[loc].yds_per_game) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].yds_per_game;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; index++)
                    cout << footballSeason[chooseYear].teams[index].yds_per_game << "\t" << footballSeason[chooseYear].teams[index].yds_per_game;
            }
            else if (item.compare("min") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp > footballSeason[chooseYear].teams[loc].yds_per_game) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].yds_per_game;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; index++)
                    cout << footballSeason[chooseYear].teams[index].yds_per_game << "\t" << footballSeason[chooseYear].teams[index].yds_per_game;
            }
            else if (item.compare("average") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++)
                    temp = temp + footballSeason[chooseYear].teams[loc].yds_per_game;
                temp = temp / NO_TEAMS;
                cout << field << "\n";
                cout << temp;
            }
            else if (item.compare("median") == 0) {
                index = NO_TEAMS / 2;
                cout << field << "\n";
                cout << footballSeason[chooseYear].teams[index].yds_per_game;
            }
        }
        else if(field.compare("yds_per_play") == 0) {
            if (item.compare("max") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp < footballSeason[chooseYear].teams[loc].yds_per_play) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].yds_per_play;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].yds_per_play << "\t" << footballSeason[chooseYear].teams[index].yds_per_play;
            }
            else if (item.compare("min") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp > footballSeason[chooseYear].teams[loc].yds_per_play) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].yds_per_play;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].yds_per_play << "\t" << footballSeason[chooseYear].teams[index].yds_per_play;
            }
            else if (item.compare("average") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++)
                    temp = temp + footballSeason[chooseYear].teams[loc].yds_per_play;
                temp = temp / NO_TEAMS;
                cout << field << "\n";
                cout << temp;
            }
            else if (item.compare("median") == 0) {
                index = NO_TEAMS / 2;
                cout << field << "\n";
                cout << footballSeason[chooseYear].teams[index].yds_per_play;
            }
        }
        else if(field.compare("first_per_game") == 0) {
            if (item.compare("max") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp < footballSeason[chooseYear].teams[loc].first_per_game) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].first_per_game;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].first_per_game << "\t" << footballSeason[chooseYear].teams[index].first_per_game;
            }
            else if (item.compare("min") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp > footballSeason[chooseYear].teams[loc].first_per_game) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].first_per_game;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].first_per_game << "\t" << footballSeason[chooseYear].teams[index].first_per_game;
            }
            else if (item.compare("average") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++)
                    temp = temp + footballSeason[chooseYear].teams[loc].first_per_game;
                temp = temp / NO_TEAMS;
                cout << field << "\n";
                cout << temp;
            }
            else if (item.compare("median") == 0) {
                index = NO_TEAMS / 2;
                cout << field << "\n";
                cout << footballSeason[chooseYear].teams[index].first_per_game;
            }
        }
        else if(field.compare("third_md") == 0) {
            if (item.compare("max") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp < footballSeason[chooseYear].teams[loc].third_md) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].third_md;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].third_md << "\t" << footballSeason[chooseYear].teams[index].third_md;
            }
            else if (item.compare("min") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp > footballSeason[chooseYear].teams[loc].third_md) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].third_md;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].third_md << "\t" << footballSeason[chooseYear].teams[index].third_md;
            }
            else if (item.compare("average") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++)
                    temp = temp + footballSeason[chooseYear].teams[loc].third_md;
                temp = temp / NO_TEAMS;
                cout << field << "\n";
                cout << temp;
            }
            else if (item.compare("median") == 0) {
                index = NO_TEAMS / 2;
                cout << field << "\n";
                cout << footballSeason[chooseYear].teams[index].third_md;
            }
        }
        else if(field.compare("third_att") == 0) {
            if (item.compare("max") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp < footballSeason[chooseYear].teams[loc].third_att) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].third_att;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].third_att << "\t" << footballSeason[chooseYear].teams[index].third_att;
            }
            else if (item.compare("min") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp > footballSeason[chooseYear].teams[loc].third_att) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].third_att;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].third_att << "\t" << footballSeason[chooseYear].teams[index].third_att;
            }
            else if (item.compare("average") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++)
                    temp = temp + footballSeason[chooseYear].teams[loc].third_att;
                temp = temp / NO_TEAMS;
                cout << field << "\n";
                cout << temp;
            }
            else if (item.compare("median") == 0) {
                index = NO_TEAMS / 2;
                cout << field << "\n";
                cout << footballSeason[chooseYear].teams[index].third_att;
            }
        }
        else if(field.compare("third_pct") == 0) {
            if (item.compare("max") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp < footballSeason[chooseYear].teams[loc].third_pct) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].third_pct;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].third_pct << "\t" << footballSeason[chooseYear].teams[index].third_pct;
            }
            else if (item.compare("min") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp > footballSeason[chooseYear].teams[loc].third_pct) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].third_pct;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].third_pct << "\t" << footballSeason[chooseYear].teams[index].third_pct;
            }
            else if (item.compare("average") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++)
                    temp = temp + footballSeason[chooseYear].teams[loc].third_pct;
                temp = temp / NO_TEAMS;
                cout << field << "\n";
                cout << temp;
            }
            else if (item.compare("median") == 0) {
                index = NO_TEAMS / 2;
                cout << field << "\n";
                cout << footballSeason[chooseYear].teams[index].third_pct;
            }
        }
        else if(field.compare("fourth_md") == 0) {
            if (item.compare("max") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp < footballSeason[chooseYear].teams[loc].fourth_md) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].fourth_md;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].fourth_md << "\t" << footballSeason[chooseYear].teams[index].fourth_md;
            }
            else if (item.compare("min") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp > footballSeason[chooseYear].teams[loc].fourth_md) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].fourth_md;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].fourth_md << "\t" << footballSeason[chooseYear].teams[index].fourth_md;
            }
            else if (item.compare("average") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++)
                    temp = temp + footballSeason[chooseYear].teams[loc].fourth_md;
                temp = temp / NO_TEAMS;
                cout << field << "\n";
                cout << temp;
            }
            else if (item.compare("median") == 0) {
                index = NO_TEAMS / 2;
                cout << field << "\n";
                cout << footballSeason[chooseYear].teams[index].fourth_md;
            }
        }
        else if(field.compare("fourth_att") == 0) {
            if (item.compare("max") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp < footballSeason[chooseYear].teams[loc].fourth_att) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].fourth_att;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].fourth_att << "\t" << footballSeason[chooseYear].teams[index].fourth_att;
            }
            else if (item.compare("min") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp > footballSeason[chooseYear].teams[loc].fourth_att) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].fourth_att;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].fourth_att << "\t" << footballSeason[chooseYear].teams[index].fourth_att;
            }
            else if (item.compare("average") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++)
                    temp = temp + footballSeason[chooseYear].teams[loc].fourth_att;
                temp = temp / NO_TEAMS;
                cout << field << "\n";
                cout << temp;
            }
            else if (item.compare("median") == 0) {
                index = NO_TEAMS / 2;
                cout << field << "\n";
                cout << footballSeason[chooseYear].teams[index].fourth_att;
            }
        }
        else if(field.compare("fourth_pct") == 0) {
            if (item.compare("max") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp < footballSeason[chooseYear].teams[loc].fourth_pct) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].fourth_pct;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].fourth_pct << "\t" << footballSeason[chooseYear].teams[index].fourth_pct;
            }
            else if (item.compare("min") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp > footballSeason[chooseYear].teams[loc].fourth_pct) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].fourth_pct;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].fourth_pct << "\t" << footballSeason[chooseYear].teams[index].fourth_pct;
            }
            else if (item.compare("average") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++)
                    temp = temp + footballSeason[chooseYear].teams[loc].fourth_pct;
                temp = temp / NO_TEAMS;
                cout << field << "\n";
                cout << temp;
            }
            else if (item.compare("median") == 0) {
                index = NO_TEAMS / 2;
                cout << field << "\n";
                cout << footballSeason[chooseYear].teams[index].fourth_pct;
            }
        }
        else if(field.compare("penalties") == 0) {
            if (item.compare("max") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp < footballSeason[chooseYear].teams[loc].penalties) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].penalties;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].penalties << "\t" << footballSeason[chooseYear].teams[index].penalties;
            }
            else if (item.compare("min") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp > footballSeason[chooseYear].teams[loc].penalties){
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].penalties;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].penalties << "\t" << footballSeason[chooseYear].teams[index].penalties;
            }
            else if (item.compare("average") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++)
                    temp = temp + footballSeason[chooseYear].teams[loc].penalties;
                temp = temp / NO_TEAMS;
                cout << field << "\n";
                cout << temp;
            }
            else if (item.compare("median") == 0) {
                index = NO_TEAMS / 2;
                cout << field << "\n";
                cout << footballSeason[chooseYear].teams[index].penalties;
            }
        }
        else if(field.compare("pen_yds") == 0) {
            if (item.compare("max") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp < footballSeason[chooseYear].teams[loc].pen_yds) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].pen_yds;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].pen_yds << "\t" << footballSeason[chooseYear].teams[index].pen_yds;
            }
            else if (item.compare("min") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp > footballSeason[chooseYear].teams[loc].pen_yds) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].pen_yds;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].pen_yds << "\t" << footballSeason[chooseYear].teams[index].pen_yds;
            }
            else if (item.compare("average") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++)
                    temp = temp + footballSeason[chooseYear].teams[loc].pen_yds;
                temp = temp / NO_TEAMS;
                cout << field << "\n";
                cout << temp;
            }
            else if (item.compare("median") == 0) {
                index = NO_TEAMS / 2;
                cout << field << "\n";
                cout << footballSeason[chooseYear].teams[index].pen_yds;
            }
        }
        else if(field.compare("fum") == 0) {
            if (item.compare("max") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp < footballSeason[chooseYear].teams[loc].fum) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].fum;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].fum << "\t" << footballSeason[chooseYear].teams[index].fum;
            }
            else if (item.compare("min") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp > footballSeason[chooseYear].teams[loc].fum) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].fum;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].fum << "\t" << footballSeason[chooseYear].teams[index].fum;
            }
            else if (item.compare("average") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++)
                    temp = temp + footballSeason[chooseYear].teams[loc].fum;
                temp = temp / NO_TEAMS;
                cout << field << "\n";
                cout << temp;
            }
            else if (item.compare("median") == 0) {
                index = NO_TEAMS / 2;
                cout << field << "\n";
                cout << footballSeason[chooseYear].teams[index].fum;
            }
        }
        else if(field.compare("lost") == 0) {
            if (item.compare("max") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp < footballSeason[chooseYear].teams[loc].lost) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].lost;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].lost << "\t" << footballSeason[chooseYear].teams[index].lost;
            }
            else if (item.compare("min") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp > footballSeason[chooseYear].teams[loc].lost) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].lost;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].lost << "\t" << footballSeason[chooseYear].teams[index].lost;
            }
            else if (item.compare("average") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++)
                    temp = temp + footballSeason[chooseYear].teams[loc].lost;
                temp = temp / NO_TEAMS;
                cout << field << "\n";
                cout << temp;
            }
            else if (item.compare("median") == 0) {
                index = NO_TEAMS / 2;
                cout << field << "\n";
                cout << footballSeason[chooseYear].teams[index].lost;
            }
        }
        else if(field.compare("to") == 0) {
            if (item.compare("max") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp < footballSeason[chooseYear].teams[loc].to) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].to;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].to << "\t" << footballSeason[chooseYear].teams[index].to;
            }
            else if (item.compare("min") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++) {
                    if (temp > footballSeason[chooseYear].teams[loc].to) {
                        index = loc;
                        temp = footballSeason[chooseYear].teams[loc].to;
                    }
                }
                cout << "Team\n" << field;
                for(loc = 0; loc < NO_TEAMS; loc++)
                    cout << footballSeason[chooseYear].teams[index].to << "\t" << footballSeason[chooseYear].teams[index].to;
            }
            else if (item.compare("average") == 0) {
                for (loc = 0; loc < NO_TEAMS; loc++)
                    temp = temp + footballSeason[chooseYear].teams[loc].to;
                temp = temp / NO_TEAMS;
                cout << field << "\n";
                cout << temp;
            }
            else if (item.compare("median") == 0) {
                index = NO_TEAMS / 2;
                cout << field << "\n";
                cout << footballSeason[chooseYear].teams[index].to;
            }
        }
    }
}

void bSortRange(int startYear, int endYear, string field, string order){
    int locYear, loc, temp;
    int swap = 0;
    int size = (endYear - startYear) * NO_TEAMS;
    float swapf = 0;

    sortInt intTeams[size];
    sortFloat floatTeams[size];

    if (checkYear(startYear) && checkYear(endYear) && checkField(field) && checkOrder(order)){
        if(field.compare("games") == 0) {
            for(locYear = selectYear(startYear); startYear <= endYear; startYear++)
                for(loc = 0; loc < NO_TEAMS; loc++) {
                    intTeams[loc].year = footballSeason[locYear].year;
                    strncpy(intTeams[loc].team_name, footballSeason[locYear].teams[loc].team_name, sizeof(footballSeason[locYear].teams[loc].team_name));
                    intTeams[loc].stat = footballSeason[locYear].teams[loc].games;
                }
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat > intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat < intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            printRangeInt(intTeams, field);
        }
        else if(field.compare("pts_per_game") == 0) {
            for(locYear = selectYear(startYear); startYear <= endYear; startYear++)
                for(loc = 0; loc < NO_TEAMS; loc++) {
                    floatTeams[loc].year = footballSeason[locYear].year;
                    strncpy(floatTeams[loc].team_name, footballSeason[locYear].teams[loc].team_name, sizeof(footballSeason[locYear].teams[loc].team_name));
                    floatTeams[loc].stat = footballSeason[locYear].teams[loc].pts_per_game;
                }
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (floatTeams[loc].stat > floatTeams[loc + 1].stat) {
                            swapf = floatTeams[loc].stat;
                            floatTeams[loc].stat = floatTeams[loc + 1].stat;
                            floatTeams[loc + 1].stat = swapf;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (floatTeams[loc].stat < floatTeams[loc + 1].stat) {
                            swapf = floatTeams[loc].stat;
                            floatTeams[loc].stat = floatTeams[loc + 1].stat;
                            floatTeams[loc + 1].stat = swapf;
                        }
                    }
                }
            }
            printRangeFloat(floatTeams, field);
        }
        else if(field.compare("total_points") == 0) {
            for(locYear = selectYear(startYear); startYear <= endYear; startYear++)
                for(loc = 0; loc < NO_TEAMS; loc++) {
                    intTeams[loc].year = footballSeason[locYear].year;
                    strncpy(intTeams[loc].team_name, footballSeason[locYear].teams[loc].team_name, sizeof(footballSeason[locYear].teams[loc].team_name));
                    intTeams[loc].stat = footballSeason[locYear].teams[loc].total_points;
                }
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat > intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat < intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            printRangeInt(intTeams, field);
        }
        else if(field.compare("scrimmage_plays") == 0) {
            for(locYear = selectYear(startYear); startYear <= endYear; startYear++)
                for(loc = 0; loc < NO_TEAMS; loc++) {
                    intTeams[loc].year = footballSeason[locYear].year;
                    strncpy(intTeams[loc].team_name, footballSeason[locYear].teams[loc].team_name, sizeof(footballSeason[locYear].teams[loc].team_name));
                    intTeams[loc].stat = footballSeason[locYear].teams[loc].scrimmage_plays;
                }
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat > intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat < intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            printRangeInt(intTeams, field);
        }
        else if(field.compare("yds_per_game") == 0) {
            for(locYear = selectYear(startYear); startYear <= endYear; startYear++)
                for(loc = 0; loc < NO_TEAMS; loc++) {
                    floatTeams[loc].year = footballSeason[locYear].year;
                    strncpy(floatTeams[loc].team_name, footballSeason[locYear].teams[loc].team_name, sizeof(footballSeason[locYear].teams[loc].team_name));
                    floatTeams[loc].stat = footballSeason[locYear].teams[loc].yds_per_game;
                }
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (floatTeams[loc].stat > floatTeams[loc + 1].stat) {
                            swapf = floatTeams[loc].stat;
                            floatTeams[loc].stat = floatTeams[loc + 1].stat;
                            floatTeams[loc + 1].stat = swapf;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (floatTeams[loc].stat < floatTeams[loc + 1].stat) {
                            swapf = floatTeams[loc].stat;
                            floatTeams[loc].stat = floatTeams[loc + 1].stat;
                            floatTeams[loc + 1].stat = swapf;
                        }
                    }
                }
            }
            printRangeFloat(floatTeams, field);
        }
        else if(field.compare("yds_per_play") == 0) {
            for(locYear = selectYear(startYear); startYear <= endYear; startYear++)
                for(loc = 0; loc < NO_TEAMS; loc++) {
                    floatTeams[loc].year = footballSeason[locYear].year;
                    strncpy(floatTeams[loc].team_name, footballSeason[locYear].teams[loc].team_name, sizeof(footballSeason[locYear].teams[loc].team_name));
                    floatTeams[loc].stat = footballSeason[locYear].teams[loc].yds_per_play;
                }
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (floatTeams[loc].stat > floatTeams[loc + 1].stat) {
                            swapf = intTeams[loc].stat;
                            floatTeams[loc].stat = floatTeams[loc + 1].stat;
                            floatTeams[loc + 1].stat = swapf;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (floatTeams[loc].stat < floatTeams[loc + 1].stat) {
                            swapf = intTeams[loc].stat;
                            floatTeams[loc].stat = floatTeams[loc + 1].stat;
                            floatTeams[loc + 1].stat = swapf;
                        }
                    }
                }
            }
            printRangeFloat(floatTeams, field);
        }
        else if(field.compare("first_per_game") == 0) {
            for(locYear = selectYear(startYear); startYear <= endYear; startYear++)
                for(loc = 0; loc < NO_TEAMS; loc++) {
                    floatTeams[loc].year = footballSeason[locYear].year;
                    strncpy(floatTeams[loc].team_name, footballSeason[locYear].teams[loc].team_name, sizeof(footballSeason[locYear].teams[loc].team_name));
                    floatTeams[loc].stat = footballSeason[locYear].teams[loc].first_per_game;
                }
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (floatTeams[loc].stat > floatTeams[loc + 1].stat) {
                            swapf = intTeams[loc].stat;
                            floatTeams[loc].stat = floatTeams[loc + 1].stat;
                            floatTeams[loc + 1].stat = swapf;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat < intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            printRangeFloat(floatTeams, field);
        }
        else if(field.compare("third_md") == 0) {
            for(locYear = selectYear(startYear); startYear <= endYear; startYear++)
                for(loc = 0; loc < NO_TEAMS; loc++) {
                    intTeams[loc].year = footballSeason[locYear].year;
                    strncpy(intTeams[loc].team_name, footballSeason[locYear].teams[loc].team_name, sizeof(footballSeason[locYear].teams[loc].team_name));
                    intTeams[loc].stat = footballSeason[locYear].teams[loc].third_md;
                }
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat > intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat < intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            printRangeInt(intTeams, field);
        }
        else if(field.compare("thirdr_att") == 0) {
            for(locYear = selectYear(startYear); startYear <= endYear; startYear++)
                for(loc = 0; loc < NO_TEAMS; loc++) {
                    intTeams[loc].year = footballSeason[locYear].year;
                    strncpy(intTeams[loc].team_name, footballSeason[locYear].teams[loc].team_name, sizeof(footballSeason[locYear].teams[loc].team_name));
                    intTeams[loc].stat = footballSeason[locYear].teams[loc].third_att;
                }
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat > intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat < intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            printRangeInt(intTeams, field);
        }
        else if(field.compare("third_pct") == 0) {
            for(locYear = selectYear(startYear); startYear <= endYear; startYear++)
                for(loc = 0; loc < NO_TEAMS; loc++) {
                    intTeams[loc].year = footballSeason[locYear].year;
                    strncpy(intTeams[loc].team_name, footballSeason[locYear].teams[loc].team_name, sizeof(footballSeason[locYear].teams[loc].team_name));
                    intTeams[loc].stat = footballSeason[locYear].teams[loc].third_pct;
                }
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat > intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat < intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            printRangeInt(intTeams, field);
        }
        else if(field.compare("fourth_md") == 0) {
            for(locYear = selectYear(startYear); startYear <= endYear; startYear++)
                for(loc = 0; loc < NO_TEAMS; loc++) {
                    intTeams[loc].year = footballSeason[locYear].year;
                    strncpy(intTeams[loc].team_name, footballSeason[locYear].teams[loc].team_name, sizeof(footballSeason[locYear].teams[loc].team_name));
                    intTeams[loc].stat = footballSeason[locYear].teams[loc].fourth_md;
                }
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat > intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat < intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            printRangeInt(intTeams, field);
        }
        else if(field.compare("fourth_att") == 0) {
            for(locYear = selectYear(startYear); startYear <= endYear; startYear++)
                for(loc = 0; loc < NO_TEAMS; loc++) {
                    intTeams[loc].year = footballSeason[locYear].year;
                    strncpy(intTeams[loc].team_name, footballSeason[locYear].teams[loc].team_name, sizeof(footballSeason[locYear].teams[loc].team_name));
                    intTeams[loc].stat = footballSeason[locYear].teams[loc].fourth_att;
                }
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat > intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat < intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            printRangeInt(intTeams, field);
        }
        if(field.compare("fourth_pct") == 0) {
            for(locYear = selectYear(startYear); startYear <= endYear; startYear++)
                for(loc = 0; loc < NO_TEAMS; loc++) {
                    intTeams[loc].year = footballSeason[locYear].year;
                    strncpy(intTeams[loc].team_name, footballSeason[locYear].teams[loc].team_name, sizeof(footballSeason[locYear].teams[loc].team_name));
                    intTeams[loc].stat = footballSeason[locYear].teams[loc].fourth_pct;
                }
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat > intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat < intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            printRangeInt(intTeams, field);
        }
        else if(field.compare("penalties") == 0) {
            for(locYear = selectYear(startYear); startYear <= endYear; startYear++)
                for(loc = 0; loc < NO_TEAMS; loc++) {
                    intTeams[loc].year = footballSeason[locYear].year;
                    strncpy(intTeams[loc].team_name, footballSeason[locYear].teams[loc].team_name, sizeof(footballSeason[locYear].teams[loc].team_name));
                    intTeams[loc].stat = footballSeason[locYear].teams[loc].penalties;
                }
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat > intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat < intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            printRangeInt(intTeams, field);
        }
        else if(field.compare("pen_yds") == 0) {
            for(locYear = selectYear(startYear); startYear <= endYear; startYear++)
                for(loc = 0; loc < NO_TEAMS; loc++) {
                    intTeams[loc].year = footballSeason[locYear].year;
                    strncpy(intTeams[loc].team_name, footballSeason[locYear].teams[loc].team_name, sizeof(footballSeason[locYear].teams[loc].team_name));
                    intTeams[loc].stat = footballSeason[locYear].teams[loc].pen_yds;
                }
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat > intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat < intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            printRangeInt(intTeams, field);
        }
        else if(field.compare("fum") == 0) {
            for(locYear = selectYear(startYear); startYear <= endYear; startYear++)
                for(loc = 0; loc < NO_TEAMS; loc++) {
                    intTeams[loc].year = footballSeason[locYear].year;
                    strncpy(intTeams[loc].team_name, footballSeason[locYear].teams[loc].team_name, sizeof(footballSeason[locYear].teams[loc].team_name));
                    intTeams[loc].stat = footballSeason[locYear].teams[loc].fum;
                }
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat > intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat < intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            printRangeInt(intTeams, field);
        }
        else if(field.compare("lost") == 0) {
            for(locYear = selectYear(startYear); startYear <= endYear; startYear++)
                for(loc = 0; loc < NO_TEAMS; loc++) {
                    intTeams[loc].year = footballSeason[locYear].year;
                    strncpy(intTeams[loc].team_name, footballSeason[locYear].teams[loc].team_name, sizeof(footballSeason[locYear].teams[loc].team_name));
                    intTeams[loc].stat = footballSeason[locYear].teams[loc].lost;
                }
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat > intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat < intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            printRangeInt(intTeams, field);
        }
        else if(field.compare("to") == 0) {
            for(locYear = selectYear(startYear); startYear <= endYear; startYear++)
                for(loc = 0; loc < NO_TEAMS; loc++) {
                    intTeams[loc].year = footballSeason[locYear].year;
                    strncpy(intTeams[loc].team_name, footballSeason[locYear].teams[loc].team_name, sizeof(footballSeason[locYear].teams[loc].team_name));
                    intTeams[loc].stat = footballSeason[locYear].teams[loc].to;
                }
            if (order == "incr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat > intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            else if (order == "decr") {
                for (temp = 0; temp < NO_TEAMS - 1; temp++) {
                    for (loc = 0; loc < NO_TEAMS - temp - 1; loc++) {
                        if (intTeams[loc].stat < intTeams[loc + 1].stat) {
                            swap = intTeams[loc].stat;
                            intTeams[loc].stat = intTeams[loc + 1].stat;
                            intTeams[loc + 1].stat = swap;
                        }
                    }
                }
            }
            printRangeInt(intTeams, field);
        }
    }
}

bool checkYear(int year){
    int temp = 0;

    while(temp <= counter){
        if(year == footballSeason[temp].year)
            return true;
        else
            temp++;
    }
    return false;
}

bool checkField(string field){
    if(field.compare("team_name") == 0 || field.compare("games") == 0 || field.compare("pts_per_game") == 0 || field.compare("total_points") == 0
       || field.compare("scrimmage_plays") == 0 || field.compare("yds_per_game") == 0 || field.compare("yds_per_play") == 0
       || field.compare("first_per_game") == 0 || field.compare("third_md") == 0 || field.compare("third_att") == 0
       || field.compare("third_pct") == 0 || field.compare("fourth_md") == 0 || field.compare("fourth_att") == 0
       || field.compare("fourth_pct") == 0 || field.compare("penalties") == 0 || field.compare("pen_yds") == 0
       || field.compare("top_per_game") == 0 || field.compare("fum") == 0 || field.compare("lost") == 0
       || field.compare("to") == 0)
        return true;
    else
        return false;
}

bool checkOrder(string order){
    if(order.compare("incr") == 0 || order.compare("decr") == 0)
        return true;
    else
        false;
}

bool checkItem(string item){
    if(item.compare("max") == 0 || item.compare("min") == 0 || item.compare("average") == 0 || item.compare("median") == 0)
        return true;
    else
        return false;
}

int selectYear(int year){
    int loc = 0;

    while(loc <= counter){
        if(footballSeason[loc].year == year)
            return loc;
        else
            loc++;
    }
    return -1;
}

void printList(int year, string field, string order){
    int index;
    int chooseYear = selectYear(year);

    bSort(year, field, order);

    if(checkYear(year) && checkField(field) && checkOrder(order)){
        cout << "Team\n" << field;
        if(field.compare("games") == 0) {
            for (index = 0; index < NO_TEAMS; index++)
                cout << footballSeason[chooseYear].teams[index].games << "\t" << footballSeason[chooseYear].teams[index].games;
        }
        else if(field.compare("pts_per_game") == 0) {
            for (index = 0; index < NO_TEAMS; index++)
                cout << footballSeason[chooseYear].teams[index].pts_per_game << "\t" << footballSeason[chooseYear].teams[index].pts_per_game;
        }
        else if(field.compare("total_points") == 0) {
            for (index = 0; index < NO_TEAMS; index++)
                cout << footballSeason[chooseYear].teams[index].total_points << "\t" << footballSeason[chooseYear].teams[index].total_points;
        }
        else if(field.compare("scrimmage_plays") == 0) {
            for (index = 0; index < NO_TEAMS; index++)
                cout << footballSeason[chooseYear].teams[index].scrimmage_plays << "\t" << footballSeason[chooseYear].teams[index].scrimmage_plays;
        }
        else if(field.compare("yds_per_game") == 0) {
            for (index = 0; index < NO_TEAMS; index++)
                cout << footballSeason[chooseYear].teams[index].yds_per_game << "\t" << footballSeason[chooseYear].teams[index].yds_per_game;
        }
        else if(field.compare("yds_per_play") == 0) {
            for (index = 0; index < NO_TEAMS; index++)
                cout << footballSeason[chooseYear].teams[index].yds_per_play << "\t" << footballSeason[chooseYear].teams[index].yds_per_play;
        }
        else if(field.compare("first_per_game") == 0) {
            for (index = 0; index < NO_TEAMS; index++)
                cout << footballSeason[chooseYear].teams[index].first_per_game << "\t" << footballSeason[chooseYear].teams[index].first_per_game;
        }
        else if(field.compare("third_md") == 0) {
            for (index = 0; index < NO_TEAMS; index++)
                cout << footballSeason[chooseYear].teams[index].third_md << "\t" << footballSeason[chooseYear].teams[index].third_md;
        }
        else if(field.compare("third_att") == 0) {
            for (index = 0; index < NO_TEAMS; index++)
                cout << footballSeason[chooseYear].teams[index].third_att << "\t" << footballSeason[chooseYear].teams[index].third_att;
        }
        else if(field.compare("third_pct") == 0) {
            for (index = 0; index < NO_TEAMS; index++)
                cout << footballSeason[chooseYear].teams[index].third_pct << "\t" << footballSeason[chooseYear].teams[index].third_pct;
        }
        else if(field.compare("fourth_md") == 0) {
            for (index = 0; index < NO_TEAMS; index++)
                cout << footballSeason[chooseYear].teams[index].fourth_md << "\t" << footballSeason[chooseYear].teams[index].fourth_md;
        }
        else if(field.compare("fourth_att") == 0) {
            for (index = 0; index < NO_TEAMS; index++)
                cout << footballSeason[chooseYear].teams[index].fourth_att << "\t" << footballSeason[chooseYear].teams[index].fourth_att;
        }
        else if(field.compare("fourth_pct") == 0) {
            for (index = 0; index < NO_TEAMS; index++)
                cout << footballSeason[chooseYear].teams[index].fourth_pct << "\t" << footballSeason[chooseYear].teams[index].fourth_pct;
        }
        else if(field.compare("penalties") == 0) {
            for (index = 0; index < NO_TEAMS; index++)
                cout << footballSeason[chooseYear].teams[index].penalties << "\t" << footballSeason[chooseYear].teams[index].penalties;
        }
        else if(field.compare("pen_yds") == 0) {
            for (index = 0; index < NO_TEAMS; index++)
                cout << footballSeason[chooseYear].teams[index].pen_yds << "\t" << footballSeason[chooseYear].teams[index].pen_yds;
        }
        else if(field.compare("fum") == 0) {
            for (index = 0; index < NO_TEAMS; index++)
                cout << footballSeason[chooseYear].teams[index].fum << "\t" << footballSeason[chooseYear].teams[index].fum;
        }
        else if(field.compare("lost") == 0) {
            for (index = 0; index < NO_TEAMS; index++)
                cout << footballSeason[chooseYear].teams[index].lost << "\t" << footballSeason[chooseYear].teams[index].lost;
        }
        else if(field.compare("to") == 0) {
            for (index = 0; index < NO_TEAMS; index++)
                cout << footballSeason[chooseYear].teams[index].to << "\t" << footballSeason[chooseYear].teams[index].to;
        }
    }
}

void printRangeInt(sortInt* teams, string field){
    int index;

    cout << "Team\t" << field << "\tYear\t";
    for (index = 0; index < sizeof(teams); index++)
        cout << teams[index].team_name << "\t" << teams[index].stat << "\t" << teams[index].year;
}

void printRangeFloat(sortFloat* teams, string field){
    int index;

    cout << "Team\t" << field << "\tYear\t";
    for (index = 0; index < sizeof(teams); index++)
        cout << teams[index].team_name << "\t" << teams[index].stat << "\t" << teams[index].year;
}

void flush(){
    int c;
    do{
        c = getchar();
    }while (c != '\n' && c != EOF);
}