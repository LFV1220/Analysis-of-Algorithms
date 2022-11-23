// COT4400 Project 2 - Group 11
// Description: Given an input file describing how to assemble one of two different kinds
// of robots, omnidroids and robotomata, and all of the intermediate products required to construct
// them, and you will need to compute the total cost required to make them.

// Names: Luis Vega, Het Thakkar, Ismaeel Rahman

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

// function declarations
void omniReader(int n, int m, ifstream *inputFile, vector<int> *i, vector<int> *j, vector<int> *parts);
void roboReader(int stages, ifstream *inputFile, vector<int> *i, vector<int> *j);
vector<int> roboHelper(int stages, vector<int> *i, vector<int> *j);
vector<int> robotomaton(int stages, vector<int> *i, vector<int> *j, vector<int> *soln);
int omniHelper(int n, int m, vector<int> *i, vector<int> *j, vector<int> *parts);
int omnidroid(int n, int m, vector<int> *i, vector<int> *j, vector<int> *parts, vector<int> *soln);

int main()
{
    ifstream inputFile;
    ofstream outputFile;
    string robotType;   // first line of input telling us which
    string robotSpec;   // to get n and m from input
    string inputAmount; // how many types of input (1 or 2)
    int n, m, stages;
    vector<int> i, j, parts;

    inputFile.open("input.txt", ios::in);
    outputFile.open("output.txt");

    if (inputFile.is_open())
    {
        // Takes the first line to determine whether we have 1 or 2 types of robots for inputs/outputs
        getline(inputFile, inputAmount);

        // Checks if we have 1 input amount
        if (inputAmount.compare("1") == 0)
        {
            getline(inputFile, robotType);

            while (!inputFile.eof())
            {
                // Checks whether the robot type is omnidroid or robotomaton and scans the inputFile
                // and sends it to the respective reader function
                if (robotType.compare("omnidroid") == 0)
                {
                    getline(inputFile, robotSpec);
                    sscanf(robotSpec.c_str(), "%d %d", &n, &m);
                    omniReader(n, m, &inputFile, &i, &j, &parts);
                }
                else if (robotType.compare("robotomaton") == 0)
                {
                    getline(inputFile, robotSpec);
                    sscanf(robotSpec.c_str(), "%d", &stages);
                    roboReader(stages, &inputFile, &i, &j);
                }
            }

            // Checks for robot type in order to output solution to outputFile
            if (robotType.compare("omnidroid") == 0)
            {
                int solution = omniHelper(n, m, &i, &j, &parts);
                cout << "Output in \"output.txt\"" << endl;
                outputFile << solution << endl;
            }
            else if (robotType.compare("robotomaton") == 0)
            {
                int total = 0;
                vector<int> solution = roboHelper(stages, &i, &j);

                // Adding all the values from the soln vector to give us the output in the outputFile
                for (int a = 0; a < solution.size(); a++)
                {
                    total += solution.at(a);
                }
                cout << "Output in \"output.txt\"" << endl;
                outputFile << total << endl;
            }

            inputFile.close();
        }
        // Checks if we have 2 input amounts
        else if (inputAmount.compare("2") == 0)
        {
            vector<int> i1, j1;
            getline(inputFile, robotType);

            while (!inputFile.eof())
            {
                // Checks for robot type
                if (robotType.compare("omnidroid") == 0)
                {
                    getline(inputFile, robotSpec);

                    // Checks if robot type changed, if it does we change robot type and
                    // go to the next iteration of loop
                    if (robotSpec.compare("robotomaton") == 0)
                    {
                        robotType = robotSpec;
                        continue;
                    }

                    // scans input into n and m and sends it to the reader function
                    sscanf(robotSpec.c_str(), "%d %d", &n, &m);
                    omniReader(n, m, &inputFile, &i, &j, &parts);
                }
                else if (robotType.compare("robotomaton") == 0)
                {
                    getline(inputFile, robotSpec);

                    // Checks if robot type changed, if it does we change robot type and
                    // go to the next iteration of loop
                    if (robotSpec.compare("omnidroid") == 0)
                    {
                        robotType = robotSpec;
                        continue;
                    }
                    sscanf(robotSpec.c_str(), "%d", &stages);
                    roboReader(stages, &inputFile, &i1, &j1);
                }
            }

            // Checks for robot type
            if (robotType.compare("omnidroid") == 0)
            {
                int total1 = 0;
                vector<int> solution1 = roboHelper(stages, &i, &j);
                int solution2 = omniHelper(n, m, &i, &j, &parts);

                // Summing up values from the soln vector for output
                for (int a = 0; a < solution1.size(); a++)
                {
                    total1 += solution1.at(a);
                }
                cout << "Output in \"output.txt\"" << endl;

                // Switch output order to it into correct order
                outputFile << total1 << endl;
                outputFile << solution2 << endl;
            }
            else if (robotType.compare("robotomaton") == 0)
            {
                int total2 = 0;
                int solution1 = omniHelper(n, m, &i, &j, &parts);
                vector<int> solution2 = roboHelper(stages, &i1, &j1);

                // Summing up values from the soln vector for output
                for (int a = 0; a < solution2.size(); a++)
                {
                    total2 += solution2.at(a);
                }
                cout << "Output in \"output.txt\"" << endl;

                // Switch output order to it into correct order
                outputFile << solution1 << endl;
                outputFile << total2 << endl;
            }

            inputFile.close();
            outputFile.close();
        }
    }

    return 0;
}

// Reads from inputFile into vectors i, j, and parts as well as into integers n and m
void omniReader(int n, int m, ifstream *inputFile, vector<int> *i, vector<int> *j, vector<int> *parts)
{
    string temp;
    int ncount = 0;
    int mcount = 0;

    // adding next m lines into n and m vectors
    while (mcount < m)
    {
        int x, y;
        getline(*inputFile, temp);
        sscanf(temp.c_str(), "%d %d", &x, &y);
        i->push_back(x);
        j->push_back(y);

        mcount++;
    }

    // adding n lines (after m lines) into parts vector
    while (ncount < n && mcount == m)
    {
        int z;
        getline(*inputFile, temp);
        sscanf(temp.c_str(), "%d", &z);
        parts->push_back(z);

        ncount++;
    }
}

// Reads from inputFile into vectors i and j
void roboReader(int stages, ifstream *inputFile, vector<int> *i, vector<int> *j)
{
    string temp;
    int stageCount = 0;

    while (stageCount < stages)
    {
        int x, y;
        getline(*inputFile, temp);
        sscanf(temp.c_str(), "%d %d", &x, &y);
        i->push_back(x);
        j->push_back(y);

        stageCount++;
    }
}

// Initializes soln vector (to all zeros) and calls omnidroid function
int omniHelper(int n, int m, vector<int> *i, vector<int> *j, vector<int> *parts)
{
    vector<int> soln;

    for (int a = 0; a < n; a++)
    {
        soln.push_back(0);
    }

    return omnidroid(n, m, i, j, parts, &soln);
}

// Computes the total sprocket count into soln vector given integers n and m as well as vectors i,
// j, parts, and soln and then returns the last index of the soln vector
int omnidroid(int n, int m, vector<int> *i, vector<int> *j, vector<int> *parts, vector<int> *soln)
{
    int x = i->at(m - 1);
    int y = j->at(m - 1);

    // Add into soln vector if the value at this index is 0 (not worked on yet)
    if (soln->at(n - 1) == 0)
    {
        // Checks whether we are at first index of m
        if (m - 1 == 0)
        {
            soln->at(y) = parts->at(x) + parts->at(y);
            parts->at(y) = soln->at(y);
        }
        // Otherwise we recursively call the omnidroid function and add the parts to solution,
        // while also modifying the parts vector
        else
        {
            omnidroid(n, m - 1, i, j, parts, soln);
            soln->at(y) = parts->at(x) + parts->at(y);
            parts->at(y) = soln->at(y);
        }
    }

    return soln->at(n - 1);
}

// Initializes soln vector (to all zeros) and calls robotomaton function
vector<int> roboHelper(int stages, vector<int> *i, vector<int> *j)
{
    vector<int> soln;

    for (int a = 0; a < stages; a++)
    {
        soln.push_back(0);
    }

    return robotomaton(stages, i, j, &soln);
}

// Computes the total sprocket count into soln vector given integer stages as well as vectors i,
// j, and soln and returns a vector that is summed in main
vector<int> robotomaton(int stages, vector<int> *i, vector<int> *j, vector<int> *soln)
{
    int x = i->at(stages - 1);
    int y = j->at(stages - 1);

    // Add into soln vector if the value at this index is 0 (not worked on yet)
    if (soln->at(stages - 1) == 0)
    {
        // Checks if we are at the first index of stages
        if (stages - 1 == 0)
        {
            soln->at(stages - 1) = x;
        }
        // Checks if j at this index is 0 and recursively calls the robotomaton function
        else if (y == 0)
        {
            robotomaton(stages - 1, i, j, soln);
            soln->at(stages - 1) += x;
        }
        // Checks if j at this index is 1 and recursively calls the robotomaton function
        else if (y == 1)
        {
            robotomaton(stages - 1, i, j, soln);
            soln->at(stages - 1) += x + robotomaton(stages - 1, i, j, soln).at(stages - 2);
        }
        // Otherwise we recursively call robotomaton and add i at this index into soln,
        // then also uses j to determine how many previous solutions to add on to soln
        else
        {
            robotomaton(stages - 1, i, j, soln);
            soln->at(stages - 1) += x;

            if (y != 0)
            {
                for (int b = stages - 2; b >= y; b--)
                {
                    soln->at(stages - 1) += soln->at(b);
                    if (j->at(b) == 1)
                    {
                        soln->at(stages - 1) += i->at(b - 1);
                    }
                }
            }
        }
    }

    return *soln;
}
