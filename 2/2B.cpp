#include <climits>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

// The size of the matrix in the question
int n;

// Vectors to hold data about optimal routes through the matrix
vector<vector<unsigned int>> best_power2;
vector<vector<unsigned int>> best_power5;
vector<vector<char>> path_power2;
vector<vector<char>> path_power5;

// Vector to hold the matrix entries
vector<vector<unsigned int>> matrix;

// Bool to store whether there is a zero in the matrix
bool zero = false;
int zero_i, zero_j;

/*******************************************************************************
* Initialise the storage vectors with zeroes, using the given size             *
*******************************************************************************/
void init_vectors()
{
    // Initialise best_power2, best_power5, path_power2, path_power5 and matrix
    for (int i = 0; i < n; ++i)
    {
        best_power2.push_back(vector<unsigned int>(n, 0));
        best_power5.push_back(vector<unsigned int>(n, 0));
        path_power2.push_back(vector<char>(n, 0));
        path_power5.push_back(vector<char>(n, 0));
        matrix.push_back(vector<unsigned int>(n, 0));
    }
}

/*******************************************************************************
* Read in the matrix entries from stdin and store them in a vector             *
*******************************************************************************/
void read_matrix()
{
    // Get the size of the matrix
    cin >> n;
    init_vectors();

    // Read in all the entries
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> matrix[i][j];

            // Check if the entry is zero
            if (matrix[i][j] == 0)
            {
                zero = true;
                zero_i = i; zero_j = j;
            }
        }
    }
}

/*******************************************************************************
* Utility function to calculate the highest power of the given p that divides  *
* the given positive integer                                                   *
*******************************************************************************/
ll max_power(int m, int p)
{
    // Need to handle zero specially
    if (m == 0)
    {
        return INT_MAX;
    }

    // Otherwise just repeatedly divide by p
    int ret = 0;

    while (m % p == 0)
    {
        m /= p;
        ++ret;
    }
    return ret;
}

/*******************************************************************************
* Dynamic programming to calculate, for each position in the matrix, the       *
* minimum powers of 2 and 5 that can divide the product of a path ending at    *
* that point.                                                                  *
*                                                                              *
* This can be calculated by iterating through the matrix entries, and updating *
* each one based on the minimum values of its neighbours immediately above and *
* to the right, taking the smaller one.                                        *
*******************************************************************************/
void dynamic_prog()
{
    // best_nbr holds the minimum value of either of the neighbour entries
    ll best_nbr2, best_nbr5;
    ll next_nbr2, next_nbr5;

    // direction holds the direction we should travel into this square from
    // in order to follow the optimal path
    char direction2, direction5;
    int i, j;

    // Base case is the top-left corner of the matrix
    best_power2[0][0] = max_power(matrix[0][0], 2);
    best_power5[0][0] = max_power(matrix[0][0], 5);

    // Iterate over the remaining entries in the matrix
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            if ((i == 0) && (j == 0))
            {
                continue;
            }

            // Update best_nbr based on the neighbouring entries
            best_nbr2 = INT_MAX; best_nbr5 = INT_MAX;
            direction2 = 0; direction5 = 0;

            // If i > 0 then we have an upwards neighbour
            if (i > 0)
            {
                next_nbr2 = best_power2[i-1][j];
                if (next_nbr2 <= best_nbr2)
                {
                    best_nbr2 = next_nbr2;
                    direction2 = 'D';
                }

                next_nbr5 = best_power5[i-1][j];
                if (next_nbr5 <= best_nbr5)
                {
                    best_nbr5 = next_nbr5;
                    direction5 = 'D';
                }
            }

            // If j > 0 then we have a leftwards neighbour
            if (j > 0)
            {
                next_nbr2 = best_power2[i][j-1];
                if (next_nbr2 <= best_nbr2)
                {
                    best_nbr2 = next_nbr2;
                    direction2 = 'R';
                }

                next_nbr5 = best_power5[i][j-1];
                if (next_nbr5 <= best_nbr5)
                {
                    best_nbr5 = next_nbr5;
                    direction5 = 'R';
                }
            }

            // Calculate the best values for this square and the best route to
            // reach the square from
            best_power2[i][j] = best_nbr2 + max_power(matrix[i][j], 2);
            best_power5[i][j] = best_nbr5 + max_power(matrix[i][j], 5);
            path_power2[i][j] = direction2;
            path_power5[i][j] = direction5;
        }
    }
}

/*******************************************************************************
* Finds the best path through the matrix to minimise the power of 2 in the     *
* product of the numbers on the path, where zero is viewed as having a single  *
* power of 2 dividing it.                                                      *
*******************************************************************************/
string best_path2()
{
    string path = "";

    // If there are no zeroes in the matrix, or if we can avoid powers of 2
    // completely, then just take the actual best path. Use the dynamic
    // programming array to build up the path from end to beginning.
    if (!zero || (best_power2[n-1][n-1] == 0))
    {
        // Keep track of the current square in the path so we know when we have
        // reached the beginning
        int i = n-1; int j = n-1;
        while ((i > 0) || (j > 0))
        {
            if (path_power2[i][j] == 'D')
            {
                path = "D" + path;
                --i;
            }
            else if (path_power2[i][j] == 'R')
            {
                path = "R" + path;
                --j;
            }
        }
    }

    // Otherwise, the best path involves travelling through a zero, so find that
    // path and return it
    else
    {
        // Step to the zero square, first of all
        for (int i = 0; i < zero_i; ++i)
        {
            path += "D";
        }
        for (int j = 0; j < zero_j; ++j)
        {
            path += "R";
        }

        // Then step to the bottom-right of the matrix
        for (int i = zero_i; i < n - 1; ++i)
        {
            path += "D";
        }
        for (int j = zero_j; j < n - 1; ++j)
        {
            path += "R";
        }
    }

    return path;
}

/*******************************************************************************
* Finds the best path through the matrix to minimise the power of 5 in the     *
* product of the numbers on the path, where zero is viewed as having a single  *
* power of 5 dividing it.                                                      *
*******************************************************************************/
string best_path5()
{
    string path = "";

    // If there are no zeroes in the matrix, or if we can avoid powers of 5
    // completely, then just take the actual best path. Use the dynamic
    // programming array to build up the path from end to beginning.
    if (!zero || (best_power5[n-1][n-1] == 0))
    {
        // Keep track of the current square in the path so we know when we have
        // reached the beginning
        int i = n-1; int j = n-1;
        while ((i > 0) || (j > 0))
        {
            if (path_power5[i][j] == 'D')
            {
                path = "D" + path;
                --i;
            }
            else if (path_power5[i][j] == 'R')
            {
                path = "R" + path;
                --j;
            }
        }
    }

    // Otherwise, the best path involves travelling through a zero, so find that
    // path and return it
    else
    {
        // Step to the zero square, first of all
        for (int i = 0; i < zero_i; ++i)
        {
            path += "D";
        }
        for (int j = 0; j < zero_j; ++j)
        {
            path += "R";
        }

        // Then step to the bottom-right of the matrix
        for (int i = zero_i; i < n - 1; ++i)
        {
            path += "D";
        }
        for (int j = zero_j; j < n - 1; ++j)
        {
            path += "R";
        }
    }

    return path;
}

/*******************************************************************************
* Finds the minimum possible number of trailing zeroes at the end of the       *
* product of a path through the matrix                                         *
*******************************************************************************/
ll best_zeroes()
{
    // If there are no zeroes in the matrix, then the best we can do is simply
    // take the path that gives the smallest power of 2 or 5
    if (!zero || (best_power2[n-1][n-1] == 0) || (best_power5[n-1][n-1] == 0))
    {
        if (best_power2[n-1][n-1] < best_power5[n-1][n-1])
        {
            return best_power2[n-1][n-1];
        }
        else
        {
            return best_power5[n-1][n-1];
        }
    }

    // If there are zeroes and we can't avoid 2's or 5's completely, then the
    // best we can do is the path through the zero
    else
    {
        return 1;
    }
}

/*******************************************************************************
* Finds the path through the matrix that minimises the number of trailing      *
* zeroes at the end of the product of the path                                 *
*******************************************************************************/
string best_path()
{
    if (best_power2[n-1][n-1] < best_power5[n-1][n-1])
    {
        return best_path2();
    }
    else
    {
        return best_path5();
    }
}

/*******************************************************************************
* Read matrix values from stdin and find the best path through the matrix      *
*******************************************************************************/
int main()
{
    // Get the matrix values from stdin
    read_matrix();

    // Calculate the best paths
    dynamic_prog();

    // Output the result
    cout << best_zeroes() << endl << best_path() << endl;
    return 0;
}