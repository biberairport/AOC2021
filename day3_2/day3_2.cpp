#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void readFile2d(ifstream& inputFile, vector<vector<char>>& map)            
{   
    string buffer = "";

    while (inputFile >> buffer) {
        vector <char> v1;
        for (int i = 0; i < buffer.length(); i++)
            v1.push_back(buffer[i]);
        v1.push_back('O');
        v1.push_back('N');
        map.push_back(v1);
    }
}

void checkWinner(vector<vector<char>>& map, char& result, int position) {
    int m_heigh = map.size();
    
    int temp_1 = 0;
    int temp_0 = 0;

    for (int j = 0; j < m_heigh; j++) {
        if (map[j][position] == '1')
            temp_1++;
        else
            temp_0++;
    }
    if (temp_1 > temp_0)
        result = '1';
    else if (temp_1 < temp_0)
        result = '0';
    else if (temp_1 == temp_0)
        result = '2';

    cout << "\nWinner: " << result << " 1: " << temp_1 << " 0: "  << temp_0;
        
}

void flagLines(vector<vector<char>>& map, int position)
{
    char result;                         // result if 0 or 1 is winner
    int length = map[0].size();

    checkWinner(map, result, position);

        for (int j = 0; j < map.size(); j++) {
            if (map[j][position] == '0' && result == '1' || map[j][position] == '1' && result == '0' || map[j][position] == '0' && result == '2'){
                map[j][length-2] = 'F';
            }
            if (map[j][position] == '1' && result == '1' || map[j][position] == '0' && result == '0' || map[j][position] == '1' && result == '2'){
                map[j][length-1] = 'F';
            }
        }
    
}

vector<vector<char>> retGasdata(vector<vector<char>> oldmap, char OxyOrNit) {

    vector <vector<char>> return_gasdata;
    int length = oldmap[0].size();
    for (int i = 0; i < oldmap.size(); i++) {
       
        vector<char> line_data_temp;
        if(OxyOrNit == 'O'){
            if (oldmap[i][length-2] != 'F') {
                for(int k=0; k < (oldmap[i].size() - 2); k++)
                    line_data_temp.push_back(oldmap[i][k]);
                line_data_temp.push_back('O');
                line_data_temp.push_back('O');
            }            
        }
        else if (OxyOrNit == 'N') {
            if (oldmap[i][length-1] != 'F') {
                for (int k = 0; k < (oldmap[i].size() - 2); k++)
                    line_data_temp.push_back(oldmap[i][k]);
                line_data_temp.push_back('N');
                line_data_temp.push_back('N');
            }            
        }
        if(line_data_temp.size()!=0)
            return_gasdata.push_back(line_data_temp);                
    }

    return return_gasdata;
}

int binarytoint(vector<vector<char>> map) {

    int helper = map[0].size() - 2;
    int res = 0;

    for (int i = 0; i < map[0].size()-2; i++) {
        res += (map[0][helper-1]-'0') * pow(2, i);                
        helper--;
    }
    return res;
}

int main()
{
    ifstream myFile("data_day3.txt");
    vector<vector<char>> map = {};      
    vector<vector<char>> map_oxy = {};
    vector<vector<char>> map_nit = {};
    
    readFile2d(myFile, map);
           
    flagLines(map,0);

    map_oxy = retGasdata(map, 'O');
    map_nit = retGasdata(map, 'N');

    int flagline = 1;

    while(map_oxy.size() > 1)
    {   
        flagLines(map_oxy,flagline);
        map_oxy = retGasdata(map_oxy, 'O');                
        flagline++;        
    }

    cout << "\n" << binarytoint(map_oxy) << endl;

    flagline = 1;

    while (map_nit.size() > 1)
    {
        flagLines(map_nit,flagline);
        map_nit = retGasdata(map_nit, 'N');        
        flagline++;
    }

    cout << "\n" << binarytoint(map_nit) << endl;
    cout << "\nResult2: " << binarytoint(map_nit) * binarytoint(map_oxy);
}
