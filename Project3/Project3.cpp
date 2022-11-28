#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream inputFile; 
    ofstream outputFile;
    string temp;
    int levels, rows, cols;
    vector<int> start, goal;
    vector<int> graphs;

    inputFile.open("input.txt", ios::in);
    if(inputFile.is_open()) {
        // For levels, rows, and columns
        getline(inputFile, temp);
        sscanf(temp.c_str(), "%d %d %d", &levels, &rows, &cols);

        // For start coordinates
        int x, y, z;
        getline(inputFile, temp);
        sscanf(temp.c_str(), "%d %d %d", &x, &y, &z);
        start.push_back(x); start.push_back(y); start.push_back(z);

        // For goal coordinates
        getline(inputFile, temp);
        sscanf(temp.c_str(), "%d %d %d", &x, &y, &z);
        goal.push_back(x); goal.push_back(y); goal.push_back(z);

        // 3D Adjacency matrix with 2 extra spaces for up and down levels
        // vector<vector<int> > graph(rows+2, vector<int>(cols+2));
        vector<vector<vector<string> > > graph(levels, vector<vector<string> >(cols+2, vector<string>(rows+2, 0)));

        // Reading from input file onto graph 
        // go through all the graphs
        for(int i = 0; i < levels; i++) {
            // Traverse through rows
            for(int j = 0; j < cols; j++) {
                // Traverse through columns
                for(int k = 0; k < rows; k++) {
                    // add to matrix and
                    // add a bunch of if statements checking each bit
                    string temp1, temp2; 
                    inputFile >> temp1; 
                    cout << temp1 << endl;
                    // cout << "graph[" << i << "][" << j << "][" << k << "]: " << graph[i][j][k] << endl;
                    
                }
            }
        }
        

        // while(!inputFile.eof()) {


        // }
    }

    inputFile.close();

    return 0;
}
