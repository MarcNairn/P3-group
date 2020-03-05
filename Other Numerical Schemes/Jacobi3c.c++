//This program generates two coaxial cylinders, of different radii. The inner cylinder is grounded while the outer one is at a positive potential.

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <ctime>

#define max 100                        /* number of grid points */

//Voltages:

#define V_1 -10.0 			/* Bottom plate voltage*/
#define V_2 -200.0			/* Middle plate voltage*/
#define V_3 -300.0			/* Top plate voltage */



//Define parameter for bottom pair of finite thickness plates
#define t_0 15.0				/* height above ground of bottom side of first plate*/


//Parameters for top pair of finite thickness plates
#define t_y 20.0				/*height of above ground of bottom side of top plate*/

//Common parameters for both plates
#define t_x 15.0				/*length of plates*/
#define dy 2.0				/*thickness of plates */
#define dx 15.0 			/*distance between the plates*/

using namespace std;

int main()
{
  auto start = std::chrono::system_clock::now();

  double x, oldV[max][max], currentV[max][max], V0[max][max];
  int i, j, iter, y, sum_of_elems=0;
  
  
  
  ofstream myfile;
  myfile.open("Jacobi3c.dat");
  for(i=0; i<max; i++)
    {
      for (j=0; j<max; j++){
	oldV[i][j] = 0;
	V0[i][j]=0;
	currentV[i][j]=0;
      }
    }

  for(i=0; i<(max); i++){
    V0[i][0] = 0;
    oldV[i][0]=0;/* Set the ground plate */
    currentV[i][0]=0;
  }

     

  for(i=0; i<max; i++){
    V0[i][max-1] = V_3; 
    oldV[i][max-1]=V_3;
    currentV[i][max-1]=V_3;/* Set top plate potential*/
  }


  for(i=1;i<max-1;i++){
    for(j=1;j<max-1;j++){
      
      if((i>=dx/2 && i<=dx/2+t_x) || (i>=max-t_x-dx/2 && i<=max-1-dx/2)){
	
	if(j>=t_0 && j<=(t_0+dy)){
	  V0[i][j]=V_1;			/* Set second plate to V_1 voltage */

	}
      }
      if((i>=dx/2 && i<=dx/2+t_x) || (i>=max-t_x-dx/2 && i<=max-1-dx/2)){
	if(j>=t_y && j<=(t_y+dy)){
	  V0[i][j]=V_2;	
	  /* Set third plate to V_2 voltage*/
	}
      }
    }
  }

  for (i=1;i<max-1;i++){
    for (j=1;j<max-1;j++){
      
       int a, b, c, d, e, f, g, h;		//Set conditions on grid edges to set up preiodic boundary conditions
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
	    
      
      oldV[i][j] = 0.25*(V0[a][b]+V0[c][d]+V0[e][f]+V0[g][h]);

    }
  }








  for(iter=0; iter<10000; iter++)               /* iterations */
    {
      for(i=1; i<(max-1); i++)                  /* x-direction */
	{
	  for(j=1; j<(max-1); j++){               /* y-direction */
	    
	    int a, b, c, d, e, f, g, h;		//Set conditions on grid edges to set up preiodic boundary conditions
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

	    currentV[i][j] = 0.25*(oldV[a][b]+oldV[c][d]+oldV[e][f]+oldV[g][h]);

	    if((i>=dx/2 && i<=dx/2+t_x) || (i>=max-t_x-dx/2 && i<=max-1-dx/2)){
	      if(j>=t_0 && j<=(t_0+dy)){
		currentV[i][j]=V_1;			/* Set second plate to V_1 voltage */

	      }
	    }
	    if((i>=dx/2 && i<=dx/2+t_x) || (i>=max-t_x-dx/2 && i<=max-1-dx/2)){
	      if(j>=t_y && j<=(t_y+dy)){
		currentV[i][j]=V_2;	
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
	  myfile << currentV[i][j] << endl;
	 
      }
      myfile << "\n";	  /* empty line for gnuplot */
   }
   cout << "Data stored in problem3c.dat"<< endl;
   myfile.close();
  
  
   auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
     
    /*Check time elapsed since setting the first marker, that is, the time it takes to run the program */
}
