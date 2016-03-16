#include <iostream>
using namespace std;

typedef long long ll;

/*******************************************************************************
* Calculate the number of stones of the given size required to completely tile *
* tile a rectangle of the given width and height.                              *
*                                                                              *
* The answer is found by simply multiplying together the number of stones      *
* needed in each dimension, which is found by, for example, dividing the width *
* by the size of the stone (rounding up if necessary)                          *
*******************************************************************************/
ll stones_reqd(ll width, ll height, ll stone_size)
{
    // Calculate the number of stones required in each direction using ceiling
    // division.
    ll width_reqd = (width + stone_size - 1) / stone_size;
    ll height_reqd = (height + stone_size - 1) / stone_size;

    // Multiply together to get the result.
    return width_reqd * height_reqd;
}   

/*******************************************************************************
* Get input from stdin and output the required answer                          *
*******************************************************************************/
int main()
{
    // Get input
    ll width, height, stone_size;
    cin >> width >> height >> stone_size;

    // Calculate and output the answer
    cout << stones_reqd(width, height, stone_size);

    return 0;
}