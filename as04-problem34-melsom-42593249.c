//phys3071 as04 melsom 42593249

/*****************************************************************************
This program solves a pair of coupled ODEs modelling a predator prey system
using the Lotka-Volterra equations and attempts to converge to the steady state
solutions for the given interaction constants (ALPHA, BETA, GAMMA, DELTA).

Inputs: The user is required to provide initial populations for the predators
and prey, the size of the time steps (dt), and the finish time (t_fin). All of 
these are double types.

Calculations: The program finds the min and max values of both of the prey and 
predator over their interactions. The midpoint of the min and max is used as 
the new initial populations and the calculations are repeated. The iterations
end when either 30 iterations have passed or the differences between the min 
and max of both the predator and the prey is within threshold value.

Outputs: The program will either output that no solution has been found within
30 iterations, or it will print the stable initial populations.

compiled as gcc as04-problem34-melsom-42593249.c -o as042 -lm -Wall
*****************************************************************************/

#include<math.h>
#include<stdio.h>
#include<stdlib.h>

//defined global variables using all CAPS for global variable names.
//These represent interaction values between the populations.
#define ALPHA 1.5
#define BETA 0.1
#define GAMMA 3.0
#define DELTA 0.1

int main () {
  //time is the current time step position, which will be advanced by dt per
  //time step until time > t_fin. threshold is used as a small threshold amount 
  //to determine when a solution is stable.
  double time, t_fin, dt, threshold = 1e-5;
  //new are the calculation results based off of current results.
  double x_new, y_new, x_current, y_current;
  //self explanatory variables.
  double y_min, y_max, x_min, x_max;
  int iteration_count;
  
  printf("This program will solve a pair of coupled ODEs. The user is required"
         " to enter the starting\n conditions, the time steps and end times.\n");  
  printf("Please provide the initial number of predators.\n");
  scanf("%lf",&y_current);
  printf("Please provide the initial number of prey.\n");
  scanf("%lf",&x_current);
  printf("Please provide the size of the time steps, delta t.\n");
  scanf("%lf",&dt);
  printf("Please provide the time to end calculations.\n");
  scanf("%lf",&t_fin);
  
  //start the iterations
  iteration_count = 0;
  do {
    //resets the min and max positions to be within values that we know the min
    //and max may exceed.
    x_min = x_current;
    x_max = x_current;
    y_min = y_current;
    y_max = y_current;
    time = 0.0;
    //This solves for all time steps 
    while (time < t_fin) {
      x_new = x_current+ x_current* (ALPHA- BETA* y_current)* dt;
      y_new = y_current- y_current* (GAMMA- DELTA* x_current)* dt;
      if (x_new > x_max) x_max = x_new;
      if (x_new < x_min) x_min = x_new;
      if (y_new > y_max) y_max = y_new;
      if (y_new < y_min) y_min = y_new;
      x_current = x_new;
      y_current = y_new;
      time = time+ dt;
    }
    x_current = (x_min+x_max)/2.0;
    y_current = (y_min+y_max)/2.0;

    //break condition for unsuccessful convergence within 30 steps
    if (iteration_count == 30) {
      printf("\nERROR: The program did not find a stable solution to the "
             "\ncoupled differential equations in less than 30 iterations.\n");
      exit(EXIT_FAILURE);
      }
    iteration_count ++;
    //break condition for successful convergence
    } while (fabs(x_max- x_min)> threshold || fabs(y_max- x_min)> threshold); 
  printf("\nThe initial conditions that lead to a stationary solution are\n"
         "prey: %lf // predator: %lf\n\n", x_current, y_current);
  return EXIT_SUCCESS;
}