#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;


int main()
{
double v=1;				//Velocity of ball (set to a unit vector of 1 since the simulation is meant to look at the trajectory of the ball)
double balldeg=40.;		//Angle of ball in degrees
double ballrad;			//Angle of ball in radians
double wallrad;			//Angle of the slope tangent to the wall at the point of impact
double dt;				//Size of time step
double N=1000000;		//Number of iterations to run simulation
double l=1;				//Length of straight walls of pool table
double r=0.5;			//Radius of curved walls of pool table
double x_i=0;			//Initial x-position of ball (where (0,0) is the center of the table)
double x_f;
double y_i=0;			//Initial y-position of ball (where (0,0) is the center of the table)
double y_f;
double v_x;				//Velocity x-component
double v_y;				//Velocity y-component
double t_total=15;		//Total number of seconds the simulation is run for
double tf=0;			//Current simulation time set to zero
double c;				//Counter variable

FILE *output;

output=fopen("round_pool_general.txt","w");

ballrad=2*M_PI*balldeg/360.;	//Initial ball direction (in this the ball is initially fired 40 degrees to the horizontal)
v_x=v*cos(ballrad);				//Solving for velocity x-component
v_y=v*sin(ballrad);				//Solving for velocity y-component
		
	while(tf<t_total)			//While loop that says "While the current simulation time is less than the total time the simulation will run for, do the following."
	{
		if(x_i < (l/2) && x_i > (-l/2) && y_i > -r + 0.1 && y_i < r - 0.1) {dt=0.05;}	//If statement that checks to see if the ball is near any of the walls.  If it is not near any walls, the dt is made large so that less data is put into a file (since we know it will not hit a wall near the center of the table).
		else{dt=0.00001;}		//If ball is close to a wall, the time step is made small so as to not pass up the wall by a large amount.
		tf=dt+tf;				//Next "Current simulation time" is calculated using new dt
		
		fprintf(output, "%f %f %f %f %f %f %f\n", tf, x_i, y_i, v_x, v_y, ballrad, wallrad); //Desired data is output
		
		if(x_i > (l/2) && c<=0){		//If statement that checks if the ball has entered the right semicircle's area, and if the counter variable is at 0
			if(pow(r, 2) <= (pow((x_i-(l/2)),2)+pow(y_i, 2))){	//If statement to check if the balls position is inside or outside of the semicircle's circumference using the equation of a circle and the ball's current position.
			wallrad=(M_PI/2)+atan((y_i)/(x_i-(l/2)));	//If the ball's position is outside of the circumference (a "hit") the slope of the tangent line to the point of impact is calculated
			ballrad=(2*wallrad)-ballrad;		//The new angle of the ball is calculated after the impact occurs
				if(ballrad < 0){				//If statement that helps to ensure the ball's angle (in radians) is between 0 and 2*pi
					ballrad=ballrad+(2*M_PI);}
				if(ballrad > (2*M_PI)){			//If statement that helps to ensure the ball's angle (in radians) is between 0 and 2*pi
					ballrad=ballrad-(2*M_PI);}}
			v_x=v*cos(ballrad);					//New velocity in the x-direction is calculated
			v_y=v*sin(ballrad);					//New velocity in the y-direction is calculated
			c=10;}								//Setting the counter variable to 10, helps to ensure that when the ball "hits" the wall and overshoots the boundary (or hits the boundary exactly), it has enough iterations of the while statement to come back to the inside of the table before the program checks if the ball has "hit" again
			
		if(x_i < (-l/2) && c<=0){				//Same as if statement in line 44, except everything is for the left semicircle
			if(pow(r, 2) <= (pow((x_i-(-l/2)), 2)+pow(y_i, 2))){
			wallrad=(M_PI/2)+atan((y_i)/(x_i+(l/2)));
			ballrad=(2*wallrad)-ballrad;
				if(ballrad < 0){
					ballrad=ballrad+(2*M_PI);}
				if(ballrad > (2*M_PI)){
					ballrad=ballrad-(2*M_PI);}}
			v_x=v*cos(ballrad);
			v_y=v*sin(ballrad);
			c=10;}
			
		if(y_i >= l/2 && c<=0)			//If statement to see if ball has hit top wall of the pool table
			{wallrad=M_PI*(0./180.);	//Top wall's angle (with respect to the right horizontal)
			ballrad=wallrad-ballrad;	//Calculating new ball angle after impact
			if(ballrad < 0){			//If statement that helps to ensure the ball's angle (in radians) is between 0 and 2*pi
				ballrad=ballrad+(2*M_PI);}
			if(ballrad > (2*M_PI)){		//If statement that helps to ensure the ball's angle (in radians) is between 0 and 2*pi
				ballrad=ballrad-(2*M_PI);}
			v_x=v*cos(ballrad);					//New velocity in the x-direction is calculated
			v_y=v*sin(ballrad);					//New velocity in the y-direction is calculated
			c=10;}								//Setting the counter variable to 10, helps to ensure that when the ball "hits" the wall and overshoots the boundary (or hits the boundary exactly), it has enough iterations of the while statement to come back to the inside of the table before the program checks if the ball has "hit" again
			
		if(y_i <= -l/2 && c<=0)			//Same as if statement in line 68 except for bottom wall of the pool table
			{wallrad=M_PI*(0./180.);
			ballrad=wallrad-ballrad;
			if(ballrad < 0){
				ballrad=ballrad+(2*M_PI);}
			if(ballrad > (2*M_PI)){
				ballrad=ballrad-(2*M_PI);}
			v_x=v*cos(ballrad);
			v_y=v*sin(ballrad);
			c=10;}
		
		x_f=(v_x*dt)+x_i;	//New x-position is solved by using the solved velocity and the x-position at the beggining of the dt increment
		y_f=(v_y*dt)+y_i;	//New y-position is solved by using the solved velocity and the y-position at the beggining of the dt increment
		
		x_i=x_f;	//New x-position is substituted for old x-position so loop can run with new values
		y_i=y_f;	//New y-position is substituted for old x-position so loop can run with new values	
		
		c=c-1;		//Subtract one from the counter variable
	}

fclose(output);

return(0);
}
