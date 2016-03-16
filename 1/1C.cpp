#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

#define PI 3.1415926535897932384626433832795028841971693993
#define EPS 1e-5

/*******************************************************************************
* Structure representing a point in two-dimensional Euclidean space            *
*******************************************************************************/
struct point
{
	double x;
	double y;
};

/*******************************************************************************
* Finds the area of a triangle in two-dimensional Euclidean space using the    *
* determinant formula.                                                         *
*******************************************************************************/
double area(point a, point b, point c)
{
	return abs(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2;
}

/*******************************************************************************
* Finds the Euclidean distance between the two given points                    *
*******************************************************************************/
double distance(point a, point b)
{
	double dx = b.x - a.x; double dy = b.y - a.y;
	return sqrt(dx * dx + dy * dy);
}

/*******************************************************************************
* Finds the circumradius of the triangle formed by three given points          *
*******************************************************************************/
double circumradius(point a, point b, point c)
{
	double ab = distance(a, b);
	double ac = distance(a, c);
	double bc = distance(b, c);

	return (ab * bc * ac) / (4 * area(a, b, c));
}

/*******************************************************************************
* Finds the area of a regular polygon with the given circumradius and the      *
* given number of sides                                                        *
*******************************************************************************/
double polygon_area(double radius, int n)
{
	return n * radius * radius * sin((2 * PI) / n) / 2;
}

/*******************************************************************************
* Finds the minimal number of sides required by a regular polygon having the   *
* three given points as vertices.                                              *
*******************************************************************************/
int min_sides(point a, point b, point c)
{
	// Calculate the three angles of the triangle - the n we seek is the
	// smallest n such that each angle is a multiple of PI / n.
	double ab = distance(a, b);
	double ac = distance(a, c);
	double bc = distance(b, c);

	double angle_a = acos((ab * ab + ac * ac - bc * bc) / (2 * ab * ac));
	double angle_b = acos((ab * ab + bc * bc - ac * ac) / (2 * ab * bc));
	double angle_c = acos((ac * ac + bc * bc - ab * ab) / (2 * ac * bc));

	// Iterate over n, testing whether the angles are all multiples of PI / n
	int n = 3; while (1)
	{
		if (abs(sin(angle_a * n)) < EPS && 
			abs(sin(angle_b * n)) < EPS &&
			abs(sin(angle_c * n)) < EPS)
		{
			return n;
		}
		++n;
	}
}

/*******************************************************************************
* Finds the minimal area of a Berland circus containing the three given points *
*******************************************************************************/
double min_area(point a, point b, point c)
{
	// Find the circumradius of the three points
	double radius = circumradius(a, b, c);

	// Find the minimum number of sides of the circus
	int n = min_sides(a, b, c);

	// Return the area of the minimal circus
	return polygon_area(radius, n);
}

/*******************************************************************************
* Get input from stdin and output the required answers                         *
*******************************************************************************/
int main()
{
	// Get the three points
	point a, b, c;
	cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;

	// Output the minimal area of the circus
	cout << fixed << setprecision(8) << min_area(a, b, c) << endl;

	return 0;
}