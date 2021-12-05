#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void printBingoCard(vector<vector<vector< int >>> v3, int shownumber)
{
    cout << "\nBingo Card: " << shownumber << "\n";        // show current bingo card
    for (int j = 0; j < 5; j++)   
    {
        for (int k = 0; k < 5; k++)        
            cout << v3[shownumber][j][k] << " ";    
        cout << "\n";
    }
    
}

int calcBingoCard(vector<vector<vector< int >>> v3, int cardnumber)
{
    int sum = 0;
      
    for (int j = 0; j < 5; j++)
        for (int k = 0; k < 5; k++)        
            if (v3[cardnumber][j][k] >= 0)                 
                sum += v3[cardnumber][j][k];

    return(sum);
}

bool checkforBingo(vector<vector<vector< int>>>& v3, int current_card)
{

    if(v3[current_card][0][5] == -2)                        // check if bingo card has already won
        return(false);

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
            if (tempH < -4 || tempV < -4){
                if(tempH < -4)
                    cout << "BINGO!!! Horizontal Line " << j+1 << " with Card No: " << current_card << endl;                
                else if(tempV < -4)
                    cout << "BINGO!!! Vertical Line " << k-1 << " with Card No: " << current_card << endl;

                v3[current_card][0][5] = -2;                // if bingo card won => flag with "-2" on last element
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
  

    // get first line only
    myFile >> buffer;
    
    stringstream ss(buffer);

    // fill vector with bingo numbers
    for (int a; ss >> a;) {
        bingo.push_back(a);
        if (ss.peek() == ',')
            ss.ignore();
        }

    // count bingo papers 
    while (myFile >> buffer) {
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
            v1.push_back(-5);
            v2.push_back(v1);            
        }
        v3.push_back(v2);
    }

    // remove current bingo number from vector and check if card is winner
    for (int b = 0; b < bingo.size(); b++)
    {
        for(int x = 0; x<v3.size(); x++) 
            if (checkforBingo(v3, x) == true)
            {
                printBingoCard(v3, x);
                cout << "\nSum of Card: " << calcBingoCard(v3, x) << "\n";
                cout << "Day4 Result: " << calcBingoCard(v3, x) * bingo[b-1] << "\nBingo NUmber: " << bingo[b-1] << endl;
                cout << "------------------------------" << endl;
            }
            
        for (int i = 0; i < v3.size(); i++)
            for (int j = 0; j < 5; j++)
                for (int k = 0; k < 5; k++)
                    if (v3[i][j][k] == bingo[b])
                    {
                        v3[i][j][k] -= bingo[b];
                        v3[i][j][k] --;                        
                    }                        
     }           
    return(0);
}