//This program generates two coaxial cylinders, of different radii. The inner cylinder is grounded while the outer one is at a positive potential. The outer cylinder is treated as a disk of thickness t=rad3-rad2, where rad3 and rad2 are the radii of the outer and inner edges of the disk.

//.............................USING THE SUCCESSIVE OVER RELAXATION METHOD ..............

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
  double x, oldV[max][max], currentV[max][max], diffMatrix[max][max], V0[max][max];
  int i, j, iter, y;

  auto start = std::chrono::system_clock::now();

  ofstream myfile;
  myfile.open("SOR.dat");

  double lambda=1.5;

  for(i=0; i<max; i++)
    {
      for (j=0; j<max; j++){ 
	
	V0[i][j] = 0;	/* clear arrays*/
	oldV[i][j]=0;
	currentV[i][j]=0;
	
	
      }
    }
  /*INITIAL BOUNDARY CONDITIONS FOR VOLTAGE MATRICES*/
  for (i=0;i<max;i++){
    for (j=0;j<max;j++){

	if (((i-cent)*(i-cent)+(j-cent)*(j-cent)>= rad2*rad2) && ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad3*rad3)){
	  V0[i][j] = 100.0;
	  oldV[i][j]=100.0;
	  currentV[i][j]=100.0;
	  /* Check point belongs on outer disk of thickness rad3-rad2, and set the disks potential to +100V */
	}

	if ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad1*rad1 || (i-cent)*(i-cent)+(j-cent)*(j-cent)> rad3*rad3){
	  V0[i][j] = 0.0;
	  oldV[i][j]=0.0;
	  currentV[i][j]=0;
      }
	   /*Ground inner cylinder and points outside the outer edge of the disk*/

    }
  }
	   
	   /*first iteration set out of the main loop, defining initial voltage V0; same as when doing Jacobi method*/
	  for(i=1; i<(max-1); i++)
	    {
	      for(j=1; j<(max-1); j++){  
		oldV[i][j] =(1-lambda)*V0[i][j]+lambda/4*(oldV[i+1][j]+V0[i-1][j]+oldV[i][j+1]+V0[i][j-1]);
	      }
	    }
    
				   
  for(iter=1;iter<10000;iter++){
	     /* iterations */
      for(i=1; i<(max-1); i++)                  /* x-direction */
	{
	 for(j=1; j<(max-1); j++){               /* y-direction */

	   currentV[i][j] =(1-lambda)*oldV[i][j]+lambda/4*(currentV[i+1][j]+currentV[i-1][j]+currentV[i][j+1]+currentV[i][j-1]);	/* Finite-difference method*/

	  if (((i-cent)*(i-cent)+(j-cent)*(j-cent)>= rad2*rad2) && ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad3*rad3)){
	      currentV[i][j] = 100.0;
 	 /* Check point belongs on outer disk of thickness rad3-rad2, and set the disks potential to +100V */
	    }

      if ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad1*rad1 || (i-cent)*(i-cent)+(j-cent)*(j-cent)> rad3*rad3) currentV[i][j] = 0.0;

	        oldV[i][j]=currentV[i][j];	
	}

	 /*Ground inner cylinder and points outside the outer edge of the disk*/
     }


  
     //At the end of every iteration, set the oldV equal to the newly obtained currentV, and repeat process until convergence


  }

      /*Take difference matrix*/
     
//     diffMatrix[i][j]=currentV[i][j]-oldV[i][j];
	      
     //Add all elements of difference matrix
     
  //   sum_of_elems= sum_of_elems + diffMatrix[i][j];
	      
     //Take average of all terms in the difference matrix
     
    // avgdiff=sum_of_elems/(max*max);

     
    
 for (i=0; i<max ; i++)         /* write data gnuplot 3D format */
   {
      for (j=0; j<max; j++) 
	{	
	/* save data in SOR.dat */
	myfile << currentV[i][j] << endl;
	 
      }
      myfile << "\n";	  /* empty line for gnuplot */
   }
   cout << "Data stored in SOR.dat"<< endl;
   myfile.close();
	 
  

   auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
	 << "elapsed time: " << elapsed_seconds.count() << "s\n";

}

