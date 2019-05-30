#ifndef TURTLEBOT_SLAM_CONTROLLER
#define TURTLEBOT_SLAM_CONTROLLER

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <geometry_msgs/Twist.h>
#include <turtlebot_common/publisher.h>
#include <turtlebot_slam_controller/move_to_pillarAction.h>
#include "pillar_pos_subscriber.h"

namespace turtlebot_slam_controller {
        

        class TurtlebotSLAMController {
                public:
                        TurtlebotSLAMController(ros::NodeHandle& nh);
                        void FindAndMoveToPillar();
                                                
                private:
                        void GoalCallback();
                        void PreemptCallback();
                        void FindPillar() const;
                        void MoveToPillar() const;
                        void Stop() const;
                        ros::NodeHandle nh_;
                        actionlib::SimpleActionServer<turtlebot_slam_controller::move_to_pillarAction> as_;
                        turtlebot_common::Publisher<geometry_msgs::Twist> pub_;
                        PillarPosSubscriber sub_;
                        float base_linear_speed_;
                        float base_angular_speed_;
                        float p_factor_;
                        bool move_;
                };
}

#endif /* TURTLEBOT_SLAM_CONTROLLER */
