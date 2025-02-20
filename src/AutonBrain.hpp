#ifndef AUTONBRAIN_HPP
#define AUTONBRAIN_HPP

#include "Robot.hpp"
#include "LimitSwitch.hpp"

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


    void Tick()
    {
        LimSwitch_.Tick();

        Robot_->InputTick();
        
        Robot_->Arm_.SetTarget(armPos);
        
        if (intakeOn) {
            if (!mogoOn && LimSwitch_.GetValue()) {
                Robot_->Intake_.Stop();
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

        Robot_->AutonOutputTick();
    }

    void SetAllianceAsRed(bool isRed) {
        Robot_->SetAllianceAsRed(isRed);
    }
};
#endif // AUTONBRAIN_HPP