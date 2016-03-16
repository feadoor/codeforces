#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

/*******************************************************************************
* Structure representing a point in two-dimensional Euclidean space            *
*******************************************************************************/
struct point
{
    double x;
    double y;
};

/*******************************************************************************
* Structure representing a circle in two-dimensional Euclidean space           *
*******************************************************************************/
struct circle
{
    point centre;
    double r;
};

/*******************************************************************************
* Finds the Euclidean distance between the two given points                    *
*******************************************************************************/
double distance(point a, point b)
{
    double dx = b.x - a.x; double dy = b.y - a.y;
    return sqrt(dx * dx + dy * dy);
}

/*******************************************************************************
* Calculates the coordinates of the circumcentre of the given three points,    *
* which are guaranteed to not be collinear                                     *
*                                                                              *
* In barycentric coordinates, the circumcentre of triangle ABC has coordinates *
* (sin(2A), sin(2B), sin(2C)), so by calculating these quantities, we can find *
* the circumcentre as a barycentric combination of the vertices                *
*******************************************************************************/
point circumcentre(point a, point b, point c)
{
    // Find the side-lengths of the triangle
    double ab = distance(a, b);
    double ac = distance(a, c);
    double bc = distance(b, c);

    // Find cos(A) and sin(A) for each angle of the triangle
    double cos_a = (ab * ab + ac * ac - bc * bc) / (2 * ab * ac);
    double cos_b = (ab * ab + bc * bc - ac * ac) / (2 * ab * bc);
    double cos_c = (ac * ac + bc * bc - ab * ab) / (2 * ac * bc);

    double sin_a = sqrt(1 - cos_a * cos_a);
    double sin_b = sqrt(1 - cos_b * cos_b);
    double sin_c = sqrt(1 - cos_c * cos_c);

    // Find sin(2A) for each angle of the triangle
    double sin_2a = 2 * sin_a * cos_a;
    double sin_2b = 2 * sin_b * cos_b;
    double sin_2c = 2 * sin_c * cos_c;

    // Take the barycentric combination
    point ret;

    double normalise = sin_2a + sin_2b + sin_2c;
    ret.x = (sin_2a * a.x + sin_2b * b.x + sin_2c * c.x) / normalise;
    ret.y = (sin_2a * a.y + sin_2b * b.y + sin_2c * c.y) / normalise;

    return ret;
}

/*******************************************************************************
* Finds all the intersection points of the two given circles, using the method *
* described at http://paulbourke.net/geometry/circlesphere/                    *
*******************************************************************************/
vector<point> intersections(circle c1, circle c2)
{
    vector<point> ret = {};

    // Name everything in accordance with the linked method
    double x0 = c1.centre.x;
    double y0 = c1.centre.y;
    double r0 = c1.r;

    double x1 = c2.centre.x;
    double y1 = c2.centre.y;
    double r1 = c2.r;

    // Check if the circles intersect at all
    double d = distance(c1.centre, c2.centre);
    if ((d > r0 + r1) || (d < abs(r0 - r1)))
    {
        return ret;
    }

    // Find the values of a and h
    double a = (r0 * r0 - r1 * r1 + d * d) / (2 * d);
    double h = sqrt(r0 * r0 - a * a);

    // Find the point P2
    double x2 = x0 + (a * (x1 - x0)) / d;
    double y2 = y0 + (a * (y1 - y0)) / d;

    // If h is zero, then there is only one intersection, otherwise there are 2
    point p3;

    p3.x = x2 + (h * (y1 - y0)) / d;
    p3.y = y2 - (h * (x1 - x0)) / d;
    ret.push_back(p3);

    if (h != 0)
    {
        p3.x = x2 - (h * (y1 - y0)) / d;
        p3.y = y2 + (h * (x1 - x0)) / d;
        ret.push_back(p3);
    }

    return ret;
}

/*******************************************************************************
* Finds the circle of Apollonius given by the locus of points X such that      *
* AX / BX = lambda, assuming that lambda is not equal to 1                     *
*******************************************************************************/
circle apollonius(point a, point b, double lambda)
{
    // Find the two endpoints of the diameter of the circle. These points divide
    // the line segment AB internally and externally in the ratio lambda
    point in, ex;

    in.x = (a.x + lambda * b.x) / (1 + lambda);
    in.y = (a.y + lambda * b.y) / (1 + lambda);

    ex.x = (a.x - lambda * b.x) / (1 - lambda);
    ex.y = (a.y - lambda * b.y) / (1 - lambda);

    // Find the centre of the circle and its radius
    point centre;
    centre.x = (in.x + ex.x) / 2;
    centre.y = (in.y + ex.y) / 2;

    double radius = distance(in, ex) / 2;

    // Return the circle
    circle ret;
    ret.centre = centre;
    ret.r = radius;
    return ret;
}

/*******************************************************************************
* Find all points from which the three given circles can be viewed from the    *
* same angle.                                                                  *
*                                                                              *
* If all three given circles have the same radius, the only solution is the    *
* circumcentre of the triangle formed by their centres. Otherwise, label the   *
* circles X1, X2 and X3 in such a way that X1 has a different radius from each *
* of the others.                                                               *
*                                                                              *
* Then the locus of points from which X1 and X2 can be viewed from the same    *
* angle is a circle of Apollonius based on the centres of X1, X2, with ratio   *
* given by the ratio between their radii. Similarly for X1, X3. Then just take *
* the intersection of these circles.                                           *
*                                                                              *
* Once all points have been found, choose the best one; that is, the one which *
* is closest to any of the stadiums.                                           *
*                                                                              *
* Returned as a vector so that we can optionally return an empty vector if no  *
* points are found.                                                            *
*******************************************************************************/
vector<point> best_viewpoint(circle c1, circle c2, circle c3)
{
    // Check if all the circles have the same radius
    if ((c1.r == c2.r) && (c2.r == c3.r))
    {
        return {circumcentre(c1.centre, c2.centre, c3.centre)};
    }

    // Find a circle with a radius distinct from the other two and make it c1
    if (c1.r == c2.r)
    {
        circle c4 = c1;
        c1 = c3; c3 = c4;
    }
    else if (c1.r == c3.r)
    {
        circle c4 = c1;
        c1 = c2; c2 = c4;
    }

    // Find the circles of Apollonius associated with the given circles
    double lambda2 = c1.r / c2.r;
    double lambda3 = c1.r / c3.r;

    circle apollonius2 = apollonius(c1.centre, c2.centre, lambda2);
    circle apollonius3 = apollonius(c1.centre, c3.centre, lambda3);

    // Find the intersections of these two circles
    vector<point> ints = intersections(apollonius2, apollonius3);

    // If there are fewer than 2 intersections, just return
    if (ints.size() < 2)
    {
        return ints;
    }

    // Otherwise, return the better of the two intersections
    if (distance(ints[0], c1.centre) < distance(ints[1], c1.centre))
    {
        return {ints[0]};
    }
    else
    {
        return {ints[1]};
    }
}

/*******************************************************************************
* Read in the three stadiums from stdin and output the best viewpoint, if it   *
* exists, and output nothing otherwise                                         *
*******************************************************************************/
int main()
{
    // Input the three circles
    point o1, o2, o3;
    double r1, r2, r3;
    circle c1, c2, c3;

    cin >> o1.x >> o1.y >> r1;
    cin >> o2.x >> o2.y >> r2;
    cin >> o3.x >> o3.y >> r3;

    c1.centre = o1; c1.r = r1;
    c2.centre = o2; c2.r = r2;
    c3.centre = o3; c3.r = r3;

    // Output the best viewpoint, if it exists
    vector<point> viewpoint = best_viewpoint(c1, c2, c3);
    if (viewpoint.size() > 0)
    {
        cout << fixed << setprecision(5) << viewpoint[0].x << " ";
        cout << fixed << setprecision(5) << viewpoint[0].y << endl;
    }

    return 0;
}