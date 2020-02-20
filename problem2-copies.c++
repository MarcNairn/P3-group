#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <ctime>

#define max_y 1000                        /* number of grid points in y */
#define max_x 100		/* number of grid points in x */
#define rad 20				/* define the radius of the cylinder between plates */
#define cent_x 50			/* define coordenates of centre of circle */
#define cent_y 500				
using namespace std;

int main()
{
   double x, p[max_x][max_y];
   int i, j, iter, y;
  
   auto start = std::chrono::system_clock::now();

   ofstream myfile;
   myfile.open ("problem2-copies.dat");
   for(i=0; i<max_x; i++)                 /* clear the array  */
   {   
      for (j=0; j<max_y; j++) p[i][j] = 0;
   }

   for(i=0; i<max_x; i++) p[i][0] = 100.0;        /* p[i][0] = 100 V */		
   for(i=0; i<max_x; i++) p[i][max_y-1] = -100.0;
   


   for(iter=0; iter<1000; iter++)               /* iterations */
     {
      for(i=1; i<(max_x-1); i++)                  /* x-direction */
	{
	 for(j=1; j<(max_y-1); j++){               /* y-direction */

	  p[i][j] = 0.25*(p[i+1][j]+p[i-1][j]+p[i][j+1]+p[i][j-1]);
	  if ((i-cent_x)*(i-cent_x)+(j-cent_y)*(j-cent_y)<= rad*rad) p[i][j] = 0.0;
	}
	}
     }

  
   for (i=0; i<max_x ; i++)         /* write data gnuplot 3D format */
   {
      for (j=max_x; j<2*max_x; j++) 
	{	
	/* save data in problem2-copies.dat */
	myfile << p[i][j] << endl;
	 
      }
      myfile << "\n";	  /* empty line for gnuplot */
   }
   cout << "Data stored in problem2-copies.dat"<< endl;
   myfile.close();


 auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
     
    /*Check time elapsed since setting the first marker, that is, the time it takes to run the program */
  
}
