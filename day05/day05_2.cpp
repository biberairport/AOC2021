#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


using namespace std;


unsigned int readFile(string myFilename, vector<vector<int>>& source, vector<vector<int>>& target)                        
{
    ifstream myFile(myFilename);
    string buffer = "";
    string delimiter = ",";
    bool flag = false;    

    while (myFile >> buffer) {                      // read file, ignore ->, split by "," and move data to x / y coordinates        
        vector <int>v1s;
        vector <int>v1t;
        if (buffer != "->") {
            if (flag == false) {
                v1s.push_back(stoi(buffer.substr(0, buffer.find(delimiter))));                          // filter x coordinates
                v1s.push_back(stoi(buffer.substr(buffer.find(delimiter) + 1, buffer.length())));        // filter y coordinates
                source.push_back(v1s);
                flag = true;
            }
            else {
                v1t.push_back(stoi(buffer.substr(0, buffer.find(delimiter))));                          // filter x coordinates
                v1t.push_back(stoi(buffer.substr(buffer.find(delimiter) + 1, buffer.length())));        // filter y coordinates
                target.push_back(v1t);
                flag = false;
            }
        }
    }
    return(source.size());
}

unsigned int calcMap(vector<vector<int>> worldmap) {
    int mines = 0;
    for (int a = 0; a < worldmap[0].size(); a++) {
        for (int i = 0; i < worldmap.size(); i++)
            if (worldmap[i][a] != 0 && worldmap[i][a] != 1)
                mines++;        
    }
    return(mines);
}

void drawLine(vector<vector<int>> source, vector<vector<int>> target, vector<vector<int>>& worldmap, unsigned int position)
{
    int x = 0;
    int y = 1;

    int distanceX = abs(target[position][x] - source[position][x]);
    int distanceY = abs(target[position][y] - source[position][y]);

    // On the same positive slope diagonal : y2 - y1 == x2 - x1
    // On the same negative slope diagonal : y2 - y1 == x1 - x2

    int diaD = (target[position][y] - source[position][y]) - (target[position][x] - source[position][x]);
    int diaU = (target[position][y] - source[position][y]) - (source[position][x] - target[position][x]);

    int startingY = min(target[position][y], source[position][y]);
    int startingX = min(target[position][x], source[position][x]);
    int endingY   = max(target[position][y], source[position][y]);
    //int endingX   = max(target[position][x], source[position][x]); 

    if (distanceX == 0)
        for (int i = 0; i <= distanceY; i++)
            worldmap[startingX][startingY + i] += 1;
    if (distanceY == 0)
        for (int i = 0; i <= distanceX; i++)
            worldmap[startingX + i][startingY] += 1;
    if (diaD == 0)
        for (int i = 0; i <= distanceX; i++)
            worldmap[startingX + i][startingY + i] += 1;
    if (diaU == 0)
        for (int i = 0; i <= distanceX; i++)
            worldmap[startingX + i][endingY - i] += 1;
}

void populateMap(vector<vector<int>>& map, unsigned int size) 
{
    vector<int>v1;
    v1.resize(size);
    for (int i = 0; i < size; i++)
        map.push_back(v1);    
}

int main()
{        
    vector<vector<int>> source;
    vector<vector<int>> target;
    vector<vector<int>> worldmap;

    populateMap(worldmap, 1000);

    auto lines = readFile("day5_data.txt", source, target);

    for (; lines > 0; --lines)
        drawLine(source, target, worldmap, lines-1);

    cout << calcMap(worldmap);
}