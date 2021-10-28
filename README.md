# Assignment 1 of the Research Track 1 course (MSc Robotics Engineering, Unige)

The assignment requires controlling a holonomic robot in a 2d space with a simple 2d simulator, Stage. 

### Content Structure

There are two packages **assignment1_controller** and **target_srv**. Each of these packages contain one node which perform their assigned functionalities. Please find the breadown of these functionalities below. Beside this please also check the graph file separately attached with this repository.

## assignment1_controller Package

assignment1_controller package have one ROS node with name assignment1_controller (node1) as well. For this node there is a cpp file with name assignment1_controller.cpp. This node perform following functionalities:

1. It subscribe to the /odom topic and using nav_msgs/Odometry it captures the current position of robot. For this, there is a subscriber implemented in this node. 
2. Once the current position of the robot is captures the node checks if the difference between the current position and target position is less then 0.1. If this condition satisfy then the node send the request to the target_server (node2) which send back the new target coordinates between range from -6.0 to 6.0. For this, there is a ROS client implemented in this node. 
3. If this condition doesn't satisfy then the node pulishes linear x and y speed of the robot using cmd_vel. For this, there is a ROS publisher implemented in this node. 
5. There is another publisher implemented in this node that publishes a custom message in topic assignment1/position. This message contains msg name, robot current position x coordinate, robot current position y coordinate, robot new target position x coordinate, robot new target position y coordinate and distance between current and target x and y coordinates. This msg was implemented just debuging purposes.

## target_srv Package

1. This node implement a ROS server which request for the min and max value of x and y coordinates of the new target positon. 
2. In reply to this request, it randomly generates a new target position for the robot and sent it to assignment1_controlller (node1)

## Computation graph: 

![alt text](https://github.com/ShozabAbidi10/ResearchTrack_Assignment1/blob/main/computational_graph.PNG)

## Instruction to run the code

1. Launched the simulator by executing the following command:
```
rosrun stage_ros stageros $(rospack find assignment1)/world/exercise.world
```

2. Open a new terminal tab and launched the target_server (node2) so that it can provide new target position for the robot. Execute the command:
```
rosrun target_srv target_server
```

3. Open an other terminal tab and launched the assignment1_controller (node1) by executing the command:
```
rosrun assignment1_controller assignment1_controller
```

4. (Optional) You can check what information about robot the custom message is publishing in the topic assignment1/position by executing the following command. 
```
rostopic echo /assignment1/position
```
# Note: 
At any stage if there is an error regarding "No such file or directory found" or any command not executing properly. Do the following steps.

Step 1: Make sure that currently you are in my_ros_ws directory, execute the following command
```
cd devel 
```
Step 2: Run the setup.bash file by using this command.

```
source setup.bash 
```
Step 3: Go back to my_ros_ws directory and the run that command again. Hopefully it will run this time.
 
