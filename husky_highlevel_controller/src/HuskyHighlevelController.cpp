#include "husky_highlevel_controller/HuskyHighlevelController.hpp"
#include <string>
#include <iterator>
#include <algorithm>
#include <math.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2/utils.h>


namespace husky_highlevel_controller
{
    HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& node_handle) :
    node_handle_(node_handle),listener_(tf_buffer_){
       // tf::TransformListener listener;
    }
    ros::Publisher publisher;
    ros::Publisher vis_pub;
    visualization_msgs::Marker marker;
     
   

    HuskyHighlevelController::~HuskyHighlevelController() {}

    void HuskyHighlevelController::laserScanCallback(const sensor_msgs::LaserScan& msg)
    {
        int i  = std::min_element(std::begin(msg.ranges),std::end(msg.ranges)) - std::begin(msg.ranges);
        double min_dist = *std::min_element(std::begin(msg.ranges), std::end(msg.ranges));
        ROS_INFO(
            "Smallest distance: %f",min_dist            
        );
        //calc rigth or left
        double angle= (msg.angle_min + i * msg.angle_increment);
        //p param auslesen
        ROS_INFO(
            "Angle to pillar: %f",angle            
        );
        float p = 0.0;
        if ( !node_handle_.getParam("controll_parameter/p", p) )
            ROS_ERROR("Could not find topic parameter!");
        //geometry_twist msg aufbauen 
        if(min_dist > 0.16){
            geometry_msgs::Twist c_msg;
            c_msg.linear.x = min_dist * p; 
            c_msg.angular.z =  -angle * p;
            publisher.publish(c_msg);
        }
        marker.header.frame_id = "base_laser";
        marker.header.stamp = ros::Time();
        marker.ns = "husky_ctrl";
        marker.id = 0;
        marker.type = visualization_msgs::Marker::CYLINDER;
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose.position.x = cos(angle)*min_dist+0.2;
        marker.pose.position.y = sin(angle)*min_dist;
        marker.pose.position.z = -0.5;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;
        marker.scale.x = 0.4;
        marker.scale.y = 0.4;
        marker.scale.z = 2;
        marker.color.a = 1.0; // Don't forget to set the alpha!
        marker.color.r = 0.0;
        marker.color.g = 1.0;
        marker.color.b = 0.0;
        vis_pub.publish(marker);
        geometry_msgs::TransformStamped transform;
        
        try{
            marker.header.frame_id = "odom";
            transform = tf_buffer_.lookupTransform("odom", "base_laser",ros::Time(0));
            geometry_msgs::Pose pose;
            tf2::doTransform(marker.pose,pose,transform);
            marker.id = 1;
            marker.pose = pose;
            marker.color.g= 0.0;
            marker.color.b = 1.0;
            vis_pub.publish(marker);
        }    
        catch (tf::TransformException &ex) {
             ROS_ERROR("%s",ex.what());
        }
        
            


    }

    void HuskyHighlevelController::listen()
    {
        std::string topic;
        if ( !node_handle_.getParam("laser/topic", topic) )
            ROS_ERROR("Could not find topic parameter!");

        int queue_size;
        if ( !node_handle_.getParam("laser/queue_size", queue_size) )
            ROS_ERROR("Could not find queue_size parameter!");

        laser_scan_subscriber_ = node_handle_.subscribe(
            topic,
            queue_size,
            &HuskyHighlevelController::laserScanCallback,
            this
        );
       publisher =
		node_handle_.advertise<geometry_msgs::Twist>("/cmd_vel",
		queue_size);

        vis_pub = node_handle_.advertise<visualization_msgs::Marker>( "marker", 0 );
       
        
        //only if using a MESH_RESOURCE marker type:
        //marker.mesh_resource = "package://pr2_description/meshes/base_v0/base.dae";
       
        
        
        ros::spin();
    }
} /* namespace */
