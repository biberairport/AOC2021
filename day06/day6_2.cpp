#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <numeric>

using namespace std;

#define DAYS 256

vector<unsigned __int64> grow(vector<unsigned __int64>& swarm, int days) 
{
    while (days > 0)
    {
        unsigned __int64 momafish = swarm[0];
        rotate(swarm.begin(), swarm.begin() + 1, swarm.end());              // rotate vector to left, first point goes to last etc.
        swarm[6] += momafish;                                               // add cooldown to momafish; position 0 => 6
        days--;
    }
    return(swarm);
}

int main()
{    
    ifstream myFile("data_day6.txt");
    vector<unsigned __int64> swarm(9);                                      // create array for 9 numbers (0 - 8), unsigned int64 = 0 -> 18.446.744.073.709.551.615
    stringstream ss;
    string s = "";

    ss << myFile.rdbuf();                                                   // read ifstream to stringsteam

    while (getline(ss, s, ','))                                             // split numbers by ","
        swarm[stoi(s)]++;                                                   // amount of all individual numbers => stored in vector (0-8)
    
    swarm = grow(swarm, DAYS);
    unsigned __int64 sum = accumulate(swarm.begin(), swarm.end(), 1ULL);    // add all numbers of every element from array, return = 1ULL = unsigned long long
   
    duration<double, std::milli> ms_double = t2 - t1;    
    cout << "\nResult: " << sum - 1 << endl;                                  // -1 ???
 
    return 0;
}

