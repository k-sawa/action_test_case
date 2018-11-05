#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <control_msgs/FollowJointTrajectoryAction.h>

class TestServer
{
protected:
  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<control_msgs::FollowJointTrajectoryAction> as_;
  uint32_t count_;

public:
  TestServer() : as_(nh_, "follow_joint_trajectory_action", boost::bind(&TestServer::goalCb, this, _1), false), count_(0)
  {
    as_.start();
  }

  ~TestServer()
  {
  }

  void goalCb(const control_msgs::FollowJointTrajectoryGoalConstPtr& goal)
  {
    // ros::Duration(0.01).sleep();
    control_msgs::FollowJointTrajectoryResult result;
    as_.setSucceeded(result);
    ROS_INFO("setSucceeded [%u]", ++count_);
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "TestServer");
  TestServer ts;
  ros::spin();

  return 0;
}
