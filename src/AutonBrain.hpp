#ifndef AUTONBRAIN_HPP
#define AUTONBRAIN_HPP

#include "Robot.hpp"
#include "Basic Control Classes/LimitSwitch.hpp"

class AutonBrain
{

private:

    Robot* Robot_;
    LimitSwitch LimSwitch_;
   
public:
    AutonBrain(Robot* Robot)
        : Robot_(Robot), LimSwitch_('B')
    {

    }
    
    Arm::State armPos = Arm::DOCK;
    bool intakeOn = false;
    bool mogoOn = false;
    bool doinkerOn = false;
    bool rushClampOn = false;
    bool rushArmOn = false;
    bool intakeLiftOn = false;
    bool rollerOnly = false;

    void Tick()
    {
        LimSwitch_.Tick();

        Robot_->InputTick();
        
        Robot_->Arm_.SetTarget(armPos);
        
        if (armPos == Arm::DOCK) {
            Robot_->Intake_.SetArmDocked(true);
        }
        else {
            Robot_->Intake_.SetArmDocked(false);
        }

        if (intakeOn) {
            if(rollerOnly) {
                Robot_->Intake_.PreRollForward();
            }
            else {
                Robot_->Intake_.Forward();
            }
        }
        else {
            Robot_->Intake_.Stop();
        }

        if (mogoOn) {
            Robot_->Mogo_.Activate();
        }
        else {
            Robot_->Mogo_.Deactivate();
        }

        if (doinkerOn) {
            Robot_->Doinker_.Activate();
        }
        else {
            Robot_->Doinker_.Deactivate();
        }

        if (rushClampOn) {
            Robot_->rushClamp_.Activate();
        }
        else {
            Robot_->rushClamp_.Deactivate();
        }

        if (rushArmOn) {
            Robot_->rushArm_.Activate();
        }
        else {
            Robot_->rushArm_.Deactivate();
        }

        if (intakeLiftOn) {
            Robot_->IntakeLift_.Activate();
        } else {
            Robot_->IntakeLift_.Deactivate();
        }

        Robot_->AutonOutputTick();
    }

    void SetAllianceAsRed(bool isRed) {
        Robot_->SetAllianceAsRed(isRed);
    }
};
#endif // AUTONBRAIN_HPP