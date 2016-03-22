#include <iostream>
#include <string>
#include <queue>

using namespace std;

// Some constants to determine whether lines that cannot be perfectly centred
// should be shifted to the left or to the right
#define LEFT 0
#define RIGHT 1
int shift_dir = LEFT;

// The width of the frame
int frame_width = 0;

// The lines of text to be printed
queue<string> text_lines;

/*******************************************************************************
* Read in the lines of text from stdin, recording the maximum length of the    *
* lines that are given and storing the lines of text in a queue.               *
*******************************************************************************/
void read_lines()
{
    // Read in each line in turn
    string line;
    while (getline(cin, line))
    {
        // Store this line and check for a new longest line
        text_lines.push(line);
        frame_width = (frame_width > line.size()) ? frame_width : line.size();
    }
}

/*******************************************************************************
* Output a single line of text, centred in the frame.                          *
*******************************************************************************/
void print_line()
{
    // The left-hand border of the frame
    cout << '*';

    // Pop the line of text off the queue
    string line = text_lines.front(); text_lines.pop();

    // Work out how much space will be left in the frame after writing the line
    int spare = frame_width - line.size();

    // How much space to leave on the left side of the text - if the spare space 
    // is odd, then we need to leave extra room on one side
    int offset_amt = spare / 2;
    if (spare % 2 == 1)
    {
        if (shift_dir == LEFT)
        {
            shift_dir = RIGHT;
        }
        else if (shift_dir == RIGHT)
        {
            ++offset_amt;
            shift_dir = LEFT;
        }
    }

    // Print the left-hand offset, followed by the line, followed by the right
    // hand offset, and finally, the edge of the frame.
    cout << string(offset_amt, ' ');
    cout << line;
    cout << string(spare - offset_amt, ' ');
    cout << '*' << endl;
}

/*******************************************************************************
* Read in the lines of text from stdin, and print them again in a frame        *
*******************************************************************************/
int main()
{
    // Read in the lines of text from stdin
    read_lines();

    // Print the top frame border
    cout << string(frame_width + 2, '*') << endl;

    // Print the lines of text
    while (!text_lines.empty())
    {
        print_line();
    }

    // Print the bottom frame border
    cout << string(frame_width + 2, '*') << endl;

    return 0;
}