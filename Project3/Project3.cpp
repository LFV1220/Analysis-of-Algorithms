#include <bits/stdc++.h>
using namespace std;

int levels, rows, cols;
vector<int> start, goal;

void reader(ifstream &inputFile, vector<int> &start, vector<int> &goal)
{
    string temp;

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
}

void initialize(ifstream &inputFile, vector<vector<vector<string>>> &graph, vector<vector<vector<bool>>> &visited)
{
    for (int i = 0; i < levels; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            for (int k = 0; k < cols; k++)
            {
                // Adding direction info into matrix and initializing adjacency matrix
                inputFile >> graph[i][j][k];
                visited[i][j][k] = false;
            }
        }
    }
}

int dfs(int l, int r, int c, deque<string> &directions, vector<vector<vector<string>>> graph, vector<vector<vector<bool>>> &visited)
{

    visited[l][r][c] = true;

    // Checks if we are the goal coordinates and if so returns
    if (visited[goal[0]][goal[1]][goal[2]])
    {
        return 1;
    }

    string directionInfo = graph[l][r][c];
    int result = 0;

    // Goes through direction info (6 bit string)
    for (int i = 0; i < 6; i++)
    {
        if (directionInfo[i] == '1')
        {
            // Checks index of directionInfo for direction
            switch (i)
            {
            // When index is 1 call dfs recursively with that specific direction
            case (0):
                directions.push_back("N");
                if (!visited[l][r - 1][c])
                {
                    result = dfs(l, r - 1, c, directions, graph, visited);
                }

                break;
            case (1):
                directions.push_back("E");
                if (!visited[l][r][c + 1])
                {
                    result = dfs(l, r, c + 1, directions, graph, visited);
                }

                break;
            case (2):
                directions.push_back("S");
                if (!visited[l][r + 1][c])
                {
                    result = dfs(l, r + 1, c, directions, graph, visited);
                }
                break;
            case (3):
                directions.push_back("W");
                if (!visited[l][r][c - 1])
                {
                    result = dfs(l, r, c - 1, directions, graph, visited);
                }
                break;
            case (4):
                directions.push_back("U");
                if (!visited[l + 1][r][c])
                {
                    result = dfs(l + 1, r, c, directions, graph, visited);
                }
                break;
            case (5):
                directions.push_back("D");
                if (!visited[l - 1][r][c])
                {
                    result = dfs(l - 1, r, c, directions, graph, visited);
                }
                break;
            }

            if (result)
            {
                return 1;
            }
            else
            {
                directions.pop_back();
            }
        }
    }
    return 0;
}

int main()
{
    ifstream inputFile;
    ofstream outputFile;
    string temp;
    deque<string> directions;
    int count = 0;

    inputFile.open("input.txt", ios::in);
    outputFile.open("output.txt");

    if (inputFile.is_open())
    {
        reader(inputFile, start, goal);

        // Initialize graph and visited vector matrices
        vector<vector<vector<string>>> graph(levels, vector<vector<string>>(rows, vector<string>(cols)));
        vector<vector<vector<bool>>> visited(levels, vector<vector<bool>>(rows, vector<bool>(cols)));
        initialize(inputFile, graph, visited);

        // DFS with backtracking
        dfs(start[0], start[1], start[2], directions, graph, visited);

        // Iterate through the directions and output it
        while (!directions.empty())
        {
            outputFile << directions.front() << " ";
            directions.pop_front();
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
