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

// int mapWidth = 20;
// int mapHeight = 20;

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

vector<Point> Astar(char** bitmap,int mapWidth,int mapHeight, Point start, Point end, int& vc ){
    // char bitmap[20][20];
    bool visited[mWidth][mHeight];

    


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


    auto push = [&]( const Point& from, int x, int y, int step,int mapWidth,int mapHeight )
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

        push( start, start.first, start.second, 0,mapWidth,mapHeight );

        bitmap[ start.first ][ start.second ] = obstacle;
    }
    else {
        push( start, start.first, start.second, 0,mapWidth,mapHeight);
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

        push( cpoint, cpoint.first + 1, cpoint.second, cstep + 1 ,mapWidth,mapHeight );
        push( cpoint, cpoint.first - 1, cpoint.second, cstep + 1 ,mapWidth,mapHeight);
        push( cpoint, cpoint.first, cpoint.second + 1, cstep + 1 ,mapWidth,mapHeight);
        push( cpoint, cpoint.first, cpoint.second - 1, cstep + 1 ,mapWidth,mapHeight);
    }

    return reconstructPath( get<2>(clostestPoint ) );
}

char** create2DArray(unsigned height, unsigned width)
{
    char** array2D = 0;
    array2D = new char*[height];

    for (int h = 0; h < height; h++){
        array2D[h] = new char[width];
        for (int w = 0; w < width; w++) {
            // fill in some initial values
            // (filling in zeros would be more logic, but this is just for the example)
            array2D[h][w] = '-';
        }
    }

    return array2D;
}
// int main()
// {

//     int n = 20;
//     double totalTime = 0;
//     int vc;    
//     char**  b = create2DArray(n,n);

//     // b[0][1] = obstacle;
//     // b[1][1] = obstacle;

//         b[1][2] = 'b'; 
//         b[1][7] = 'b';

//         b[2][1] = 'b';
//         b[2][2] = 'b';
//         b[2][4] = 'b';
//         b[2][5] = 'b';
//         b[2][7] = 'b';
//         b[2][8] = 'b';

//         b[3][2] = 'b';
//         b[3][7] = 'b';

//         b[4][2] = 'b';
//         b[4][7] = 'b';

//         b[5][6] = 'b';

//         b[7][1] = 'b';
//         b[7][4] = 'b';
//         b[7][5] = 'b';
//         b[7][7] = 'b';
//         b[7][8] = 'b';

//         b[8][1] = 'b';

//         b[1][12] = 'b';    
//         b[1][17] = 'b';

//         b[2][10] = 'b';
//         b[2][11] = 'b';
//         b[2][14] = 'b';
//         b[2][15] = 'b';
//         b[2][17] = 'b';
//         b[2][18] = 'b';

//         b[3][12] = 'b';
//         b[3][17] = 'b';

//         b[4][12] = 'b';
//         b[4][17] = 'b';

//         b[5][16] = 'b';

//         b[7][11] = 'b';
//         b[7][14] = 'b';
//         b[7][15] = 'b';
//         b[7][17] = 'b';
//         b[7][18] = 'b';

//         b[8][11] = 'b';


//         b[11][2] = 'b';    
//         b[11][7] = 'b';

//         b[12][1] = 'b';
//         b[12][2] = 'b';
//         b[12][4] = 'b';
//         b[12][5] = 'b';
//         b[12][7] = 'b';
//         b[12][8] = 'b';

//         b[13][2] = 'b';
//         b[13][7] = 'b';

//         b[14][2] = 'b';
//         b[14][7] = 'b';

//         b[15][6] = 'b';

//         b[17][1] = 'b';
//         b[17][4] = 'b';
//         b[17][5] = 'b';
//         b[17][7] = 'b';
//         b[17][8] = 'b';

//         b[18][1] = 'b';

//         b[11][12] = 'b';   
//         b[11][17] = 'b';

//         b[12][10] = 'b';
//         b[12][11] = 'b';
//         b[12][14] = 'b';
//         b[12][15] = 'b';
//         b[12][17] = 'b';
//         b[12][18] = 'b';

//         b[13][12] = 'b';
//         b[13][17] = 'b';

//         b[14][12] = 'b';
//         b[14][17] = 'b';

//         b[15][16] = 'b';

//         b[17][11] = 'b';
//         b[17][14] = 'b';
//         b[17][15] = 'b';
//         b[17][17] = 'b';
//         b[17][18] = 'b';

//         b[18][11] = 'b';



//         b[3][1] = 's';
//         b[3][3] = 'e';

//     for (int i = 0; i < n; i++)  {
//         for(int j = 0;j<n; j++){
//             cout << b[i][j] << " ";
//         }
//         cout << endl;
//     }

//     char** bitmap = (char**)b;
//     auto answer = Astar(bitmap,n,n, Point(3,1), Point(3, 3 ), vc );
//     for(int i = 0; i < answer.size(); i++)
//         cout << "linha " << answer[i].first << " coluna " << answer[i].second <<endl;
    

//     return 0;
// }