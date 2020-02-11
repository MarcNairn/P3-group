//This program reads in a data file containing a potential array representing the initial boundary conditions on an arbitrary electric potential field. The boindaries are specified by a further data file specifying which data points can and can't changed from their original potential array value throughout the calculation 

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <ctime>

#define max_x 607                        /* number of grid points */
#define max_y 540


//Define parameter for bottom pair of finite thickness plates
#define t_0 15.0				/* height above ground of bottom side of first plate*/


//Parameters for top pair of finite thickness plates
#define t_y 20.0				/*height of above ground of bottom side of top plate*/

//Common parameters for both plates
#define t_x 15.0				/*length of plates*/
#define dy 2.0				/*thickness of plates */
#define dx 15.0 			/*distance between the plates*/

using namespace std;
/*
inline int finite(int x, int y,int size_x, int size_y, int (*q)[size_y]{
  


  int a, b, c, d, e, f, g, h;		//Set conditions on grid edges to set up periodic boundary conditions
	    
  if (x+1 == size_x) {
    a = 0; 
    cout << a <<"\n";
  }
  else {
    a = x+ 1;
  }

  b = y;

  if (x-1 == -1) {
    c = size_x; }
  else {
    c = x-1;
  }

  d = y ;
  e = x ;

  if (y+1 == size_y) {
    f = 0; }
  else {
    f = y+ 1;
  }

  g = x;

  if (y-1 == -1) {
    h = size_y; }
  else {
    h = y-1;
  }
  
  p[x][y] = 0.25*(q[a][b]+q[c][d]+q[e][f]+q[g][h]);
  /*Perform finite difference method on grid*/
/* return 0;
}

*/

int main()
{
  auto start = std::chrono::system_clock::now();

  double x, p[max_x][max_y], mask[max_x][max_y], bound[max_x][max_y];
  int i, j, iter, y;
  
   
  ofstream myfile;
  myfile.open("reader.dat");
  for(i=0; i<max_x; i++)
    {
      for (j=0; j<max_y; j++) p[i][j] = 0;	/* clear the array */
    }

  /*Read in boundary conditions from txt file given by Python */

  ifstream fp("potentialarrayC.txt");
  for (int i=0; i<max_x; i++){
     for(int j=0; j<max_y; j++){
       fp >> bound[i][j];
       /*Reads in data file and stores each row of data columns into default array bound[i][j] which represents the boundary conditions on the system */

        if ( ! fp ) {
	  cout << "Error reading .txt file for element " << i <<","<< j<< endl;
	  return 1;
	}
     }
  }

  ifstream fp2("maskarrayC.txt");		//read in masked array
  for (int i=0; i<max_x; i++){			
    for(int j=0; j<max_y; j++){
      fp2 >> mask[i][j];
      }
  }

 

  for(iter=0; iter<1000; iter++)               /* iterations */
    {

      for(i=1; i<(max_x-1); i++)                  /* x-direction */
	{

	  for(j=1; j<(max_y-1); j++){               /* y-direction */

	   
		if (mask[i][j]==1){
        
		  p[i][j]=bound[i][j];			/*array consists of 0s and 1s. A 1 represents a point which are subject to the boundary conditions and don't change through the finite-difference method.*/
		}
		
		else {
	        	  
		  p[i][j] = 0.25*(p[i+1][j]+p[i-1][j]+p[i][j+1]+p[i][j-1]);
		  //perform finite difference method.
		  //finite(i,j,max_x, max_y);
		  
		    }
	  }
	}
    }
  

 for (i=0; i<max_x ; i++)         /* write data gnuplot 3D format */
   {
      for (j=0; j<max_y; j++) 
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
