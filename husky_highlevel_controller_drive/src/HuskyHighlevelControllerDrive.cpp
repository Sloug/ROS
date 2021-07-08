#include "husky_highlevel_controller_drive/HuskyHighlevelControllerDrive.hpp"
#include <string>
#include <iterator>
#include <algorithm>
#include <math.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2/utils.h>
#include <husky_highlevel_controller_msgs/Position.h>
#include <husky_highlevel_controller_msgs/driveAction.h>
#include <actionlib/server/simple_action_server.h>

namespace husky_highlevel_controller_drive
{
    ros::Publisher publisher;
    bool listenF = false;
    bool finish = false;
    // bool active = false;
    HuskyHighlevelControllerDrive::HuskyHighlevelControllerDrive(ros::NodeHandle& node_handle) :
    node_handle_(node_handle),
    as_(node_handle_, "drive_server", boost::bind(&HuskyHighlevelControllerDrive::executeCB, this, _1), false),
    action_name_("drive_server")    
    {
        as_.registerPreemptCallback(boost::bind(&HuskyHighlevelControllerDrive::preemptCB, this));
        as_.start();
        listen();
    }
    

    HuskyHighlevelControllerDrive::~HuskyHighlevelControllerDrive() {}

    void HuskyHighlevelControllerDrive::driveCallback(const husky_highlevel_controller_msgs::Position& msg)
    {   

        if(!listenF){
            return;
        }
        //check preented return / callback abmelden
        float p = 0.0;
        if ( !node_handle_.getParam("controll_parameter/p", p) )
            ROS_ERROR("Could not find topic parameter!");
        if(msg.dist > 0.16){
            
            geometry_msgs::Twist c_msg;
            c_msg.linear.x = msg.dist*p; 
            c_msg.angular.z =  -msg.angle*p;
            feedback_.dist = msg.dist;        
            as_.publishFeedback(feedback_);
            publisher.publish(c_msg);            
        }else{            
            finish = true;            
            listenF = false;
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
    }

    void HuskyHighlevelControllerDrive::executeCB(const husky_highlevel_controller_msgs::driveGoalConstPtr &goal)
    {
            
            listenF = true;
            while (!finish) {
                
            }
            result_.success = true;
            as_.setSucceeded(result_);
            return;      
        
    }
     void HuskyHighlevelControllerDrive::preemptCB()
    {
        listenF = false;
        geometry_msgs::Twist breaks;

        publisher.publish(breaks);

        as_.setPreempted();
    }
    

} 
