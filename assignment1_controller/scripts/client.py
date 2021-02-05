#!/usr/bin/envpython
import rospy
from turtlesim.msg import Pose
from turtlesim.srv import Spawn
from geometry_msgs.msg import Twist

pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=1000)
def positionCallback(msg):
    rospy.loginfo("Robot position [%f, %f]", msg.x, msg.y)
    vel= Twist()
    vel.linear.x= 0.1
    vel.angular.z= 0.1
    pub.publish(vel)

def control():
    rospy.init_node('turtlebot_controller')
    rospy.Subscriber("/turtle1/pose", Pose, positionCallback)
    client = rospy.ServiceProxy('/spawn', Spawn)
    client(x=1.0, y=1.0)
    rospy.spin()

if __name__ == '__main__':
    try:
        control()
    except rospy.ROSInterruptException:
        pass
