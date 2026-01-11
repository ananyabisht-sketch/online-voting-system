#include <stdio.h>
#include <string.h>

#define MAX_CANDIDATES 10
#define NAME_LEN 50

/* Candidate structure */
typedef struct {
    char name[NAME_LEN];
    int votes;
} Candidate;

/* Global variables */
Candidate candidates[MAX_CANDIDATES];
int candidateCount;

/* Function declarations */
int readInt(int *num);
void setupCandidates(void);
void castVotes(void);
void displayResults(void);

/* Safe integer input */
int readInt(int *num)
{
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        return 0;
    return sscanf(buffer, "%d", num) == 1;
}

int main()
{
    printf("====================================\n");
    printf("        ONLINE VOTING SYSTEM         \n");
    printf("====================================\n\n");

    setupCandidates();
    castVotes();
    displayResults();

    return 0;
}

/* Setup candidates */
void setupCandidates(void)
{
    while (1) {
        printf("Enter number of candidates (1-%d): ", MAX_CANDIDATES);
        if (readInt(&candidateCount) && candidateCount > 0 && candidateCount <= MAX_CANDIDATES)
            break;
        printf("Invalid input. Try again.\n");
    }

    for (int i = 0; i < candidateCount; i++) {
        printf("Enter name of candidate %d: ", i + 1);
        fgets(candidates[i].name, NAME_LEN, stdin);
        candidates[i].name[strcspn(candidates[i].name, "\n")] = '\0';
        candidates[i].votes = 0;
    }
}

/* Voting process */
void castVotes(void)
{
    int voters, choice;

    while (1) {
        printf("\nEnter number of voters: ");
        if (readInt(&voters) && voters > 0)
            break;
        printf("Invalid input. Try again.\n");
    }

    for (int i = 0; i < voters; i++) {
        printf("\nVoter %d - Cast your vote\n", i + 1);

        for (int j = 0; j < candidateCount; j++) {
            printf("%d) %s\n", j + 1, candidates[j].name);
        }

        while (1) {
            printf("Enter your choice (1-%d): ", candidateCount);
            if (readInt(&choice) && choice >= 1 && choice <= candidateCount) {
                candidates[choice - 1].votes++;
                break;
            }
            printf("Invalid choice. Try again.\n");
        }
    }
}

/* Display results */
void displayResults(void)
{
    int maxVotes = 0;
    int winner = -1;
    int tie = 0;

    printf("\n====================================\n");
    printf("             FINAL RESULTS           \n");
    printf("====================================\n");

    for (int i = 0; i < candidateCount; i++) {
        printf("%s : %d votes\n", candidates[i].name, candidates[i].votes);

        if (candidates[i].votes > maxVotes) {
            maxVotes = candidates[i].votes;
            winner = i;
            tie = 0;
        }
        else if (candidates[i].votes == maxVotes) {
            tie = 1;
        }
    }

    printf("------------------------------------\n");

    if (tie || winner == -1) {
        printf("Result: Tie / No clear winner\n");
    } else {
        printf("Winner: %s with %d votes\n",
               candidates[winner].name,
               candidates[winner].votes);
    }
}