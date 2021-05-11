#include <ros/ros.h>
#include "husky_highlevel_controller/HuskyHighlevelController.hpp"
#include <tf/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2/utils.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "husky_highlevel_controller");
    ros::NodeHandle nh("~");
   
    husky_highlevel_controller::HuskyHighlevelController hhlc(nh);
    hhlc.listen();

    return 0;
}
