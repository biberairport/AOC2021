#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>


using namespace std;

void getInput(vector<string>& map, string filename) {

    ifstream myFile(filename);
    string s = "";

    while (myFile >> s) {
        map.push_back(s);
    }
}

int main()
{
    vector<string> map;
    vector<string> complete;            
    vector <char> stack;

    int result = 0;
    vector <long long int> result2 = { 0 };

    getInput(map, "data_day10.txt");

    complete.resize(map.size());
    result2.resize(map.size());

    fill(result2.begin(), result2.end(), 0);


    for (int i = 0; i < map.size(); i++){                                           // line by line
        
        for (int j = 0; j < map[i].size(); j++) {                                   // for each element of line i            

            if (map[i][j] == '{' || map[i][j] == '[' || map[i][j] == '(' || map[i][j] == '<') {
                stack.push_back(map[i][j]);
                complete[i].insert(j, string(1,map[i][j]));

            if (map[i][j] == '{')
                complete[i].insert(j+1, "}");

            if (map[i][j] == '[')
                complete[i].insert(j+1, "]");

            if (map[i][j] == '<')
                complete[i].insert(j+1, ">");

            if (map[i][j] == '(')
                complete[i].insert(j+1, ")");
            }
            
            
            else if (stack[stack.size() - 1] == '{' && map[i][j] == '}')
                    stack.pop_back();                    

            else if (stack[stack.size() - 1] == '[' && map[i][j] == ']')
                    stack.pop_back();                  

            else if (stack[stack.size() - 1] == '(' && map[i][j] == ')')
                    stack.pop_back();                               

            else if (stack[stack.size() - 1] == '<' && map[i][j] == '>')
                    stack.pop_back();                  


            else {
                if (map[i][j] == ')')
                    result += 3;

                if (map[i][j] == ']')
                    result += 57;

                if (map[i][j] == '}')
                    result += 1197;

                if (map[i][j] == '>')
                    result += 25137;
                
                map[i].clear();
                complete[i].clear();
            }
        }
    }        

    for (int i = 0; i < map.size(); i++) {
        for (int j = map[i].size(); j <= complete[i].size(); j++) {
            if (complete[i][j] == ')'){
                result2[i] *= 5;
                result2[i] += 1;                
            }

            if (complete[i][j] == ']'){
                result2[i] *= 5;
                result2[i] += 2;                
            }

            if (complete[i][j] == '}'){
                result2[i] *= 5;
                result2[i] += 3;                
            }

            if (complete[i][j] == '>'){
                result2[i] *= 5;
                result2[i] += 4;                
            }
        }
    }

    result2.erase(std::remove(result2.begin(), result2.end(), 0), result2.end());
    sort(result2.begin(), result2.end());
    result2.shrink_to_fit();
    
    auto mid = result2.size() / 2;

    cout << "First: " << result;
    cout << "\nSecond: " << result2[mid];
}


