#ifndef ARM_HPP
#define ARM_HPP


#include "PID.hpp"

class Arm
{

private:
    Motor Motor_;
    RotationSensor RotationSensor_;
    PIDController pid_ = PIDController(2, 0.05, 2, 0.0);

    bool manualTakeover_ = false;
    bool zeroMode = false;
    int StickInput_;


public:
    enum State
    {
        DOCK = 0,
        LOAD = 1,
        REACH = 2,
        SCORE = 3,
        REMOTE = 4,
        DESCORE1 = 5,
        DESCORE2 = 6,
        DESCORE3 = 7,
        DESCORE4 = 8,
        DESCORE5 = 9,
        DESCORE6 = 10
    };

    int downPresses_ = 0;
    int upPresses_ = 0;

private:
    State Target_ = DOCK;

public:
    Arm(Motor Motor, RotationSensor RotationSensor)
        : Motor_(Motor), RotationSensor_(RotationSensor)
    {
    }

    void InputTick()
    {
        RotationSensor_.Tick();
    }

    void OutputTick() {
        if (!manualTakeover_)
        {
            int current_position = RotationSensor_.GetPosition();
            double pid_output = pid_.Calculate(current_position);

            // Use the output from PID to set motor speed
            Motor_.SetSpeed(pid_output);

            switch (Target_)
            {
            case DOCK:
                pid_.setTarget(2.0);
                break;
            case LOAD:
                pid_.setTarget(28.0);
                break;
            case REACH:
                pid_.setTarget(130.0);
                break;
            case SCORE:
                pid_.setTarget(235.0);
                break;
            case REMOTE:
                pid_.setTarget(90.0);
                break;
            case DESCORE1:
                pid_.setTarget(160.0);
                break;
            case DESCORE2:
                pid_.setTarget(170.0);
                break;
            case DESCORE3:
                pid_.setTarget(180.0);
                break;
            case DESCORE4:
                pid_.setTarget(193.0);
                break;
            case DESCORE5:
                pid_.setTarget(205.0);
                break;
            case DESCORE6:
                pid_.setTarget(220.0);
                break;
            default:
                break;
            }
            ez::screen_print("normal pid", 2);
        }
        else if (zeroMode) {
            Motor_.SetSpeed(-10);

            if (Motor_.GetReverseTimer() > 14) {
                RotationSensor_.Zero();
                zeroMode = false;
                //ManualTakeoverSet(false);
            }
            ez::screen_print("zero Mode", 2);
        }
        else {
            int current_position = RotationSensor_.GetPosition();
            double pid_output = pid_.Calculate(current_position);

            // Use the output from PID to set motor speed
            Motor_.SetSpeed(pid_output);

            ez::screen_print("Manual Takeover", 2);
        }
    }

    void MoveUp() {
        pid_.setTarget(RotationSensor_.GetPosition() - 10);
        manualTakeover_ = true;
    }

    void MoveDown() {
        pid_.setTarget(RotationSensor_.GetPosition() + 10);
        manualTakeover_ = true;
    }

    void SetTarget(State state)
    {
        Target_ = state;
    }

    void ManualTakeoverSet(bool takeOverSetting)
    {
        manualTakeover_ = takeOverSetting;
    }

    void Zero() {
        ManualTakeoverSet(true);
        zeroMode = true;
    }

#pragma region get functions
    double GetPosition()
    {
        return RotationSensor_.GetPosition();
    }

    double GetPIDValue()
    {
        return pid_.getCurrentValue();
    }

    State GetState()
    {
        return Target_;
    }
#pragma endregion

};
#endif // ARM_HPP