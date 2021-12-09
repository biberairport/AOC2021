#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

void getInput(vector<string>& map, string filename) {

    ifstream myFile(filename);    
    string s = "";
    
    while (myFile >> s){
        s.append("9");
        s.insert(0, "9");
        map.push_back(s);         
    }

     s = "";
     for (int i = 0; i < map[0].size(); i++)
        s.append("9");

     map.insert(map.begin(), s);
     map.push_back(s);    
}

int Aufgabe1(vector<string> map, vector<int>& coordY, vector<int>& coordX) 
{
    int result = 0;
    for (int i = 1; i < map.size() - 1; i++) {        
        for (int j = 1; j < map[i].length() - 1; j++) {
            int current_point = stoi(string(1, map[i][j]));
            int pointU = stoi(string(1, map[i - 1][j]));
            int pointD = stoi(string(1, map[i + 1][j]));
            int pointL = stoi(string(1, map[i][j - 1]));
            int pointR = stoi(string(1, map[i][j + 1]));

            if (current_point < pointU && current_point < pointD && current_point < pointL && current_point < pointR) {
                result += current_point + 1;
                coordY.push_back(i);
                coordX.push_back(j);                
            }
        }        
    }
    return(result);
}

int crawler(vector<string>& map, int startposY, int startposX, int & flood)
{    
    map[startposY][startposX] = 'A';
    flood += 1;  

    if (map[startposY + 1][startposX] != '9' && map[startposY + 1][startposX] != 'A')
        crawler(map, startposY + 1, startposX, flood);    
    if (map[startposY][startposX+1] != '9' && map[startposY][startposX+1] != 'A')
        crawler(map, startposY, startposX+1, flood);    
    if (map[startposY-1][startposX] != '9' && map[startposY - 1][startposX] != 'A')
        crawler(map, startposY-1, startposX, flood);
    if (map[startposY][startposX - 1] != '9' && map[startposY][startposX - 1] != 'A')
        crawler(map, startposY, startposX - 1, flood);
    else
        return(flood);
}

int Aufgabe2(vector<string>& map, vector<int>coordY, vector<int>coordX)
{
    vector <int> results;
    int flood = 0;

    for (int i = 0; i < coordY.size(); i++)
    {
        int res = 0;
        res = crawler(map, coordY[i], coordX[i], flood);
        results.push_back(res);
        flood = 0;
    }

    sort(results.begin(), results.end(), greater<int>());

    int final = 1;
    for (int i = 0; i < 3; i++)
        final *= results[i];

    return(final);
}


int main()
{
    vector <string> map;        
    vector <int> coordX;
    vector <int> coordY;
    
    getInput(map, "data_day9.txt");
           
    cout << "Aufgabe1: "   << Aufgabe1(map, coordY, coordX);
    cout << "\nAufgabe2: " << Aufgabe2(map, coordY, coordX);
}