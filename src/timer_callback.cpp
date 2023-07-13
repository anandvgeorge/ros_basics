#include <ros/ros.h>
#include <ros/callback_queue.h>

void callback1(const ros::TimerEvent&)
{
    ROS_INFO("Callback 1 triggered, waiting 0.4s");
    ros::Duration(0.4).sleep();
}

void callback2(const ros::TimerEvent&)
{
    ROS_INFO("Callback 2 triggered, waiting 1.9s");
    ros::Duration(1.9).sleep();
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "timer_callback");

    ros::NodeHandle nh;
    ros::NodeHandle nh2;
    ros::CallbackQueue my_queue;
    ros::CallbackQueue my_queue2;
    // ros::MultiThreadedSpinner spinner(10);
    nh.setCallbackQueue(&my_queue);
    nh2.setCallbackQueue(&my_queue2);
    // my_queue.callAvailable(ros::WallDuration());
    ros::AsyncSpinner spinner(2, &my_queue);
    ros::AsyncSpinner spinner2(2, &my_queue2);

    ros::Timer timer1 = nh.createTimer(ros::Duration(0.5), &callback1);
    ros::Timer timer2 = nh2.createTimer(ros::Duration(2), &callback2);

    spinner.start();
    spinner2.start();
    // ros::spin(); // it's a blocking spinner, it will block all other spinners

    ros::waitForShutdown();
    return 0;
}
