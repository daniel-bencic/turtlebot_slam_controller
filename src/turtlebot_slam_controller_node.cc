#include <ros/ros.h>



int main(int argc, char *argv[])
{
        ros::init(argc, argv, "turtlebot_slam_controller");
        ros::NodeHandle nh{ };
        ros::spin();

        return 0;
}
