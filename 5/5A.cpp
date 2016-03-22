#include <iostream>
#include <string>

using namespace std;

// The number of people in the chat
int n_people = 0;
// The number of output lines from the chat
int output_lines = 0;

/*******************************************************************************
* Read lines of chat from stdin, and process them according to the given rules *
*******************************************************************************/
void read_lines()
{
    // Somewhere to store each line of chat as it comes in
    string chat_line;

    // Read each line in turn
    while (getline(cin, chat_line))
    {
        if (chat_line[0] == '+')
        {
            // Someone joined the chat
            ++n_people;
        }
        else if (chat_line[0] == '-')
        {
            //Someone left the chat
            --n_people;
        }
        else
        {
            // Someone sent a message
            int message_len = (chat_line.size() - chat_line.find(':') - 1);
            output_lines += n_people * message_len;
        }
    }
}

/*******************************************************************************
* Read all the lines from chat and print the number of output lines produced   *
*******************************************************************************/
int main()
{
    // Read in the input data
    read_lines();
    // Output the answer
    cout << output_lines << endl;

    return 0;
}