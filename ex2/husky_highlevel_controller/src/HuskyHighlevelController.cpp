#include "husky_highlevel_controller/HuskyHighlevelController.hpp"

namespace husky_highlevel_controller {

HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{
  std::string topic ;
  int queue_size ;
  if(!nodeHandle.getParam("topic",topic))
  {
    ROS_ERROR("Couldn't find topic parameter !!! ");
  }
  if(!nodeHandle.getParam("queue_size",queue_size))
  {
    ROS_ERROR("Couldn't find queue_size parameter !!! ");
  }
  ros::Subscriber subscriber_ = nodeHandle.subscribe(topic,queue_size,&HuskyHighlevelController::topic_callback,this);
}

HuskyHighlevelController::~HuskyHighlevelController()
{
}
void HuskyHighlevelController::topic_callback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  float minimum_distance = msg->ranges.at(0);
  for(int i=0; i<=msg->ranges.size();i++)
  {
    if(msg->ranges.at(i)<minimum_distance)
    {
      minimum_distance=msg->ranges.at(i);
    }
  }
  ROS_INFO("The minimum distnace in the vector is  %f", minimum_distance);
}

} /* namespace */
