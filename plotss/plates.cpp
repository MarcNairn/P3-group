#include<iostream>
#include <stdlib.h> // used for exit function
#include <math.h>
#include <ctime> // for random number
#include <fstream>
#define PI 3.141592654
using namespace std;

// analytical function which creates matrix of analytical solutions
int analytical_pot(double v, double rad_1, int distance) {

// declare variables
  double x[distance], y[distance], analytical_p[distance][distance], analytical_e[distance][distance], angle;

// open external data files
  ofstream myfile;
  myfile.open("plates_anal.dat");

  ofstream myfile2;
  myfile2.open("plates_ef.dat");
 
// initialise x and y values 
  for (int i=0;i<distance;i++) {
    x[i] = i-(distance/2.0);
    y[i] = i-(distance/2.0);
  }
  
// loop for each cell in grid 
  for (int j=0; j<distance; j++) {
    for (int i=0; i<distance;i++) {
      // find electric field at point
 
      
      if ((x[i] < 0) && (y[j] < 0)) {
	angle = PI + atan((y[j])/(x[i]));
      }
      if ((x[i] > 0) && (y[j] < 0)) {
	angle = 2*PI - atan((y[j])/(x[i]));
      }
      if ((x[i] > 0) && (y[j] > 0)) {
	angle = atan((y[j])/(x[i]));
      }
      if ((x[i] < 0) && (y[j] > 0)) {
	angle = PI - atan((y[j])/(x[i]));
      }
      if ((x[i] == 0) && (y[j] < 0)) {
	angle = (3*PI/2.0);
      }
      if ((x[i] == 0) && (y[j] > 0)) {
	angle = PI/2.0;
      }
      if ((x[i] > 0) && (y[j] == 0)) {
	angle = 0;
      }
      if ((x[i] < 0) && (y[j] == 0)) {
	angle = PI;
      }
      if ((x[i] == 0) && (y[j] == 0)) {
	analytical_p[i][j] = 0;
      }
     
      cout << angle << endl;
      
      analytical_e[i][j] = (2*v/distance)*(cos(angle)*(((-1*rad_1*rad_1)/(x[i]*x[i]+y[j]*y[j]))-1) - (sin(angle)*(((rad_1*rad_1)/(x[i]*x[i]+y[j]*y[j]))-1)));
										  

      // if cell is located inside cylinder, potential = 0
      if (((x[i]*x[i]+y[j]*y[j]) < rad_1*rad_1)) {
	analytical_p[i][j] = 0;
      }
      
      // if cell is located outside cylinder, potential is given by analytical formula
      if (((x[i]*x[i] + y[j]*y[j]) > rad_1*rad_1)) {
	analytical_p[i][j] = (2 * v)/distance * cos(angle) * ((rad_1*rad_1)/(sqrt(x[i]*x[i]+y[j]*y[j])) - sqrt(x[i]*x[i]+y[j]*y[j]));
	
      }
      
      // write to data file
      myfile << analytical_p[i][j] << endl;
      myfile2 << analytical_e[i][j] << endl;
										  
    }  
    myfile << "\n";
    myfile2 << "\n";
  }

cout << "Potential data stored in plates_anal.dat" << endl;
cout << "Electric field data stored in plates_ef.dat" << endl;

myfile.close();
myfile2.close();

return 0;
}



// main function 
int main() {

  double v, rad_1, rad_2, distance;
  // get user input for voltage and radius
  cout << "Voltage of plates (both plates are oppositely charged)?" << endl;
  cin >> v;
    cout << "Radius of ground cylinder?" << endl;
  cin >> rad_1;
  cout << "Distance between plates?" << endl;
  cin >> distance;

  // call analytical function 
  analytical_pot(v, rad_1, distance);
  return 0;

}
