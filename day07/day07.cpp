#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <numeric>
#include <algorithm>

using namespace std;

int power_used(int i)
{
    int tmp = 0;
    while (i > 0) {
        tmp = tmp + i;
        i--;
    }
    return(tmp);        
}

int main() {


    ifstream myFile("data_day7.txt");                                         
    stringstream ss;
    string s = "";
    vector <int> crabs;
    vector <int> result;
    vector <int> result_max;
    vector <int> value;

    ss << myFile.rdbuf();                                                   // read ifstream to stringsteam

    while (getline(ss, s, ','))                                             // split numbers by ","   
        crabs.push_back(stoi(s));

    auto max_e = max_element(begin(crabs),end(crabs));
    auto min_e = min_element(begin(crabs),end(crabs));

    for (int a = min_e[0]; a <= max_e[0]; a++) {                            // from min position to max position
        int tempvalue = 0;
        int tempvalmax = 0;
        for (int i = 0; i < crabs.size(); i++) {                            // all crabs                        
            tempvalue += abs(crabs[i] - a);                                  
            tempvalmax += power_used(abs(crabs[i] - a));
        }
        result.push_back(tempvalue);     
        result_max.push_back(tempvalmax);
        value.push_back(a);
    }

    for (int a = 0; a < result.size(); a++)
        cout << "\n" << result[a] << " " << value[a];

    cout << "\n Result 1: " << min_element(begin(result), end(result))[0];
    cout << "\n Result 2: " << min_element(begin(result_max), end(result_max))[0];
}