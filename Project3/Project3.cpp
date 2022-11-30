#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Graph
{
public:
    int levels, rows, columns;
    bool start, goal, visited;
    string directionInfo;

    // Adjacency list based gaph
    vector<Graph> graph;
};

void pathdfs(int levels, int rows, int cols, stack<Graph> moves, vector<vector<vector<Graph>>> graph);

int main()
{
    ifstream inputFile;
    ofstream outputFile;
    string temp;
    int levels, rows, cols;
    vector<int> start, goal;

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
                    graph[i][j][k].columns = cols;

                    inputFile >> graph[i][j][k].directionInfo;
                    graph[i][j][k].start = graph[i][j][k].goal = graph[i][j][k].visited = false;
                    // cout << "graph[" << i << "][" << j << "][" << k << "]: " << graph[i][j][k] << endl;
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

        stack<Graph> moves;
        // call recursive function (pathdfs)
        pathdfs(goal[0], goal[1], goal[2], moves, graph);

        inputFile.close();
        return 0;
    }
}

void pathdfs(int l, int r, int c, stack<Graph> moves, vector<vector<vector<Graph>>> graph)
{

    int levels = l;
    int rows = r;
    int cols = c;

    cout << "levels: " << l << endl;
    cout << "rows: " << r << endl;
    cout << "cols: " << c << endl;

    graph[l][r][c].visited = true;
    cout << graph[l][r][c].visited << endl;
    moves.push(graph[l][r][c]);

    if (graph[l][r][c].start)
    {
        while (!moves.empty())
        {

            cout << moves.top().levels << " " << moves.top().rows << " " << moves.top().columns << endl;
            // maybe print direction here somehow
            // for (int z = 0; z < 6; z++)
            // {
            //     // cout << graph[l][r][c].directionInfo[z] << endl;
            //     if (graph[l][r][c].directionInfo[z] == '1')
            //     {
            //         // North direction
            //         if (z == 0)
            //         {
            //             cout << "n" << endl;
            //         }
            //         // East direction
            //         else if (z == 1)
            //         {
            //             cout << "e" << endl;
            //         }
            //         // South direction
            //         else if (z == 2)
            //         {
            //             cout << "s" << endl;
            //         }
            //         // West direction
            //         else if (z == 3)
            //         {
            //             cout << "w" << endl;
            //         }
            //         // Up
            //         else if (z == 4)
            //         {
            //             cout << "u" << endl;
            //         }
            //         // Down
            //         else if (z == 5)
            //         {
            //             cout << "d" << endl;
            //         }
            //     }
            // }

            moves.pop();
        }
    }

    for (int i = 0; i < graph[l][r][c].graph.size(); i++)
    {
        levels = graph[l][r][c].graph[i].levels;
        rows = graph[l][r][c].graph[i].rows;
        cols = graph[l][r][c].graph[i].columns;

        if (!graph[levels][rows][cols].visited)
        {
            pathdfs(levels, rows, cols, moves, graph);
        }
    }
}