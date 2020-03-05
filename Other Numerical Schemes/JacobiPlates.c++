/*This program generates, TWO PARALLEL PLATES at opposite potentials, with an added GROUNDED CYLINDER between the two*/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <chrono>

#define max 100                         /* number of grid points */
#define rad 20				/* define the radius of the cylinder between plates, recall analytic solution is only valid in the low radius region */
#define cent 50				/* define centre of circle */
using namespace std;

int main()
{
  double x, oldV[max][max], currentV[max][max],diffMatrix[max][max],V0[max][max], avgdiff, updateMatrix[max][max];
  int i, j, iter, y, sum_of_elems=0;
   
  auto start = std::chrono::system_clock::now();

   ofstream myfile;
   myfile.open ("Jacobi2.dat");
   for(i=0; i<max; i++)                 /* clear the array  */
   {   
     for (j=0; j<max; j++) {
       oldV[i][j]=0;
       currentV[i][j]=0;
       V0[i][j]=0;
     }
   }

   for(i=0; i<max; i++){
     V0[i][0] = 100.0;
     oldV[i][0]=100.0;
     currentV[i][0];
   } 		
     for(i=0; i<max; i++){
       V0[i][max-1] = -100.0;
       oldV[i][max-1]=-100.0;
       currentV[i][max-1]=-100.0;
     }
   for(i=1; i<max-1; i++){
     
     for(j=1; j<max-1; j++){
       oldV[i][j]=0.25*(V0[i-1][j]+V0[i+1][j]+V0[i][j-1]+V0[i][j+1]);
     }
   }
   

   for(iter=1; iter<10000; iter++)               /* iterations */
   {
      for(i=1; i<(max-1); i++)                  /* x-direction */
      {
         for(j=1; j<(max-1); j++)               /* y-direction */
         {
	    
	   currentV[i][j]=0.25*(oldV[i-1][j]+oldV[i+1][j]+oldV[i][j-1]+oldV[i][j+1]);

	   if ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad*rad){
	      currentV[i][j]=0.0;
	    }
	   oldV[i][j]=currentV[i][j];
         }
      }
      //At the end of every iteration, set the oldV equal to the newly obtained currentV, and repeat process until convergence
      // oldV[i][j]=currentV[i][j];
      /*Take difference matrix*/
      //diffMatrix[i][j]=currentV[i][j]-oldV[i][j];
	      
      //Add all elements of difference matrix
      //sum_of_elems= sum_of_elems + diffMatrix[i][j];
	      
      //Take average of all terms in the difference matrix
      //avgdiff=sum_of_elems/(max*max);

   }
  
   for (i=0; i<max ; i++)         /* write data gnuplot 3D format */
   {
      for (j=0; j<max; j++) 
	{

	 		/* save data in Jacobi2.dat */
	myfile << currentV[i][j] << endl;
	 
      }
      myfile << "\n";	  /* empty line for gnuplot */
   }
   cout << "Data stored in Jacobi2.dat"<< endl;
   myfile.close();



   auto end = std::chrono::system_clock::now();

   std::chrono::duration<double> elapsed_seconds = end-start;
   std::time_t end_time = std::chrono::system_clock::to_time_t(end);

   std::cout << "finished computation at " << std::ctime(&end_time)
	     << "elapsed time: " << elapsed_seconds.count() << "s\n";
     
   /*Check time elapsed since setting the first marker, that is, the time it takes to run the program */
}
