//This program generates two coaxial cylinders, of different radii. The inner cylinder is grounded while the outer one is at a positive potential.

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


inline int wrap(int const x, int const size) {
  if (0 <= x && x < size){
      return x;
    }
  if (x < 0){
    return x + size;
  }
  else {
    return x - size;
  }
}


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

     

  for(i=0; i<max; i++) p[i][max-1] = 0.0; 	/* Ground top plate*/

  for(iter=0; iter<1000; iter++)               /* iterations */
    {
      for(i=1; i<(max-1); i++)                  /* x-direction */
	{
	  for(j=1; j<(max-1); j++){               /* y-direction */
	    
	    wrap (i+1, max);
	    wrap (j+1, max);
	    wrap (i-1, max);
	    wrap (j-1, max);

	    int a, b, c, d, e, f, g, h;
	    if (i+1 == max) {
		a = 0; }
	    else {
	      a = i+ 1;
	    }

	    b = j;

	    if (i-1 == -1) {
		c = max; }
	    else {
	      c = i-1;
	    }

	    d = j ;
	    e = i ;

	    if (j+1 == max) {
		f = 0; }
	    else {
	      f = j+ 1;
	    }

	    g = i;

	    if (j-1 == -1) {
		h = max; }
	    else {
	      h = j-1;
	    }

	    p[i][j] = 0.25*(p[a][b]+p[c][d]+p[e][f]+p[g][h]);

	    if((i>=0 && i<=t_x) || (i>=max-t_x && i<=max-1)){
	      if(j>=t_0 && j<=(t_0+dy)){
		p[i][j]=V_1;			/* Set second plate to V_1 voltage */

	      }
	    }
	    if((i>=0 && i<=t_x) || (i>=max-t_x && i<=max-1)){
	      if(j>=t_y && j<=(t_y+dy)){
		p[i][j]=V_2;	
		/* Set third plate to V_2 voltage*/


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
