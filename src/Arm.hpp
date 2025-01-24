#ifndef ARM_HPP
#define ARM_HPP


#include "PID.hpp"

class Arm
{

private:
    Motor Motor_;
    RotationSensor RotationSensor_;
    PIDController pid_ = PIDController(2.7, 0.05, 13.0, 0.0);

    bool manualTakeover_ = false;
    bool stickInput = false;

public:
    enum State
    {
        DOCK = 0,
        LOAD = 1,
        REACH = 2,
        SCORE = 3,
        MANUAL = 4
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

        if (manualTakeover_ == false)
        {
            int current_position = RotationSensor_.GetPosition();
            double pid_output = pid_.Calculate(current_position);

            // Use the output from PID to set motor speed
            Motor_.SetSpeed(-pid_output);

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
            default:
                break;
            }
        }
        else {
            pid_.setTarget(RotationSensor_.GetPosition());
            int current_position = RotationSensor_.GetPosition();
            double pid_output = pid_.Calculate(current_position);

            // Use the output from PID to set motor speed
            Motor_.SetSpeed(-pid_output);
        }
    }

    void ManualMove(int stickInput)
    {
        Motor_.SetSpeed(stickInput / 2);
        stickInput = true;
    }

    void SetTarget(State state)
    {
        Target_ = state;
    }

    void ManualMoveSet(bool takeOverSetting)
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
        pid_.setTarget(38.0);
    }

    void Reach()
    {
        pid_.setTarget(150.0);
    }
#pragma endregion
};
#endif // ARM_HPP