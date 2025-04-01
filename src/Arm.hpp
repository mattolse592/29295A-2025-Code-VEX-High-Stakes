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
        MANUAL = 5,
        REMOTE = 6
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
            case REMOTE:
            Remote();
            break;
            default:
                break;
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
        pid_.setTarget(2.0);
    }

    void Load()
    {
        pid_.setTarget(28.0);
    }

    void Reach()
    {
        pid_.setTarget(130.0);
    }

    void Score()
    {
        pid_.setTarget(235.0);
    }

    void Descore() {
        pid_.setTarget(160.0);
    }

    void Remote() {
        pid_.setTarget(90.0);
    }
#pragma endregion
};
#endif // ARM_HPP