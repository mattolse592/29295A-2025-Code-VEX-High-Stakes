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
    int StickInput_;

public:
    enum State
    {
        DOCK = 0,
        LOAD = 1,
        REACH = 2,
        SCORE = 3,
        DESCORE = 4,
        MANUAL = 5
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
        if (!manualTakeover_)
        {
            int current_position = RotationSensor_.GetPosition();
            double pid_output = pid_.Calculate(current_position);

            // Use the output from PID to set motor speed
            Motor_.SetSpeed(pid_output);

            switch (Target_)
            {
            case DOCK:
                Dock();
                break;
            case LOAD:
                Load();
                break;
            case REACH:
                Reach();
                break;
            case SCORE:
                Score();
                break;
            case DESCORE:
                Descore();
                break;
            default:
                break;
            }
        }
        else {
            if (StickInput_ > 10 || StickInput_ < -10) {
                Motor_.SetSpeed(StickInput_ / 2);
            }
            else {
                Motor_.SetSpeed(0);
                Motor_.SetBrakeMode(MOTOR_BRAKE_BRAKE);
                // pid_.setTarget(RotationSensor_.GetPosition());
                // int current_position = RotationSensor_.GetPosition();
                // double pid_output = pid_.Calculate(current_position);

                // // Use the output from PID to set motor speed
                // Motor_.SetSpeed(pid_output);

                // //THIS PROBABLY WONT WORK BECAUAUSE TIKCPSEED MIGHT BE TOO HIGH
            }
        }
    }

    void ManualMove(int stickInput)
    {
        StickInput_ = stickInput;
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

#pragma region arm states
private:
    void Dock()
    {
        pid_.setTarget(5.0);
    }

    void Load()
    {
        pid_.setTarget(33.0);
    }

    void Reach()
    {
        pid_.setTarget(130.0);
    }

    void Score()
    {
        pid_.setTarget(240.0);
    }

    void Descore() {
        pid_.setTarget(160.0);
    }
#pragma endregion
};
#endif // ARM_HPP