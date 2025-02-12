#ifndef DRIVERTRAIN_HPP
#define DRIVERTRAIN_HPP

#include "../include/EZ-Template/drive/drive.hpp"


class DriveTrain
{

private:
    //  variable for # of motors per side
    const int sideMotors = 3;
    bool AutonomousMode_ = false; // In autonomous mode, we use PID control for motors. In non-autonomous mode, we use human controller inputs.
    int LeftSpeed_;
    int RightSpeed_;

public:
    Drive Chassis_;

private:
    void default_constants() {
        // P, I, D, and Start I
        Chassis_.pid_drive_constants_set(137.0, 0.0, 80.0);         // Fwd/rev constants, used for odom and non odom motions
        Chassis_.pid_heading_constants_set(10, 0.0, 45);        // Holds the robot straight while going forward without odom
        Chassis_.pid_turn_constants_set(5.0, 0.0, 30.5, 0.0);     // Turn in place constants
        Chassis_.pid_swing_constants_set(6.0, 0.0, 65.0);      //6.0 , 0.0, 65,0     // Swing constants
        Chassis_.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
        Chassis_.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

        // Exit conditions
        Chassis_.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
        Chassis_.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
        Chassis_.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
        Chassis_.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
        Chassis_.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
        Chassis_.pid_turn_chain_constant_set(3_deg);
        Chassis_.pid_swing_chain_constant_set(5_deg);
        Chassis_.pid_drive_chain_constant_set(3_in);

        // Slew constants
        Chassis_.slew_turn_constants_set(3_deg, 70);
        Chassis_.slew_drive_constants_set(3_in, 70);
        Chassis_.slew_swing_constants_set(3_in, 80);

        // The amount that turns are prioritized over driving in odom motions
        // - if you have tracking wheels, you can run this higher.  1.0 is the max
        Chassis_.odom_turn_bias_set(0);

        Chassis_.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
        Chassis_.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
        Chassis_.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are
        Chassis_.odom_enable(false);

        Chassis_.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
    }

public:
    DriveTrain()
        :Chassis_(
            // These are your drive motors, the first motor is used for sensing!
            { 1, -3, 4 },     // Left Chassis Ports (negative port will reverse it!)
            { -6, 7, -8 },  // Right Chassis Ports (negative port will reverse it!)

            10,      // IMU Port
            2.75,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
            450)
    {
        default_constants();
        Chassis_.initialize();
    }

    void OutputTick()
    {
        if (AutonomousMode_ == false)
        {
            // assigns motor speeds
            for (int i = 0; i < sideMotors; i++)
            {
                Chassis_.left_motors[i].move(LeftSpeed_);
                Chassis_.right_motors[i].move(RightSpeed_);
            }
        }
    }

    void setLeftSpeed(int leftSpeed)
    {
        LeftSpeed_ = leftSpeed;
    }
    void setRightSpeed(int rightSpeed)
    {
        RightSpeed_ = rightSpeed;
    }
};

#endif // DRIVERTRAIN_HPP