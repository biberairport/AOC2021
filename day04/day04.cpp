#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void printBingoCard(vector<vector<vector< int >>> v3, int shownumber)
{
    if(shownumber <= 0)
    {
    for (int i = 0; i < v3.size(); i++)
    {
        cout << "\nBingo Card: " << i << "\n";        // show current bingo card
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    cout << v3[i][j][k] << " ";
                }
                cout << endl;
            }
        }
    }
    else
    {
        cout << "\nBingo Card: " << shownumber << "\n";        // show current bingo card
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                cout << v3[shownumber][j][k] << " ";
            }
            cout << endl;
        }
    }
}

int calcBingoCard(vector<vector<vector< int >>> v3, int cardnumber)
{
    int sum = 0;
    cout << "\nSum of Card: " << "\n";        
    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            if (v3[cardnumber][j][k] >= 0)
                sum += v3[cardnumber][j][k];
        }            
    }
    return(sum);
}

bool checkforBingo(vector<vector<vector< int>>> v3, int current_card)
{
    int tempH = 0;
    int tempV = 0;
    int k = 0;


        for (int j = 0; j < 5; j++)
        {
            tempH = 0;
            tempV = 0;

            for (k = 0; k < 5; k++)
            {             
                tempV += v3[current_card][k][j];           // lol
                tempH += v3[current_card][j][k];           // j=array horizonal, k = elements of vector j;
            }
            if (tempH < 0 || tempV < 0){
                if(tempH < 0){
                    cout << "BINGO!!! Horizontal Line " << j+1 << " with Card No: " << current_card << endl;
                }
                else if(tempV < 0){
                    cout << "BINGO!!! Vertical Line " << k-1 << " with Card No: " << current_card << endl;
                }
                return(true);
            }
        }

    return(false);
}


int main()
{
    // open file + variables    
    vector<vector<vector< int >>> v3;               // 3d vector
    vector<int>     bingo       = {};
    ifstream        myFile      ("day4_data.txt");
    string          buffer      = "";    
    int             lines       = 0;
    int             horizon     = 0;
    int             vertica     = 0;
    int             currentPaper = 0;
       

    // get first line only
    myFile >> buffer;
    
    stringstream ss(buffer);

    // fill bingo with numbers
    for (int a; ss >> a;) {
        bingo.push_back(a);
        if (ss.peek() == ',')
            ss.ignore();
        }

    // count bingo papers 
    while (myFile >> buffer) {
        currentPaper = lines / 25;        
        lines++;
    }

    myFile.clear();
    myFile.seekg(0);

    myFile >> buffer; // jump to next line ez

    // create 3d vector and fill with bingo numbers
    for (int i = 0; i < lines / 25; i++) {
        vector < vector<int>> v2;
        for (int j = 0; j < 5; j++) {
            vector <int> v1;
            for (int k = 0; k < 5; k++){
                myFile >> buffer;
                v1.push_back(stoi(buffer));
            }
            v2.push_back(v1);
        }
        v3.push_back(v2);
    }

    bool win = false;
    // remove current bingo number from vector        
    for (int b = 0; b < bingo.size(); b++)
    {
        if (win == true)
            break;

        for(int x = 0; x<v3.size(); x++) {
            if (checkforBingo(v3, x))
            {
                printBingoCard(v3, x);
                cout << calcBingoCard(v3, x);
                cout << "Day4 Result1: " << calcBingoCard(v3, x) * bingo[b-1] << "\nBingo NUmber: " << bingo[b-1] << endl;
                x = 101;
                win = true;
                break;
            }
            
            
        }
    
        for (int i = 0; i < lines / 25; i++)
        {            
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 5; k++)
                {                    
                    if (v3[i][j][k] == bingo[b])
                    {
                        v3[i][j][k] -= bingo[b];
                        v3[i][j][k] --;                        
                    }                        
                }             
            }
        }
     }           
    return(0);
}