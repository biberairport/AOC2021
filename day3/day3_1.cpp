#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    ifstream myInput("day3_data");
    vector< string > vdata;
    vector< string > xdata;
    vector< string > udata;
    int x = 0, depth = 0, horizon = 0, aim = 0;
    string value = "";
    int ti[12] = {};
    int ta[12] = {};
    int count = 0;
    int res1=0;
    int res2=0;

    while (myInput >> value) {
        vdata.push_back(value);
	x++;
 }



    for(int a=0; a<x; a++){
	for (int i = 0; i<12; i++){
	   if(vdata[a][i] == '1'){
	     ti[i]+=1;
             ta[i]+=1;
	   }
	 }
    }


   int helper = 11;
   for(int b = 0; b < 12; b++)
   {
     if(ti[b] > x/2){
       ti[b] = 1;}
       
     else
       ti[b] = 0;

    res1 += ti[b]*pow(2,helper);
   helper--;
   }

  helper = 11;
   for(int b = 0; b < 12; b++)
   {
     if(ta[b] < x/2)
       ta[b] = 1;
    else
       ta[b] = 0;

    res2 += ta[b]*pow(2,helper);
    helper--;
   }

int g=0;
  for(int g; g<x; g++)
   { 
     for(int helper=11; helper--; helper >=0)
{
       if(ti[g]==1)
        xdata.push_back(vdata[g]);
}
}


 g=0;
  for(int g; g<x; g++)
   { 
     for(int helper=11; helper--; helper >=0)
	{
       	if(ti[g]==0)
            udata.push_back(vdata[g]);
	}
    }


int res3 = 0;
int res4 = 0;

helper = 11;
   for(int b = 0; b < 12; b++)
   {
    res3 += xdata[0][b]*pow(2,helper);
    helper--;
   }

helper = 11;
   for(int b = 0; b < 12; b++)
   {
    res4 += udata[0][b]*pow(2,helper);
    helper--;
   }

cout << res3 << endl << res4 << endl << res3*res4 << endl;
cout << g << endl << xdata[0] << endl << udata[0] << endl;
}
