//g++ -std=c++11 -O3 ./*.cpp -o JSdiv.out

#include <iostream>
#include <sstream>

#include <map>
#include <set>
#include <list>
#include <vector>

using namespace std;

/********************************************************************/
/**************************    PARAMETERS    ************************/
/********************************************************************/
// number of binary (spin) variables:
unsigned int n = 9;

// INPUT DATA FILES (optional):  must be in the INPUT folder
string input_directory = "INPUT/";
string input_datafile1 = "SCOTUS_n9_N895.dat"; 
string input_datafile2 = "Shapes_n9_N895.dat"; 

/********************************************************************/
/**************************    FUNCTIONS    *************************/
/********************************************************************/

map<__int128_t, double> read_datafile128(string datafilename, unsigned int *N, unsigned int r);    // O(N)  where N = data set size

map<__int128_t, double> average_proba(map<__int128_t, double> Ps_1, map<__int128_t, double> Ps_2);  

double entropy(map<__int128_t, double> Ps);

double JS_div(map<__int128_t, double> Ps_1, map<__int128_t, double> Ps_2);

/******************************************************************************/
/************************** MAIN **********************************************/
/******************************************************************************/

int main(int argc, char *argv[])
{
// **********************     READ ARGUMENTS    ********************************* //
    // argv[0] contains the name of the datafile, from the current folder (i.e. from the folder containing "data.h");
    // argv[1] contains the number of variables to read;
    // argv[2] contains flag
    // argv[3] contains kmax

// **********************   CREATE OUTPUT DIRECTORIES    *************************** //

    cout << endl;

    // Read filename
    if (argc == 3)
    {
        input_datafile1 = argv[1];
        input_datafile2 = argv[2]; 
    }


    cout << endl << "*******************************************************************************************";
    cout << endl << "***********************************  READ THE DATA:  **************************************";
    cout << endl << "*******************************************************************************************" << endl;

	unsigned int N1=0;  // will contain the number of datapoints in the dataset
    unsigned int N2=0;  // will contain the number of datapoints in the dataset

    map<__int128_t, double>  Ps_1 = read_datafile128(input_directory + input_datafile1, &N1, n); 
    map<__int128_t, double>  Ps_2 = read_datafile128(input_directory + input_datafile2, &N2, n); 
    map<__int128_t, double>  Ps_mean = average_proba(Ps_1, Ps_2);

	if ((N1==0) || (N2==0)) { return 0; } // Terminate program if the file can't be found or is empty

    cout << endl << "*******************************************************************************************";
    cout << endl << "***************************************  ENTROPY:  ****************************************";
    cout << endl << "*******************************************************************************************" << endl;

    cout << "S(D1) = " << entropy(Ps_1) << endl; 
    cout << "S(D2) = " << entropy(Ps_2) << endl;
    cout << "S(D_mean) = " << entropy(Ps_mean) << endl << endl;

    cout << "JS_div(D1,D2) = " << JS_div(Ps_1, Ps_2) << endl << endl;

    return 0;
}



