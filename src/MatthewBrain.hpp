#ifndef MATTHEWBRAIN_HPP
#define MATTHEWBRAIN_HPP

#include "Robot.hpp"
#include "MatthewController.hpp"

class MatthewBrain
{

private:

    Robot* Robot_;
    MatthewController Controller_;

    //piston boolean values
    bool MogoOn_ = false;
    bool DoinkerOn_ = false;
    bool RushArmOn_ = false;
    bool RushJawOn_ = false;

public:
    MatthewBrain(Robot* Robot)
        : Robot_(Robot), Controller_()

    {
        Controller_.Y_.setValue(true);
        Robot_->Intake_.SetArmDocked(false);

        // //initialize the robot to your starting state
        // Robot_->Mogo_.Deactivate();
        // Robot_->Doinker_.Deactivate();
        // Robot_->rushArm_.Deactivate();
        // Robot_->rushClamp_.Deactivate();

        // Robot_->Intake_.Stop();
        // Robot_->Arm_.Zero();

        // // turn off slew
        // Robot->DriveTrain_.DriveTrain_.Chassis_.slew_drive_set(false);

        // //turn off drive pid
        // Robot_->DriveTrain_.DriveTrain_.Chassis_.pid_targets_reset();


    }

    void Tick()
    {
        //inputs 
        Controller_.Tick();
        Robot_->InputTick();

        //assign drivetrain values
        Robot_->DriveTrain_.SetLeftStickValue(Controller_.LeftY_.GetPosition());
        Robot_->DriveTrain_.SetRightStickValue(Controller_.RightX_.GetPosition());

        //
        //intake
        //

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
            if (Robot_->Arm_.GetState() == Arm::LOAD) {
                Controller_.L1_.SetPressed(0);
            }
            else {
                Controller_.L1_.SetPressed(1);
            }

            Robot_->Arm_.SetTarget((Arm::State)(Controller_.L1_.TimesPressed() % 4));
            Robot_->Arm_.ManualTakeoverSet(false);
        }

        if (Controller_.L1_.IsHeld()) {
            Robot_->Arm_.SetTarget((Arm::State)(Controller_.L1_.TimesPressed() % 4));
            Robot_->Arm_.ManualTakeoverSet(false);
        }

        if (Controller_.X_.WasTapped()) {
            Robot_->Arm_.SetTarget(Arm::DESCORE);
            Controller_.L1_.SetPressed(3);
            Robot_->Arm_.ManualTakeoverSet(false);
        }



        //
        //pistons
        //
        if (Controller_.R1_.IsPressed()) {
            Robot_->Intake_.ChangeHooksSpeed(0);

            if (Controller_.A_.WasTapped()) {
                RushJawOn_ = !RushJawOn_;
            }
            if (Controller_.B_.WasTapped()) {
                RushArmOn_ = !RushArmOn_;
            }

            if (Controller_.X_.WasTapped()) {
                Robot_->HalfSpeed = !Robot_->HalfSpeed;
                Controller_.Vibrate();
            }
        }
        else {
            if (Controller_.A_.WasTapped()) {
                MogoOn_ = !MogoOn_;
            }
            if (Controller_.B_.WasTapped()) {
                DoinkerOn_ = !DoinkerOn_;
            }

        }

        Robot_->Mogo_.SetValue(MogoOn_);
        Robot_->Doinker_.SetValue(DoinkerOn_);
        Robot_->rushArm_.SetValue(RushArmOn_);
        Robot_->rushClamp_.SetValue(RushJawOn_);

        //outputs
        Robot_->OutputTick();
    }
};
#endif // MATTHEWBRAIN_HPP