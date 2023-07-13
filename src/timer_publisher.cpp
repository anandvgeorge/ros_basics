#include <ros/ros.h>
#include <ros/callback_queue.h>

#include <std_msgs/Bool.h>
#include <std_msgs/String.h>

class DummyClass
{
private:
    ros::NodeHandle nh_;
    ros::NodeHandle nh_pub_;
    ros::AsyncSpinner pub_spinner_;
    ros::Timer pub_timer_;

    ros::Publisher pub_;
    ros::Subscriber sub_;

    void Publisher(const ros::TimerEvent&);
    void SubscriberCallback(const std_msgs::Bool::ConstPtr& msg);
public:
    DummyClass(ros::NodeHandle& nh, ros::NodeHandle& nh_pub, ros::AsyncSpinner& spinner);
    ~DummyClass() {}
};

DummyClass::DummyClass(ros::NodeHandle& nh, ros::NodeHandle& nh_pub, ros::AsyncSpinner& spinner)
        : nh_(nh), nh_pub_(nh_pub), 
          pub_spinner_(spinner)
{
    // set timer
    pub_timer_ = nh_pub_.createTimer(ros::Duration(2), &DummyClass::Publisher, this);
    sub_ = nh_.subscribe<std_msgs::Bool>("toggle_publisher", 1, &DummyClass::SubscriberCallback, this);
    pub_ = nh_pub_.advertise<std_msgs::String>("some_string", 1);
}

void DummyClass::Publisher(const ros::TimerEvent&)
{
    ROS_INFO("Publishing some data");
    std_msgs::String msg;
    msg.data = "It's working!";
    pub_.publish(msg);
}

void DummyClass::SubscriberCallback(const std_msgs::Bool::ConstPtr& msg)
{
    if (msg->data)
    {
        ROS_INFO("Start publishing");
        pub_spinner_.start();
    }
    else
    {
        ROS_INFO("Stop publishing");
        pub_spinner_.stop();
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "timer_publisher");

    ros::NodeHandle nh;

    ros::NodeHandle nh_pub("~nh_pub");
    ros::CallbackQueue my_queue;
    nh_pub.setCallbackQueue(&my_queue);
    ros::AsyncSpinner spinner(2, &my_queue);

    DummyClass dummy(nh, nh_pub, spinner);

    ros::spin(); // for the regular nodeHandle

    ros::waitForShutdown();
    return 0;
}
