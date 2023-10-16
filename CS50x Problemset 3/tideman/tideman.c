#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

// Function prototype for cycle check
bool cycleCheck(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // check if name is in candidate array
    for (int i = 0; i < candidate_count; i++)
    {
        // If name in candidate array, add candidate index to ranks array with rank given by user
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Read out ranks array
    for (int i = 0; i < candidate_count; i++)
    {
        // For last rank in ranks no action
        if (i != candidate_count - 1)
        {
            for (int j = i + 1; j < candidate_count; j++)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Compare pairs and find winner and loser, then add to pairs array
    for (int i = 0; i < candidate_count; i++)
    {
        // j = i + 1 to avoid candidate comparing to
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Iterate through pairs and compare each element
    int swapCounter = -1;
    while (swapCounter != 0)
    {
        swapCounter = 0;
        for (int i = 0; i < pair_count; i++)
        {
            for (int j = i + 1; j < pair_count; j++)
            {
                if (preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner] <
                    preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner])
                {
                    int tempWinner = pairs[i].winner;
                    int tempLoser = pairs[i].loser;
                    pairs[i].winner = pairs[j].winner;
                    pairs[i].loser = pairs[j].loser;
                    pairs[j].winner = tempWinner;
                    pairs[j].loser = tempLoser;
                    swapCounter++;
                }
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // loop through pairs array
    for (int i = 0; i < pair_count; i++)
    {
        // Get winner and loser
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        // Check for cycle

        // No Cycle found
        if (cycleCheck(winner, loser) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            //locked[pairs[i].loser][pairs[i].winner] = false;
        }
        // Cycle found, pair is skipped
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // No true in candidates column
    for (int i = 0; i < candidate_count; i++)
    {
        int trueCounter = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                trueCounter++;
            }
        }
        if (trueCounter == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

// Recursive Function for lock_pairs
bool cycleCheck(int winner, int loser)
{
    // base case cycle found
    if (winner == loser)
    {
        return true;
    }

    // recursive case
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true)
        {
            if (cycleCheck(winner, i) == true)
            {
                return true;
            }
        }
    }
    return false;
}