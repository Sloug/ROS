#pragma once

#include <ros/ros.h>
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "visualization_msgs/Marker.h"
#include <tf/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2/utils.h>

#include <husky_highlevel_controller_msgs/Position.h>
namespace husky_highlevel_controller_drive {

/*!
 * Class containing the Husky Highlevel Controller
 */
class HuskyHighlevelControllerDrive {
public:
    /*!
     * Constructor.
     */
    HuskyHighlevelControllerDrive(ros::NodeHandle& node_handle);

    /*!
     * Destructor.
     */
    virtual ~HuskyHighlevelControllerDrive();

    void listen();

private:
	ros::NodeHandle node_handle_;
    ros::Subscriber drive_subscriber_;
    tf2_ros::TransformListener listener_;
    tf2_ros::Buffer tf_buffer_;

    void driveCallback(const husky_highlevel_controller_msgs::Position& msg);
};

} /* namespace */
