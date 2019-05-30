#include "../include/turtlebot_slam_controller/pillar_pos_subscriber.h"

namespace turtlebot_slam_controller {
        turtlebot_slam_sensor::pillar_pos kLatestPillarPos{ };
        
        PillarPosSubscriber::~PillarPosSubscriber() {}

        void PillarPosSubscriber::Callback(const turtlebot_slam_sensor::pillar_pos& pos) const
        {
                kLatestPillarPos = pos;
        }
}
