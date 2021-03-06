#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
//#include <geometery_msgs/Quaternion.h>
#include <tf/transform_datatypes.h>

nav_msgs::Odometry odom;


double x,y,z,w;


void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  x = (double)msg->pose.pose.position.x;
  y = (double)msg->pose.pose.position.y;
  z = (double)msg->pose.pose.orientation.z;
  w = (double)msg->pose.pose.orientation.w;
}

int main(int argc, char** argv){
  ros::init(argc, argv, "robot_tf_publisher");
  ros::NodeHandle n;

  //ros::Subscriber sub = n.subscribe("/robot_odom", 1, odomCallback);
  ros::Subscriber sub = n.subscribe("/robot_filter", 1, odomCallback);
  ros::Rate r(10);

  tf::TransformBroadcaster broadcaster;
  tf::Quaternion q_temp;


  while(n.ok()){
    //q_temp = tf::createQuaternionFromRPY(0,0,z);
    //q_temp.normalize();

    broadcaster.sendTransform(
        tf::StampedTransform(
        tf::Transform(tf::Quaternion(0, 0, z , w), 
	tf::Vector3(x,y,0)),
        ros::Time::now(),"odom", "base_link"));
      
    //tf::StampedTransform(tf::Transform(q_temp, tf::Vector3(x,y,0.2)), ros::Time::now(), "base_link", "laser"));
    ros::spinOnce();
    r.sleep();
  }
ros::spin();
}
