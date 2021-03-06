#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "beginner_tutorials/Num.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt16.h"
#include "stdio.h"
#include "iostream"

using namespace std;
void Callback(const beginner_tutorials::Num::ConstPtr&temp_msg){
	//ROS_INFO("I heard %4.2f",temp_msg->data);
	float temp = temp_msg->data;
	cout<< "Temperature (°C): "<< temp <<"\n";
		ros::NodeHandle n;
		ros::Publisher servo_pub = n.advertise<std_msgs::UInt16>("servo",1000);
		ros::Rate loop_rate(1);
		    /**
		     * This is a message object. You stuff it with data, and then publish it.
		     */
		int count=0;
		while (ros::ok())
		{
		std_msgs::UInt16 cmd_msg;
		if (temp>29){
		cmd_msg.data=120;
		}
		else {
			cmd_msg.data=0;
		}
		    /**
		     * The publish() function is how you send messages. The parameter
		     * is the message object. The type of this object must agree with the type
		     * given as a template parameter to the advertise<>() call, as was done
		     * in the constructor above.
		     */
		servo_pub.publish(cmd_msg);
		cout<< "position (grades): "<< cmd_msg.data <<"\n";
		ros::spin();
		loop_rate.sleep();
		++count;
		}
	}
/*void servoCallback(const std_msgs::UInt16::ConstPtr&cmd_msg){
	//ROS_INFO("I heard %ld",cmd_msg->data);
	float result = cmd_msg->data;
	cout<< "position (grados): "<< result <<"\n";
}*/
int main(int argc, char **argv){
	// Say HelloWorld five times
	ros::init(argc, argv, "computing");
	ros::NodeHandle n;
	ros::Subscriber sub1 = n.subscribe<beginner_tutorials::Num>("temperature",1000, Callback);
	//ros::Subscriber sub2 = n.subscribe<std_msgs::UInt16>("servo",1000,servoCallback);
	cout<<"Hey, you, I'm alive \n";
	ros::spin();
	return 0;
}
