#pragma once

#include <ros/ros.h>
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "visualization_msgs/Marker.h"
#include <tf/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2/utils.h>

#include <husky_highlevel_controller_msgs/Position.h>
#include <husky_highlevel_controller_msgs/driveAction.h>
#include <actionlib/server/simple_action_server.h>
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
    actionlib::SimpleActionServer<husky_highlevel_controller_msgs::driveAction> as_;
    husky_highlevel_controller_msgs::driveFeedback feedback_;
    husky_highlevel_controller_msgs::driveResult result_;
    std::string action_name_;
    void driveCallback(const husky_highlevel_controller_msgs::Position& msg);
    void executeCB(const husky_highlevel_controller_msgs::driveGoalConstPtr &goal);
    void preemptCB();
};

} /* namespace */
