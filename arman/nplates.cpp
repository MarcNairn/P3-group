/*This program generates, TWO PARALLEL PLATES at opposite potentials, with an added GROUNDED CYLINDER between the two*/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int fdm(int iters, int max, double rad, double voltage, string gif)
{
   
   int i, j, iter, y;
   int max_y = 500;
   double cent_x = max/2;			/* define coordinates of centre of circle */
   double cent_y = max_y/2;
   double x, p[max][max_y];
   
   ofstream myfile;
   myfile.open ("laplace.dat");
   for(i=0; i<max; i++)                 /* clear the array  */
   {   
      for (j=0; j<max_y; j++) p[i][j] = 0;
   }

   for(i=0; i<max_y-1; i++) p[0][i] = voltage;        /* p[i][0] = 100 V */		
   for(i=0; i<max_y; i++) p[max-1][i] = -1*voltage;
      


   for(iter=0; iter<iters; iter++)               /* iterations */
   {
      for(i=1; i<(max-1); i++)                  /* x-direction */
      {
         for(j=1; j<(max_y-1); j++)               /* y-direction */
         {
	    if ((i-cent_x)*(i-cent_x)+(j-cent_y)*(j-cent_y)<= rad*rad){
	      p[i][j]=0.0;
	    }
	    else {

	      p[i][j] = 0.25*(p[i+1][j]+p[i-1][j]+p[i][j+1]+p[i][j-1]);
	    
	
	    }
         }
      }
   }
  
   for (j=(cent_y-max/2); j<(cent_y+max/2); j++)          /* write data gnuplot 3D format */
   {
      for (i=0; i<max ; i++)
	{
	  		
	myfile << p[i][j] << endl; /* save data in laplace.dat */
	 
      }
      myfile << "\n";	  /* empty line for gnuplot */
   }
   if (gif != "yes") {
    cout << "Data stored in laplace.dat"<< endl;
   }
   myfile.close();
}

int main()
{
  int iters, max;
  double rad, voltage;
  string method, gif;
  
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
  cout << "Gif? (if yes, will take significantly longer to run!)" << endl;
  cin >> gif;
  
  if (method=="FDM" || method=="fdm") {
    fdm(iters, max, rad, voltage, gif);
 }
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
      myfile.open("/home/2317101h/year_3/group_project/numerical_sol/section2.1/plates/anim/" + std::to_string(i*step) +".dat");
      fdm(i*step, max, rad, voltage, gif);
      ifstream infile;
      infile.open("laplace.dat");
      while (std::getline(infile, str)) {
	myfile << str << endl;
      }
      cout << "Data stored in " << i*step << ".dat" << endl;
      
    }
  }
}