#pragma once

#include <ros/ros.h>
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "visualization_msgs/Marker.h"
#include <tf/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2/utils.h>
namespace husky_highlevel_controller {

/*!
 * Class containing the Husky Highlevel Controller
 */
class HuskyHighlevelController {
public:
    /*!
     * Constructor.
     */
    HuskyHighlevelController(ros::NodeHandle& node_handle);

    /*!
     * Destructor.
     */
    virtual ~HuskyHighlevelController();

    void listen();

private:
	ros::NodeHandle node_handle_;
    ros::Subscriber laser_scan_subscriber_;
    tf::TransformListener listener_;

    void laserScanCallback(const sensor_msgs::LaserScan& msg);
};

} /* namespace */
