#ifndef MATTHEWBRAIN_HPP
#define MATTHEWBRAIN_HPP

#include "Robot.hpp"
#include "MatthewController.hpp"

class MatthewBrain
{

private:

    Robot* Robot_;
    MatthewController Controller_;

public:
    MatthewBrain(Robot* Robot)
        : Robot_(Robot), Controller_()

    {
        Controller_.Down_.setValue(true);
    }

    void Tick()
    {
        //inputs 
        Controller_.Tick();
        Robot_->InputTick();

        //assign drivetrain values
        Robot_->DriveTrain_.SetLeftStickValue(Controller_.LeftY_.GetPosition());
        Robot_->DriveTrain_.SetRightStickValue(Controller_.RightX_.GetPosition());
        Robot_->DriveTrain_.SetShiftButtonValue(Controller_.R1_.IsPressed());

        //intake
        if (Controller_.R2_.IsPressed()) {
            Robot_->Intake_.Forward();
        }
        else if (Controller_.L2_.IsPressed()) {
            Robot_->Intake_.Reverse();
        }
        else {
            Robot_->Intake_.Stop();
        }

        if (Controller_.Down_.IsOn()) {
            Robot_->Intake_.SortOn();
        } else {
             Robot_->Intake_.SortOff();
        }

        //arm
        if (Controller_.Left_.IsPressed()) {
            Robot_->Arm_.Zero();
        }

        if (Controller_.R1_.IsPressed()) {
            Robot_->Arm_.ManualMoveSet(true);
            Robot_->Arm_.ManualMove(Controller_.RightY_.GetPosition());
        } else {
            Robot_->Arm_.ManualMoveSet(false);
        }

        Robot_->Arm_.SetTarget((Arm::State)(Controller_.L1_.TimesPressed() % 3));

        //pistons
        if (Controller_.A_.IsOn()) {
            Robot_->Mogo_.Activate();
        }
        else {
            Robot_->Mogo_.Deactivate();
        }
        
        if (Controller_.B_.IsOn()) {
            Robot_->Doinker_.Activate();
        }
        else {
            Robot_->Doinker_.Deactivate();
        }

        //outputs
        Robot_->OutputTick();
    }
};
#endif // MATTHEWBRAIN_HPP