#include <iostream>
#include <cstring>

#include <omp.h>
using namespace std;


/*

https://www.techiedelight.com/print-possible-knights-tours-chessboard/
https://www.techiedelight.com/chess-knight-problem-find-shortest-path-source-destination/
https://oeis.org/A165134


On an 8 × 8 board, there are exactly 26,534,728,821,064 directed closed tours
 (i.e. two tours along the same path that travel in opposite directions are counted separately, as are rotations and reflections).
The number of undirected closed tours is half this number, since every tour can be traced in reverse. 
There are 9,862 undirected closed tours on a 6 × 6 board.
The numbers of all directed tours (open and closed) on an n × n board for n = 1, 2, … are:
    1; 0; 0; 0; 1,728; 6,637,920; 165,575,218,320; 19,591,828,170,979,904. (sequence A165134 in the OEIS).
*/

// N x N chessboard
#define N 5

// Below arrays details all 8 possible movements for a knight.
// It is important to avoid changing sequence of below arrays
int row[] = { 2, 1, -1, -2, -2, -1,  1,  2 , 2 };
int col[] = { 1, 2,  2,  1, -1, -2, -2, -1, 1 };

// Check if (x, y) is valid chess board coordinates
// Note that a knight cannot go out of the chessboard
bool isValid(int x, int y)
{
	if (x < 0 || y < 0 || x >= N || y >= N)
		return false;

	return true;
}

// Recursive function to perform the Knight's tour using backtracking
void KnightTour(int visited[N][N], int x, int y, int pos)
{
	// mark current square as visited	
	visited[x][y] = pos;
	
	// if all squares are visited, print the solution
	if (pos >= N*N)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				cout << visited[i][j] << " ";
			cout << endl;
		}
		cout << endl;
		// backtrack before returning
		visited[x][y] = 0;
		return;
	}

	// check for all 8 possible movements for a knight
	// and recur for each valid movement
    //#pragma omp parallel for firstprivate(visited, x, y, pos, row, col)
	for (int k = 0; k < 8; k++)
	{
		// Get the new position of Knight from current
		// position on chessboard
		int newX = x + row[k];
		int newY = y + col[k];

		// if new position is a valid and not visited yet
		if (isValid(newX, newY) && !visited[newX][newY])
			KnightTour(visited, newX, newY, pos + 1);
	}

	// backtrack from current square and remove it from current path
	visited[x][y] = 0;
}

/*
// Print all Possible Knight's Tours in a chessboard
int main()
{
	// visited[][] serves two purpose -
	// 1. It keep track of squares involved the Knight's tour.
	// 2. It stores the order in which the squares are visited
	int visited[N][N];
	
	// initialize visited[][] by 0 (unvisited)
	memset(visited, 0, sizeof visited);

	int pos = 1;
	
	// start knight tour from corner square (0, 0)
	KnightTour(visited, 0, 0, pos);
	
	return 0;
}
*/

int main()
{
	// visited[][] serves two purpose -
	// 1. It keep track of squares involved the Knight's tour.
	// 2. It stores the order in which the squares are visited
    int i,j;
    #pragma omp parallel for private(i, j)
    for(i=0; i<5;i++){
        //#pragma omp parallel for firstprivate(i, j)
        for(j=0; j<5; j++){
            int visited[N][N];
	
	        // initialize visited[][] by 0 (unvisited)
	        memset(visited, 0, sizeof visited);

	        int pos = 1;
	
	        // start knight tour from corner square (0, 0)
	        KnightTour(visited, i, j, pos);
        }
    }
	
	
	return 0;
}