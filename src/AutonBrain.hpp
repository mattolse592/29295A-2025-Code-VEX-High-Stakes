#ifndef AUTONBRAIN_HPP
#define AUTONBRAIN_HPP

#include "Robot.hpp"


class AutonBrain
{

private:

    Robot* Robot_;
   

public:
    AutonBrain(Robot* Robot)
        : Robot_(Robot)
    {

    }
    
    Arm::State armPos = Arm::DOCK;
    bool intakeOn;
    bool mogoOn;


    void Tick()
    {
        Robot_->InputTick();
        
        Robot_->Arm_.SetTarget(armPos);
        
        if (intakeOn) {
            Robot_->Intake_.Forward();
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

    }
};
#endif // AUTONBRAIN_HPP