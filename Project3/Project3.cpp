#include <iostream>
#include <fstream>
#include <stdio.h>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class Graph
{
public:
    int levels, rows, columns, coordCount;
    bool start, goal, visited;
    string directionInfo;

    // Adjacency list based gaph
    vector<Graph> graph;
};

void bfs(int constantRowSize, int levels, int rows, int cols, queue<Graph> moves, vector<vector<vector<Graph>>> graph);
void BFSBT(int constantRowSize, int endX, int endY, int endZ, int l, int r, int c, queue<Graph> moves, vector<vector<vector<Graph>>> graph);

int main()
{
    ifstream inputFile;
    ofstream outputFile;
    string temp;
    int levels, rows, cols;
    vector<int> start, goal;
    int count = 0;

    inputFile.open("input.txt", ios::in);
    if (inputFile.is_open())
    {
        // For levels, rows, and columns
        getline(inputFile, temp);
        sscanf(temp.c_str(), "%d %d %d", &levels, &rows, &cols);

        // For start coordinates
        int x, y, z;
        getline(inputFile, temp);
        sscanf(temp.c_str(), "%d %d %d", &x, &y, &z);
        start = {x, y, z};

        // For goal coordinates
        getline(inputFile, temp);
        sscanf(temp.c_str(), "%d %d %d", &x, &y, &z);
        goal = {x, y, z};

        // Graph matrix
        vector<vector<vector<Graph>>> graph(levels, vector<vector<Graph>>(rows, vector<Graph>(cols)));

        // Reading from input file onto graph
        for (int i = 0; i < levels; i++)
        {
            // Traverse through rows
            for (int j = 0; j < rows; j++)
            {
                // Traverse through columns
                for (int k = 0; k < cols; k++)
                {
                    graph[i][j][k].levels = i;
                    graph[i][j][k].rows = j;
                    graph[i][j][k].columns = k;
                    graph[i][j][k].coordCount = count;
                    
                    inputFile >> graph[i][j][k].directionInfo;
                    // cout << graph[i][j][k].coordCount << " " << graph[i][j][k].directionInfo << endl;
                    graph[i][j][k].start = graph[i][j][k].goal = graph[i][j][k].visited = false;
                    count++;
                }
            }
        }

        graph[start[0]][start[1]][start[2]].start = graph[goal[0]][goal[1]][goal[2]].goal = true;
        int direction;

        for (int i = 0; i < levels; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                for (int k = 0; k < cols; k++)
                {
                    for (int l = 0; l < 6; l++)
                    {
                        if (graph[i][j][k].directionInfo[l] == '1')
                        {
                            // North direction
                            if (l == 0)
                            {
                                graph[i][j][k].graph.push_back(graph[i][j - 1][k]);
                            }
                            // East direction
                            else if (l == 1)
                            {
                                graph[i][j][k].graph.push_back(graph[i][j][k + 1]);
                            }
                            // South direction
                            else if (l == 2)
                            {
                                graph[i][j][k].graph.push_back(graph[i][j + 1][k]);
                            }
                            // West direction
                            else if (l == 3)
                            {
                                graph[i][j][k].graph.push_back(graph[i][j][k - 1]);
                            }
                            // Up
                            else if (l == 4)
                            {
                                graph[i][j][k].graph.push_back(graph[i + 1][j][k]);
                            }
                            // Down
                            else if (l == 5)
                            {
                                graph[i][j][k].graph.push_back(graph[i - 1][j][k]);
                            }
                        }
                    }
                }
            }
        }

        queue<Graph> moves;
        // call recursive function (pathbfs)
        bfs(rows, start[0],start[1],start[2], moves, graph);
        // BFSBT(rows, goal[0], goal[1], goal[2], start[0],start[1],start[2], moves, graph);

        inputFile.close();
        return 0;
    }
}

void bfs(int constantRowSize, int l, int r, int c, queue<Graph> moves, vector<vector<vector<Graph>>> graph)
{
    int levels = l;
    int rows = r;
    int cols = c;
    Graph node;
    // cout << graph[l][r][c].levels << " ";
    // cout << graph[l][r][c].rows << " ";
    // cout << graph[l][r][c].columns << endl;

    graph[l][r][c].visited = true;

    moves.push(graph[l][r][c]);

    if (graph[l][r][c].goal)
    {
        while (!moves.empty())
        {
            // node = moves.back();
            // if(node.goal) {
            //     cout << "path found" << endl;
            //     return;
            // }

            int coordCount1 = moves.front().coordCount;
            moves.pop();
            int coordCount2 = moves.front().coordCount;

            if (coordCount2 == coordCount1 - 1)
            {
                cout << "W ";
            }
            else if (coordCount2 == coordCount1 + 1)
            {
                cout << "E ";
            }
            else if (coordCount2 == coordCount1 - constantRowSize)
            {
                cout << "N ";
            }
            else if (coordCount2 == coordCount1 + constantRowSize)
            {
                cout << "S ";
            }
            else if (coordCount2 == coordCount1 + (constantRowSize * constantRowSize))
            {
                cout << "U ";
            }
            else if (coordCount2 == coordCount1 - (constantRowSize * constantRowSize))
            {
                cout << "D ";
            }

            // stop here but not stopping completely

        }
    }

    if(graph[l][r][c].goal) {
        cout << "END" << endl;
        return;
    }

    // fix here (still going after END)
    for (int i = 0; i < graph[l][r][c].graph.size(); i++)
    {
        levels = graph[l][r][c].graph[i].levels;
        rows = graph[l][r][c].graph[i].rows;
        cols = graph[l][r][c].graph[i].columns;

        if (!graph[levels][rows][cols].visited)
        {
            bfs(constantRowSize, levels, rows, cols, moves, graph);
        }
    }
}


// Trying to implement BFS with backtracking, not working :(
// void BFSBT(int constantRowSize, int endX, int endY, int endZ, int l, int r, int c, queue<Graph> moves, vector<vector<vector<Graph>>> graph)
// {
//     int levels = l;
//     int rows = r;
//     int cols = c;
//     queue<Graph> path;
//     Graph node;
//     // cout << maze[z][x][y].z << " ";
//     // cout << maze[z][x][y].x << " ";
//     // cout << maze[z][x][y].y << endl;

//     // Mark the passed vertex into DFS function as visited and push onto stack
//     graph[l][r][c].visited = true;
//     moves.push(graph[l][r][c]);

//     while (!moves.empty())
//     {
//         cout << "while !empty loop start" << endl;
//         path.push(moves.front());
//         moves.pop();

//         // this part might be why its not working
//         node = path.back();
//         if (node.goal)
//         {
//             // return path
//             cout << "path found" << endl;
//             return;
//         }


//         for (int i = 0; i < graph[l][r][c].graph.size(); i++)
//         {
//             cout << "for loop for adjacent vertex runs" << endl;
//             levels = graph[l][r][c].graph[i].levels;
//             rows = graph[l][r][c].graph[i].rows;
//             cols = graph[l][r][c].graph[i].columns;

//             queue<Graph> new_path = path;
//             new_path.push(graph[l][r][c].graph[i]);
//             if (!graph[l][r][c].visited)
//             {
//                 moves.push(new_path.back());
//             }

//             cout << "recursion call" << endl;
//             BFSBT(constantRowSize, endX, endY, endZ, levels, rows, cols, moves, graph);
//         }
//     }
// }