#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// The number of days and the total required study time
int days;
int reqd_time;

// The maximum and minimum time spent each day
vector<int> min_time;
vector<int> max_time;

// Somewhere to store the actual times studied on each day
vector<int> actual_time;

/*******************************************************************************
* Read in the problem data from stdin, ready to be processed                   *
*******************************************************************************/
void read_data()
{
    // Read in the number of days and the total study time
    cin >> days >> reqd_time;

    // Read in the minimum and maximum study time for each day
    min_time = vector<int>(days, 0);
    max_time = vector<int>(days, 0);

    for (int i = 0; i < days; ++i)
    {
        cin >> min_time[i] >> max_time[i];
    }
}

/*******************************************************************************
* Determine whether Peter can study for the required amount of time while      *
* meeting the constraints for how much time to study each day. Returns true if *
* this can be achieved, and false otherwise. In the case that the constraints  *
* can be met, fills in the actual_time vector with the amount of time that he  *
* should study for each day.                                                   *
*******************************************************************************/
bool can_study()
{
    // Find the total of the minima and maxima for each day
    int min_total = 0; int max_total = 0;
    for (int i = 0; i < days; ++i)
    {
        min_total += min_time[i];
        max_total += max_time[i];
    }

    // If the required study time doesn't fall in the right range, return false
    if ((min_total > reqd_time) || (max_total < reqd_time))
    {
        return false;
    }

    // Determine a suitable timetable for Peter. Start by giving him the minimum
    // time each day, and then increasing days in turn until he has reached the
    // required study time
    int study_time = 0;
    actual_time = vector<int>(days, 0);

    for (int i = 0; i < days; ++i)
    {
        actual_time[i] = min_time[i];
        study_time += min_time[i];
    }

    // Increase the study time for each day until the required time is used
    int ix = 0;

    while (study_time < reqd_time)
    {
        int increase = min(max_time[ix] - min_time[ix], reqd_time - study_time);
        study_time += increase;
        actual_time[ix] += increase;
        ++ix;
    }

    return true;
}

/*******************************************************************************
* Read in the data from stdin and output whether or not Peter can study for    *
* the required amount of time                                                  *
*******************************************************************************/
int main()
{
    // Read in the data from stdin
    read_data();

    // Check whether Peter can meet his constraints
    if (can_study())
    {
        cout << "YES" << endl;
        for (int i = 0; i < days; ++i)
        {
            cout << actual_time[i] << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    return 0;
}