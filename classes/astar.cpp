#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <tuple>
#include <set>
#include <cmath>
#include <cassert>

using namespace std;

typedef pair< int, int > Point;

// maximum width
const int mWidth = 1000;
const int mHeight = 1000;

int mapWidth = 20;
int mapHeight = 20;

const char obstacle = 'b';

// graph for back tracking path
Point cameFrom[mWidth][mHeight];


int mDistance( const Point& a, const Point& b ){
    return (std::abs( a.first - b.first ) + std::abs( a.second - b.second ));
}

// void printMap(){
//     for( int y = 0; y < mapHeight; ++ y ){
//         for( int x = 0; x < mapWidth; ++ x ){
//             cout << setw(3) << bitmap[x][y];
//         }
//         cout << endl;
//     }
// }

// score, step, point
typedef tuple< int, int, Point > Node;

vector<Point> Astar( Point start, Point end, int& vc ){
    char bitmap[20][20];
    bool visited[mWidth][mHeight];

    bitmap[1][2] = obstacle; 
    bitmap[1][7] = obstacle;

    bitmap[2][1] = obstacle;
    bitmap[2][2] = obstacle;
    bitmap[2][4] = obstacle;
    bitmap[2][5] = obstacle;
    bitmap[2][7] = obstacle;
    bitmap[2][8] = obstacle;

    bitmap[3][2] = obstacle;
    bitmap[3][7] = obstacle;

    bitmap[4][2] = obstacle;
    bitmap[4][7] = obstacle;

    bitmap[5][6] = obstacle;

    bitmap[7][1] = obstacle;
    bitmap[7][4] = obstacle;
    bitmap[7][5] = obstacle;
    bitmap[7][7] = obstacle;
    bitmap[7][8] = obstacle;

    bitmap[8][1] = obstacle;

    bitmap[1][12] = obstacle;    
    bitmap[1][17] = obstacle;

    bitmap[2][10] = obstacle;
    bitmap[2][11] = obstacle;
    bitmap[2][14] = obstacle;
    bitmap[2][15] = obstacle;
    bitmap[2][17] = obstacle;
    bitmap[2][18] = obstacle;

    bitmap[3][12] = obstacle;
    bitmap[3][17] = obstacle;

    bitmap[4][12] = obstacle;
    bitmap[4][17] = obstacle;

    bitmap[5][16] = obstacle;

    bitmap[7][11] = obstacle;
    bitmap[7][14] = obstacle;
    bitmap[7][15] = obstacle;
    bitmap[7][17] = obstacle;
    bitmap[7][18] = obstacle;

    bitmap[8][11] = obstacle;


    bitmap[11][2] = obstacle;    
    bitmap[11][7] = obstacle;

    bitmap[12][1] = obstacle;
    bitmap[12][2] = obstacle;
    bitmap[12][4] = obstacle;
    bitmap[12][5] = obstacle;
    bitmap[12][7] = obstacle;
    bitmap[12][8] = obstacle;

    bitmap[13][2] = obstacle;
    bitmap[13][7] = obstacle;

    bitmap[14][2] = obstacle;
    bitmap[14][7] = obstacle;

    bitmap[15][6] = obstacle;

    bitmap[17][1] = obstacle;
    bitmap[17][4] = obstacle;
    bitmap[17][5] = obstacle;
    bitmap[17][7] = obstacle;
    bitmap[17][8] = obstacle;

    bitmap[18][1] = obstacle;

    bitmap[11][12] = obstacle;   
    bitmap[11][17] = obstacle;

    bitmap[12][10] = obstacle;
    bitmap[12][11] = obstacle;
    bitmap[12][14] = obstacle;
    bitmap[12][15] = obstacle;
    bitmap[12][17] = obstacle;
    bitmap[12][18] = obstacle;

    bitmap[13][12] = obstacle;
    bitmap[13][17] = obstacle;

    bitmap[14][12] = obstacle;
    bitmap[14][17] = obstacle;

    bitmap[15][16] = obstacle;

    bitmap[17][11] = obstacle;
    bitmap[17][14] = obstacle;
    bitmap[17][15] = obstacle;
    bitmap[17][17] = obstacle;
    bitmap[17][18] = obstacle;

    bitmap[18][11] = obstacle;



    // for (int i = 0; i < 20; i++)
    // {
    //     for (int j = 0; j < 20; j++)
    //     {
    //         bitmap[i][j] = map[i][j];
    //     }
    // }

    // assert( mapWidth <= mWidth );
    // assert( mapHeight <= mHeight );
    // assert( 0 <= start.first && start.first < mapWidth );
    // assert( 0 <= start.second && start.second < mapHeight );

    // assert( 0 <= end.first && end.first < mapWidth );
    // assert( 0 <= end.second && end.second < mapHeight );

    // clear previous memory
    memset( visited, 0, sizeof( visited ));
    memset( cameFrom, 0, sizeof( cameFrom ));

    priority_queue< Node, vector<Node>, greater<Node> > Q;

    // clostestPoint reachable by the unit if target cannot be reached
    // special case : distance, step, point
    Node clostestPoint = Node( mDistance( start, end), 0, start );

    auto reconstructPath = [&]( Point endPt )
    {
        vector<Point> path;

        int cx, cy;
        Point tmpPt;

        cx = endPt.first;
        cy = endPt.second;

        while( start.first != cx || start.second != cy ){
            path.push_back( Point( cx, cy ) );
            tmpPt = cameFrom[cx][cy];
            cx = tmpPt.first;
            cy = tmpPt.second;
        }

        return path;
    };


    auto push = [&]( const Point& from, int x, int y, int step )
    {

        if( x >= mapWidth || x < 0 || y >= mapHeight || y < 0 ) return;
        if( bitmap[x][y] == obstacle ) return;

//        if( visited[x][y] && step > bitmap[x][y] ) return;
        if( visited[x][y] ) return;
        visited[x][y] = true;


        const Point pt( x, y );

        int distance = mDistance( pt, end );

        if( get<0>(clostestPoint) > distance ||
            (get<0>(clostestPoint) == distance && get<1>(clostestPoint) > step )
           ) {
                clostestPoint = Node( distance, step, pt );
        }

        // add to open list
        Q.push( Node( step + distance * 3/2, step, pt ) );
        cameFrom[x][y] = from;
    };

    // special case if start point is an obstacle ignore it
    if( bitmap[ start.first ][ start.second ] == obstacle ) {
        bitmap[ start.first ][ start.second ] = 0;

        push( start, start.first, start.second, 0 );

        bitmap[ start.first ][ start.second ] = obstacle;
    }
    else {
        push( start, start.first, start.second, 0 );
    }

    while( !Q.empty() ){
        ++ vc;

        const Node current = Q.top();

        const Point cpoint = std::get<2>( current );
        const int cscore = std::get<0>( current );
        const int cstep = std::get<1>( current );


        if( cpoint == end ){
            return reconstructPath( end );
        }

        Q.pop();

        push( cpoint, cpoint.first + 1, cpoint.second, cstep + 1 );
        push( cpoint, cpoint.first - 1, cpoint.second, cstep + 1 );
        push( cpoint, cpoint.first, cpoint.second + 1, cstep + 1 );
        push( cpoint, cpoint.first, cpoint.second - 1, cstep + 1 );
    }

    return reconstructPath( get<2>(clostestPoint ) );
}



// int main()
// {

    
//     mapWidth = 20;
//     mapHeight = 20;

//     const int ncase = 1;
//     const int nobstacle = 160;

//     double totalTime = 0;
//     int totalVisit = 0;
//     int vc;
//     auto answer = Astar( Point(0,0), Point(1, 3 ), vc );
//     for(int i = 0; i < answer.size(); i++)
//         cout << answer[i].first << " " << answer[i].second <<endl;
    

//     return 0;
// }