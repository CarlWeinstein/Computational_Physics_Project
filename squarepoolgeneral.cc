#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
double v=1;			//Velocity of ball (set to a unit vector of 1 since the simulation is meant to look at the trajectory of the ball)
double balldeg=40.;	//Angle of ball in degrees
double ballrad;		//Angle of ball in radians
double dt=0.00001;	//Size of time interval
double N=750000;	//Number of iterations to run simulation
double l=1;			//Length of pool table walls
double x_i=-.21;	//Initial x-position of ball (where (0,0) is the center of the table)
double x_f;
double y_i=0;		//Initial y-position of ball (where (0,0) is the center of the table)
double y_f;
double v_x;			//Velocity x-component
double v_y;			//Velocity y-component
double ti, tf;

FILE *output;

output=fopen("square_pool_general.txt","w");

ballrad=M_PI*balldeg/180.;  //Initial ball direction (in this the ball is initially fired 40 degrees to the horizontal)
v_x=v*cos(ballrad);			//Solving for velocity x-component
v_y=v*sin(ballrad);			//Solving for velocity y-component
		
	for(int j=0; j<N; j++)
	{
		ti=dt*j;	//Initial time value
		tf=dt+ti;	//Final time value
		
		fprintf(output, "%f %f %f\n", ti, x_i, y_i);	//Prints time, x-position, and y-position to a file
		
		if(x_i >= l/2)									//If statement that will determine if the "ball" has hit the Right "wall" of pool table
			v_x=-v_x;}									//If the ball "hits" the wall, the velocity component perpendicular to the wall is made negative.  This is repeated for each "wall" if statement. 
		if(x_i <= -l/2)									//If statement that will determine if the "ball" has hit the Left "wall" of pool table
			v_x=-v_x;}
		if(y_i >= l/2)									//If statement that will determine if the "ball" has hit the Top "wall" of pool table
			v_y=-v_y;}
		if(y_i <= -l/2)									//If statement that will determine if the "ball" has hit the Bottom "wall" of pool table
			v_y=-v_y;}
		
		x_f=(v_x*dt)+x_i;	//New x-position is solved by using the solved velocity and the x-position at the beggining of the dt increment
		y_f=(v_y*dt)+y_i;	//New y-position is solved by using the solved velocity and the y-position at the beggining of the dt increment
		
		x_i=x_f;	//New x-position is substituted for old x-position so loop can run with new values
		y_i=y_f;	//New y-position is substituted for old x-position so loop can run with new values		
	}

fclose(output);

return(0);
}
