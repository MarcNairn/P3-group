//This program generates two coaxial cylinders, of different radii. The inner cylinder is grounded while the outer one is at a positive potential. The outer cylinder is treated as a disk of thickness t=rad3-rad2, where rad3 and rad2 are the radii of the outer and inner edges of the disk.
//.....................<<<<<<USING THE JACOBI ITERATION METHOD>>>>>>>..........
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <ctime>

#define max 100                         /* number of grid points */
#define rad1 20			       /* define the radius of the inner coaxial cylinder */
#define rad2 40				/*define the inner radius of the outer disk, belonging to the outer coaxial cylinder */ 	
#define rad3 44 			/*define the outer radius of the outer disk,*/
			
#define cent 50 		       	/* define the centre of the coaxial circles */

using namespace std;

int main()
{
  double x, currentV[max][max], oldV[max][max], diffMatrix[max][max],V0[max][max], avgdiff, updateMatrix[max][max];
  int i, j, iter, y, sum_of_elems=0;
 
  auto start = std::chrono::system_clock::now();

  ofstream myfile;
  myfile.open("Jacobi1.dat");
  for(i=0; i<max; i++){
    for (j=0; j<max; j++){
      V0[i][j] = 0; 	  /* clear the array */	
      oldV[i][j] = 0;
      currentV[i][j]=0;
    }
  }

  // Set initial conditions to define voltage arrays
 
  for (i=0; i<max; i++)
    {
      for (j=0;j<max;j++)
	{
	  if (((i-cent)*(i-cent)+(j-cent)*(j-cent)>= rad2*rad2) && ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad3*rad3)){
	    V0[i][j] = 100.0;
	    /* Check point belongs on outer disk of thickness rad3-rad2, and set the disks potentias */
	  }
      
    	  if ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad1*rad1 || (i-cent)*(i-cent)+(j-cent)*(j-cent)> rad3*rad3) V0[i][j] = 0.0;
	}
    }
  /*Set initial voltage matrix V0, perform Jacobi iteration on it to obtain oldV, from which the rest of the iteration follows. This is done to prevent the loop from reaching the convergence at the first step. Actual main loop starts after first iteration*/ 

  for(i=1; i<(max-1); i++)                  /* x-direction */
    {
      for(j=1; j<(max-1); j++){               /* y-direction */

	oldV[i][j]=0.25*(V0[i-1][j]+V0[i+1][j]+V0[i][j-1]+V0[i][j+1]);
      }
    }

  
  for (iter=1; iter<10000; iter++){
    /* iterates until convergence*/	
    for(i=1; i<(max-1); i++)                  /* x-direction */
      {
	for(j=1; j<(max-1); j++){               /* y-direction */
	  /* Perform Jacobi Iterative method on oldV to return currentV*/
	      
	  currentV[i][j]=0.25*(oldV[i-1][j]+oldV[i+1][j]+oldV[i][j-1]+oldV[i][j+1]);
				   
	  if (((i-cent)*(i-cent)+(j-cent)*(j-cent)>= rad2*rad2) && ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad3*rad3)){
	    currentV[i][j] = 100.0;
	    /* Check point belongs on outer disk of thickness rad3-rad2, and set the disks potential */
	  }

	  if ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad1*rad1 || (i-cent)*(i-cent)+(j-cent)*(j-cent)> rad3*rad3) currentV[i][j] = 0.0;
	    
	  /*Ground inner cylinder and points outside the outer edge of the disk*/
	  
	  //At the end of every iteration, set the oldV equal to the newly obtained currentV, and repeat process until convergence
	  oldV[i][j]=currentV[i][j];
	  /*Take difference matrix*/
	  //diffMatrix[i][j]=currentV[i][j]-oldV[i][j];
	      
	  //Add all elements of difference matrix
	  //sum_of_elems= sum_of_elems + diffMatrix[i][j];
	      
	  //Take average of all terms in the difference matrix
	  //avgdiff=sum_of_elems/(max*max);

	}
      }
  }
      


		



   
    /* iterations terminate once tolerance condition is met */




 for (i=0; i<max ; i++)         /* write data gnuplot 3D format */
   {
      for (j=0; j<max; j++) 
	{	
	/* save data in Jacobi1.dat */
	  /* only save last q output as it will be the best guess */
	myfile << currentV[i][j] << endl;
	 
      }
      myfile << "\n";	  /* empty line for gnuplot */
   }
   cout << "Data stored in Jacobi1.dat"<< endl;
   myfile.close();


   auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
	 << "elapsed time: " << elapsed_seconds.count() << "s\n";
     
    /*Check time elapsed since setting the first marker, that is, the time it takes to run the program */
  
}
