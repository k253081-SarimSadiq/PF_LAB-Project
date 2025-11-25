#include <stdio.h>
#include <string.h>

// Structure to store voter information
struct Voter {
    char name[50];
    char cnic[20];
    int age;
    char votedFor[20];
};

// Function to check  Pakistani CNIC format
int checkCNIC(char cnic[]) {
    int i;

    if (strlen(cnic) != 15)
        return 0;

    for (i = 0; i < 15; i++) {
        if (i == 5 || i == 13) { 
            if (cnic[i] != '-')
                return 0;
        } else {
            if (cnic[i] < '0' || cnic[i] > '9')
                return 0;
        }
    }
    return 1;
}

int main() {

    struct Voter voters[100];      
    char usedCNICs[100][20];       
    int totalVoters = 0;

    int votesA = 0, votesB = 0, votesC = 0;
    int choice;
    char again;

    FILE *file = fopen("voters.txt", "a");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    do {
        struct Voter v;   
        int alreadyUsed = 0;

        printf("\nEnter your name: ");
        scanf(" %[^\n]s", v.name);

        printf("Enter your CNIC (xxxxx-xxxxxxx-x): ");
        scanf("%s", v.cnic);

        // Check CNIC format
        if (!checkCNIC(v.cnic)) {
            printf("Invalid CNIC format! Try again.\n");
            continue;
        }

        // Check for duplicate CNIC
        int i;
        for (i = 0; i < totalVoters; i++) {
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
            printf("You are under 18. Cannot vote.\n");
            continue;
        }

        printf("\nCandidates:\n");
        printf("1. Muhammad Ali (A)\n");
        printf("2. Hamza Khan (B)\n");
        printf("3. Ayesha Ahmed (C)\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            votesA++;
            strcpy(v.votedFor, "Candidate A");
        }
        else if (choice == 2) {
            votesB++;
            strcpy(v.votedFor, "Candidate B");
        }
        else if (choice == 3) {
            votesC++;
            strcpy(v.votedFor, "Candidate C");
        }
        else {
            printf("Invalid choice. Try again.\n");
            continue;
        }

       
        strcpy(usedCNICs[totalVoters], v.cnic);

        
        voters[totalVoters] = v;
        totalVoters++;

        
        fprintf(file, "Name: %s\n", v.name);
        fprintf(file, "CNIC: %s\n", v.cnic);
        fprintf(file, "Age: %d\n", v.age);
        fprintf(file, "Voted For: %s\n", v.votedFor);
        fprintf(file, "-----------------------------\n");

        printf("\nYour vote has been recorded!\n");

        printf("\nDo you want to enter another vote? (Y/N): ");
        scanf(" %c", &again);

    } while (again == 'Y' || again == 'y');

    fclose(file);

    
    printf("\n--- Final Voting Results ---\n");
    printf("Candidate A: %d\n", votesA);
    printf("Candidate B: %d\n", votesB);
    printf("Candidate C: %d\n", votesC);

    return 0;
}

