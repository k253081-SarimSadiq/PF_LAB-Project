#include <stdio.h>
#include <string.h>

// ---------------------------
// STRUCTURES
// ---------------------------
struct Voter {
    char name[50];
    char cnic[20];
    int age;
    char votedFor[50];
};

struct Candidate {
    char name[50];
    int votes;
};

// ---------------------------
// GLOBAL VARIABLES
// ---------------------------
struct Candidate candidates[20];
int candidateCount = 5; 

// ---------------------------
// FUNCTION: Check CNIC Format
// ---------------------------
int checkCNIC(char cnic[]) {
	int i;
    if (strlen(cnic) != 15) return 0;

    for ( i = 0; i < 15; i++) {
        if (i == 5 || i == 13) {
            if (cnic[i] != '-') return 0;
        } else {
            if (cnic[i] < '0' || cnic[i] > '9') return 0;
        }
    }
    return 1;
}

// ---------------------------
// FUNCTION: ADMIN LOGIN
// ---------------------------
int adminLogin() {
    char id[20], pass[20];

    printf("\n--- ADMIN LOGIN ---\n");
    printf("Enter Admin ID: ");
    scanf("%s", id);

    printf("Enter Password: ");
    scanf("%s", pass);

    if ((strcmp(id, "253043") == 0 || strcmp(id, "253081") == 0)
        && strcmp(pass, "missizzah") == 0) 
    {
        printf("Admin Login Successful!\n");
        return 1;
    }

    printf("Invalid Admin Credentials!\n");
    return 0;
}

// ---------------------------
// FUNCTION: ADD A CANDIDATE (ADMIN ONLY)
// ---------------------------
void addCandidate() {
    if (!adminLogin()) return;

    if (candidateCount >= 20) {
        printf("Maximum candidate limit reached.\n");
        return;
    }

    printf("\nEnter name of new candidate: ");
    scanf(" %[^\n]s", candidates[candidateCount].name);

    candidates[candidateCount].votes = 0;
    candidateCount++;

    printf("Candidate added successfully!\n");
}

// ---------------------------
// FUNCTION: SHOW RESULTS (ADMIN ONLY)
// ---------------------------
void showResults() {
	int i;
    if (!adminLogin()) return;

    printf("\n--- FINAL VOTING RESULTS ---\n");
    for ( i = 0; i < candidateCount; i++) {
        printf("%s: %d votes\n", candidates[i].name, candidates[i].votes);
    }
}

// ---------------------------
// MAIN PROGRAM
// ---------------------------
int main() {

    
    strcpy(candidates[0].name, "Imran Khan");
    strcpy(candidates[1].name, "Shahbaz Shareef");
    strcpy(candidates[2].name, "Fazl ur Rehman");
    strcpy(candidates[3].name, "Saad Rizvi");
    strcpy(candidates[4].name, "Bilawal Bhutto");
    int i;
    for ( i = 0; i < candidateCount; i++)
        candidates[i].votes = 0;

    struct Voter voters[100];
    char usedCNICs[100][20];
    int totalVoters = 0;
    int choice;
    char again;

    FILE *file = fopen("voters.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    do {
        printf("\n--- ELECTION MENU ---\n");
        printf("1. Cast Vote\n");
        printf("2. Add Candidate (Admin)\n");
        printf("3. Show Results (Admin)\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {

            struct Voter v;
            int alreadyUsed = 0;

            printf("\nEnter your name: ");
            scanf(" %[^\n]s", v.name);

            printf("Enter CNIC (xxxxx-xxxxxxx-x): ");
            scanf("%s", v.cnic);

            // Check format
            if (!checkCNIC(v.cnic)) {
                printf("Invalid CNIC format!\n");
                continue;
            }

            // Duplicate CNIC check
            int i;
            for ( i = 0; i < totalVoters; i++) {
                if (strcmp(usedCNICs[i], v.cnic) == 0) {
                    alreadyUsed = 1;
                    break;
                }
            }
            if (alreadyUsed) {
                printf("This CNIC has already voted!\n");
                continue;
            }

            printf("Enter your age: ");
            scanf("%d", &v.age);

            if (v.age < 18) {
                printf("Under 18. Cannot vote.\n");
                continue;
            }

            printf("\n--- Candidates ---\n");
            
            for ( i = 0; i < candidateCount; i++) {
                printf("%d. %s\n", i + 1, candidates[i].name);
            }

            printf("Your choice: ");
            scanf("%d", &choice);

            if (choice < 1 || choice > candidateCount) {
                printf("Invalid choice.\n");
                continue;
            }

            strcpy(v.votedFor, candidates[choice - 1].name);
            candidates[choice - 1].votes++;

            strcpy(usedCNICs[totalVoters], v.cnic);
            voters[totalVoters++] = v;

            fprintf(file, "Name: %s\n", v.name);
            fprintf(file, "CNIC: %s\n", v.cnic);
            fprintf(file, "Age: %d\n", v.age);
            fprintf(file, "Voted For: %s\n", v.votedFor);
            fprintf(file, "-----------------------------\n");

            printf("Vote Recorded Successfully!\n");
        }

        else if (choice == 2) {
            addCandidate();
        }

        else if (choice == 3) {
            showResults();
        }

        else if (choice == 4) {
            break;
        }

        else {
            printf("Invalid option!\n");
        }

        printf("\nReturn to menu? (Y/N): ");
        scanf(" %c", &again);

    } while (again == 'Y' || again == 'y');

    fclose(file);

    return 0;
}

