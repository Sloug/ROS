#include <ros/ros.h>
#include "husky_highlevel_controller_drive/HuskyHighlevelControllerDrive.hpp"
#include <tf/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2/utils.h>


int main(int argc, char** argv)
{
    ros::init(argc, argv, "husky_highlevel_controller_drive");
    ros::NodeHandle nh("~");
   
    husky_highlevel_controller_drive::HuskyHighlevelControllerDrive hhlc(nh);   
    ros::spin();
    return 0;
}
 