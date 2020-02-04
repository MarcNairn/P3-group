#include<iostream>
#include <stdlib.h> // used for exit function
#include <math.h>
#include <ctime> // for random number
#include <fstream>
using namespace std;

// main function
int main() {

// declare variables
  double x[200], y[200], analytical_sol[200][200];
  double V=100.0, rad_1 = 20.0, rad_2 = 100.0;

// open external data file
  ofstream myfile;
  myfile.open("coax_anal.dat");
 
// initialise x and y values 
  for (int i=-100;i<100;i++) {
     x[i+100] = i;
     y[i+100] = i;
  }

// loop for each cell in grid 
  for (int i=-100; i<100; i++) {
    for (int j=-100; j<100;j++) {
      // if cell is located inside small cylinder, potential = 0
      if ((x[i+100]*x[i+100]+y[j+100]*y[j+100] < rad_1*rad_1) || (x[i+100]*x[i+100]+y[j+100]*y[j+100] > rad_2*rad_2))  {
	analytical_sol[i+100][j+100] = 0;
      }
      
      // if cell is located between the cylinders, potential is given by analytical formula
      if ((x[i+100]*x[i+100] + y[j+100]*y[j+100] <= rad_2*rad_2) && (x[i+100]*x[i+100] + y[j+100]*y[j+100] >= rad_1*rad_1)) {
	analytical_sol[i+100][j+100] = ((V * log(sqrt(x[i+100]*x[i+100] + y[j+100]*y[j+100])/rad_1)) / log(rad_2/rad_1));
      }
      // write to data file
      myfile << analytical_sol[i+100][j+100] << endl;
      
    }  
    myfile << "\n";
  }

cout << "Data stored in coax_anal.dat" << endl;
myfile.close();

return 0;
}
 

