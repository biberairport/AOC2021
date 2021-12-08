#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream myInput("tag1_data");
    vector< int > vdata;
    int value = 0, x = 0, inc1 = 0, inc2 =0;
       
    while (myInput >> value) {
        vdata.push_back(value);
    }

    while (x < vdata.size() - 1) {
        if (vdata[x] < vdata[x + 1])
            inc1++;

        if (x < vdata.size() - 3)
            if (vdata[x] + vdata[x + 1] + vdata[x + 2] < vdata[x + 1] + vdata[x + 2] + vdata[x + 3])
                inc2++;
        x++;
    }
    cout << "Result Q1: " << inc1 << endl;
    cout << "Result Q2: " << inc2 << endl;
}
