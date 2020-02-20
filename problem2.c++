#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <ctime>

#define max 100                         /* number of grid points */
#define rad 20				/* define the radius of the cylinder between plates */
#define cent 50				/* define centre of circle */
using namespace std;

int main()
{
   double x, p[max][max];
   int i, j, iter, y;
  
   auto start = std::chrono::system_clock::now();

   ofstream myfile;
   myfile.open ("problem2.dat");
   for(i=0; i<max; i++)                 /* clear the array  */
   {   
      for (j=0; j<max; j++) p[i][j] = 0;
   }

   for(i=0; i<max; i++) p[i][0] = 100.0;        /* p[i][0] = 100 V */		
   for(i=0; i<max; i++) p[i][max-1] = -100.0;
   


   for(iter=0; iter<1000; iter++)               /* iterations */
     {
      for(i=1; i<(max-1); i++)                  /* x-direction */
	{
	 for(j=1; j<(max-1); j++){               /* y-direction */

	  if ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad*rad) p[i][j] = 0.0;
	  else {

	    int a, b, c, d, e, f, g, h;		//Set conditions on grid edges to set up preiodic boundary conditions

	    if (i+1 == size) {
		a = 0; }
	    else {
	      a = i+ 1;
	    }

	    b = j;

	    if (i-1 == -1) {
		c = size; }
	    else {
	      c = i-1;
	    }

	    d = j ;
	    e = i ;

	    if (j+1 == size) {
		f = 0; }
	    else {
	      f = j+ 1;
	    }

	    g = i;

	    if (j-1 == -1) {
		h = size; }
	    else {
	      h = j-1;
	    }

	    p[x][y] = 0.25*(p[a][b]+p[c][d]+p[e][f]+p[g][h]);
	    
	    return 0;
	  }

	 }
	}
     }

  
   for (i=0; i<max ; i++)         /* write data gnuplot 3D format */
   {
      for (j=0; j<max; j++) 
	{	
	/* save data in problem2.dat */
	myfile << p[i][j] << endl;
	 
      }
	myfile << "\n";	  /* empty line for gnuplot */
   }
   cout << "Data stored in problem2.dat"<< endl;
   myfile.close();


 auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
     
    /*Check time elapsed since setting the first marker, that is, the time it takes to run the program */
  
}
