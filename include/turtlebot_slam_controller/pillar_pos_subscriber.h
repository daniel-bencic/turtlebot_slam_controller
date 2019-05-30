#ifndef PILLAR_POS_SUBSCRIBER
#define PILLAR_POS_SUBSCRIBER

#include <string>
#include <ros/ros.h>
#include <turtlebot_common/subscriber.h>
#include <turtlebot_slam_sensor/pillar_pos.h>

namespace turtlebot_slam_controller {
        extern turtlebot_slam_sensor::pillar_pos kLatestPillarPos;
        
        class PillarPosSubscriber 
                : public turtlebot_common::Subscriber<turtlebot_slam_sensor::pillar_pos> {
                public:
                        using turtlebot_common::Subscriber<turtlebot_slam_sensor::pillar_pos>::Subscriber;
                        ~PillarPosSubscriber();

                private:
                        void Callback(const turtlebot_slam_sensor::pillar_pos& pos) const;
        };
}

#endif /* PILLAR_POS_SUBSCRIBER */
