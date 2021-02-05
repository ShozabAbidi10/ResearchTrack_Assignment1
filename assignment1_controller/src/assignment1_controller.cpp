#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "target_srv/Target.h"
#include "assignment1_controller/Pos.h"
#include <sstream>
#include <iostream>


//TODO declare the publisher as global
ros::Publisher pub;
ros::Publisher pub2;
ros::ServiceClient client5;
float new_target_x = 0.0;
float new_target_y = 0.0;

//Distance formula to calculate the distance between current position and new target position of the robot.
float distance(float x1, float y1, float x2, float y2) 
{ 
    // Calculating distance 
    return sqrt(pow(x2 - x1, 2) +  
                pow(y2 - y1, 2) * 1.0); 
}

void subscriberCallback(const nav_msgs::Odometry::ConstPtr& pos_msg)
{
    ROS_INFO("Robot position [%f, %f]", pos_msg->pose.pose.position.x, pos_msg->pose.pose.position.y);
    target_srv::Target rec_vel;           // Initiallizing the target service to get new target values.
       
   
   // This if statement is just checking if     
   if (distance(pos_msg->pose.pose.position.x,pos_msg->pose.pose.position.y,new_target_x,new_target_y)<0.1){               
       rec_vel.request.min= -6.0;             // Sending request with requirement inputs min and max value of range 
       rec_vel.request.max=  6.0;    
       client5.call(rec_vel);                 // Calling the request client now.
       new_target_x = rec_vel.response.x;     // Getting the new target value in response
       new_target_y = rec_vel.response.y;             
       }
   else{    
        geometry_msgs::Twist vel;    
	vel.linear.x = 1*((new_target_x - pos_msg->pose.pose.position.x));  // Setting velocity to the difference between current position
        vel.linear.y = 1*((new_target_y - pos_msg->pose.pose.position.y));  // and new target position.        
        pub.publish(vel);            
        
        assignment1_controller::Pos mymsg;  // Initiallizing the custom message. 
    	mymsg.name = "Position";            
    	mymsg.x = new_target_x;             
    	mymsg.y = new_target_y; 
    	mymsg.c = pos_msg->pose.pose.position.x;
    	mymsg.d = pos_msg->pose.pose.position.y;
    	mymsg.distance_x = sqrt(pow(new_target_x - pos_msg->pose.pose.position.x, 2));
    	mymsg.distance_y = sqrt(pow(new_target_y - pos_msg->pose.pose.position.y, 2));
    	pub2.publish(mymsg);
	}     

}

 
int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "assignment1_controller");
  ros::NodeHandle n;

  client5 = n.serviceClient<target_srv::Target>("/target");
  pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  pub2 = n.advertise<assignment1_controller::Pos>("assignment1/position", 1000);
  ros::Subscriber pose_sub = n.subscribe("/odom", 1000, subscriberCallback);
  ros::spin();

  return 0;
}
