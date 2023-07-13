#include <ros/ros.h>

void callback1(const ros::TimerEvent&)
{
    ROS_INFO("Callback 1 triggered, waiting 0.4s");
    ros::Duration(0.4).sleep();
}

void callback2(const ros::TimerEvent&)
{
    ROS_INFO("Callback 2 triggered, waiting 2.2s");
    ros::Duration(2.2).sleep();
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "timer_basics");

    ros::NodeHandle nh;
    ros::NodeHandle nh2;
    // ros::MultiThreadedSpinner spinner(10);
    ros::AsyncSpinner spinner(10);

    ros::Timer timer1 = nh.createTimer(ros::Duration(0.5), &callback1);
    ros::Timer timer2 = nh2.createTimer(ros::Duration(2), &callback2);

    spinner.start();

    ros::waitForShutdown();
    return 0;
}
