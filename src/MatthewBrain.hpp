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

    //timers for arm zero
    int zeroPressedCounter = 0;
    int zeroPressedResetCounter = 0;

public:
    MatthewBrain(Robot* Robot)
        : Robot_(Robot), Controller_()

    {
        Controller_.Y_.setValue(true);
        Robot_->Intake_.SetArmDocked(false);
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

        //zero
        if (Controller_.Left_.IsPressed()) {
            zeroPressedCounter++;

            if (zeroPressedCounter > 50) {
                Controller_.Vibrate();
                Robot_->Arm_.Zero();
                zeroPressedCounter = 0;
            }
        } else if (zeroPressedCounter > 0) {
            zeroPressedResetCounter++;

            if (zeroPressedResetCounter > 50) {
                zeroPressedCounter = 0;
                zeroPressedResetCounter = 0;
            }
        }



        if (Controller_.Down_.WasTapped()) {
            if (Robot_->Arm_.GetState() > 4) {
                Robot_->Arm_.SetTarget((Arm::State)(Robot_->Arm_.GetState() + 1));
            } else {
                Robot_->Arm_.MoveDown();
            }
        }

        if (Controller_.Up_.WasTapped()) {
            if (Robot_->Arm_.GetState() > 5) {
                Robot_->Arm_.SetTarget((Arm::State)(Robot_->Arm_.GetState() - 1));
            } else {
                Robot_->Arm_.MoveUp();
            }
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

        if (Controller_.X_.IsPressed()) {
            Robot_->Arm_.SetTarget(Arm::DESCORE1);
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