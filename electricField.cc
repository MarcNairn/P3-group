#include <iostream>
#include <cstdlib>
#include <fstream>

/*
This program takes a scalar field V and outputs the negative of the gradient, for an electrostatic
potential this is the electric field.
*/

int main() {

	using namespace std;

	int x_values=40, y_values=40; //Defines the number of x and y, grid of size (x_values)*(y_values)

	float x_0 = 0; //The starting x coordinate in space

	float y_0 = 0; //The starting y coordinate in space

	float h=0.5; //Defines the separation of the points (stepsize) in the grid

	float V[x_values][y_values]; //Defines array to store the values of the potential
	

	//SECTION OF CODE TO READ IN THE POTENTIAL FROM FILE


	float E[x_values][y_values][2]; //Initialises array to store E-field values, E[][][0] x component and E[][][1] y component of E-field

	ofstream outFile;
  	outFile.open("electricField.txt"); //opens file to write data to

  	 outFile << "x Pos \ty Pos \tE_x \tE_y" << endl; //writes headings in the output file

	for (int x=0; x<x_values; x++) { //Loops over x positions

		for (int y=0; y<y_values; y++) { //Loops over y positions

			//Calculation of x components of the E-field

			if ( x==0 ) { //If on left boundary of grid
				E[x][y][0] = -(V[x+1][y] - V[x][y])/h; //Finite difference using point to the right
			}

			else if ( x == (x_values-1) ) { //If on right boundary of grid
				E[x][y][0] = -(V[x][y] - V[x-1][y])/h; //Finite difference using point to the left
			}

			else { //If on central point of grid
				E[x][y][0] = -(V[x+1][y] - V[x-1][y])/(2*h); //Central difference method
			}

			//Calculation of y components of the E-field

			if ( y == 0 ) { //If on upper boundary of grid
				E[x][y][1] = -(V[x][y+1] - V[x][y])/h; //Finite difference using point below
			}

			else if ( y == (y_values-1) ) { //If on lower boundary of grid
				E[x][y][1] = -(V[x][y] - V[x][y-1])/h; //Finite difference using point from above
			}

			else { //If on central point of grid
				E[x][y][1] = -(V[x][y+1] - V[x][y-1])/(2*h); //Central difference method
			}

			outFile << x_0+x*h << "\t"  << y_0+y*h << "\t" << V[x][y] << "\t" << E[x][y][0] << "\t" << E[x][y][1] << endl; //outputs data to output file

		}
	}

	outFile.close(); //closes the output file

	return 0;
}