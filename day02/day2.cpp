#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    ifstream myInput("day2_data");
    vector< string > vdata;
    int x = 0, depth = 0, horizon = 0, aim = 0;
    string value = "";

    while (myInput >> value) {
        vdata.push_back(value);
        if (x >= 1) {
            if (vdata[x - 1][0] == 'f') {
                int a = stoi(vdata[x]);
                horizon += a;
                depth += a * aim;
            }
            else if (vdata[x - 1][0] == 'd')
                aim += stoi(vdata[x]);

            else if (vdata[x - 1][0] == 'u')
                aim -= stoi(vdata[x]);
        }
        x++;
    }
    cout << "Task1: " << horizon * aim << endl << "Task2: " << horizon * depth;
}