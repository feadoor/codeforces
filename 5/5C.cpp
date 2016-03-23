#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <utility>

using namespace std;

// Somewhere to store the string of '(' and ')'. The string is stored in a
// linked list, with each entry in the list being represented by a pair
// (c, i) where c is either '(' or  ')' and i is the index of the character
// in the original string
list<pair<char, int>> bracket_seq;

/*******************************************************************************
* Read in the sequence of brackets and store it for future processing          *
*******************************************************************************/
void read_data()
{
    string brackets;
    cin >> brackets;

    // Populate the linked list of brackets from the string we just read
    for (int i = 0; i < brackets.size(); ++i)
    {
        bracket_seq.push_back(make_pair(brackets[i], i));
    }
}

/*******************************************************************************
* Find the length of the longest regular sub-sequence of the bracket sequence, *
* and also the number of such sequences. This can be done in O(n), where n is  *
* the length of the bracket sequence, using the following algorithm:           *
*                                                                              *
* Observe that in any regular bracket sequence, there must exist a pair '()'   *
* of adjacent matching brackets. So iterate over the sequence left-to-right.   *
* Whenever there is such a pair at the current position, remove it from the    *
* sequence. If doing so creates a new pair at the same position, remove that   *
* too, and so on, before continuing on in the sequence.                        *
*                                                                              *
* Every time a pair of brackets is removed, that corresponds to a regular      *
* bracket sub-sequence bounded by those two brackets in the original sequence. *
* Keep track of the regular sequences we have found, sorted by their starting  *
* position. Whenever we find a new regular sub-sequence, if its starting       *
* position is earlier than that of some of the ones we have found previously,  *
* then the new sequence contains the old ones, so we can forget about them. In *
* this way, we eventually end up with only the maximal regular sequences.      *
*                                                                              *
* Finally, any maximal regular sequences which are adjacent can be joined      *
* together into a longer sequence, and then the longest can be found easily.   *
*******************************************************************************/
pair<int, int> longest_regular_subseq()
{
    // Set up iterators into the bracket sequence. These will be positioned at
    // the left and right brackets of the pair we are currently checking.
    auto it1 = bracket_seq.begin();
    auto it2 = bracket_seq.begin(); ++it2;

    // Keep track of the regular subsequences found so far. Each is stored as
    // a pair (start, end) - the indices of the brackets bounding the sequence.
    vector<pair<int, int>> subseqs;

    // Iterate over the bracket sequence
    while ((it1 != bracket_seq.end()) && (it2 != bracket_seq.end()))
    {
        // Check if we have a matching pair at this position
        if ((it1->first == '(') && (it2->first == ')'))
        {
            // Store the sub-sequence and remove any old sub-sequences it 
            // contains - they have no chance of being maximal
            while ((!subseqs.empty()) && (subseqs.back().first > it1->second))
            {
                subseqs.pop_back();
            }
            subseqs.push_back(make_pair(it1->second, it2->second));

            // Remove the brackets and reposition the iterators
            ++it2; bracket_seq.erase(it1, it2); it1 = it2;
            if (it2 != bracket_seq.begin())
            {
                --it1;
            }
            else
            {
                ++it2;
            }
        }

        // If there isn't a match, just increment the iterators
        else
        {
            ++it1; ++it2;
        }
    }

    // Concatenate any adjacent subsequences
    vector<pair<int, int>> joined_subseqs;
    for (int i = 0; i < subseqs.size(); ++i)
    {
        // Check if we should concatenate
        if ((!joined_subseqs.empty()) && 
            (joined_subseqs.back().second == subseqs[i].first - 1))
        {
            // We should concatenate
            int start, end;
            start = joined_subseqs.back().first; joined_subseqs.pop_back();
            end = subseqs[i].second;
            joined_subseqs.push_back(make_pair(start, end));
        }
        else
        {
            // We don't need to concatenate
            joined_subseqs.push_back(subseqs[i]);
        }
    }

    // Find the longest subsequence, and how many there are of that length
    int best_len = 0; int num_seqs = 1;
    for (int i = 0; i < joined_subseqs.size(); ++i)
    {
        int new_len = joined_subseqs[i].second - joined_subseqs[i].first + 1;
        if (new_len > best_len)
        {
            best_len = new_len;
            num_seqs = 1;
        }
        else if (new_len == best_len)
        {
            ++num_seqs;
        }
    }

    return make_pair(best_len, num_seqs);
}

/*******************************************************************************
* Read in the bracket sequence from stdin and output the length of the longest *
* regular subsequence                                                          *
*******************************************************************************/
int main()
{
    // Read in the data
    read_data();

    // Find the answer
    pair<int, int> ans = longest_regular_subseq();
    cout << ans.first << " " << ans.second << endl;

    return 0;
}