#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>

using namespace std;

void writeIn(vector<int>& vec)
{
    cout << "in: ";
    for(int ii = 0; ii < vec.size(); ii++)
    {
        cout << vec[ii] << ".0 ";
    }
    cout << endl;
}

void writeOut(vector<int>& vec)
{
    cout << "out: ";
    for(int ii = 0; ii < vec.size(); ii++)
    {
        cout << vec[ii] << ".0 ";
    }
    cout << endl;
}

int main()
{
    // Random training sets for ticTacToe -- 9 inputs and 6 outputs
    // Current board input, output is 0,0 0,1 0,2 1,0 1,1 1,2 2,0 2,1 2,2

    cout << "topology: 9 27 6" << endl;

    // 0.0 = BLANK, 1.0 = X, 2.0 = O
    // X:0 1 2 Y:0 1 2

    // Move 1
    vector<int> board = 
    {
        0, 0, 0,
        0, 1, 0,
        0, 0, 0,
    };
    vector<int> outputs = 
    {
        1, 0, 0, 1, 0, 0, 
    };


    // First random X placement
    int N = 10000;
    for(int ii = 0; ii < N; ii++)
    {
        board = {0,0,0,0,0,0,0,0,0};
        outputs = {0,0,0,0,0,0};
        int xPlace = rand() % 9;
        board[xPlace] = 1;

        // Find optimal move

        // Always bias toward center
        {
            switch (xPlace)
            {
                case 0: outputs = { 0, 0, 1, 0, 0, 1}; break;
                case 1: outputs = { 0, 1, 0, 0, 0, 1}; break;
                case 2: outputs = { 1, 0, 0, 0, 0, 1}; break;
                case 3: outputs = { 0, 0, 1, 0, 1, 0}; break;
                case 4: outputs = { 1, 0, 0, 1, 0, 0}; break;
                case 5: outputs = { 1, 0, 0, 0, 1, 0}; break;
                case 6: outputs = { 0, 0, 1, 1, 0, 0}; break;
                case 7: outputs = { 0, 1, 0, 1, 0, 0}; break;
                case 8: outputs = { 1, 0, 0, 1, 0, 0}; break;
            }
        }

        writeIn(board);
        writeOut(outputs);
    }
}
