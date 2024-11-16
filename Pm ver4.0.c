#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Player {
    int jerseyNumber;
    char name[30];
    int runs;
    int wickets;
    int matchesPlayed;
} Player;

int size = 2, count = 0;

void usersChoice(Player**);
void addPlayer(Player**);
void displayPlayers(Player*);
int searchByJn(Player*, int);
int searchByName(Player*, char*);
void displaySinglePlayer(Player*, int*);
void updatePlayer(Player*);
void removePlayer(Player*);
Player* copyPlayer(Player*);
void sortByRuns(Player*);
void sortByWickets(Player*);

void usersChoice(Player** plr) {
    int choice, sch, jn, index, sortch;
    Player* newPlr;
    char sname[30];
    do {
        printf("+----------------------------------+\n");
        printf("|             Content              |\n");
        printf("|----------------------------------|\n");
		printf("|  1. To Add Players               |\n");
		printf("|  2. To Display Players           |\n");
		printf("|  3. To Search Player             |\n");
		printf("|  4. To Update Player             |\n");
		printf("|  5. To Display Sorted Players    |\n");
		printf("|  6. To Remove Player             |\n");
		printf("|  7. To Exit                      |\n");
        printf("+----------------------------------+\n\n");

        printf("Enter your choice: \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPlayer(plr);
                break;

            case 2:
                printf("Players List: \n");
                displayPlayers(*plr);
                break;

            case 3:
               	printf("+---------------------------------------+ \n");
                printf("|   How do you want to search player?   | \n");
                printf("|---------------------------------------| \n");
                printf("| 1. To search player by Jersey Number  | \n");
                printf("| 2. To search player by Name           | \n");
                printf("+---------------------------------------+ \n\n");
                
                scanf("%d", &sch);
                if (sch == 1) {
                    printf("Enter jersey number: \n");
                    scanf("%d", &jn);
                    index = searchByJn(*plr, jn);
                    if (index != -1) {
                        displaySinglePlayer(*plr, &index);
                    } else {
                        printf("Player not found \n");
                    }
                } else if (sch == 2) {
                    getchar();
                    printf("Enter the name of the player: \n");
                    gets(sname);
                    index = searchByName(*plr, sname);
                    if (index != -1) {
                        displaySinglePlayer(*plr, &index);
                    } else {
                        printf("Player not found \n");
                    }
                } else {
                    printf("Invalid choice! \n");
                }
                break;

            case 4:
                updatePlayer(*plr);
                break;

            case 5:
                printf("+--------------------------------------+ \n");
                printf("|   How do you want to sort players?   | \n");
                printf("|--------------------------------------| \n");
                printf("| 1. To sort the players by runs       | \n");
                printf("| 2. To sort the players by wickets    | \n");
                printf("+--------------------------------------+ \n\n");
                printf("Enter your choice: \n");
                
                scanf("%d", &sortch);
                newPlr = copyPlayer(*plr);
                if (sortch == 1) {
                    sortByRuns(newPlr);
                } else {
                    sortByWickets(newPlr);
                }
                free(newPlr);
                break;

            case 6:
                removePlayer(*plr);
                break;

            case 7:
                printf("Exiting...!\n");
                break;

            default:
                printf("Invalid choice \n");
                break;
        }
    } while (choice != 7);
}

void addPlayer(Player** plr) {
    int n;
    printf("Enter number of players you want to add: \n");
    scanf("%d", &n);

    if ((size - count) < n) {
        printf("Array is now full, increasing by %d \n", n - (size - count));
        Player* temp = (Player*)realloc(*plr, sizeof(Player) * (size + (n - (size - count))));
        if (temp == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }
        *plr = temp;
        size = size + (n - (size - count));
    }

    for (int i = 0; i < n; i++) {
        printf("Enter the jersey number: \n");
        scanf("%d", &(*plr)[count].jerseyNumber);

        fflush(stdin);
        printf("Enter name of the player: \n");
        gets((*plr)[count].name);

        printf("Enter number of runs: \n");
        scanf("%d", &(*plr)[count].runs);

        printf("Enter number of wickets: \n");
        scanf("%d", &(*plr)[count].wickets);

        printf("Enter number of matches played: \n");
        scanf("%d", &(*plr)[count].matchesPlayed);
        printf("\n Player Added! \n\n");

        count++;
    }
}

void displayPlayers(Player* plr) {
    printf("+------------+------------------------------+------------+------------+-------------------+\n");
    printf("| Jersey No. | Name                         | Runs       | Wickets    | Matches Played    |\n");
    printf("+------------+------------------------------+------------+------------+-------------------+\n");
    
    for (int i = 0; i < count; i++) {
        printf("| %-10d | %-28s | %-10d | %-10d | %-17d |\n", 
               plr[i].jerseyNumber, plr[i].name, plr[i].runs, plr[i].wickets, plr[i].matchesPlayed);
    }
    
    printf("+------------+------------------------------+------------+------------+-------------------+\n");
}

int searchByJn(Player* plr, int jn) {
    for (int i = 0; i < count; i++) {
        if (jn == plr[i].jerseyNumber) {
            return i;
        }
    }
    return -1;
}

int searchByName(Player* plr, char* sname) {
    for (int i = 0; i < count; i++) {
        if (strcmp(plr[i].name, sname) == 0) {
            return i;
        }
    }
    return -1;
}

void displaySinglePlayer(Player* plr, int* index) {
    printf("+------------+------------------------------+------------+------------+-------------------+\n");
    printf("| Jersey No. | Name                         | Runs       | Wickets    | Matches Played    |\n");
    printf("+------------+------------------------------+------------+------------+-------------------+\n");
    printf("| %-10d | %-28s | %-10d | %-10d | %-17d |\n", 
           plr[*index].jerseyNumber, plr[*index].name, plr[*index].runs, plr[*index].wickets, plr[*index].matchesPlayed);
    printf("+------------+------------------------------+------------+------------+-------------------+\n");
}

void updatePlayer(Player* plr) {
    int jn, uch, uruns, uwickets, ump;
    printf("Enter the jersey number: \n");
    scanf("%d", &jn);
    int index = searchByJn(plr, jn);
    if (index == -1) {
        printf("Player not found\n");
    } else {
        printf("+-------------------------------------------+ \n");
        printf("|      what do you want to update?          | \n");
        printf("|-------------------------------------------| \n");
        printf("| 1. To update runs                         | \n");
        printf("| 2. To update wickets                      | \n");
        printf("| 3. To update number of matches played     | \n");
        printf("+-------------------------------------------+ \n\n");
        
        printf("Enter your choice: \n");
        scanf("%d", &uch);
        switch (uch) {
            case 1:
                printf("Old runs: %d \n", plr[index].runs);
                printf("Enter the runs to update: \n");
                scanf("%d", &uruns);
                plr[index].runs = uruns;
                displaySinglePlayer(plr, &index);
                break;

            case 2:
                printf("Old wickets: %d \n", plr[index].wickets);
                printf("Enter the wickets to update: \n");
                scanf("%d", &uwickets);
                plr[index].wickets = uwickets;
                displaySinglePlayer(plr, &index);
                break;
            case 3:
                printf("Old matches played: %d \n", plr[index].matchesPlayed);
                printf("Enter matches played to update: \n");
                scanf("%d", &ump);
                plr[index].matchesPlayed = ump;
                displaySinglePlayer(plr, &index);
                break;
        }
    }
}

Player* copyPlayer(Player* plr) {
    Player* newPlr = (Player*)malloc(sizeof(Player) * count);
    for (int i = 0; i < count; i++) {
        newPlr[i] = plr[i]; // Copy entire struct
    }
    return newPlr;
}

void sortByRuns(Player* newPlr) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (newPlr[i].runs < newPlr[j].runs) {
                Player temp = newPlr[i];
                newPlr[i] = newPlr[j];
                newPlr[j] = temp;
            }
        }
    }
    printf("Players sorted by Runs:\n");
    displayPlayers(newPlr);
}

void sortByWickets(Player* newPlr) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (newPlr[i].wickets < newPlr[j].wickets) {
                Player temp = newPlr[i];
                newPlr[i] = newPlr[j];
                newPlr[j] = temp;
            }
        }
    }
    printf("Players sorted by Wickets:\n");
    displayPlayers(newPlr);
}

void removePlayer(Player* plr) {
    int jn, index;
    printf("Enter the jersey number: \n");
    scanf("%d", &jn);
    index = searchByJn(plr, jn);
    if (index == -1) {
        printf("Player not found\n");
    } else {
        for (int i = index; i < count - 1; i++) {
            plr[i] = plr[i + 1];
        }
        count--;
        printf("\n Player Removed! \n\n");
        displayPlayers(plr);
    }
}

int main() {
    Player* plr = (Player*)malloc(sizeof(Player) * size);
    usersChoice(&plr);
    free(plr);
    return 0;
}
