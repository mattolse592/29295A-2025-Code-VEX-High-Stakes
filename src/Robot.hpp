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

    Intake Intake_;

    Arm Arm_;

    DriveTrainCurveJoystickMath DriveTrain_;



public:
    Robot()
        : Mogo_('A'),
          Doinker_('D'),
          Intake_(Motor(20), Motor(-18)),
          Arm_(Motor(-13), RotationSensor(15)),
          DriveTrain_()

    {
        Arm_.Zero();
        Intake_.SortOn();
    }

    void InputTick()
    {
        Intake_.InputTick();
        Arm_.InputTick();
        DriveTrain_.InputTick();
    }

    void OutputTick() {
        Intake_.OutputTick();
        Arm_.OutputTick();
        DriveTrain_.OutputTick();
    }
};
#endif // ROBOT_HPP