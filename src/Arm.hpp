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
    bool ZeroMode_ = false;
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
        Motor_.Tick();
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
                pid_.setTarget(26.0);
                break;
            case REACH:
                pid_.setTarget(130.0);
                break;
            case SCORE:
                pid_.setTarget(260.0);
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
                pid_.setTarget(192.0);
                break;
            case DESCORE5:
                pid_.setTarget(205.0);
                break;
            case DESCORE6:
                pid_.setTarget(218.0);
                break;
            default:
                break;
            }
        }
        else if (ZeroMode_) {
            Motor_.SetSpeed(-60);

            if (Motor_.IsStalled()) {
                RotationSensor_.Zero();
                ZeroMode_ = false;
                manualTakeover_ = false;
            }
        }
        else {
            int current_position = RotationSensor_.GetPosition();
            double pid_output = pid_.Calculate(current_position);

            // Use the output from PID to set motor speed
            Motor_.SetSpeed(pid_output);
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
        ZeroMode_ = true;
        ManualTakeoverSet(true);
    }

    void RotationSensorZero() {
        RotationSensor_.Zero();
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