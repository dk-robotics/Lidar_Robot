/**
 * Class to control the motors of the robot
 * http://www.instructables.com/id/Monster-Motor-Shield-VNH2SP30/
 */

#ifndef LIDARROBOT_MOTOR_H
#define LIDARROBOT_MOTOR_H

#include "PinSetup.h"

class Motor {
public:
    Motor();

    void forward(uint8_t speed);
    void backwards(uint8_t speed);

    void right(uint8_t speed, uint8_t turnRate);
    void left(uint8_t speed, uint8_t turnRate);

    void degreeTurn(uint8_t speed, unsigned int degrees);
};


#endif //LIDARROBOT_MOTOR_H
