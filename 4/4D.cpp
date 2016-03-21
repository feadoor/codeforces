#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// Types for envelopes and indexed envelopes
typedef pair<int, int> envelope;
typedef pair<envelope, int> envelope_ix;

// The number of envelopes and the size of the card
int n; envelope card;

// Somewhere to store the envelope sizes - each one is stored as a pair
// ((w, h), ix) where (w, h) are the width and height of the envelope, and ix
// is the index of the envelope in the input data
vector<envelope_ix> envelopes;

// Somewhere to store data about the longest chains available using the given
// envelopes. The vector lengths[i] stores the length of the longest chain
// which has envelopes[i] as the largest envelope, and the vector parents[i]
// stores the parent of envelope[i] in one such longest chain.
vector<int> lengths;
vector<int> parents;

/*******************************************************************************
* Read in the envelope sizes from stdin and store them for further processing  *
*******************************************************************************/
void read_data()
{
    // Read in the number of envelopes and the size of the card
    cin >> n >> card.first >> card.second;

    // Read in the sizes of all the envelopes - only store an envelope if the
    // card can fit inside it.
    envelope size;

    for (int i = 0; i < n; ++i)
    {
        cin >> size.first >> size.second;
        if ((size.first > card.first) && (size.second > card.second))
        {
            envelopes.push_back(make_pair(size, i + 1));
        }
    }
}

/*******************************************************************************
* Calculate the lengths of the longest chain using the given envelope sizes.   *
* Sort the envelopes by width, then by height, and for each envelope, the      *
* length of the longest path ending at that envelope is one greater than the   *
* length of the longest path ending at any of its parent envelopes. Find the   *
* best such parent and store it, along with the length of the longest path.    *
* This function returns the length of the longest chain, and also the indices  *
* of the envelopes which comprise the chain.                                   *
*******************************************************************************/
pair<int, vector<int>> best_chain()
{
    // Sort the vector of envelopes
    sort(envelopes.begin(), envelopes.end());

    // Initialise the vectors of lengths and parents
    lengths = vector<int>(envelopes.size(), 0);
    parents = vector<int>(envelopes.size(), 0);

    // Store the best chain so far
    int best_chain_len = 0; int best_chain_parent = -1;

    // Iterate over the envelopes in size order
    for (int i = 0; i < envelopes.size(); ++i)
    {
        // Keep track of the best parent of this envelope so far
        int best_len = 0; int best_parent = -1;

        // Iterate over all possible parents of this envelope looking for the
        // parent with the longest incoming chain
        for (int j = 0; j < i; ++j)
        {
            if ((envelopes[j].first.first < envelopes[i].first.first) &&
                (envelopes[j].first.second < envelopes[i].first.second))
            {
                // This is a possible parent, so update best_len and best_parent
                if (lengths[j] > best_len)
                {
                    best_len = lengths[j];
                    best_parent = j;
                }
            }
        }

        // Store the best length and the best parent
        lengths[i] = best_len + 1;
        parents[i] = best_parent;

        // Check if we have a new best overall chain
        if (lengths[i] > best_chain_len)
        {
            best_chain_len = lengths[i];
            best_chain_parent = i;
        }
    }

    // Calculate the members of the longest chain
    vector<int> chain;
    for (int i = best_chain_parent; i != -1; i = parents[i])
    {
        // Use the original index of the envelope, not the sorted index
        chain.push_back(envelopes[i].second);
    }

    return make_pair(best_chain_len, chain);
}

/*******************************************************************************
* Read input from stdin and output the longest chain                           *
*******************************************************************************/
int main()
{
    // Read in the data
    read_data();

    // Find the longest chain and output it
    pair<int, vector<int>> chain = best_chain();
    cout << chain.first << endl;
    for (auto i = chain.second.rbegin(); i != chain.second.rend(); ++i)
    {
        cout << *i << " ";
    }
    cout << endl;

    return 0;
}
