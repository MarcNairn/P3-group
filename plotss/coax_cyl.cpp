#include<iostream>
#include <stdlib.h> // used for exit function
#include <math.h>
#include <ctime> // for random number
#include <fstream>
using namespace std;

// analytical function which creates matrix of analytical solutions
int analytical_pot(double v, double rad_1, double rad_2, int grid) {

// declare variables
  double x[grid], y[grid], analytical_p[grid][grid], analytical_e[grid][grid], analytical_ex[grid][grid], analytical_ey[grid][grid], angle;

// open external data files
  ofstream myfile;
  myfile.open("coax_anal.dat");

  ofstream myfile2;
  myfile2.open("coax_ef.dat");
 
// initialise x and y values 
  for (int i=0;i<grid;i++) {
     x[i] = i-(grid/2);
     y[i] = i-(grid/2);
  }
  
// loop for each cell in grid 
  for (int i=0; i<grid; i++) {
    for (int j=0; j<grid;j++) {
      // find electric field at point
      angle = atan(y[j]/x[i]);
      // analytical_e[i][j] = (-1*v)/(log(rad_2/rad_1)*sqrt(x[i]*x[i] + y[j]*y[j]))*(x[i]*cos(angle)+y[j]*sin(angle)/sqrt(x[i]*x[i] + y[j]*y[j]));
										  
      analytical_ex[i][j] = (-1*v)/(log(rad_2/rad_1)*(x[i]/cbrt(x[i]*x[i] + y[j]*y[j])));
      analytical_ey[i][j] = (-1*v)/(log(rad_2/rad_1)*(y[i]/cbrt(x[i]*x[i] + y[j]*y[j])));
      
      // if cell is located inside small cylinder, potential = 0
      if ((x[i]*x[i]+y[j]*y[j] < rad_1*rad_1) || (x[i]*x[i]+y[j]*y[j] > rad_2*rad_2))  {
	analytical_p[i][j] =0;
      }
      
      // if cell is located between the cylinders, potential is given by analytical formula
      if ((x[i]*x[i] + y[j]*y[j] <= rad_2*rad_2) && (x[i]*x[i] + y[j]*y[j] >= rad_1*rad_1)) {
	analytical_p[i][j] = ((v * log(sqrt(x[i]*x[i] + y[j]*y[j])/rad_1)) / log(rad_2/rad_1));
	
      }
      // write to data file
      myfile << analytical_p[i][j] << endl;
      myfile2 << x[i] << "\t" << y[j] << "\t" << analytical_ex[i][j] << "\t" << analytical_ey[i][j] << endl;
										  
    }  
    myfile << "\n";
    //myfile2 << "\n";
  }

cout << "Potential data stored in coax_anal.dat" << endl;
cout << "Electric field data stored in coax_ef.dat" << endl;

myfile.close();
myfile2.close();

return 0;
}


// main function 
int main() {

  double v, rad_1, rad_2;
  int grid;
  // get user input for voltage and radius
  cout << "Voltage?" << endl;
  cin >> v;
  cout << "Radius of larger cylinder?" << endl;
  cin >> rad_2;
  cout << "Radius of smaller cylinder?" << endl;
  cin >> rad_1;
  cout << "Grid size?" << endl;
  cin >> grid;

  // call analytical function 
  analytical_pot(v, rad_1, rad_2, grid);
  return 0;
}
