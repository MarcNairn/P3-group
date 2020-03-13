//This program generates two coaxial cylinders, of different radii. The inner cylinder is grounded while the outer one is at a positive potential.

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <ctime>

/*#define max 100                        //number of grid points

//Voltages:

#define V_1 -10.0 			//Bottom plate voltage
#define V_2 -200.0			//Middle plate voltage
#define V_3 -300.0			// Top plate voltage 



//Define parameter for bottom pair of finite thickness plates
#define t_0 15.0				//height above ground of bottom side of first plate


//Parameters for top pair of finite thickness plates
#define t_y 20.0				// height of above ground of bottom side of top plate

//Common parameters for both plates
#define t_x 15.0				// length of plates
#define dy 2.0				//Thickness of plates 
#define dx 15.0 			//distance between the plates */

using namespace std;

int fdm(int iters, int max_x, int max_y, int V_1, int V_2, int V_3, double t_0, double t_y, double t_x, double dy, double dx, string gif) {
 auto start = std::chrono::system_clock::now();       /*Set the marker to check the internal clock before the program executes */
  
  double x, p[max_x][max_y];
  int i, j, iter, y;
  


  ofstream myfile;
  myfile.open("gas.dat");
  for(i=0; i<max_x; i++)
    {
      for (j=0; j<max_y; j++) p[i][j] = 0;	/* clear the array */
    }

  for(i=0; i<max_x; i++){
    p[i][0] = 0;        /* Set the ground plate */
  }

     

  for(i=0; i<max_x; i++) p[i][max_y-1] = V_3; 	/* Set top plate potential*/

  for(iter=0; iter<iters; iter++)               /* iterations */
    {
      for(i=1; i<(max_x-1); i++)                  /* x-direction */
	{
	  for(j=1; j<(max_y-1); j++){               /* y-direction */
	    

	    p[i][j] = 0.25*(p[i+1][j]+p[i-1][j]+p[i][j+1]+p[i][j-1]);

	    if((i>=(dx/2) && i<=t_x+dx/2) || (i>=max_x-t_x-dx/2 && i<=max_x-1-dx/2) || (i>=max_x/3-t_x-dx/2 && i<=max_x/3-1-dx/2) ||(i>=max_x/3+dx/2 && i<=max_x/3+t_x+dx/2) || (i>=2*max_x/3-t_x-dx/2 && i<=2*max_x/3-1-dx/2) ||(i>=2*max_x/3+dx/2 && i<=2*max_x/3+t_x+dx/2)) {
	      if(j>=t_0 && j<=(t_0+dy)){
		p[i][j]=V_1;			/* Set second plate to V_1 voltage */

	      }
	    }
	    if((i>=(dx/2) && i<=t_x+dx/2) || (i>=max_x-t_x-dx/2 && i<=max_x-1-dx/2) || (i>=max_x/3-t_x-dx/2 && i<=max_x/3-1-dx/2) ||(i>=max_x/3+dx/2 && i<=max_x/3+t_x+dx/2) || (i>=2*max_x/3-t_x-dx/2 && i<=2*max_x/3-1-dx/2) ||(i>=2*max_x/3+dx/2 && i<=2*max_x/3+t_x+dx/2)){
	      if(j>=t_y && j<=(t_y+dy)){
		p[i][j]=V_2;	
		/* Set third plate to V_2 voltage*/


	      }
	    }
	  }
	}
    }

 for (i=max_x/3-1; i<2*max_x/3 ; i++)         /* write data gnuplot 3D format */
   {
      for (j=0; j<max_y; j++) 
	{	
	/* save data in copies.dat */
	  myfile << p[i][j] << endl;
	 
      }
      myfile << "\n";	  /* empty line for gnuplot */
   }
   if (gif != "yes") {
    cout << "Data stored in gas.dat"<< endl;
   }
   myfile.close();
  
  
    

	/*Check time elapsed since setting the first marker, that is, the time it takes to run the program */

  }

int jacobi(int iters, int max, int V_1, int V_2, int V_3, double t_0, double t_y, double t_x, double dy, double dx, string gif) {
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








  for(iter=0; iter<iters; iter++)               /* iterations */
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
   if (gif != "yes") {
    cout << "Data stored in Jacobi3c.dat"<< endl;
   }
   myfile.close();
  
  
     
    /*Check time elapsed since setting the first marker, that is, the time it takes to run the program */
}
  
  
}


int main()
{
  int iters, max_x, max_y;
  double V_1, V_2, V_3, t_0, t_y, t_x, dy, dx;
  string method, gif;
  
  /*cout << "Grid points x" << endl; // 300.0
  cin >> max_x;
  /*cout << "Grid points y" << endl; // 100.0
  cin >> max_y;
  cout << "Voltage of bottom plate" << endl; // -10.0
  cin >> V_1;
  cout << "Voltage of middle plate?" << endl; // -200.0
  cin >> V_2;
  cout << "Voltage of top plate?" << endl; // -300.0
  cin >> V_3;
  cout << "Height above ground of bottom side of first plate?" << endl; // 15.0
  cin >> t_0;
  cout << "Height of above ground of bottom side of top plate?" << endl; // 20.0
  cin >> t_y;
  cout << "Length of plates?" << endl; // 15.0
  cin >> t_x;
  cout << "Thickness of plates?" << endl; // 2.0
  cin >> dy;
  cout << "Distance between plates?" << endl; // 30.0
  cin >> dx;*/
  cout << "Iterations?" << endl;
  cin >> iters; 
  cout << "Method?" << endl;
  cin >> method;
  cout << "Gif? (if yes, will take significantly longer to run!)" << endl;
  cin >> gif;
  
  max_x = 300.0;
  max_y = 100;
  V_1 = -10;
  V_2 = -200;
  V_3 = -300;
  t_0 = 15;
  t_y = 20;
  t_x = 25;
  dy = 5;
  dx = 30;
  
  
  // create gif for each iteration depending on given step size
  if (method=="FDM" || method=="fdm") {
    fdm(iters, max_x, max_y, V_1, V_2, V_3, t_0, t_y, t_x, dy, dx, gif);
    if (gif =="yes") {
      int max_iters, step;
      cout << "Max iterations?" << endl;
      cin >> max_iters;
    
      cout << "Step size between each iteration?" << endl;
      cin >> step;
    
      for (int i=0; i<=(max_iters/step); i++) {
	string str;
	ofstream myfile;
	myfile.open("/home/2317101h/year_3/group_project/numerical_sol/section2.2/anim/" + std::to_string(i*step) +".dat");
	fdm(i*step, max_x, max_y, V_1, V_2, V_3, t_0, t_y, t_x, dy, dx, gif);
	ifstream infile;
	infile.open("gas.dat");
	while (std::getline(infile, str)) {
	  myfile << str << endl;
	}
	cout << "Data stored in " << i*step << ".dat" << endl;
      }
    }
  }
  
   if (method=="Jacobi" || method=="jacobi") {
    jacobi(iters, max, V_1, V_2, V_3, t_0, t_y, t_x, dy, dx, gif);
    if (gif =="yes") {
      int max_iters, step;
      cout << "Max iterations?" << endl;
      cin >> max_iters;
    
      cout << "Step size between each iteration?" << endl;
      cin >> step;
    
      for (int i=0; i<=(max_iters/step); i++) {
	string str;
	ofstream myfile;
	myfile.open("/home/2317101h/year_3/group_project/numerical_sol/section2.2/anim/jacobi/text" + std::to_string(i*step) +".dat");
	fdm(i*step, max_x, max_y, V_1, V_2, V_3, t_0, t_y, t_x, dy, dx, gif);
	ifstream infile;
	infile.open("Jacobi3c.dat");
	while (std::getline(infile, str)) {
	  myfile << str << endl;
	}
	cout << "Data stored in " << i*step << ".dat" << endl;
      }
    }
  }
}
  