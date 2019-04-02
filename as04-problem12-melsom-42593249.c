//phys3071 as04 melsom 42593249

/*****************************************************************************
This program solves a pair of coupled ODEs modelling a predator prey system
using the Lotka-Volterra equations.

Inputs: The user is required to provide initial populations for the predators
and prey, the size of the time steps (dt), the size interval between printing
to file (tout), and the finish time (t_fin). All of these are double types.

Calculations: The time steps are calculated in a single while loop, with an if
conditional statement inside of the loop which sets off the print loop. The 
next printing interval is also updated.

Outputs: A file is crated in the running folder that contains the number of 
predator and prey at each time step. The file columns are TIME, PREY, PREDATOR

compiled as gcc as04-problem12-melsom-42593249.c -o as041 -lm -Wall
*****************************************************************************/

#include<math.h>
#include<stdio.h>
#include<stdlib.h>

//defined global variables using all CAPS for global variable names.
#define ALPHA 1.5
#define BETA 0.1
#define GAMMA 3.0
#define DELTA 0.1

int main () {
  double x_current, y_current, x_new, y_new;
  double dt, time, t_out, t_fin, t_out_int;
  FILE *fp; //for pointing at file.
  
  printf("This program will solve a pair of coupled ODEs. The user is required"
         " to enter the starting conditions, the time steps and end times.\n");  
  printf("Please provide the initial number of predators.\n");
  scanf("%lf",&y_current);
  printf("Please provide the initial number of prey.\n");
  scanf("%lf",&x_current);
  printf("Please provide the size of the time steps, delta t.\n");
  scanf("%lf",&dt);
  printf("Please provide a time for outputting to file.\n");
  scanf("%lf",&t_out);
  printf("Please provide the time to end calculations.\n");
  scanf("%lf",&t_fin);
  
  fp = fopen("test.dat", "w");
  
  //these values need to be initialised before the start of the loop.
  //t_out_int is used to store the intervals between tout points.
  t_out_int = t_out;
  time=0.0;
  //This solves for all time steps 
  while (time < t_fin) {
    x_new = x_current+ x_current*(ALPHA-BETA*y_current)*dt;
    y_new = y_current- y_current*(GAMMA-DELTA*x_current)*dt;
    //This if statement just picks the points to write to file.
    if ((t_out-dt/2.0) <= time && time < (t_out+dt/2.0)) {
      fprintf(fp, "%lf\t%lf\t%lf\n", time, x_new, y_new);
      t_out = t_out + t_out_int;
    }
    x_current = x_new;
    y_current = y_new;
    time = time+ dt;
  } 
  fclose(fp);
  return EXIT_SUCCESS;
}