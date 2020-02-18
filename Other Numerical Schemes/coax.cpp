//This program generates two coaxial cylinders, of different radii. The inner cylinder is grounded while the outer one is at a positive potential. The outer cylinder is treated as a disk of thickness t=rad3-rad2, where rad3 and rad2 are the radii of the outer and inner edges of the disk.

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;


int fdm(int iters, int max, double rad1, double rad3, double voltage) {
  double x, p[max][max];
  int i, j, iter, y;
  
  int rad2 = rad3-2;
  int cent = max/2;
  
  timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);

  
  
  ofstream myfile;
  myfile.open("problem1.dat");
  for(i=0; i<max; i++)
    {
      for (j=0; j<max; j++) p[i][j] = 0;	/* clear the array */
    }
						   
   for(iter=0; iter<iters; iter++)               /* iterations */
     {
      for(i=1; i<(max-1); i++)                  /* x-direction */
	{
	 for(j=1; j<(max-1); j++){               /* y-direction */

	   p[i][j] = 0.25*(p[i+1][j]+p[i-1][j]+p[i][j+1]+p[i][j-1]);	/* Finite-difference method*/

	  if (((i-cent)*(i-cent)+(j-cent)*(j-cent)>= rad2*rad2) && ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad3*rad3)){
	      p[i][j] = voltage;
 	 /* Check point belongs on outer disk of thickness rad3-rad2, and set the disks potential to +100V */
	    }

      if ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad1*rad1 || (i-cent)*(i-cent)+(j-cent)*(j-cent)> rad3*rad3) p[i][j] = 0.0;
	}
	 /*Ground inner cylinder and points outside the outer edge of the disk*/
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
  
  return 0;
}

int main()
{
  int iters, max;
  double rad1, rad3, voltage;
  string method;
  
  // get user input for voltage and radius
  cout << "Voltage?" << endl;
  cin >> voltage;
  cout << "Radius of larger cylinder?" << endl;
  cin >> rad3;
  cout << "Radius of smaller cylinder?" << endl;
  cin >> rad1;
  cout << "Grid size?" << endl;
  cin >> max;
  cout << "Iterations?" << endl;
  cin >> iters; 
  cout << "Method?" << endl;
  cin >> method;
  
  if (method=="FDM") {
    fdm(iters, max, rad1, rad3, voltage);
  }
}