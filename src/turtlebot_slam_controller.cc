#include <turtlebot_common/parameter_accessor.h>
#include <turtlebot_common//logging.h>
#include "../include/turtlebot_slam_controller/turtlebot_slam_controller.h"

namespace turtlebot_slam_controller {
        TurtlebotSLAMController::TurtlebotSLAMController(ros::NodeHandle& nh)
                : nh_{ nh }, as_{ nh, "move_to_pillar", false }, move_{ false } 
        {
                turtlebot_common::ParameterAccessor param{ nh };
                std::string topic_sub = param.GetParameter<std::string>(
                                                "/turtlebot_slam_controller/topic_sub");
                std::string topic_pub = param.GetParameter<std::string>(
                                                "/turtlebot_slam_controller/topic_pub");
                uint32_t qs = static_cast<uint32_t>(
                                param.GetParameter<int>(
                                        "/turtlebot_slam_controller/queue_size"));
                base_linear_speed_ = param.GetParameter<float>(
                                                "/turtlebot_slam_controller/base_linear_speed");
                base_angular_speed_ = param.GetParameter<float>(
                                                "/turtlebot_slam_controller/base_angular_speed");
                p_factor_ = param.GetParameter<float>(
                                        "/turtlebot_slam_controller/p_factor");
                pub_ = turtlebot_common::Publisher<geometry_msgs::Twist>{ nh, topic_pub, qs };
                sub_ = PillarPosSubscriber{ nh, topic_sub, qs };

                sub_.Subscribe();

                as_.registerGoalCallback(boost::bind(&TurtlebotSLAMController::GoalCallback, this));
                as_.registerPreemptCallback(boost::bind(&TurtlebotSLAMController::PreemptCallback, this));

                as_.start();
                TURTLEBOT_LOG("Starting action server: done.");
        }

        void TurtlebotSLAMController::FindAndMoveToPillar()
        {
                if (!as_.isActive()) return;

                if (move_ == false) {
                        turtlebot_slam_controller::move_to_pillarResult res;
                        res.finished_moving = true;
                        as_.setSucceeded();
                        return;
                }

                if (kLatestPillarPos.dist < 0) {
                        FindPillar();
                } else if (kLatestPillarPos.dist > 0.5) {
                        MoveToPillar();
                } else {
                        Stop();
                        turtlebot_slam_controller::move_to_pillarResult res;
                        res.finished_moving = true;
                        as_.setSucceeded(res);
                }

                turtlebot_slam_controller::move_to_pillarActionFeedback f;
                f.feedback.pos = kLatestPillarPos;
                as_.publishFeedback(f.feedback);
        }

        void TurtlebotSLAMController::GoalCallback()
        {
                move_ = as_.acceptNewGoal()->move_to_pillar;
                TURTLEBOT_LOG("%d", move_);
        }

        void TurtlebotSLAMController::PreemptCallback()
        {
                as_.setPreempted();
        }

        void TurtlebotSLAMController::FindPillar() const
        {
                geometry_msgs::Twist t{ };
                t.angular.z = base_angular_speed_;
                pub_.Publish(t);
        }

        void TurtlebotSLAMController::MoveToPillar() const
        {
                geometry_msgs::Twist t{ };
                t.linear.x = base_linear_speed_;
                t.angular.z = p_factor_ * kLatestPillarPos.angle;
                pub_.Publish(t);
        }

        void TurtlebotSLAMController::Stop() const
        {
                geometry_msgs::Twist t{ };
                pub_.Publish(t);
        }
}
