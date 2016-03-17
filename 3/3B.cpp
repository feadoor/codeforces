#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// Some variables to store the input and output for the question

// The size of the lorry
int lorry_size;

// The boats themselves - store the kayaks and catamarans separately. Each boat
// is stored as a pair (capacity, ix), where ix is the index of the boat in the
// input and capacity is the capacity of the boat.
vector<pair<int, int>> kayaks;
vector<pair<int, int>> catamarans;

/*******************************************************************************
* Read in the data from stdin and store them for later use                     *
*******************************************************************************/
void read_data()
{
    // Get the size of the lorry and the number of boats
    int n_boats;
    cin >> n_boats >> lorry_size;

    // Read in the list of boats
    int size, capacity;

    for (int i = 0; i < n_boats; ++i)
    {
        cin >> size >> capacity;
        if (size == 1)
        {
            kayaks.push_back(make_pair(capacity, i + 1));
        }
        else if (size == 2)
        {
            catamarans.push_back(make_pair(capacity, i + 1));
        }
    }
}

/*******************************************************************************
* Find the optimal set of boats to carry on the lorry. This can be done using  *
* a brute-force algorithm. Our first guess for an optimal set is to load as    *
* many kayaks as is possible, and then fill the remainder with catamarans.     *
*                                                                              *
* We then repeatedly remove the smallest kayak from the lorry, and, if there   *
* is room, load the next best catamaran. At each step, we check for a new best *
* total.                                                                       *
*                                                                              *
* Once all configurations have been checked, we will know the answer and can   *
* output the results.                                                          *
*******************************************************************************/
void find_optimal_set()
{
    // Start by sorting the list of boats by capacity, largest first
    sort(kayaks.rbegin(), kayaks.rend());
    sort(catamarans.rbegin(), catamarans.rend());

    // Keep track of how many catamarans and kayaks we've loaded
    int n_kayaks = 0; int n_catamarans = 0;
    // Keep track of the total capacity
    int capacity = 0;
    // Keep track of the best values
    int b_kayaks = 0; int b_catamarans = 0; int b_capacity = 0;

    // Load up initially with as many kayaks as possible
    for (int i = 0; (i < kayaks.size()) && (lorry_size >= 1); ++i)
    {
        capacity += kayaks[i].first;
        ++n_kayaks; --lorry_size;
    }
    // Then fill the remainder with catamarans
    for (int i = 0; (i < catamarans.size()) && (lorry_size >= 2); ++i)
    {
        capacity += catamarans[i].first;
        ++n_catamarans; lorry_size -= 2;
    }
    // Store these values as a first-guess for the best
    b_kayaks = n_kayaks; b_catamarans = n_catamarans; b_capacity = capacity;

    while (n_kayaks > 0)
    {
        // Repeatedly remove kayaks from the lorry and add catamarans instead
        capacity -= kayaks[n_kayaks - 1].first;
        --n_kayaks; ++lorry_size;

        // Check if we can fit another catamaran
        if ((lorry_size >= 2) && (n_catamarans < catamarans.size()))
        {
            capacity += catamarans[n_catamarans].first;
            ++n_catamarans; lorry_size -= 2;
        }

        // Check if we have a new best
        if (capacity > b_capacity)
        {
            b_kayaks = n_kayaks; b_catamarans = n_catamarans; 
            b_capacity = capacity;
        }
    }

    // We have the answer, so output it in the required format
    cout << b_capacity << endl;
    for (int i = 0; i < b_kayaks; ++i)
    {
        cout << kayaks[i].second << " ";
    }
    for (int i = 0; i < b_catamarans; ++i)
    {
        cout << catamarans[i].second << " ";
    }
    cout << endl;
}

/*******************************************************************************
* Read in the problem data and output the optimal set of boats                 *
*******************************************************************************/
int main()
{
    read_data();
    find_optimal_set();
    return 0;
}