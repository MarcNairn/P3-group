 
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

int jacobi(int iters, int max, double rad, double voltage, string gif)
{
  double x, oldV[max][max], currentV[max][max],diffMatrix[max][max],V0[max][max], avgdiff, updateMatrix[max][max];
  int i, j, iter, y, sum_of_elems=0;
   

   ofstream myfile;
   myfile.open ("Jacobi2.dat");
   for(i=0; i<max; i++)                 /* clear the array  */
   {   
     for (j=0; j<max; j++) {
       oldV[i][j]=0;
       currentV[i][j]=0;
       V0[i][j]=0;
     }
   }

   for(i=0; i<max; i++){
     V0[i][0] = voltage;
     oldV[i][0]=voltage;
     currentV[i][0];
   } 		
     for(i=0; i<max; i++){
       V0[i][max-1] = -1*voltage;
       oldV[i][max-1]=-1*voltage;
       currentV[i][max-1]=-voltage;
     }
   for(i=1; i<max-1; i++){
     
     for(j=1; j<max-1; j++){

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
  	oldV[i][j]=0.25*(V0[i-1][j]+V0[i+1][j]+V0[i][j-1]+V0[i][j+1]);
     }
   }
   

   for(iter=1; iter<iters; iter++)               /* iterations */
   {
      for(i=1; i<(max-1); i++)                  /* x-direction */
      {
         for(j=1; j<(max-1); j++)               /* y-direction */
         {
	   
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
	   	    
	   currentV[i][j]=0.25*(oldV[a][b]+oldV[c][d]+oldV[e][f]+oldV[g][h]);

	   if ((i-cent)*(i-cent)+(j-cent)*(j-cent)<= rad*rad){
	      currentV[i][j]=0.0;
	    }
	   oldV[i][j]=currentV[i][j];
         }
      }
      //At the end of every iteration, set the oldV equal to the newly obtained currentV, and repeat process until convergence
      // oldV[i][j]=currentV[i][j];
      /*Take difference matrix*/
      //diffMatrix[i][j]=currentV[i][j]-oldV[i][j];
	      
      //Add all elements of difference matrix
      //sum_of_elems= sum_of_elems + diffMatrix[i][j];
	      
      //Take average of all terms in the difference matrix
      //avgdiff=sum_of_elems/(max*max);

   }
  
   for (i=0; i<max ; i++)         /* write data gnuplot 3D format */
   {
      for (j=0; j<max; j++) 
	{

	 		/* save data in Jacobi2.dat */
	myfile << currentV[i][j] << endl;
	 
      }
      myfile << "\n";	  /* empty line for gnuplot */
   }
   if (gif != "yes") {
   cout << "Data stored in Jacobi2.dat"<< endl;
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
  
  
 
 // create gif for each iteration depending on given step size
  if (method=="FDM" || method=="fdm") {
    fdm(iters, max, rad, voltage, gif);
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

if (method=="Jacobi" || method=="jacobi") {
    jacobi(iters, max, rad, voltage, gif);
    if (gif =="yes") {
      int max_iters, step;
      cout << "Max iterations?" << endl;
      cin >> max_iters;
    
      cout << "Step size between each iteration?" << endl;
      cin >> step;
      

      for (int i=0; i<=(max_iters/step); i++) {
	string str;
	ofstream myfile;
	myfile.open("/home/2317101h/year_3/group_project/numerical_sol/section2.1/plates/anim/jacobi/text/" + std::to_string(i*step) +".dat");
	jacobi(i*step, max, rad1, rad3, voltage, gif);
	ifstream infile;
	infile.open("Jacobi2.dat");
	while (std::getline(infile, str)) {
	  myfile << str << endl;
	}
	cout << "Data stored in " << i*step << ".dat" << endl;
	}
      }
    }
    
  }
}
