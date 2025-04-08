#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "../include/pros/adi.h"

#include "Basic Control Classes/Piston.hpp"
#include "Intake.hpp"
#include "Arm.hpp"
#include "DriveTrainCurveJoystickMath.hpp"

class Robot
{

public:
    Pistonf Mogo_;
    Pistonf Doinker_;
    Pistonf rushArm_;
    Pistonf rushClamp_;
    Pistonf IntakeLift_;

    Intake Intake_;

    Arm Arm_;

    DriveTrainCurveJoystickMath DriveTrain_;

    bool IsAutonomous = false;

    bool HalfSpeed = false;

public:
    Robot()
        : Mogo_('A'),
          Doinker_('D'),
          rushArm_('E'),
          rushClamp_('C'),
          IntakeLift_('F'),
          Intake_(Motor(20), Motor(18)),
          Arm_(Motor(-13), RotationSensor(15)),
          DriveTrain_()

    {
        Arm_.RotationSensorZero();
        Intake_.SortOn();
    }

    void InputTick()
    {
        Intake_.InputTick();
        Arm_.InputTick();
        DriveTrain_.SetHalfSpeedValue(HalfSpeed);
        DriveTrain_.InputTick();
    }

    void OutputTick() {
        Intake_.OutputTick();
        Arm_.OutputTick();
        DriveTrain_.OutputTick();
    }

    void AutonOutputTick() {
        Intake_.OutputTick();
        Arm_.OutputTick();
    }

    void SetAllianceAsRed(bool isRed) {
        Intake_.SetAllianceAsRed(isRed);
    }
};


#endif // ROBOT_HPP