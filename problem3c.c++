//This program simulates a Gas Electron Multiplier. Two plates are set at opposite ends of the grid, one grounded the other at a positive potential.
//Two pairs of plates are set in between these two, at a high potential difference between the two, closely separated.


#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>

#define max 100                        /* number of grid points */

//Voltages:

#define V_1 10.0 			/* Bottom plate voltage*/
#define V_2 200.0			/* Middle plate voltage*/
#define V_3 300.0			/* Top plate voltage */



//Define parameter for bottom pair of finite thickness plates
#define t_0 15.0				/* height above ground of bottom side of first plate*/


//Parameters for top pair of finite thickness plates
#define t_y 20.0				/*height of above ground of bottom side of top plate*/

//Common parameters for both plates
#define t_x 15.0				/*length of plates*/
#define dy 2.0				/*thickness of plates */


using namespace std;

int main()
{
  double x, p[max][max];
  int i, j, iter, y;
  
  timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);

  ofstream myfile;
  myfile.open("problem3c.dat");
  for(i=0; i<max; i++)
    {
      for (j=0; j<max; j++) p[i][j] = 0;	/* clear the array */
    }

  for(i=0; i<(max); i++){
    p[i][0] = 0;        /* Set the ground plate */
  }

     

  for(i=0; i<max; i++) p[i][max-1] = V_3; 	/* Set top plate to V_3 voltage */

  for(iter=0; iter<1000; iter++)               /* iterations */
    {
      for(i=1; i<(max-1); i++)                  /* x-direction */
	{
	  for(j=1; j<(max-1); j++){               /* y-direction */

	    p[i][j] = 0.25*(p[i+1][j]+p[i-1][j]+p[i][j+1]+p[i][j-1]);
	    if((i>=0 && i<=t_x) || (i>=max-t_x && i<=max-1)){
	      if(j>=t_0 && j<=(t_0+dy)){
		p[i][j]=V_1;			/* Set bottom plates to V_1 voltage */

	      }
	    }
	    if((i>=0 && i<=t_x) || (i>=max-t_x && i<=max-1)){
	      if(j>=t_y && j<=(t_y+dy)){
		p[i][j]=V_2;	
		/* Set middle plates to V_2 voltage*/


	      }
	    }
	  }
	}
    }
  

 for (i=0; i<max ; i++)         /* write data gnuplot 3D format */
   {
      for (j=0; j<max; j++) 
	{	
	/* save data in problem3c.dat */
	  myfile << p[i][j] << endl;
	 
      }
      myfile << "\n";	  /* empty line for gnuplot */
   }
   cout << "Data stored in problem3c.dat"<< endl;
   myfile.close();
  
     
  }
