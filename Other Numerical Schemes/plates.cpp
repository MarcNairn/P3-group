/*This program generates, TWO PARALLEL PLATES at opposite potentials, with an added GROUNDED CYLINDER between the two*/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int fdm(int iters, int max, double rad, double voltage)
{
   double x, p[max][max];
   int i, j, iter, y;
   
   double cent = max/2; 
   
   ofstream myfile;
   myfile.open ("laplace.dat");
   for(i=0; i<max; i++)                 /* clear the array  */
   {   
      for (j=0; j<max; j++) p[i][j] = 0;
   }

   for(i=0; i<max; i++) p[i][0] = voltage;        /* p[i][0] = 100 V */		
   for(i=0; i<max; i++) p[i][max-1] = -1*voltage;
      


   for(iter=0; iter<iters; iter++)               /* iterations */
   {
      for(i=1; i<(max-1); i++)                  /* x-direction */
      {
         for(j=1; j<(max-1); j++)               /* y-direction */
         {
	    if ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad*rad){
	      p[i][j]=0.0;
	    }
	    else {
            p[i][j] = 0.25*(p[i+1][j]+p[i-1][j]+p[i][j+1]+p[i][j-1]);
	    }
         }
      }
   }
  
   for (i=0; i<max ; i++)         /* write data gnuplot 3D format */
   {
      for (j=0; j<max; j++) 
	{
	  /* if ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad*rad){
	 p[i][j]=0.0;
	 }*/		/* save data in laplace.dat */
	myfile << p[i][j] << endl;
	 
      }
      // myfile << "\n";	  /* empty line for gnuplot */
   }
   cout << "Data stored in laplace.dat"<< endl;
   myfile.close();
}

int main()
{
  int iters, max;
  double rad, voltage;
  string method;
  
  // get user input for voltage and radius
  cout << "Voltage of plates (oppositely charged)?" << endl;
  cin >> voltage;
  cout << "Radius of cylinder?" << endl;
  cin >> rad;
  cout << "Distance between plates?" << endl;
  cin >> max;
  cout << "Iterations?" << endl;
  cin >> iters; 
  cout << "Method?" << endl;
  cin >> method;
  
  if (method=="FDM") {
    fdm(iters, max, rad, voltage);
  }
}