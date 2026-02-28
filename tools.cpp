#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include <cmath>

//#include <ctime> // for chrono
//#include <ratio> // for chrono
//#include <chrono> // for chrono

using namespace std;

/******************************************************************************/
/***************************   Constant variables   ***************************/
/******************************************************************************/
const __int128_t one128 = 1;

/******************************************************************************/
/**************************     READ FILE    **********************************/
/******************************************************************************/
/**************    READ DATA and STORE them in Nset    ************************/

map<__int128_t, double> read_datafile128(string datafilename, unsigned int *N, unsigned int r)    // O(N)  where N = data set size
{
//  auto start = chrono::system_clock::now();

  cout << endl << "--->> Read the datafile: \"" << datafilename << "\", \t Build Nset..." << endl;
  cout << "\t Number of variables to read: n = " << r << endl;

  string line, line2;     char c = '1';
  __int128_t state = 0, Op;
  (*N) = 0;            // N = dataset sizes

// ***** The data is stored in Nset as an histogram:  ********************************
  map<__int128_t, unsigned int> Nset; // Nset[mu] = #of time state mu appears in the data set

  ifstream myfile (datafilename.c_str());
  if (myfile.is_open())
  {
    while ( getline (myfile,line))
    {
      line2 = line.substr (0,r);          //take the r first characters of line
      Op = one128 << (r - 1);
      state = 0;
      for (auto &elem: line2)     //convert string line2 into a binary integer
      {
        if (elem == c) { state += Op; }
        Op = Op >> 1;
      }
      Nset[state] += 1;
      (*N)++;
    }
    myfile.close();
  }
  else cout << endl << "--->> Unable to open file: Check datafilename and location." << endl << endl;

  if ((*N) == 0) 
    { 
    cout << endl << "--->> Failure to read the file, or file is empty:  Terminate." << endl << endl;
    }
  else
    {
    cout << endl << "--->> File has been read successfully:" << endl;
    cout << "\t Data size, N = " << (*N) << endl;
    cout << "\t Number of different states, Nset.size() = " << Nset.size() << endl << endl;
    }
/*
  vector<pair<__int128_t, unsigned int>> Nvect(Nset.size());
  int i=0;
  for (auto& my_pair : Nset)
  {
    Nvect[i]=my_pair;
    i++;
  }
  return Nvect;
*/

  double Nd = (double) *N;
  map<__int128_t, double> Ps_data;

  for (auto pair : Nset)
    { Ps_data[pair.first]+= (double)(pair.second)/Nd; }

  return Ps_data;
}

/******************************************************************************/
/****************************     Average Data    *****************************/
/******************************************************************************/
map<__int128_t, double> average_proba(map<__int128_t, double> Ps_1, map<__int128_t, double> Ps_2)  
{
  map<__int128_t, double> Ps_mean;

  for (auto pair : Ps_1)
    { Ps_mean[pair.first] += (pair.second)/2.; }

  for (auto pair : Ps_2)
    { Ps_mean[pair.first] += (pair.second)/2.; }

  return Ps_mean;
}

/******************************************************************************/
/****************************     ENTROPY    **********************************/
/******************************************************************************/

double entropy(map<__int128_t, double> Ps)
{
  double S = 0;
//  double Pk = 0;
//  double Nd = (double) N;

  for (auto it : Ps)
  {
    //Pk = (double) (it_ks)/Nd; // ks = (it).second = number of time state s appear in the dataset
    S += (it.second) * log(it.second);
  }

  return -S;
}

double JS_div(map<__int128_t, double> Ps_1, map<__int128_t, double> Ps_2)
{
  map<__int128_t, double>  Ps_mean = average_proba(Ps_1, Ps_2);
  
  double H1=entropy(Ps_1);
  double H2=entropy(Ps_2); 
  double H =entropy(Ps_mean);

  return H-(H1+H2)/2.;
}



