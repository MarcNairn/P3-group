//This program reads in a data file containing a potential array representing the initial boundary conditions on an arbitrary electric potential field. The boindaries are specified by a further data file specifying which data points can and can't changed from their original potential array value throughout the calculation 

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <ctime>

#define max 100                        /* number of grid points */

//Voltages:

#define V_1 -10.0 			/* Bottom plate voltage*/
#define V_2 -200.0			/* Middle plate voltage*/
#define V_3 -300.0			/* Top plate voltage */



//Define parameter for bottom pair of finite thickness plates
#define t_0 15.0				/* height above ground of bottom side of first plate*/


//Parameters for top pair of finite thickness plates
#define t_y 20.0				/*height of above ground of bottom side of top plate*/

//Common parameters for both plates
#define t_x 15.0				/*length of plates*/
#define dy 2.0				/*thickness of plates */
#define dx 15.0 			/*distance between the plates*/

using namespace std;


inline int finite(int x, int y, int size){
  
  
  double p[size][size];
  int a, b, c, d, e, f, g, h;		//Set conditions on grid edges to set up preiodic boundary conditions
	    
  if (x+1 == size) {
    a = 0; }
  else {
    a = x+ 1;
  }

  b = y;

  if (x-1 == -1) {
    c = size; }
  else {
    c = x-1;
  }

  d = y ;
  e = x ;

  if (y+1 == size) {
    f = 0; }
  else {
    f = y+ 1;
  }

  g = x;

  if (y-1 == -1) {
    h = size; }
  else {
    h = y-1;
  }
  
  p[x][y] = 0.25*(p[a][b]+p[c][d]+p[e][f]+p[g][h]);
  /*Perform finite difference method on grid*/
  return 0;
}



int main()
{
  auto start = std::chrono::system_clock::now();

  double x, p[max][max], mask[max][max], bound[max][max];
  int i, j, iter, y;
  
   
  ofstream myfile;
  myfile.open("reader.dat");
  for(i=0; i<max; i++)
    {
      for (j=0; j<max; j++) p[i][j] = 0;	/* clear the array */
    }

  /*Read in boundary conditions from txt file given by Python */

  ifstream fp("potentialarray.dat");
  for (int i=0; i<max; i++){
     for(int j=0; j<max; j++){
       fp >> bound[i][j];					/*Reads in data file and stores each row of data columns into default array bound[i][j] which represents the boundary conditions on the system */
        if ( ! fp ) {
	  cout << "Error reading .txt file for element " << i <<","<< j<< endl;
	  return 1;
	}
     }
  }




  for(iter=0; iter<1000; iter++)               /* iterations */
    {
      for(i=1; i<(max-1); i++)                  /* x-direction */
	{
	  for(j=1; j<(max-1); j++){               /* y-direction */
	    
	    
	    ifstream fp2("maskarray.dat");		//read in masked array
	    for (int i=0; i<max; i++){			
	      for(int j=0; j<max; j++){
		fp2 >> mask[i][j];
		if (mask[i][j]==1.0){
		  p[i][j]=bound[i][j];			/*array consists of 0s and 1s. A 1 represents a point which are subject to the boundary conditions and don't change through the finite-difference method.*/
		}
		
		else {
		  p[i][j]=finite(i,j,max);
		    }
		


	      }
	    }
	  }
	}
    }

  

 for (i=0; i<max ; i++)         /* write data gnuplot 3D format */
   {
      for (j=0; j<max; j++) 
	{	
	/* save data in reader.dat */
	  myfile << p[i][j] << endl;
	 
      }
      myfile << "\n";	  /* empty line for gnuplot */
   }
   cout << "Data stored in reader.dat"<< endl;
   myfile.close();
  
  
   auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
     
    /*Check time elapsed since setting the first marker, that is, the time it takes to run the program */
}
