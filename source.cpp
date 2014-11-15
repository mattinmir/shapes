#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "classHeader.hpp"

using namespace std;

int get_farthest_point(const vector<point> &points);
int member_point(const vector<point> &v, const point p, bool ordered);
int member_point_unordsearch(const vector<point> &v, const point p);
int member_point_binsearch(const vector<point> &v, const point p, int imin, int imax);
void pointdup(const vector<point> &v1, const vector<point> &v2, vector<point> &v3, bool v2_ordered);

int main(int argc, char *argv[])
// argv = {-, point file 1, point file 2, is point file 2 ordered bool}
{
	ifstream infile;
	string line;
	vector<point> vin1, vin2, vout;
	double x, y;

	infile.open(argv[1]);
	if (!infile.is_open())
	{
		cout << "Could not open file" << endl;
		exit(EXIT_FAILURE);
	}
	while (infile >> x >> y) // See spring lab 5
	{
		vin1.push_back(point(x, y));
	}
	infile.close();

	infile.open(argv[2]);
	if (!infile.is_open())
	{
		cout << "Could not open file" << endl;
		exit(EXIT_FAILURE);
	}
	while (infile >> x >> y) // See spring lab 5
	{
		vin2.push_back(point(x, y));
	}
	infile.close();

	bool ordered;
	if (string(argv[3]) == "false")
		ordered = false;
	else
		ordered = true;

	pointdup(vin1, vin2, vout, ordered);

	ofstream outfile("vector3.txt");
	if (!outfile.is_open())
	{
		cout << "Could not open file" << endl;
		exit(EXIT_FAILURE);
	}
	for (unsigned int i = 0; i < vout.size(); i++)
	{
		outfile << '(' << vout.at(i).get_x() << ',' << vout.at(i).get_y() << ')' << endl;
	}

	return 0;
}

int get_farthest_point(const vector<point> &points)
{
	int index = 0;
	for (unsigned int i = 1; i < points.size(); i++)
	{
		if (points[i].get_magnitude() > points[index].get_magnitude())
			index = i;
	}

	return index;
}

int member_point(const vector<point> &v, const point p, bool ordered = false)
{
	if (ordered)
		return member_point_binsearch(v, p, 0, v.size() - 1);
	else
		return member_point_unordsearch(v, p);
}

int member_point_unordsearch(const vector<point> &v, point p)
{
	unsigned int index = 0;

	for (index = 0; index < v.size(); index++)
	{
		if (v.at(index) == p)
				return index;
	}

	return v.size();
}

int member_point_binsearch(const vector<point> &v, const point p, int imin, int imax)
{
	if (imax <= imin)
		return v.size();
	else
	{
		int imid = (imax - imin) / 2;
		if (v.at(imid) > p)
			return member_point_binsearch(v, p, imin, imid - 1);
		else if (v.at(imid) < p)
			return member_point_binsearch(v, p, imid + 1, imax);
		else 
			return imid;
	}
}

void pointdup(const vector<point> &v1, const vector<point> &v2, vector<point> &v3, bool v2_ordered)
{

	for (unsigned int i = 0; i < v1.size(); i++)
	{
		if (member_point(v2, v1.at(i), v2_ordered))
			v3.push_back(v1.at(i));
	}
}
