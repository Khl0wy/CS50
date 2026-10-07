#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
// preferences [0][1] = The first voter, and the second candidate that the voter selected
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    //Default Value
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Loop through the number of candidates
    for (int i = 0; i < candidate_count; i++) {
        // If the keyed-in candidates' name from voters is the same as the candidates' name from command section
        if (strcmp(name, candidates[i].name) == 0) {
            // Set the preferences
            // Search for the candidate by name, then store the candidate's index in
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Loop through the number of voters (Like Round 1, Round 2 etc)
    for (int i = 0; i < voter_count; i++) {
        // Loop through the number of candidates
        for (int j = 0; j < candidate_count; j++) {
            // Get the preferences and store it as the candidate's index
            // j+1 (for human understanding) is the preference of voter i
            int candidate_index = preferences[i][j];
            // Check if that candidate is eliminated
            if (!candidates[candidate_index].eliminated) {
                // Else add votes
                candidates[candidate_index].votes++;
                break;
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{

    // Run through number of candidates
    for (int i = 0; i < candidate_count; i++) {
        // Check if eliminated
        if (!candidates[i].eliminated) {
            // Check whether the candidate's vote is greater than the number of voters (number of voters = total number of votes)
            // More than 50% so divide by 2 (The candidate needs to have more than 50% in order to win)
            if (candidates[i].votes > voter_count / 2) {
                printf ("%s\n", candidates[i].name);
                return true;
            }
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // min is the total number of votes
    int min = voter_count;
    // Loop through the number of candidates
    for (int i = 0; i < candidate_count; i++) {
        // If not eliminated
        if (!candidates[i].eliminated) {
            // If the specific candidate's vote is less than the minimum
            if (candidates[i].votes <= min) {
                min = candidates[i].votes;
            }
        }
    }
        return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Loop through the number of candidates
    for (int i = 0; i < candidate_count; i++) {
        // If not eliminated
        if (!candidates[i].eliminated) {
            // Not tie when the candidate's vote != to the minimum (minimum is like a base line, checking whether everyone is the same)
            if (candidates[i].votes != min) {
                return false;
            }
        }
    }
    // All tied
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Loop through the number of candidates
    for (int i = 0; i < candidate_count; i++) {
        // If the candidate is not eliminated but/and has the same amount of votes as the minimum
        if (!candidates[i].eliminated && candidates[i].votes == min) {
            // Will be eliminated
            candidates[i].eliminated = true;
        }
    }
    return;
}
