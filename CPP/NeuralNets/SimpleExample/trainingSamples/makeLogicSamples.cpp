#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;

void writeIn(ofstream& myfile, vector<int>& vec)
{
    myfile << "in: ";
    for(int ii = 0; ii < vec.size(); ii++)
    {
        if(vec[ii] == 0)
            vec[ii] = -1;

        myfile << vec[ii] << ".0 ";
    }
    myfile << endl;
}


int main()
{
    // Logic gate example
    //
    // - OR
    // -      - XOR 
    //        -
    // - AND           
    // -               - AND ->
    //                 -
    // - AND 
    // -      - OR
    //        -
    // - XOR
    // - 

    ofstream myfile("logicData.txt");
    if(myfile.is_open())
    {
        const int size = 16;
        myfile << "topology: 16 22 1" << endl;
        vector<int> in(size);
        for(int i = 800000; i >= 0; --i)
        {
            for(int ii = 0; ii < size; ii++)
            {
                in[ii] = (int)(2.0 * rand() / double(RAND_MAX));
            }

            int t = ((in[0] | in[1]) ^ (in[2] & in[3])) &
                ((in[4] & in[5]) | (in[6] ^ in[7])) | 
                ((in[8] | in[9]) | (in[10] & in[11])) &
                ((in[12] ^ in[13] | in[14] & ~in[15]));
            if (t == 0)
                t = -1;

            writeIn(myfile, in);
            myfile << "out: " << t << ".0" << endl; 
        }

        myfile.close();
    }
}
