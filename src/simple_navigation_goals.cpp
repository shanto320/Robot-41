#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>


typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>
MoveBaseClient;

int main(int argc, char** argv){
 	ros::init(argc, argv, "simple_navigation_goals");
 	//tell the action client that we want to spin a thread by default
 	MoveBaseClient ac("move_base", true);
 	//wait for the action server to come up
 	while(!ac.waitForServer(ros::Duration(5.0))){
 		ROS_INFO("Waiting for the move_base action server to come up");
 	}
	float x[4] = {1.4049,1.4049,0.3049,0.3049};
	float y[4] = {0.3049,1.4049,1.4049,0.2649};
	float z[4] = {0,1.5,3.5,0.1};
 	move_base_msgs::MoveBaseGoal goal;
 	//we'll send a goal to the robot to move 1 meter forward
	goal.target_pose.pose.orientation.w = 1;

	// goals		
	for(int i =0;i<4; i++) { 
 		goal.target_pose.header.frame_id = "map";
 		goal.target_pose.header.stamp = ros::Time::now();
 		goal.target_pose.pose.position.x = x[i]; 
 		goal.target_pose.pose.position.y = y[i];

		goal.target_pose.pose.orientation.z = z[i];

		ROS_INFO("Sending goal %d",i+1);
 		ac.sendGoal(goal);
 		ac.waitForResult();
	}
	
	
 	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
 		ROS_INFO("Success");
 	else
 		ROS_INFO("Failure");
 	return 0;
}

