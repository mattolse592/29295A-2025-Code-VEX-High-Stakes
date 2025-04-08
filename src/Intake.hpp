#ifndef INTAKE_HPP
#define INTAKE_HPP

#include "Basic Control Classes/Motor.hpp"
#include "RingDetector.hpp"

class Intake
{

private:
    Motor Preroller_;
    Motor Hooks_;

    RingDetector RingDetector_;

    int PreRollerSpeed_;
    int HooksSpeed_;
    bool ArmIsDocked_ = false;

public:
    Intake(Motor Preroller, Motor Hooks)
        : Preroller_(Preroller), Hooks_(Hooks)
    {
        Hooks_.SetBrakeMode(MOTOR_BRAKE_COAST);
        ArmIsDocked_ = true;
    }

    void InputTick() {
        RingDetector_.Tick();
        Hooks_.Tick();
    }

    void OutputTick() {
        Preroller_.SetSpeed(PreRollerSpeed_);

        if (RingDetector_.GetReverseTimer() > 0) {
            Hooks_.SetSpeed(127);
        }
        else  if (Hooks_.GetReverseTimer() > 0 && ArmIsDocked_) {
            Hooks_.SetSpeed(127);
        }
        else {
            Hooks_.SetSpeed(HooksSpeed_);
        }

        //fixez::screen_print(std::to_string(RingDetector_.GetReverseTimer()), 1);
    }

    void Forward()
    {
        PreRollerSpeed_ = 127;
        HooksSpeed_ = -127;
    }

    void Reverse()
    {
        PreRollerSpeed_ = -127;
        HooksSpeed_ = 127;
    }

    void HooksReverse()
    {
        PreRollerSpeed_ = 127;
        HooksSpeed_ = 127;
    }

    void PreRollForward()
    {
        PreRollerSpeed_ = 127;
        HooksSpeed_ = 0;
    }

    void PreRollReverse()
    {
        PreRollerSpeed_ = -127;
        HooksSpeed_ = 0;
    }

    void Stop()
    {
        PreRollerSpeed_ = 0;
        HooksSpeed_ = 0;
    }

    void ChangePreRollerSpeed(int speed)
    {
        PreRollerSpeed_ = speed;
    }

    void ChangeHooksSpeed(int speed)
    {
        HooksSpeed_ = speed;
    }

    void SortOn() {
        RingDetector_.SortOn();
    }

    void SortOff() {
        RingDetector_.SortOff();
    }

    void SetAllianceAsRed(bool isRed) {
        RingDetector_.SetAllianceAsRed(isRed);
    }

    void SetArmDocked(bool ArmIsDocked) {
        ArmIsDocked_ = ArmIsDocked;
    }

};
#endif // INTAKE_HPP