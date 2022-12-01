#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// Enumerate the directions/moves
enum
{
    N,
    E,
    S,
    W,
    U,
    D
};

struct Vertex
{
    int x;
    int y;
    int z;
    int cellNumber;
    bool start;
    bool end;
    bool visited;
    string data;
    vector<Vertex> adjList;
    vector<Vertex> charList;
};

void BFS(int sizeX, int z, int x, int y, queue<Vertex> moveQ, stack<int> directionStack, vector<vector<vector<Vertex>>> maze);
void BFSBT(int sizeX, int endX, int endY, int endZ, int z, int x, int y, queue<Vertex> moveQ, stack<int> directionStack, vector<vector<vector<Vertex>>> maze);

int main()
{
    int sizeX, sizeY, sizeZ;
    int startX, startY, startZ;
    int endX, endY, endZ;
    int volume;
    int cellCount = 0;
    stack<Vertex> moveStack;
    stack<int> directionStack;

    // Open input.txt
    string fileLine;
    ifstream inputFile;
    inputFile.open("input.txt");

    // Gets the size of the dimensions of the maze
    inputFile >> sizeZ;
    inputFile >> sizeX;
    inputFile >> sizeY;

    // Gets the start coordinates of the maze
    inputFile >> startZ;
    inputFile >> startX;
    inputFile >> startY;

    // Gets the end coordinates of the maze
    inputFile >> endZ;
    inputFile >> endX;
    inputFile >> endY;

    // Gets the total number of cells in the maze
    volume = sizeX * sizeY * sizeZ;

    // Declare a 3D vector
    vector<vector<vector<Vertex>>> maze(sizeZ, vector<vector<Vertex>>(sizeX, vector<Vertex>(sizeY)));

    // Populate every cell in the maze with a number [0...n] where n is the
    // number of cells in the maze
    for (int k = 0; k < sizeZ; k++)
    {
        for (int i = 0; i < sizeX; i++)
        {
            for (int j = 0; j < sizeY; j++)
            {
                // Assign coordinates
                maze[k][i][j].z = k;
                maze[k][i][j].x = i;
                maze[k][i][j].y = j;

                // Give each cell a direction string
                inputFile >> maze[k][i][j].data;

                // Give each cell a cell number
                maze[k][i][j].cellNumber = cellCount;
                cellCount++;

                // Mark each node not visited
                maze[k][i][j].visited = false;

                // Mark each node start/end as false
                maze[k][i][j].start = false;
                maze[k][i][j].end = false;
            }
        }
    }

    // Mark the beginning and end cells of the maze
    maze[startZ][startX][startY].start = true;
    maze[endZ][endX][endY].end = true;

    // for (int k = 0; k < sizeZ; k++)
    // {
    //     for (int i = 0; i < sizeX; i++)
    //     {
    //         for (int j = 0; j < sizeY; j++)
    //         {
    //             cout << "(" << maze[k][i][j].z << ", ";
    //             cout << maze[k][i][j].x << ", ";
    //             cout << maze[k][i][j].y << ")";
    //             cout << " = ";
    //             for (int l = 0; l < 6; l++)
    //             {
    //                 cout << maze[k][i][j].data[l];
    //             }
    //             cout << "\tCell Number: " << maze[k][i][j].cellNumber;
    //             cout << endl;
    //         }
    //     }
    // }

    int movePos;
    int moveDirection;

    // Now we need to go through each cell and get the adjacency list from the
    // binary string that holds the directions -> data
    for (int k = 0; k < sizeZ; k++)
    {
        for (int i = 0; i < sizeX; i++)
        {
            for (int j = 0; j < sizeY; j++)
            {
                for (int l = 0; l < 6; l++)
                {
                    if (maze[k][i][j].data[l] == '1')
                    {
                        movePos = l;
                        switch (movePos)
                        {
                        case 0:
                            moveDirection = N;
                            maze[k][i][j].adjList.push_back(maze[k][i - 1][j]);
                            break;
                        case 1:
                            moveDirection = E;
                            maze[k][i][j].adjList.push_back(maze[k][i][j + 1]);
                            break;
                        case 2:
                            moveDirection = S;
                            maze[k][i][j].adjList.push_back(maze[k][i + 1][j]);
                            break;
                        case 3:
                            moveDirection = W;
                            maze[k][i][j].adjList.push_back(maze[k][i][j - 1]);
                            break;
                        case 4:
                            moveDirection = U;
                            maze[k][i][j].adjList.push_back(maze[k + 1][i][j]);
                            break;
                        case 5:
                            moveDirection = D;
                            maze[k][i][j].adjList.push_back(maze[k - 1][i][j]);
                            break;
                        default:
                            break;
                        }
                    }
                    movePos = 0;
                }
            }
        }
    }

    queue<Vertex> moveQ;
    // DFS(sizeX, endZ, endX, endY, moveStack, directionStack, maze);
    BFS(sizeX, startZ, startX, startY, moveQ, directionStack, maze);
    // BFSBT(sizeX, endX, endY, endZ, startZ, startX, startY, moveQ, directionStack, maze);

    inputFile.close();
    return 0;
}

void BFS(int sizeX, int z, int x, int y, queue<Vertex> moveQ, stack<int> directionStack, vector<vector<vector<Vertex>>> maze)
{
    int tempZ = z;
    int tempX = x;
    int tempY = y;
    // cout << maze[z][x][y].z << " ";
    // cout << maze[z][x][y].x << " ";
    // cout << maze[z][x][y].y << endl;

    // Mark the passed vertex into DFS function as visited and push onto stack

    // trying to backtrack but not working
    moveQ.push(maze[z][x][y]);

    maze[z][x][y].visited = true;

    if (maze[z][x][y].end == true)
    {
        while (!moveQ.empty())
        {
            int prevCellNumber = moveQ.front().cellNumber;
            // cout << "cell number: " << moveQ.front().cellNumber << endl;
            // cout << "(" << moveQ.front().z;
            // cout << ", " << moveQ.front().x;
            // cout << ", " << moveQ.front().y;
            // cout << ")" << endl;
            moveQ.pop();

            int currentCellNumber = moveQ.front().cellNumber;

            if (currentCellNumber == prevCellNumber - 1)
            {
                cout << "W ";
            }
            else if (currentCellNumber == prevCellNumber + 1)
            {
                cout << "E ";
            }
            else if (currentCellNumber == prevCellNumber - sizeX)
            {
                cout << "N ";
            }
            else if (currentCellNumber == prevCellNumber + sizeX)
            {
                cout << "S ";
            }
            else if (currentCellNumber == prevCellNumber + (sizeX * sizeX))
            {
                cout << "U ";
            }
            else if (currentCellNumber == prevCellNumber - (sizeX * sizeX))
            {
                cout << "D ";
            }
        }
    }

    // Let's get the appropriate size for the loop
    int loopSize;
    loopSize = maze[z][x][y].adjList.size();

    // Traverse the adjacencies of the passed in vertex
    for (int i = 0; i < loopSize; i++)
    {
        tempZ = maze[z][x][y].adjList[i].z;
        tempX = maze[z][x][y].adjList[i].x;
        tempY = maze[z][x][y].adjList[i].y;
        // cout << tempZ << " " << tempX << " " << tempY << endl;

        // If the adjacent vertex is unvisited, recurse BFS()
        if (maze[tempZ][tempX][tempY].visited == false)
        {
            BFS(sizeX, tempZ, tempX, tempY, moveQ, directionStack, maze);
        }
    }
}

// Trying to implement BFS with backtracking :(
void BFSBT(int sizeX, int endX, int endY, int endZ, int z, int x, int y, queue<Vertex> moveQ, stack<int> directionStack, vector<vector<vector<Vertex>>> maze)
{
    int tempZ = z;
    int tempX = x;
    int tempY = y;
    queue<Vertex> path;
    Vertex node;
    // cout << maze[z][x][y].z << " ";
    // cout << maze[z][x][y].x << " ";
    // cout << maze[z][x][y].y << endl;

    // Mark the passed vertex into DFS function as visited and push onto stack
    maze[z][x][y].visited = true;
    moveQ.push(maze[z][x][y]);

    while (!moveQ.empty())
    {
        cout << "while !empty loop start" << endl;
        path.push(moveQ.front());
        moveQ.pop();

        // this part might be why its not working
        node = path.back();
        if (node.end)
        {
            // return path
            cout << "path found" << endl;
            return;
        }

        int loopSize;
        loopSize = maze[z][x][y].adjList.size();
        for (int i = 0; i < loopSize; i++)
        {
            cout << "for loop for adjacent vertex runs" << endl;
            tempZ = maze[z][x][y].adjList[i].z;
            tempX = maze[z][x][y].adjList[i].x;
            tempY = maze[z][x][y].adjList[i].y;

            queue<Vertex> new_path = path;
            new_path.push(maze[z][x][y].adjList[i]);
            if (!maze[z][x][y].visited)
            {
                moveQ.push(new_path.back());
            }

            cout << "recursion call" << endl;
            BFSBT(sizeX, endX, endY, endZ, tempZ, tempX, tempY, moveQ, directionStack, maze);
        }
    }
}