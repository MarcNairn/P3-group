//This program generates two coaxial cylinders, of different radii. The inner cylinder is grounded while the outer one is at a positive potential.

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>

#define max_x 200                        /* number of x  grid points */
#define max_y 100 			/* number of y grid points */
//Voltages:

#define V_1 -10.0 			/* Bottom plate voltage*/
#define V_2 -200.0			/* Middle plate voltage*/
#define V_3 -300.0			/* Top plate voltage */



//Define parameter for bottom pair of finite thickness plates
#define t_0 15.0				/* height above ground of bottom side of first plate*/


//Parameters for top pair of finite thickness plates
#define t_y 20.0				/*height above ground of bottom side of top plate*/

//Common parameters for both plates
#define t_x 15.0				/*length of plates*/
#define dy 2.0				/*thickness of plates */
#define dx 30.0				/*distance between the plates */

using namespace std;


int main()
{
  double x, p[max_x][max_y];
  int i, j, iter, y;
  
  timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);

  ofstream myfile;
  myfile.open("copies.dat");
  for(i=0; i<max_x; i++)
    {
      for (j=0; j<max_y; j++) p[i][j] = 0;	/* clear the array */
    }

  for(i=0; i<max_x; i++){
    p[i][0] = 0;        /* Set the ground plate */
  }

     

  for(i=0; i<max_x; i++) p[i][max_y-1] = V_3; 	/* Set top plate potential*/

  for(iter=0; iter<1000; iter++)               /* iterations */
    {
      for(i=1; i<(max_x-1); i++)                  /* x-direction */
	{
	  for(j=1; j<(max_y-1); j++){               /* y-direction */
	    

	    p[i][j] = 0.25*(p[i+1][j]+p[i-1][j]+p[i][j+1]+p[i][j-1]);

	    if((i>=(dx/2) && i<=t_x+dx/2) || (i>=max_x-t_x-dx/2 && i<=max_x-1-dx/2) || (i>=max_x/2-t_x-dx/2 && i<=max_x/2-1-dx/2) ||(i>=max_x/2+dx/2 && i<=max_x+t_x+dx/2)) {
	      if(j>=t_0 && j<=(t_0+dy)){
		p[i][j]=V_1;			/* Set second plate to V_1 voltage */

	      }
	    }
	    if((i>=(dx/2) && i<=t_x+dx/2) || (i>=max_x-t_x-dx/2 && i<=max_x-1-dx/2) || (i>=max_x/2-t_x-dx/2 && i<=max_x-1-dx/2) ||(i>=max_x/2+dx/2 && i<=max_x+t_x+dx/2)){
	      if(j>=t_y && j<=(t_y+dy)){
		p[i][j]=V_2;	
		/* Set third plate to V_2 voltage*/


	      }
	    }
	  }
	}
    }
  

 for (i=0; i<max_x/2 ; i++)         /* write data gnuplot 3D format */
   {
      for (j=0; j<max_y; j++) 
	{	
	/* save data in copies.dat */
	  myfile << p[i][j] << endl;
	 
      }
      myfile << "\n";	  /* empty line for gnuplot */
   }
   cout << "Data stored in copies.dat"<< endl;
   myfile.close();
  
     
  }
