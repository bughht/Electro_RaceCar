#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include "nav_msgs/Odometry.h"
#include "ackermann_msgs/AckermannDriveStamped.h"
#include "raceworld/status.h"
#include "tf/tf.h"
#include "tf/transform_listener.h"
#include <sstream>

#define PI 3.1415926535

ros::Publisher velocity_publisher;
std::string leader_name;
std::string follower1;

int isformation;

nav_msgs::Odometry ldmsg,msg1,msg2;
bool pose_flag = false;


void move(double speed, bool isForward);


void statusCallBack(const raceworld::status::ConstPtr & status_msg);
void poseCallback1(const nav_msgs::Odometry::ConstPtr& msg);
void poseCallback2(const nav_msgs::Odometry::ConstPtr& msg);

int cnt = 0;

int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "leader");

  ros::NodeHandle leaderNode;

  ros::Subscriber platoon_status = leaderNode.subscribe("/status",1,statusCallBack);
  ros::Subscriber pose1 = leaderNode.subscribe("/deepracer1/base_pose_ground_truth", 10, poseCallback1);
  ros::Subscriber pose2 = leaderNode.subscribe("/deepracer2/base_pose_ground_truth", 10, poseCallback2);
  
  

  ros::Rate loop_rate(100);
  while(ros::ok())
  {
    ros::spinOnce();
    if(leader_name!="")
    {	
      
      if(pose_flag)
      {
        switch(leader_name[9]-'0')
      {
        case 1:
          ldmsg = msg1; break;
        case 2:
          ldmsg = msg2; break;

      }
  
      }
    }
    loop_rate.sleep();
  }
  
  
  return 0;
}

void move(double speed, bool isForward)
{
   ackermann_msgs::AckermannDriveStamped vel_msg;
   tf::Quaternion ldorientation;
   tf::quaternionMsgToTF(ldmsg.pose.pose.orientation, ldorientation);
   double alpha = PI/2 - ldorientation.getAngle();
   double e = ldmsg.pose.pose.position.x - 1.87;
   double k = 1;
   if (isForward)
	   vel_msg.drive.speed =fabs(speed);
   else
	   vel_msg.drive.speed =-fabs(speed);

   vel_msg.header.stamp = ros::Time::now();
   vel_msg.header.frame_id = leader_name +"/base_link";


   vel_msg.drive.steering_angle = atan2(k*e,1) + alpha;

	 velocity_publisher.publish(vel_msg);
}



void statusCallBack(const raceworld::status::ConstPtr & status_msg)
{
	leader_name = status_msg->leader;
	isformation = status_msg->formation;
	follower1 = status_msg->follower1;
 


}

void poseCallback1(const nav_msgs::Odometry::ConstPtr& msg)
{
  pose_flag = true;
  msg1.child_frame_id = msg->child_frame_id;
  msg1.header = msg->header;
  msg1.pose = msg->pose;
  msg1.twist = msg->twist;
}

void poseCallback2(const nav_msgs::Odometry::ConstPtr& msg)
{
  pose_flag = true;
  msg2.child_frame_id = msg->child_frame_id;
  msg2.header = msg->header;
  msg2.pose = msg->pose;
  msg2.twist = msg->twist;
}

