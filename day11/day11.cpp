#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void getInput(vector<vector<int>>& map, vector<vector<int>>& flashed, string filename) {

    ifstream myFile(filename);
    string s = "";
    vector <int> v1;

    map.clear();

    while (myFile >> s) {
        for (auto w : s)
            v1.push_back(+w - '0');

        map.push_back(v1);
        v1.clear();
    }

    for (int i = 0; i < map.size(); i++){
        vector<int> v2;
        for (int j = 0; j < map[i].size(); j++)
            v2.push_back(0);

        flashed.push_back(v2);
    }
}

void inc(vector<vector<int>>& map, int i, int k){

    if (i < 0 || k < 0 || i > 9 || k > 9)
        return;
    else if (map[i][k] < 9 && map[i][k] > 0)
        map[i][k]++;
    else if (map[i][k] == 9) 
         map[i][k] = 0;      
}

void blow(vector<vector<int>>& map, int i, int k, vector<vector<int>>& flashed){

    if(flashed[i][k] == 0){
        inc(map, i - 1, k - 1);
        inc(map, i - 1, k);
        inc(map, i - 1, k + 1);
        inc(map, i, k - 1);        
        inc(map, i, k + 1);
        inc(map, i + 1, k - 1);
        inc(map, i + 1, k);
        inc(map, i + 1, k + 1);
        flashed[i][k] = 1;
    }
}

void incMap(vector<vector<int>>& map, vector<vector<int>>& flashed) {

    for (int i = 0; i < map.size(); i++)
        for (int k = 0; k < map[i].size(); k++)
            if (map[i][k] < 9)
                map[i][k]++;
            else
                map[i][k] = 0;            
}

int checkMap(vector<vector<int>>& map, vector<vector<int>>& flashed, int &result) {

    for(int x = 0; x<map.size()+1; x++){
        for (int i = 0; i < map.size(); i++)
            for (int k = 0; k < map[i].size(); k++)
                if (map[i][k] == 0)
                    blow(map, i, k, flashed);
    }

    int synchronized = 0;

    for (int i = 0; i < map.size(); i++) {     
        for (int j = 0; j < map[i].size(); j++)
            if (flashed[i][j] == 1) {
                result += 1;
                flashed[i][j] = 0;
                synchronized += 1;
            }                
    }
    return(synchronized);
}

int main()
{
    vector<vector<int>> map;
    vector<vector<int>> flashed;
    int result = 0;
    int result2 = 0;

    getInput(map, flashed, "data_day11.txt");
         
    // Q1:
    for (int i = 0; i < 100; i++) {                
        incMap(map, flashed);
        checkMap(map, flashed, result);
    }
    cout << endl << "Result1: " << result << endl;

    // Q2:
    getInput(map, flashed, "data_day11.txt");
    for (int i = 0; i < 1000; i++) {
        incMap(map, flashed);
        result2 = checkMap(map, flashed, result);
        if (result2 == 100) {
            cout << "Synchronized at: " << i + 1 << endl;
            break;
        }
    }
}