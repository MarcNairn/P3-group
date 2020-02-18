//This program reads in a data file containing a potential array representing the initial boundary conditions on an arbitrary electric potential field. The boindaries are specified by a further data file specifying which data points can and can't changed from their original potential array value throughout the calculation 

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <ctime>

/* ...................number of grid points ................*/

#define max_y 850     	//y grid points of data file                
#define max_x 540	//x grid points of data file

/* .........................................................*/
using namespace std;


int main()
{
  auto start = std::chrono::system_clock::now();

  double x, p[max_x][max_y], mask[max_x][max_y], bound[max_x][max_y];
  int i, j, iter, y;
  
  ofstream myfile;
  myfile.open("reader3b.dat");
  for(i=0; i<max_x; i++)
    {
      for (j=0; j<max_y; j++) p[i][j] = 0;	/* clear the array */
    }

  /*Read in boundary conditions from txt file given by Python */

  ifstream fp("potentialarrayB.txt");
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

  ifstream fp2("maskarrayB.txt");		//read in masked array
  for (int i=0; i<max_x; i++){			
    for(int j=0; j<max_y; j++){
      fp2 >> mask[i][j];		//Store .txt file in 2D array mask[][]
    }
  }

 

  for(iter=0; iter<10000; iter++)               /* iterations */
    {

      for(i=0; i<(max_x); i++)                  /* x-direction */
	{

	  for(j=0; j<(max_y); j++){               /* y-direction */

	   
	    if (mask[i][j]==0){

	      p[i][j]=bound[i][j];			/*array consists of 0s and 1s. A 1 represents a point which are subject to the boundary conditions and don't change through the finite-difference method.*/
		
	    }
		
	    else {
		  
        
		   
		  int a, b, c, d, e, f, g, h;		//Set conditions on grid edges to set up periodic boundary conditions
	    
		  if (i+1 == max_x) {
		    a = 0; 
		  
		  }
		  else {
		    a = i+ 1;
		  }

		  b = j;

		  if (i-1 == -1) {
		    c = max_x; }
		  else {
		    c = i-1;
		  }

		  d = j ;
		  e = i ;

		  if (j+1 == max_y) {
		    f = 0; }
		  else {
		    f = j+ 1;
		  }

		  g = i;

		  if (j-1 == -1) {
		    h = max_y; }
		  else {
		    h = j-1;
		  }
  
		  p[i][j] = 0.25*(p[a][b]+p[c][d]+p[e][f]+p[g][h]);
		 
		  //perform finite difference method with periodic boundary conditions.
		  
		  
		}
	  }
	}
    }


  for (i=0; i<max_x ; i++)         /* write data gnuplot 3D format */
    {
      for (j=0; j<max_y; j++) 
	{	
	  /* save data in reader3b.dat */
	 
	  myfile << p[i][j] << endl;

	}
      myfile << "\n";	/* empty line for gnuplot */

    }
  cout << "Data stored in reader3b.dat"<< endl;
  myfile.close();
  
     

   
  auto end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end-start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << "finished computation at " << std::ctime(&end_time)
	    << "elapsed time: " << elapsed_seconds.count() << "s\n";
     
  /*Check time elapsed since setting the first marker, that is, the time it takes to run the program */
}
