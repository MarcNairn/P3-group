#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <string>

/*
This program takes a scalar field V and outputs the negative of the gradient, for an electrostatic
potential this is the electric field.

Requires command line arguments in the form:

<executable> <x> <y>

where x is the width of the image and y is the height.

*/

int main(int argc, char** argv) {

	using namespace std;
	
	int x_values = atoi(argv[1]);
	int y_values = atoi(argv[2]);
	
	float h = 100/(x_values+0.0); //Defines the separation of the points (stepsize) in the grid
	float V[x_values][y_values]; //Defines array to store the values of the potential
	float mask[x_values][y_values]; //Defines array to store the mask array
	float E[x_values][y_values][2]; //Initialises array to store E-field values, E[][][0] x component and E[][][1] y component of E-field
	float magE=0; //Defines variable to store the |E|
	float maxE=0, minE=100; //Defines the maximum and minimum values of |E|
	
	
	//IMPORT OF POTENTIAL DATA 
	
	ifstream potentialFile("reader.dat"); //Imports potential data
	for (int i=0; i<y_values; i++){ 
	  for(int j=0; j<x_values; j++){
	    potentialFile >> V[j][i]; //Stores data in potential array
	  }
	}

	
	//IMPORT OF MASK
	
	ifstream maskFile("maskarray.txt");
	for (int i=0; i<y_values; i++){ 
	  for (int j=0; j<x_values; j++){
	    maskFile >> mask[j][i]; //Stores data in potential array
	  }
	}

	
	//DECLARATION OF OUTPUT FILE
	
	ofstream outFile;
  	outFile.open("electricField.dat"); //Opens file to write data to
	
	for (int x=0; x<x_values; x++) { //Loops over x positions
	  
	  for (int y=0; y<y_values; y++) { //Loops over y positions
		  
		  if ( mask[x][y] == 0 ) { //If out with desired region
		    E[x][y][0] = 0; //Sets the x component of E to 0
		    E[x][y][1] = 0; //Sets the y component of E to 0
		  }
		  
		  else {

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
		  }
		  
		  magE = ((E[x][y][0])*(E[x][y][0]) + (E[x][y][1])*(E[x][y][1]));
		  
		  //DETERMINATION OF MAX/MIN VALUES OF |E|
		  
		  if ( ((E[x][y][0])*(E[x][y][0])+ (E[x][y][1])*(E[x][y][1]))<minE ) { //Checks for new minimum value of |E|
		    minE = magE; //Sets new minimum value of |E|
		  }
		  
		  if ( ((E[x][y][0])*(E[x][y][0])+ (E[x][y][1])*(E[x][y][1]))>maxE ) { //Checks for new maximum value of |E|
		    maxE = magE; //Sets new maximum value of |E|
		  }
		  
		  outFile << x*h << "\t" << y*h  << "\t" << E[x][y][0] << "\t" << E[x][y][1]  << endl; //outputs data to output file
		  
		}
	}

	outFile.close(); //closes the output file

	cout << "Max |E|: " << sqrt(maxE) << "\nMin |E|: " << sqrt(minE) << endl; //Outputs maximum/minimum values of |E| to terminal

	return 0;
}
