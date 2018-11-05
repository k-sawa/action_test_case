#include <ros/ros.h>
#include <gtest/gtest.h>
#include <actionlib/client/simple_action_client.h>
#include <control_msgs/FollowJointTrajectoryAction.h>

TEST(SimpleClient, result_subscribe_test) {
  control_msgs::FollowJointTrajectoryGoal goal;

  for (int i = 0; i < 10000; i++)
  {
    actionlib::SimpleActionClient<control_msgs::FollowJointTrajectoryAction> ac("follow_joint_trajectory_action", true);

    bool started = ac.waitForServer(ros::Duration(10.0));
    ASSERT_TRUE(started);

    ac.sendGoal(goal);
    bool finished = ac.waitForResult(ros::Duration(10.0));
    ASSERT_TRUE(finished);

    //ac.cancelAllGoals();
  }
}

void spinThread()
{
  ros::NodeHandle nh;
  ros::spin();
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);

  ros::init(argc, argv, "TestClient");

  boost::thread spin_thread(&spinThread);

  int result = RUN_ALL_TESTS();

  ros::shutdown();

  spin_thread.join();

  return result;
}

