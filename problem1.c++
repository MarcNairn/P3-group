/* This program generates two coaxial cylinders, of different radii. The inner cylinder is grounded, while the surface of the outer one is at a positive potential. */

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>

#define max 100                         /* number of grid points */
#define rad1 10			       /* define the radius of the inner coaxial cylinder */
#define rad2 20				/*define the radius of the outer coaxial cylinder */ 				
#define cent 50 		       	/* define the centre of the coaxial circles */

using namespace std;

int main()
{
  double x, p[max][max];
  int i, j, iter, y;
  timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);

  ofstream myfile;
  myfile.open("problem1.dat");
  for(i=0; i<max; i++)
    {
      for (j=0; j<max; j++) p[i][j] = 0;	/* clear the array */
    }

  
  
   for(iter=0; iter<1000; iter++)               /* iterations */
     {
      for(i=1; i<(max-1); i++)                  /* x-direction */
	{
	 for(j=1; j<(max-1); j++){               /* y-direction */

	  p[i][j] = 0.25*(p[i+1][j]+p[i-1][j]+p[i][j+1]+p[i][j-1]);
 if ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad1*rad1) p[i][j] = 0.0;	/* set the inner cylinder to ground potential */
 if ((i-cent)*(i-cent)+(j-cent)*(j-cent)== rad2*rad2) p[i][j] = 100.0; /* Outer cylinders edge is set to a positive potential */
 if ((i-cent)*(i-cent)+(j-cent)*(j-cent)> rad2*rad2) p[i][j] = 0.0; /* Potential outside outer cylinder is set to zero*/ 	 
	 }
	}
     }

 for (i=0; i<max ; i++)         /* write data gnuplot 3D format */
   {
      for (j=0; j<max; j++) 
	{	
	/* save data in problem1.dat */
	myfile << p[i][j] << endl;
	 
      }
      myfile << "\n";	  /* empty line for gnuplot */
   }
   cout << "Data stored in problem1.dat"<< endl;
   myfile.close();
  
}
