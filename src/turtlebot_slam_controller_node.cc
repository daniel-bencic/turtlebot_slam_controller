#include <ros/ros.h>
#include <ros/console.h>
#include <actionlib/server/simple_action_server.h>
#include <turtlebot_slam_controller/move_to_pillarAction.h>
#include <turtlebot_common/logging.h>
#include "../include/turtlebot_slam_controller/turtlebot_slam_controller.h"

int main(int argc, char *argv[])
{
        if( ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug) ) {
                ros::console::notifyLoggerLevelsChanged();
        }
        ros::init(argc, argv, "turtlebot_slam_controller");
        ros::NodeHandle nh{ };

        turtlebot_slam_controller::TurtlebotSLAMController c{ nh };

        ros::Rate r{ 10 };
        while (ros::ok()) {
                c.FindAndMoveToPillar();
                r.sleep();
                ros::spinOnce();
        }

        return 0;
}
