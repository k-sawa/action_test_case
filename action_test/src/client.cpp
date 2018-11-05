#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <control_msgs/FollowJointTrajectoryAction.h>

void spinThread()
{
  ros::NodeHandle nh;
  ros::spin();
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "TestClient");

  boost::thread spin_thread(&spinThread);

  uint32_t i = 1;
  control_msgs::FollowJointTrajectoryGoal goal;

  while (ros::ok())
  {
    actionlib::SimpleActionClient<control_msgs::FollowJointTrajectoryAction> ac("follow_joint_trajectory_action", true);
    ac.waitForServer();

    ROS_INFO("sendGoal [%u]", i);
    ac.sendGoal(goal);

    if (!ac.waitForResult(ros::Duration(5.0)))
    {
      ROS_ERROR("waitForResult timeout %u", i);
      while (1)
        ;
    }

    i++;
  }

  ros::shutdown();

  spin_thread.join();

  return 0;
}
