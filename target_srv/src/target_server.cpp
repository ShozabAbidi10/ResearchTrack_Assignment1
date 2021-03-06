#include "ros/ros.h"           // here we have included the header file 
#include "target_srv/Target.h"   //that generated automatically when we builtthe pakage. 
#include <math.h>


double randMToN(double M, double N){ 
   return M + (rand()/(RAND_MAX/(N-M))); 

}

// There are two pointer for the request part and response part.
bool target (target_srv::Target::Request&req, target_srv::Target::Response&res){

  res.x= randMToN(req.min, req.max);
  res.y= randMToN(req.min, req.max);
  return true;
}


int main(int argc,char **argv)
{
  ros::init(argc,argv,"target_server");
  ros::NodeHandle n;
  ros::ServiceServer service= n.advertiseService("/target", target);
  ros::spin();
  
  return 0;
}
