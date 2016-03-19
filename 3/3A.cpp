#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/*******************************************************************************
* Structure to represent a square on a chessboard                              *
*******************************************************************************/
struct square
{
    int row;
    char col;
};

/*******************************************************************************
* Determines the length of the shortest path between two squares on a baord    *
*******************************************************************************/
int path_length(square source, square target)
{
    // Find the difference between the two columns
    int col_diff = abs((int)source.col - (int)target.col);

    // Find the difference between the two rows
    int row_diff = abs(source.row - target.row);

    // Output the larger of the two values
    return (row_diff > col_diff) ? row_diff : col_diff;
}

/*******************************************************************************
* Determines the shortest path between two squares on a chessboard using a     *
* simple greedy algorithm                                                      *
*******************************************************************************/
string shortest_path(square source, square target)
{
    stringstream path;

    // Calculate the path one step at a time, using a greedy algorithm
    while ((source.row != target.row) || (source.col != target.col))
    {
        // Check if we need to move left or right this step
        if (source.col < target.col)
        {
            path << "R";
            ++(source.col);
        }
        else if (source.col > target.col)
        {
            path << "L";
            --(source.col);
        }

        // Check if we need to move up or down this step
        if (source.row < target.row)
        {
            path << "U";
            ++(source.row);
        }
        else if (source.row > target.row)
        {
            path << "D";
            --(source.row);
        }

        path << "\n";
    }

    return path.str();
}

/*******************************************************************************
* Read the source and target squares from stdin and output the best path       *
*******************************************************************************/
int main()
{
    // Read in the squares from stdin
    square source, target;
    cin >> source.col >> source.row;
    cin >> target.col >> target.row;

    // Output the optimal path
    cout << path_length(source, target) << endl;
    cout << shortest_path(source, target);

    return 0;
}