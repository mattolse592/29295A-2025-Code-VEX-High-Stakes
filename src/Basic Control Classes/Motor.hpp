#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "../include/pros/motors.hpp"
#include "../include/pros/motors.h"
class Motor
{

private:
    int MotorSpeed_;
    int reverseTimer = 0;
    pros::Motor Motor_;

public:
    Motor(char PortNum)
        : Motor_(PortNum)
    {
    }

    void Tick() {
        if (Motor_.get_target_velocity() - Motor_.get_actual_velocity() > 30) {
            reverseTimer = 30;
        }
        reverseTimer--;
    }

    int GetReverseTimer() {
        return reverseTimer;
    }


    void SetSpeed(int motorSpeed) {
        // values from -127 to 127
        MotorSpeed_ = motorSpeed;
        Motor_.move(MotorSpeed_);
    }

    void Stop() {
        SetSpeed(0);
    }

    void SetBrakeMode(pros::motor_brake_mode_e brakeMode) {
        Motor_.set_brake_mode(brakeMode);
    }
};
#endif  // MOTOR_HPP