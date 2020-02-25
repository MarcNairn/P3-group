#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>

/*
This program uses the Over Relaxation Method to produce an electrostatic potential from initial
conditions using Laplace's equation.
*/

int main() {
  
  using namespace std;

  int x_values=100, y_values=100; //Defines the number of x and y points on the grid
  int iterations=1000; //Defines the number of iterations of the program
  float V[x_values][y_values][iterations]; //Initialises array to store the values of the potential
  float lambda=2-3.14159;  //Relaxation parameter MODIFY TO EXAMINE CONVERGENCE

  //SECTION OF CODE TO SET INITIAL CONDITIONS GOES HERE


  //DETERMINATION OF THE POTENTIAL

  for (int q=1; q<iterations; q++) { //Iterations
    for (int i=0; i<x_values; i++) { //x-positions
      for (int j=0; j<y_values; j++) { //y-positions
	
	//IF STATEMENT GOES HERE

	V[i][j][q] = (1-lambda)*V[i][j][q-1]+ (lambda*0.25)*(V[a][b][q] + V[c][d][q-1] + V[e][f][q] + V[g][h][q-1]);
	}
    }
  }


  //OUTPUT OF POTENTIALS

  ofstream outFile;
  outFile.open("ORpotential.dat");

  for (int i=0; i<x_values; i++) {
    for (int j=0; j<y_values;j++) {
      outFile << V[i][j][-1] << endl;
    }
  }
  
  cout << "Data stored in file ORPotential.dat." << endl;

  outFile.close();

  return 0;
}
