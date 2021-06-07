#include "husky_highlevel_controller/HuskyHighlevelController.hpp"
#include <string>
#include <iterator>
#include <algorithm>
#include <math.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2/utils.h>
#include <husky_highlevel_controller_msgs/Position.h>

namespace husky_highlevel_controller_drive
{
    HuskyHighlevelControllerDrive::HuskyHighlevelControllerDrive(ros::NodeHandle& node_handle) :
    node_handle_(node_handle),listener_(tf_buffer_){
       // tf::TransformListener listener;
    }
    ros::Publisher publisher;
    ros::Publisher vis_pub;
    visualization_msgs::Marker marker;
     
   

    HuskyHighlevelControllerDrive::~HuskyHighlevelControllerDrive() {}

    void HuskyHighlevelControllerDrive::driveCallback(const husky_highlevel_controller_msgs::Position& msg)
    {   
        float p = 0.0;
        if ( !node_handle_.getParam("controll_parameter/p", p) )
            ROS_ERROR("Could not find topic parameter!");
        if(min_dist > 0.16){
            geometry_msgs::Twist c_msg;
            c_msg.linear.x = msg.dist*p; 
            c_msg.angular.z =  -msg.angle*p;
            publisher.publish(c_msg);
        }
       
    }

    void HuskyHighlevelControllerDrive::listen()
    {
        std::string topic;
        if ( !node_handle_.getParam("drive/topic", topic) )
            ROS_ERROR("Could not find topic parameter!");

        int queue_size;
        if ( !node_handle_.getParam("drive/queue_size", queue_size) )
            ROS_ERROR("Could not find queue_size parameter!");

        drive_subscriber_ = node_handle_.subscribe(
            topic,
            queue_size,
            &HuskyHighlevelControllerDrive::driveCallback,
            this
        );
       publisher =
		node_handle_.advertise<geometry_msgs::Twist>("/cmd_vel",
		queue_size);

       
        
        //only if using a MESH_RESOURCE marker type:
        //marker.mesh_resource = "package://pr2_description/meshes/base_v0/base.dae";
       
        
        
        ros::spin();
    }
} 
