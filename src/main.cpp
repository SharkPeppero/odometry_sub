#include "ros/ros.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/TransformStamped.h"
#include <nav_msgs/Odometry.h>

#include <iostream>
#include <fstream>

using namespace std;
std::string save_path;
std::string topic_sub;
int count_;

void record_point(const nav_msgs::Odometry::ConstPtr &odomAftMapped)
{
    //===================输出里程计信息===========================
    // 保存tum格式的路径结果，RESULT_PATH根据自己的路径更改
    std::ofstream foutC(save_path, std::ios::app);//读取文件
    foutC.setf(std::ios::fixed, std::ios::floatfield);
    foutC.precision(8); // 保存结果的精度
    foutC << odomAftMapped->header.stamp << " "
          << odomAftMapped->pose.pose.position.x << " "
          << odomAftMapped->pose.pose.position.y << " "
          << odomAftMapped->pose.pose.position.z << " "
          << odomAftMapped->pose.pose.orientation.x << " "
          << odomAftMapped->pose.pose.orientation.y << " "
          << odomAftMapped->pose.pose.orientation.z << " "
          << odomAftMapped->pose.pose.orientation.w << std::endl;
    foutC.close();
    //=============================================
    ROS_INFO_STREAM(count_++);

}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"record_pathPoint");
    ros::NodeHandle nh;

    //读取话题参数||读取保存路径的参数
    nh.getParam("path_save",save_path);
    nh.getParam("sub_topic",topic_sub);
    count_=0;

    ros::Subscriber sub=nh.subscribe<nav_msgs::Odometry>(topic_sub,100,record_point);
    ros::spin();
    return 0;
}
