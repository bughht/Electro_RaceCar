#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include "sensor_msgs/LaserScan.h"
#include "ackermann_msgs/AckermannDriveStamped.h"
#include "raceworld/status.h"
#include "tf/tf.h"
#include <unistd.h>
#include <queue>

#define PI 3.1415926535

ros::Publisher slave_vel1;
ackermann_msgs::AckermannDriveStamped vel_msg1;
std::string leader_name;
std::string follower1;

const double thresh_distance = 0.2;

nav_msgs::Odometry target_point1;
std::queue<nav_msgs::Odometry> *ldmsg_queue1,*ldmsg_queue2;
int isformation;

nav_msgs::Odometry ldmsg,f1msg,msg1,msg2;
bool pose_flag = false;

//Function declerations to move
void follow (nav_msgs::Odometry);
//Call back function decleration
void laserCallBack(const sensor_msgs::LaserScan::ConstPtr & laser_msg); 
void statusCallBack(const raceworld::status::ConstPtr & status_msg);
void poseCallback1(const nav_msgs::Odometry::ConstPtr& msg);
void poseCallback2(const nav_msgs::Odometry::ConstPtr& msg);

int main(int argc, char** argv)
{
  ldmsg_queue1 = new std::queue<nav_msgs::Odometry>;
  ldmsg_queue2 = new std::queue<nav_msgs::Odometry>;
 
  ros::init(argc, argv, "follower1");

  ros::NodeHandle node;

  ros::Subscriber platoon_status = node.subscribe("/status", 1, statusCallBack);
  ros::Subscriber pose1 = node.subscribe("/deepracer1/base_pose_ground_truth", 10, poseCallback1);
  ros::Subscriber pose2 = node.subscribe("/deepracer2/base_pose_ground_truth", 10, poseCallback2);
  
  
  ros::Rate rate(100.0);
  while (ros::ok())
  {
    ros::spinOnce();
    if(follower1!="")
    {
      slave_vel1 =
      node.advertise<ackermann_msgs::AckermannDriveStamped>(follower1+"/ackermann_cmd_mux/output", 100);
      

      vel_msg1.header.stamp = ros::Time::now();
      vel_msg1.header.frame_id = follower1+"/base_link";
      
      if(pose_flag)
      {
          ldmsg = msg1;
          f1msg = msg2;
          
          ldmsg_queue1->push(ldmsg);
          ldmsg_queue2->push(f1msg);
          
          double distance1 = sqrt((target_point1.pose.pose.position.x - f1msg.pose.pose.position.x) * (target_point1.pose.pose.position.x - f1msg.pose.pose.position.x)
                                + (target_point1.pose.pose.position.y - f1msg.pose.pose.position.y) * (target_point1.pose.pose.position.y - f1msg.pose.pose.position.y));
          if(target_point1.pose.pose.position.x == 0 && target_point1.pose.pose.position.y == 0)
          target_point1 = ldmsg;
          if(distance1 < thresh_distance){
          target_point1 = ldmsg_queue1->front();
          ldmsg_queue1->pop();
          }
          else if(distance1 > 5){
            delete ldmsg_queue1;
            ldmsg_queue1 = new std::queue<nav_msgs::Odometry>;
            target_point1 = ldmsg;
          }
         
          follow(target_point1);
      }
    }
    rate.sleep();
  }
  return 0;
};


void follow (nav_msgs::Odometry target1)
{
  tf::Quaternion f1orientation,f2orientation,f3orientation,f4orientation,ldorientation;
  tf::quaternionMsgToTF(f1msg.pose.pose.orientation, f1orientation);
  
  tf::quaternionMsgToTF(ldmsg.pose.pose.orientation, ldorientation);
  double delta1 = atan2(target1.pose.pose.position.y-f1msg.pose.pose.position.y,target1.pose.pose.position.x-f1msg.pose.pose.position.x);
 
  if(delta1 < 0){
    delta1 += 2 * PI;
  }
  
  double roll,pitch,yaw1;
  tf::Matrix3x3(f1orientation).getRPY(roll, pitch, yaw1);
  
  double gamma1 = yaw1;

  if(gamma1 < 0){
    gamma1 += 2 * PI;
  }
 
  double theta1 = delta1 - gamma1;

  if(theta1 > PI){
    theta1 -= 2 * PI;
  }
  if(theta1 < -PI){
    theta1 += 2 * PI;
  }
  
  // ROS_INFO("%f",delta1);
  
  double r1 = sqrt(pow(ldmsg.pose.pose.position.x-f1msg.pose.pose.position.x, 2) +
                                  pow(ldmsg.pose.pose.position.y-f1msg.pose.pose.position.y, 2));
  
  double k = 1.0;
  if(r1 > 0.4)
  {
    vel_msg1.drive.speed = 0.3 * r1;
  }else
  {
    vel_msg1.drive.speed = 0.05;
  }
  
  vel_msg1.drive.steering_angle = k * theta1;
  
  slave_vel1.publish(vel_msg1);

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

