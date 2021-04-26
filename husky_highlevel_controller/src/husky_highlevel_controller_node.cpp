#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "limits"

ros::Publisher publisher;
double last_min;
void scannerCallback(const sensor_msgs::LaserScan& msg)
{
	for(float f:msg.ranges)
	{
		if(f< last_min)
		{
			last_min = f;
		}
	}
	
	//publisher.publish(msg);
	ROS_INFO("I heard: [%11.5f]", last_min);
}



int main(int argc, char **argv)
{
	ros::init(argc, argv, "listener");
	ros::NodeHandle nodeHandle;
	last_min = std::numeric_limits<float>::infinity();
	//load params
	std::string topic_name;
	if(!nodeHandle.getParam("scan/topic_name", topic_name))
	{
		ROS_ERROR("Could not find topic parameter1!");
		ros::requestShutdown();
		return 1;
	}
	int queue_size;
	if(!nodeHandle.getParam("scan/queue_size", queue_size))
	{
		ROS_ERROR("Could not find topic parameter2!");
		ros::requestShutdown();
		return 1;
	}
	
	publisher =
		nodeHandle.advertise<sensor_msgs::LaserScan>("laser_scan",
		queue_size);

	
	ros::Subscriber subscriber =
		nodeHandle.subscribe(topic_name, queue_size, scannerCallback);

	
	ros::spin();
	return 0;
}
