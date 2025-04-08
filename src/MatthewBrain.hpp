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

    //arm timer
    int ZeroTimer = 0;
    int DescoreWaitAmount = 500;
    int DescoreIntervalTimer = DescoreWaitAmount;
    int DownPressedAmount = 0;
    bool VibrateOnce = false;

public:
    MatthewBrain(Robot* Robot)
        : Robot_(Robot), Controller_()

    {
        Controller_.Y_.setValue(true);
        Robot_->Intake_.SetArmDocked(false);
        Robot_->Arm_.Zero();
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
            ZeroTimer++;

            if (ZeroTimer > 50) {
                Robot_->Arm_.Zero();
                Controller_.Vibrate();
                ZeroTimer = 0;

                Controller_.L1_.SetPressed(0);
                Robot_->Arm_.SetTarget((Arm::State)(Controller_.L1_.TimesPressed() % 4));
            }
        }

        if (Controller_.Down_.WasTapped()) {
            if (Robot_->Arm_.GetState() > 4) {
                if (Robot_->Arm_.GetState() == 10) {
                    Robot_->Arm_.SetTarget((Arm::State)(10));
                } else {
                    Robot_->Arm_.SetTarget((Arm::State)(Robot_->Arm_.GetState() + 1));
                }
                
                DownPressedAmount++;
            } else {
                Robot_->Arm_.MoveDown();
            }
        }

        if (Controller_.Up_.WasTapped()) {
            if (Robot_->Arm_.GetState() > 5) {
                Robot_->Arm_.SetTarget((Arm::State)(Robot_->Arm_.GetState() - 1));
                DownPressedAmount--;
            } else {
                Robot_->Arm_.MoveUp();
            }
        }

        if (Controller_.Right_.WasTapped()) {
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
            if (DescoreIntervalTimer < DescoreWaitAmount) {
                DownPressedAmount++;

                if (DownPressedAmount > 5) {
                    DownPressedAmount = 5;
                } else if (DownPressedAmount < 0) {
                    DownPressedAmount = 0;
                }

                Robot_->Arm_.SetTarget((Arm::State)(5 + DownPressedAmount));
                master.rumble(".");
            } else {
                Robot_->Arm_.SetTarget(Arm::DESCORE1);
                DownPressedAmount = 0;
            }
            
            Controller_.L1_.SetPressed(3);
            Robot_->Arm_.ManualTakeoverSet(false);
            DescoreIntervalTimer = 0;
            VibrateOnce = false;

        }

        DescoreIntervalTimer++;

        if (DescoreIntervalTimer > DescoreWaitAmount && !VibrateOnce) { 
            Controller_.Vibrate();
            VibrateOnce = true;
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