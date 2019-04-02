//phys3071 as04 melsom 42593249

/*****************************************************************************
This program solves a pair of coupled ODEs modelling a predator prey system
using the Lotka-Volterra equations and attempts to converge to the steady state
solutions for the given interaction constants (ALPHA, BETA, GAMMA, DELTA).

Inputs: The user is required to provide initial populations for the predators
and prey, the size of the time steps (dt), and the finish time (tfin). All of 
these are double types.

Calulations: The program finds the min and max values of both of the prey and 
predator over their interactions. The midpoint of the min and max is used as 
the new initial populations and the calculations are repeated. The iterations
end when either 30 iterations have passed or the differences between the min 
and max of both the predator and the prey is withing threthold value.

Outputs: The program will either output that no solution has been found within
30 iterations, or it will print the stable initial populations.
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
  //time step until time > tfin. thresh is used as a small treshold amount to 
  //determin when a solution is stable.
  double time, tfin, dt, thresh = 1e-5;
  //new are the calculation results based off of current results.
  double x_new, y_new, x_current, y_current;
  //self explanitory variables.
  double ymin, ymax, xmin, xmax;
  int iter;
  
  printf("This program will solve a pair of coupled ODEs. The user is required"
         " to enter the starting\n conditions, the time steps and end times.\n");  
  printf("Please provide the initial number of predators.\n");
  scanf("%lf",&y_current);
  printf("Please provide the initial number of prey.\n");
  scanf("%lf",&x_current);
  printf("Please provide the size of the time steps, delta t.\n");
  scanf("%lf",&dt);
  printf("Please provide the time to end calculations.\n");
  scanf("%lf",&tfin);
  
  //start the iterations
  iter = 0;
  do {
    //resets the min and max positions to be within values that we know the min
    //and max may exceed.
    xmin = x_current;
    xmax = x_current;
    ymin = y_current;
    ymax = y_current;
    time = 0.0;
    //This solves for all time steps 
    while (time < tfin) {
      x_new = x_current+ x_current* (ALPHA- BETA* y_current)* dt;
      y_new = y_current- y_current* (GAMMA- DELTA* x_current)* dt;
      if (x_new > xmax) xmax = x_new;
      if (x_new < xmin) xmin = x_new;
      if (y_new > ymax) ymax = y_new;
      if (y_new < ymin) ymin = y_new;
      x_current = x_new;
      y_current = y_new;
      time = time+ dt;
    }
    x_current = (xmin+xmax)/2.0;
    y_current = (ymin+ymax)/2.0;

    //break condition for unsuccessful convergence within 30 steps
    if (iter == 30) {
      printf("\nERROR: The program did not find a stable solution to the \ncoupled"
             " differential equations in less than 30 iterations.\n");
      exit(EXIT_FAILURE);
      }
    iter++;
    //break condition for successful convergence
    } while (fabs(xmin-xmax)>thresh && fabs(ymin-ymax)>thresh); 
  printf("\nThe initial conditions that lead to a stationary solution are\n"
         "prey: %lf // predator: %lf\n\n", x_current, y_current);
  return EXIT_SUCCESS;
}
