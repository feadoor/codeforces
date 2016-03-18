#include <iostream>
#include <string>
#include <queue>
#include <utility>

using namespace std;

typedef long long ll;

// Somewhere to keep the bracket string that we read in so we can modify it
// in-place to get the answer.
string bracket_seq;

/*******************************************************************************
* Modify the bracket sequence in-place to produce the optimal sequence. Return *
* the cost of the optimal sequence, or -1 if no valid sequence exists.         *
*                                                                              *
* An almost-greedy algorithm can be used. Start by replacing all occurrences   *
* of '?' in the bracket sequence by ')'. Iterate through the sequence left to  *
* right, counting each bracket type, and any time we have a surplus of ')'     *
* brackets, that means we need to replace one of the brackets to its left by   *
* a ')'. The bracket we should replace is the one that increases the overall   *
* cost by the smallest amount.                                                 *
*                                                                              *
* Using a priority queue, this can be implemented in time O(n log n) and       *
* memory O(n)                                                                  *
*******************************************************************************/
ll find_optimal_sequence()
{
    // Keep track of the total cost, and the number of surplus ')' brackets.
    ll cost = 0; int r_brackets = 0;

    // Temporary variables to store costs read in from the input
    ll l_cost, r_cost;

    // Priority queue to keep track of possible '(' replacements. Each entry in
    // the queue is a pair (cost, position) of the replacement.
    priority_queue<pair<int, int>> replacements;

    // Iterate through the bracket sequence
    for (int i = 0; i < bracket_seq.size(); ++i)
    {
        // If this character is already determined, just update the number of
        // brackets seen so far.
        if (bracket_seq[i] == '(')
        {
            --r_brackets;
        }
        else if (bracket_seq[i] == ')')
        {
            ++r_brackets;
        }

        // If this character is a '?', then tentatively replace it with a ')'
        // and push a possible replacement onto the queue
        else
        {
            bracket_seq[i] = ')';
            ++r_brackets;
            cin >> l_cost >> r_cost;
            cost += r_cost;

            // Use the negative cost so that elements are sorted correctly in
            // the queue
            replacements.push(make_pair(r_cost - l_cost, i));
        }

        // Deal with any surplus of ')' brackets
        while (r_brackets > 0)
        {
            // If there are no replacements ready, then the string is invalid
            if (replacements.size() == 0)
            {
                return -1;
            }

            // Use the cheapest replacement
            pair<int, int> replacement = replacements.top(); replacements.pop();
            cost += -(replacement.first);
            bracket_seq[replacement.second] = '(';
            r_brackets -= 2;
        }
    }

    // If we don't have matching brackets, then the string is invalid
    if (r_brackets != 0)
    {
        return -1;
    }
    else
    {
        return cost;
    }
}

/*******************************************************************************
* Read in the bracket sequence from stdin, and output a sequence with minimal  *
* cost, as well as the cost of such a sequence                                 *
*******************************************************************************/
int main()
{
    // Read in the bracket sequence
    cin >> bracket_seq;

    // Find the optimal cost and output the result
    ll best_cost = find_optimal_sequence();
    cout << best_cost << endl;
    if (best_cost != -1)
    {
        cout << bracket_seq << endl;
    }

    return 0;
}