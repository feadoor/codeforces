#include <iostream>
#include <regex>
#include <string>
using namespace std;

typedef long long ll;

// Regular expressions to determine the format of a given input
regex excel_style("([A-Z]+)([0-9]+)");
regex rowcol_style("R([0-9]+)C([0-9]+)");
smatch match;

/*******************************************************************************
* Convert a positive integer number to the corresponding column in Excel-style *
* format - that is, column 1 is A, 2 is B, and so on, until 27,... is AA, AB,  *
* AC, ..., BA, BB, ...                                                         *
*******************************************************************************/
string int_to_column(ll n)
{
    string ret = "";
    int remainder;

    // Repeatedly take the remainder upon dividing by 26 to convert to column
    while (n > 0)
    {
        // Get the remainder for this stage of the conversion
        remainder = (n - 1) % 26;
        n = (n - remainder) / 26;

        // Update the output
        ret = (char)('A' + remainder) + ret;
    }

    return ret;
}

/*******************************************************************************
* Convert a column given in alphabetical, Excel-style format to the positive   *
* integer representing that column.                                            *
*******************************************************************************/
ll column_to_int(string col)
{
    // Interpret the column name as a base-26 number, with A=1, B=2, ..., Z=26
    ll ret = 0;

    for (char c : col)
    {
        // Update the value based on the next base-26 digit
        ret = 26 * ret + (c - 'A' + 1);
    }

    return ret;
}

/*******************************************************************************
* Convert a coordinate from row-column format to Excel-style format            *
*******************************************************************************/
string rowcol_to_excel(string row, ll col)
{
    string ret = "";

    ret += int_to_column(col);
    ret += row;

    return ret;
}

/*******************************************************************************
* Convert a coordinate from Excel-style format to row-column format            *
*******************************************************************************/
string excel_to_rowcol(string row, string col)
{
    string ret = "";

    ret += ("R" + row);
    ret += ("C" + to_string(column_to_int(col)));

    return ret;
}

/*******************************************************************************
* Convert a string coordinate from one style to another                        *
*******************************************************************************/
string convert(string coord)
{
    // Variables to store the row and column we pull out from the coordinate
    string row;
    string col;

    // Variable to store the converted coordinate
    string conversion;

    if (regex_match(coord, match, excel_style))
    {
        // Pull out the row and column, perform the conversion
        col = match.str(1);
        row = match.str(2);
        conversion = excel_to_rowcol(row, col);
    }
    else if (regex_match(coord, match, rowcol_style))
    {
        // Pull out the row and column, perform the conversion
        row = match.str(1);
        col = match.str(2);
        conversion = rowcol_to_excel(row, stoi(col));
    }

    return conversion;
}

/*******************************************************************************
* Get input from stdin and output the converted coordinates                    *
*******************************************************************************/
int main()
{
    // Get the number of coordinates that need to be converted
    int num_coords;
    cin >> num_coords;

    // Get each coordinate in turn
    string coord;

    for (int i = 0; i < num_coords; ++i)
    {
        cin >> coord;

        // Perform the conversion and output the result
        cout << convert(coord) << endl;
    }

    return 0;
}