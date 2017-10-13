/**
 * Class to control the motors of the robot
 * http://www.instructables.com/id/Monster-Motor-Shield-VNH2SP30/
 */

#ifndef LIDARROBOT_MOTOR_H
#define LIDARROBOT_MOTOR_H

#define MOTOR_RIGHT_FORWARD 7
#define MOTOR_RIGHT_BACKWARDS 8

#define MOTOR_LEFT_FORWARD 4
#define MOTOR_LEFT_BACKWARDS 9

#define MOTOR_SPEED_RIGHT 5
#define MOTOR_SPEED_LEFT 6

class Motor {
public:
    Motor();

    void forward(uint8_t speed);
    void backwards(uint8_t speed);

    void right(uint8_t speed, uint8_t turnRate);
    void left(uint8_t speed, uint8_t turnRate);
};


#endif //LIDARROBOT_MOTOR_H
