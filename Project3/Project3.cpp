#include <iostream>
#include <fstream>
#include <stdio.h>
#include <queue>
#include <string>
#include <vector>

using namespace std;

vector<string> directions = {"N", "E", "S", "W", "U", "D"};

class Graph
{
public:
    int levels, rows, columns, coordCount;
    bool start, goal, visited;
    string directionInfo;

    // Adjacency list based gaph
    vector<Graph> graph;
};

void bfs(int constRowSize, int constColSize, int levels, int rows, int cols, queue<Graph> moves, vector<vector<vector<Graph>>> graph, vector<string> *soln);
// void BFSBT(int constantRowSize, int endX, int endY, int endZ, int l, int r, int c, queue<Graph> moves, vector<vector<vector<Graph>>> graph); // not working :(

int main()
{
    ifstream inputFile;
    ofstream outputFile;
    string temp;
    int levels, rows, cols;
    vector<int> start, goal;
    queue<Graph> moves;
    vector<string> soln;
    int count = 0;

    inputFile.open("input.txt", ios::in);
    outputFile.open("output.txt");

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
        // Traverse through levels
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
                    graph[i][j][k].start = graph[i][j][k].goal = graph[i][j][k].visited = false;
                    count++;
                }
            }
        }

        // Marking the start and goal as visited
        graph[start[0]][start[1]][start[2]].start = graph[goal[0]][goal[1]][goal[2]].goal = true;

        // Traverse through levels
        for (int i = 0; i < levels; i++)
        {
            // Traverse through rows
            for (int j = 0; j < rows; j++)
            {
                // Traverse through columns
                for (int k = 0; k < cols; k++)
                {
                    // Traverse each bit of 6 bit direction information
                    for (int l = 0; l < 6; l++)
                    {
                        // If 1, push corresponding direction into adjacency list
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

        bfs(rows, cols, start[0], start[1], start[2], moves, graph, &soln);
        // BFSBT(rows, goal[0], goal[1], goal[2], start[0],start[1],start[2], moves, graph);

        // Output
        for (int i = 0; i < soln.size(); i++)
        {
            outputFile << soln[i] << " ";
        }

        inputFile.close();
        outputFile.close();

        return 0;
    }
}

// Recursive breath-first search algorithm that returns all paths (from start coordinates to goal coordinates)
void bfs(int constRowSize, int constColSize, int l, int r, int c, queue<Graph> moves, vector<vector<vector<Graph>>> graph, vector<string> *soln)
{
    int levels = l;
    int rows = r;
    int cols = c;
    Graph node;

    if (graph[l][r][c].start)
    {
        soln->push_back("START");
        cout << "START ";
    }

    // Set the graph at these coordinates as visited and push to queue
    graph[l][r][c].visited = true;
    moves.push(graph[l][r][c]);

    // If we are at the goal coordinates
    if (graph[l][r][c].goal)
    {
        // Loops through queue until empty
        while (!moves.empty())
        {
            int coordCount1 = moves.front().coordCount;
            moves.pop();
            int coordCount2 = moves.front().coordCount;

            if (coordCount2 == coordCount1 - 1)
            {
                soln->push_back(directions[3]);
                cout << "W ";
            }
            else if (coordCount2 == coordCount1 + 1)
            {
                soln->push_back(directions[1]);
                cout << "E ";
            }
            else if (coordCount2 == coordCount1 - constRowSize)
            {
                soln->push_back(directions[0]);
                cout << "N ";
            }
            else if (coordCount2 == coordCount1 + constRowSize)
            {
                soln->push_back(directions[2]);
                cout << "S ";
            }
            else if (coordCount2 == coordCount1 + (constRowSize * constColSize))
            {
                soln->push_back(directions[4]);
                cout << "U ";
            }
            else if (coordCount2 == coordCount1 - (constRowSize * constColSize))
            {
                soln->push_back(directions[5]);
                cout << "D ";
            }
        }
    }
    else
    {
        // Looping through adjacent vertices
        for (int i = 0; i < graph[l][r][c].graph.size(); i++)
        {
            // Changing coordinates to adjacent vertex
            levels = graph[l][r][c].graph[i].levels;
            rows = graph[l][r][c].graph[i].rows;
            cols = graph[l][r][c].graph[i].columns;

            // If adjacent vertex isn't visited, visit them
            if (!graph[levels][rows][cols].visited)
            {
                bfs(constRowSize, constColSize, levels, rows, cols, moves, graph, soln);
            }
        }
    }

    // Print "END" after every path
    if (graph[l][r][c].goal)
    {
        soln->push_back("END\n ");
        cout << "END" << endl;
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