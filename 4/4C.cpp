#include <iostream>
#include <map>
#include <string>

using namespace std;

// A map to keep track of how many times each name has been requested
map<string, int> names;

// Somewhere to store each name as it comes in
string username;

/*******************************************************************************
* Deal with one username request. If the name is available, output "OK", and   *
* if not, count how many times it has been requested so far and append that    *
* number to the end of the username.                                           *
*******************************************************************************/
void name_request()
{
    // Read in the name
    cin >> username;

    // Check how many times this name has been used
    auto iter = names.find(username);
    if (iter == names.end())
    {
        // This is a new name, so add it to the database and output "OK"
        cout << "OK" << endl;
        names[username] = 1;
    }
    else
    {
        // This is a duplicate name, so output a modified name and update the
        // database of names
        cout << username << to_string((iter->second)++) << endl;
    }
}

/*******************************************************************************
* Read in the data from stdin and output the results for each username         *
*******************************************************************************/
int main()
{
    // Read in the number of usernames that will be requested
    int cnt; cin >> cnt;

    // Deal with each request in turn
    for (int i = 0; i < cnt; ++i)
    {
        name_request();
    }

    return 0;
}