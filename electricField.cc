#include <iostream>
#include <cstdlib>
#include <fstream>

/*
This program takes a scalar field V and outputs the negative of the gradient, for an electrostatic
potential this is the electric field.
*/

int main() {

	using namespace std;

	int x_values=100, y_values=100; //Defines the number of x and y, grid of size (x_values)*(y_values)
	float x_0 = 0; //Optional coordinate offset
	float y_0 = 0; //Optional coordinate offset
	float h = 1.0; //Defines the separation of the points (stepsize) in the grid
	float V[x_values][y_values]; //Defines array to store the values of the potential
	float E[x_values][y_values][2]; //Initialises array to store E-field values, E[][][0] x component and E[][][1] y component of E-field
	float magE=0; //Defines variable to store the |E|
	float maxE=0, minE=100; //Defines the maximum and minimum values of |E|
	
	
	//IMPORT OF POTENTIAL DATA 

	int i, j, iter, y;

	for(i=0; i<x_values; i++)                 /* clear the array  */
	  {   
	    for (j=0; j<y_values; j++) V[i][j] = 0;
	  }

	for(i=0; i<x_values; i++) V[i][0] = 100;        /* p[i][0] = 100 V */		
	for(i=0; i<x_values; i++) V[i][y_values-1] = -100;


	for (iter=0; iter<1000; iter++) {
	  for (i=1; i<x_values-1; i++) {
	    for (j=1; j<y_values-1; j++) {
	      V[i][j] = 0.25*(V[i+1][j] + V[i-1][j] + V[i][j+1] + V[i][j-1]);
	    }
	  }
	}


	ofstream outFile;
  	outFile.open("electricField.dat"); //Opens file to write data to

	for (int x=0; x<x_values-1; x++) { //Loops over x positions

		for (int y=0; y<y_values-1; y++) { //Loops over y positions
		  
			//OPTIONAL IF STATEMENT SHOULD BE ADDED HERE TO DEFINE REGIONS TO CALCULATE E-FIELD

			//CALCULATION OF THE X-COMPONENTS OF THE E-FIELD

		  	if ( x == 0 ) { //If on left boundary of grid
				E[x][y][0] = -(V[x+1][y] - V[x][y])/h; //Finite difference using point to the right
			}

			else if ( x == (x_values-1) ) { //If on right boundary of grid
				E[x][y][0] = -(V[x][y] - V[x-1][y])/h; //Finite difference using point to the left
			}

			else { //If on central point of grid
				E[x][y][0] = -(V[x+1][y] - V[x-1][y])/(2*h); //Central difference method
				}
   
		  
		  	//CALCULATION OF THE Y-COMPONENTS OF THE E-FIELD

		        if ( y == 0 ) { //If on lower boundary of grid
				E[x][y][1] = -(V[x][y+1] - V[x][y])/h; //Finite difference using point below
			}

			else if ( y == (y_values-1) ) { //If on upper boundary of grid
				E[x][y][1] = 0-(V[x][y] - V[x][y-1])/h; //Finite difference using point from above
			}
			
			else { //If on central point of grid
			  	E[x][y][1] = -(V[x][y+1] - V[x][y-1])/(2*h); //Central difference method
			}

			magE = ((E[x][y][0])*(E[x][y][0])+ (E[x][y][1])*(E[x][y][1]));

			//DETERMINATION OF MAX/MIN VALUES OF |E|

			if ( ((E[x][y][0])*(E[x][y][0])+ (E[x][y][1])*(E[x][y][1]))<minE ) { //Checks for new minimum value of |E|
				minE = magE; //Sets new minimum value of |E|
			}

			if ( ((E[x][y][0])*(E[x][y][0])+ (E[x][y][1])*(E[x][y][1]))>maxE ) { //Checks for new maximum value of |E|
				maxE = magE; //Sets new maximum value of |E|
			}
			
			outFile << x_0+x*h << "\t" << y_0+y*h  << "\t" << E[x][y][0] << "\t" << E[x][y][1]  << endl; //outputs data to output file

		}
	}

	outFile.close(); //closes the output file

	cout << "Max |E|: " << maxE << "\nMin |E|: " << minE << endl; //Outputs maximum/minimum values of |E| to terminal

	return 0;
}
