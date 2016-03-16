#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Vectors to hold the names and scores of the game
vector<string> names;
vector<int> scores;

// Maps to hold running totals as the game progresses and final scores at the
// end of the game
map<string, int> totals;
map<string, int> finals;

/*******************************************************************************
* Read in the names and scores from stdin and save them, ready to play through *
* and determine the winner                                                     *
*******************************************************************************/
void read_scores()
{
    int n; string name; int score;

    // Read in the number of rounds in this game
    cin >> n;

    // Read in each individual round
    for (int i = 0; i < n; ++i)
    {
        cin >> name >> score;
        names.push_back(name);
        scores.push_back(score);
    }
}

/*******************************************************************************
* Play through the game once, storing the final scores in a map                *
*******************************************************************************/
void play_once()
{
    string name; int score;

    for (int i = 0; i < names.size(); ++i)
    {
        // Get the name and score for this round
        name = names[i];
        score = scores[i];

        // Update the total score associated with this name
        if (finals.find(name) == finals.end())
        {
            finals[name] = score;
        }
        else
        {
            finals[name] += score;
        }
    }
}

/*******************************************************************************
* Find the highest total score at the end of the game                          *
*******************************************************************************/
int highest_score()
{
    int best = finals.begin()->second;
    auto iter = finals.begin();

    // Iterate over the final scores to find the maximum
    while (iter != finals.end())
    {
        if (iter->second > best)
        {
            best = iter->second;
        }
        ++iter;
    }

    return best;
}

/*******************************************************************************
* Finds the name of the winner, given that the winning score was the given     *
* value - iterate through the game's running totals, and find the first person *
* who got a score of at least the given amount who also finished on the        *
* final winning score                                                          *
*******************************************************************************/
string winner(int target_score)
{
    string name; int score;

    for (int i = 0; i < names.size(); ++i)
    {
        // Get the name and score for this round
        name = names[i];
        score = scores[i];

        // Update the total score associated with this name
        if (totals.find(name) == totals.end())
        {
            totals[name] = score;
        }
        else
        {
            totals[name] += score;
        }

        // Check if we have found the winner
        if ((totals[name] >= target_score) && (finals[name] == target_score))
        {
            return name;
        }
    }
}

/*******************************************************************************
* Read the game from stdin and determine the winner                            *
*******************************************************************************/
int main()
{
    // Read in the game from stdin
    read_scores();

    // Play through the game once to get the winning score
    play_once();
    int best_score = highest_score();

    // Find and output the winner of the game
    cout << winner(best_score) << endl;
    return 0;
}