//This program generates two coaxial cylinders, of different radii. The inner cylinder is grounded while the outer one is at a positive potential. The outer cylinder is treated as a disk of thickness t=rad3-rad2, where rad3 and rad2 are the radii of the outer and inner edges of the disk.

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <ctime>

using namespace std;


int fdm(int iters, int max, double rad1, double rad3, double voltage, string gif) {
  double x, p[max][max];
  int i, j, iter, y;
  
  int rad2 = rad3-2;
  int cent = max/2;
 

  
  
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
   if (gif != "yes") {
    cout << "Data stored in problem1.dat"<< endl;
   }
   myfile.close(); 
  
  return 0;
}

int jacobi(int iters, int max, double rad1, double rad3, double voltage, string gif) 
{
  double x, currentV[max][max], oldV[max][max], diffMatrix[max][max],V0[max][max], avgdiff, updateMatrix[max][max];
  int i, j, iter, y, sum_of_elems=0;
 
  int rad2 = rad3-2;
  int cent = max/2;
  


  ofstream myfile;
  myfile.open("Jacobi1.dat");
  for(i=0; i<max; i++){
    for (j=0; j<max; j++){
      V0[i][j] = 0; 	  /* clear the array */	
      oldV[i][j] = 0;
      currentV[i][j]=0;
    }
  }

  // Set initial conditions to define voltage arrays
 
  for (i=0; i<max; i++)
    {
      for (j=0;j<max;j++)
	{
	  if (((i-cent)*(i-cent)+(j-cent)*(j-cent)>= rad2*rad2) && ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad3*rad3)){
	    V0[i][j] = 100.0;
	    /* Check point belongs on outer disk of thickness rad3-rad2, and set the disks potentias */
	  }
      
    	  if ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad1*rad1 || (i-cent)*(i-cent)+(j-cent)*(j-cent)> rad3*rad3) V0[i][j] = 0.0;
	}
    }
  /*Set initial voltage matrix V0, perform Jacobi iteration on it to obtain oldV, from which the rest of the iteration follows. This is done to prevent the loop from reaching the convergence at the first step. Actual main loop starts after first iteration*/ 

  for(i=1; i<(max-1); i++)                  /* x-direction */
    {
      for(j=1; j<(max-1); j++){               /* y-direction */

	oldV[i][j]=0.25*(V0[i-1][j]+V0[i+1][j]+V0[i][j-1]+V0[i][j+1]);
      }
    }

  
  for (iter=1; iter<iters; iter++){
    /* iterates until convergence*/	
    for(i=1; i<(max-1); i++)                  /* x-direction */
      {
	for(j=1; j<(max-1); j++){               /* y-direction */
	  /* Perform Jacobi Iterative method on oldV to return currentV*/
	      
	  currentV[i][j]=0.25*(oldV[i-1][j]+oldV[i+1][j]+oldV[i][j-1]+oldV[i][j+1]);
				   
	  if (((i-cent)*(i-cent)+(j-cent)*(j-cent)>= rad2*rad2) && ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad3*rad3)){
	    currentV[i][j] = voltage;
	    /* Check point belongs on outer disk of thickness rad3-rad2, and set the disks potential */
	  }

	  if ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad1*rad1 || (i-cent)*(i-cent)+(j-cent)*(j-cent)> rad3*rad3) currentV[i][j] = 0.0;
	    
	  /*Ground inner cylinder and points outside the outer edge of the disk*/
	  
	  //At the end of every iteration, set the oldV equal to the newly obtained currentV, and repeat process until convergence
	  oldV[i][j]=currentV[i][j];
	  /*Take difference matrix*/
	  //diffMatrix[i][j]=currentV[i][j]-oldV[i][j];
	      
	  //Add all elements of difference matrix
	  //sum_of_elems= sum_of_elems + diffMatrix[i][j];
	      
	  //Take average of all terms in the difference matrix
	  //avgdiff=sum_of_elems/(max*max);

	}
      }
  }
  
  for (i=0; i<max ; i++)         /* write data gnuplot 3D format */
   {
      for (j=0; j<max; j++) 
	{	
	/* save data in Jacobi1.dat */
	  /* only save last q output as it will be the best guess */
	myfile << currentV[i][j] << endl;
	 
      }
      myfile << "\n";	  /* empty line for gnuplot */
   }


   
     
    /*Check time elapsed since setting the first marker, that is, the time it takes to run the program */
  
   if (gif != "yes") {
    cout << "Data stored in Jacobi1.dat"<< endl;
   }
   myfile.close(); 
   return 0;
}

int main()
{
  
  int iters, max;
  double rad1, rad3, voltage;
  string method, gif;
  
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
  cout << "Gif? (if yes, will take significantly longer to run!)" << endl;
  cin >> gif;
  

  
  if (method=="FDM" || method=="fdm") {
    fdm(iters, max, rad1, rad3, voltage, gif);
     // create gif for each iteration depending on given step size
    if (gif =="yes") {
      int max_iters, step;
      cout << "Max iterations?" << endl;
      cin >> max_iters;
    
      cout << "Step size between each iteration?" << endl;
      cin >> step;
    
 
      for (int i=0; i<=(max_iters/step); i++) {
	string str;
	ofstream myfile;
	myfile.open("/home/2317101h/year_3/group_project/numerical_sol/section2.1/coax_cyl/anim/" + std::to_string(i*step) +".dat");
	fdm(i*step, max, rad1, rad3, voltage, gif);
	ifstream infile;
	infile.open("problem1.dat");
	while (std::getline(infile, str)) {
	  myfile << str << endl;
	}
	cout << "Data stored in " << i*step << ".dat" << endl;
	}
      }
    }
  	
  
  if (method=="Jacobi" || method=="jacobi") {
    jacobi(iters, max, rad1, rad3, voltage, gif);
    if (gif =="yes") {
      int max_iters, step;
      cout << "Max iterations?" << endl;
      cin >> max_iters;
    
      cout << "Step size between each iteration?" << endl;
      cin >> step;
      

      for (int i=0; i<=(max_iters/step); i++) {
	string str;
	ofstream myfile;
	myfile.open("/home/2317101h/year_3/group_project/numerical_sol/section2.1/coax_cyl/anim/jacobi/text/" + std::to_string(i*step) +".dat");
	jacobi(i*step, max, rad1, rad3, voltage, gif);
	ifstream infile;
	infile.open("Jacobi1.dat");
	while (std::getline(infile, str)) {
	  myfile << str << endl;
	}
	cout << "Data stored in " << i*step << ".dat" << endl;
	}
      }
    }
    
  }
  

