#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <numeric>
#include <algorithm>

using namespace std;

void getSplitInput(vector<string>& first, vector<string>& second, string filename, const char* delim) {

    ifstream myFile(filename);
    stringstream ss;
    string s = "";
    int cnt = 0;

    ss << myFile.rdbuf();

    while (getline(ss, s)) {
        second.push_back(s.substr(s.find(delim) + 2, s.length()));
        first.push_back(s.substr(0, s.find(delim) - 1));
        cnt++;
    }
}

string remove_duplicates(string s) {
    if (s.begin() == s.end()) return s;
    auto no_duplicates = s.begin();
    for (auto current = no_duplicates; current != s.end();) {
        current = find_if(next(current), s.end(), [no_duplicates](const char c) { return c != *no_duplicates; });
        *++no_duplicates = move(*current);;
    }
    s.erase(++no_duplicates, s.end());
    s.pop_back();
    return s;
}

vector<string> split(const string& s, char delim) {
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

void Aufgabe1(vector<string>first, vector<string>second){

    int result = 0;

    for (int i = 0; i < second.size(); i++) {
        vector<string> v = split(second[i], ' ');
        for (auto out : v)                    
            if (out.size() == 2 || out.size() == 4 || out.size() == 3 || out.size() == 7) 
                result++;                            
                
}
std::cout << "Result 1: " << result << endl;
}

void calcTable(vector<string> first, vector<string>& table, int i)
{
    table.resize(10);
    vector <string> split_string;

//    for (int i = 0; i < first.size(); i++) {                            // go on line by line for full data

        split_string = split(first[i], ' ');                            // split line to single strings
        string bufferNum = "";
        string res7 = "";
        string res47 = "";



        // check for 1,4,7,8
        for (int k = 0; k < split_string.size(); k++) {
            if (split_string[k].size() == 2)
                table[1] = split_string[k];
            if (split_string[k].size() == 3)
                table[7] = split_string[k];
            if (split_string[k].size() == 4)
                table[4] = split_string[k];
            if (split_string[k].size() == 7)
                table[8] = split_string[k];
        }


        // check for 6 and 9
        for (int k = 0; k < split_string.size(); k++) {
            if (split_string[k].size() == 4 || split_string[k].size() == 3) {
                bufferNum.append(split_string[k]);
                sort(bufferNum.begin(), bufferNum.end());
            }
            if (split_string[k].size() == 3) {
                sort(split_string[k].begin(), split_string[k].end());
                res7 = split_string[k];
            }
        }
        res47 = remove_duplicates(bufferNum);

        bufferNum = "";

        for (int k = 0; k < split_string.size(); k++) {
            if (split_string[k].size() == 6) {
                bufferNum = split_string[k];
                bufferNum.append(res47);
                sort(bufferNum.begin(), bufferNum.end());
                auto res = remove_duplicates(bufferNum);

                // for 9
                if (res.size() == 6)
                    table[9] = split_string[k];

                // for 6 AND 0
                if (res.size() == 7) {
                    bufferNum = "";
                    res = "";
                    bufferNum = split_string[k];
                    bufferNum.append(res7);
                    sort(bufferNum.begin(), bufferNum.end());
                    res = remove_duplicates(bufferNum);

                    if (res.size() == 7)
                        table[6] = split_string[k];
                    if (res.size() == 6)
                        table[0] = split_string[k];
                }
            }
        }
        // end


        // check for 2,3,5
        bufferNum = "";

        for (int k = 0; k < split_string.size(); k++) {
            if (split_string[k].size() == 5) {
                bufferNum = split_string[k];
                bufferNum.append(table[4]);
                sort(bufferNum.begin(), bufferNum.end());
                auto res = remove_duplicates(bufferNum);

                // for 2
                if (res.size() == 7)
                    table[2] = split_string[k];

                // for 3 and 5
                if (res.size() == 6) {
                    bufferNum = "";
                    res = "";
                    bufferNum = split_string[k];
                    bufferNum.append(table[1]);          // 3+1 or 5+1
                    sort(bufferNum.begin(), bufferNum.end());
                    res = remove_duplicates(bufferNum);


                    if (res.size() == 5)
                        table[3] = split_string[k];
                    if (res.size() == 6)
                        table[5] = split_string[k];

                }
            }
        }
}

void Aufgabe2(vector<string>first, vector<string> second)
{    
    vector <string> table = {};                                         // conversion table            

    int result = 0;

    // main loop 
    for (int i = 0; i < second.size(); i++) {
        calcTable(first, table, i);
        vector<string> v = split(second[i], ' ');
        
        // sort result table 
        for (int i = 0; i < table.size(); i++)
            sort(table[i].begin(), table[i].end());
        
     
        for (int k = 0; k < v.size(); k++)
            sort(v[k].begin(), v[k].end());

        int helper = 1000;
        for (int k = 0; k < v.size(); k++) {           
            for (int u = 0; u < table.size(); u++)
            {                
                if (table[u] == v[k]){
                    result += u*helper;
                    helper = (helper / 10);
                }
            }            
        }
        
    }
    cout << "Result 2: " << result;
}

int main()
{    
    vector <string> first;
    vector <string> second;    

    getSplitInput(first, second, "data_day8.txt", "|");

    Aufgabe1(first, second);
    Aufgabe2(first, second);
}