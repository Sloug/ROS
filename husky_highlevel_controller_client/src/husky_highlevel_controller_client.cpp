#include <ros/ros.h>
  #include <actionlib/client/simple_action_client.h>
  #include <actionlib/client/terminal_state.h>
  #include <actionlib/client/simple_client_goal_state.h>
   #include <husky_highlevel_controller_msgs/driveAction.h>
   #include <cstdlib>
void exitfunction(){
ROS_INFO("Send Cancell.");
  
}
void doneCB(const actionlib::SimpleClientGoalState &state, const husky_highlevel_controller_msgs::driveResultConstPtr &result)
{
     ROS_INFO(
              "Goal was reached"       
          );
}
void activeCB()
{
    ROS_INFO("Active");
}
void feedbackCB(const husky_highlevel_controller_msgs::driveFeedbackConstPtr &feedback)
{
  ROS_INFO(
        "Im driving and dist is %f",feedback->dist       
    );
}

int main (int argc, char **argv)
   {
   ros::init(argc, argv, "driveClient");
   std::atexit(exitfunction);
   husky_highlevel_controller_msgs::driveFeedback feedback_;
  // create the action client
  // true causes the client to spin its own thread
  actionlib::SimpleActionClient<husky_highlevel_controller_msgs::driveAction> ac("husky_drive/drive_server", true);
  ROS_INFO("Waiting for action server to start.");
  // wait for the action server to start
  ac.waitForServer(); //will wait for infinite time
  
  ROS_INFO("Action server started, sending goal.");
  // send a goal to the action
  husky_highlevel_controller_msgs::driveGoal goal;
  goal.go = true;
  ac.sendGoal(goal, boost::bind(&doneCB, _1, _2),
                    boost::bind(&activeCB),
                    boost::bind(&feedbackCB, _1));
  ac.waitForResult();
  //exit
  return 0;
  }
//void serverDoneCB
  //  void serverFeedbackCB(const husky_highlevel_controller_msgs::driveActionFeedback_ &feedback)
  //   {
  //       ROS_INFO("Server Feedback reached. Distance to pillar left: [%.2f]", feedback->distance);
  //   }
