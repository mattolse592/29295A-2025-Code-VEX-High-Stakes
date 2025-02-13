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
        Controller_.Y_.setValue(true);
    }

    void Tick()
    {
        //inputs 
        Controller_.Tick();
        Robot_->InputTick();

        //assign drivetrain values
        Robot_->DriveTrain_.SetLeftStickValue(Controller_.LeftY_.GetPosition());
        Robot_->DriveTrain_.SetRightStickValue(Controller_.RightX_.GetPosition());

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

        if (Controller_.Y_.IsOn()) {
            Robot_->Intake_.SortOn();
        }
        else {
            Robot_->Intake_.SortOff();
        }

        if (Controller_.R1_.IsPressed()) { 
            Robot_->Intake_.ChangeHooksSpeed(0);
        }

        //
        //arm
        //
        if (Controller_.Left_.IsPressed()) {
            Robot_->Arm_.Zero();
        }

        if (Controller_.Down_.WasTapped()) {
            Robot_->Arm_.MoveDown();
        }

        if (Controller_.Up_.WasTapped()) {
            Robot_->Arm_.MoveUp();
        } 
        
        if (Controller_.Right_.IsPressed()) {
            Controller_.L1_.SetPressed(1);
            Robot_->Arm_.ManualTakeoverSet(false);
        }

        if (Controller_.L1_.IsHeld()) {
            Robot_->Arm_.SetTarget((Arm::State)(Controller_.L1_.TimesPressed() % 4));
            Robot_->Arm_.ManualTakeoverSet(false);
        }

        if (Controller_.X_.IsPressed()) {
            Robot_->Arm_.SetTarget(Arm::DESCORE);
            Controller_.L1_.SetPressed(3);
            Robot_->Arm_.ManualTakeoverSet(false);
        }

        

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