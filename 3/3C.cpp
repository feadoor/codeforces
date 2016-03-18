#include <iostream>
#include <string>

using namespace std;

// Some constant strings for the possible outputs
const string turn_x = "first";
const string turn_o = "second";
const string illegal = "illegal";
const string win_x = "the first player won";
const string win_o = "the second player won";
const string draw = "draw";

// Somewhere to store the board that we read in from the question
char board[3][3];

/*******************************************************************************
* Read in the board from stdin                                                 *
*******************************************************************************/
void read_board()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cin >> board[i][j];
        }
    }
}

/*******************************************************************************
* Check if the given player has any lines on the board                         *
*******************************************************************************/
bool has_lines(char p)
{
    // Horizontal lines
    if ((board[0][0] == p) && (board[0][1] == p) && (board[0][2] == p))
    {
        return true;
    }
    if ((board[1][0] == p) && (board[1][1] == p) && (board[1][2] == p))
    {
        return true;
    }
    if ((board[2][0] == p) && (board[2][1] == p) && (board[2][2] == p))
    {
        return true;
    }

    // Vertical lines
    if ((board[0][0] == p) && (board[1][0] == p) && (board[2][0] == p))
    {
        return true;
    }
    if ((board[0][1] == p) && (board[1][1] == p) && (board[2][1] == p))
    {
        return true;
    }
    if ((board[0][2] == p) && (board[1][2] == p) && (board[2][2] == p))
    {
        return true;
    }

    // Diagonal lines
    if ((board[0][0] == p) && (board[1][1] == p) && (board[2][2] == p))
    {
        return true;
    }
    if ((board[0][2] == p) && (board[1][1] == p) && (board[2][0] == p))
    {
        return true;
    }

    // No lines, return false
    return false;
}

/*******************************************************************************
* Check if the board is in a legal state, and if so, determine who has won, or *
* whose turn it is.                                                            *
*******************************************************************************/
string board_state()
{
    // Work out who had the last turn. If the number of X's and O's is
    // mismatched, then we already know the state is illegal.
    int num_x = 0; int num_o = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == 'X')
            {
                ++num_x;
            }
            else if (board[i][j] == '0')
            {
                ++num_o;
            }
        }
    }

    // Check if the number of X's and O's makes sense
    char turn; char other;

    if ((num_x < num_o) || (num_x > num_o + 1))
    {
        return illegal;
    }

    // Decide whose turn it is
    else if (num_x == num_o)
    {
        turn = 'X';
        other = '0';
    }
    else if (num_x == (num_o + 1))
    {
        turn = '0';
        other = 'X';
    }

    // Check if the player whose turn it is has any lines on the board. If so,
    // then the position is illegal, since they should have already won.
    if (has_lines(turn))
    {
        return illegal;
    }

    // Check if the player who just played definitely had any lines on the board 
    // before their last turn. If so, the position is illegal.
    // Iterate over all their pieces, remove them from the board, and check for
    // lines. If any of the resulting configurations have no lines, the position
    // is legal, otherwise, it is illegal.
    bool legal = false;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == other)
            {
                board[i][j] = '.';
                if (!has_lines(other))
                {
                    legal = true;
                }
                board[i][j] = other;
            }
        }
    }

    if (!legal)
    {
        return illegal;
    }

    // If we get here, the board is definitely in a legal state. Firstly, check
    // if the player who just moved has won.
    if (has_lines(other))
    {
        if (other == 'X')
        {
            return win_x;
        }
        else if (other == '0')
        {
            return win_o;
        }
    }

    // No-one has won, so check if the game is over and has ended in a draw
    if (num_x == 5)
    {
        return draw;
    }

    // If we get here, it must be someone's turn, so return that
    if (turn == 'X')
    {
        return turn_x;
    }
    else
    {
        return turn_o;
    }
}

/*******************************************************************************
* Read in the board from stdin and output the state of the game                *
*******************************************************************************/
int main()
{
    // Read the board state from stdin
    read_board();
    // Output the state of the game
    cout << board_state();

    return 0;
}