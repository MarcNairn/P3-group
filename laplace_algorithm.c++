#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>

#define max 40                         /* number of grid points */

using namespace std;

int main()
{
   double x, p[max][max];
   int i, j, iter, y;
   
   ofstream myfile;
   myfile.open ("laplace.dat");
   for(i=0; i<max; i++)                 /* clear the array  */
   {   
      for (j=0; j<max; j++) p[i][j] = 0;
   }

   for(i=0; i<max; i++) p[i][0] = 100.0;        /* p[i][0] = 100 V */		

   for(iter=0; iter<1000; iter++)               /* iterations */
   {
      for(i=1; i<(max-1); i++)                  /* x-direction */
      {
         for(j=1; j<(max-1); j++)               /* y-direction */
         {
            p[i][j] = 0.25*(p[i+1][j]+p[i-1][j]+p[i][j+1]+p[i][j-1]);
         }
      }
   }
   
   for (i=0; i<max ; i++)         /* write data gnuplot 3D format */
   {
      for (j=0; j<max; j++) 
      {
			/* save data in laplace.dat */
	myfile << p[i][j] << endl;
	 
      }
      myfile << "\n" << endl;	  /* empty line for gnuplot */
   }
   cout << "Data stored in laplace.dat"<< endl;
   myfile.close();
}
