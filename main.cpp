#include <iostream>
#include <utility>
#include <vector>
#include <time.h>
#include <fstream>

using namespace std;

//Function to find the orientation of 3 points
int orientation(pair<int,int> p, pair<int,int> q, pair<int,int> r)
{
    int value = (q.second - p.second) * (r.first - q.first) -
    (q.first - p.first) * (r.second - q.second);

    if (value == 0) return 0;   //If collinear
    else if(value > 0) return 1;  //If clock wise
    else return 2;   //If counter-clock wise
}

//Function to find the convex hull of points
void convexHull(vector<pair<int,int>> points_vector)
{
int size=points_vector.size();

if (size < 3) return;  //Need at least 3 points

vector<pair<int,int>> convex_hull;
int leftPt = 0;
for (int i = 1; i < size; i++)
{
    if (points_vector[i].first < points_vector[leftPt].first)
        leftPt = i;
}

// start from left point and move counter-clock wise to reach start
int p=leftPt;
int q;
do
{
    convex_hull.push_back(points_vector[p]);
    //Now searching for the next value q
    q = (p+1)%size;
    //checking orientation of three points each time
    for (int i = 0; i < size; i++)
     {
        int direction=orientation(points_vector[p], points_vector[i], points_vector[q]);
        if (direction == 2)
            q=i;
     }
    p=q;
}
while (p != leftPt); //Checking to see if we are at start point

cout<<"\n----------------------------------------\n";
cout << "Convex hull points from the vector of points\n";
for (int i = 0; i < convex_hull.size(); i++)
{
    cout << "(" << convex_hull[i].first << ", "<< convex_hull[i].second << ")\n";
}
}

int main()
{
    freopen("Grid.txt", "w", stdout);
    srand(time(NULL));
    cout<<"Generating 200 random points between 0 to 100, 1000x1000 grid\n";
    for(int i=0; i<200; i++)
    {
        int x=rand()%1000;
        int y=rand()%1000;
        cout<<"{"<<x<<"  "<<y<<"}" << ",\t";
        if ((i+1) % 10 == 0)
           {cout << endl;}
    }

    freopen("Grid.txt", "r", stdin);

    int inputs;
    cin>>inputs;

    vector<pair<int,int>> points;

    for(int i=0; i<inputs; i++)
    {
        int x, y;
        cin>>x>>y;
        points.push_back({x,y});
    }

    convexHull(points);

    return 0;
}

