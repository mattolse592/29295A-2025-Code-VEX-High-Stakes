#include "main.h"
//#include "main.cpp"
#include "AutonBrain.hpp"


/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/       Version 3.2.2
/////

// These are out of 127
int DRIVE_SPEED = 110;
int TURN_SPEED = 80;
const int SWING_SPEED = 110;

///
// Constants
///

extern Robot* robot;
AutonBrain* brain;

void brainTick() {
  while (robot->IsAutonomous) {
    brain->Tick();
    pros::delay(ez::util::DELAY_TIME);
  }
}

//  Autonomous testing, can delete 

void testAuton() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  DRIVE_SPEED = 60;

  ch->pid_drive_set(20, DRIVE_SPEED);
  brain->intakeOn = true;
  ch->pid_wait();
  pros::delay(400);


  ch->pid_drive_set(-10, DRIVE_SPEED);
  ch->pid_wait();

  pros::delay(200);
  ch->pid_drive_set(10, DRIVE_SPEED);
  brain->intakeLiftOn = true;
  ch->pid_wait();

  brain->intakeLiftOn = false;
  pros::delay(500);
  ch->pid_drive_set(-20, DRIVE_SPEED);
}
/*
void blueAWP() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(false);
  ch->slew_drive_set(true);

  //load ring into lb
  brain->armPos = Arm::LOAD;
  brain->intakeOn = true;
  //drive forward
  ch->pid_drive_set(5, 50);
  ch->pid_wait();
  pros::delay(350);
  //score on alliance stake
  brain->intakeOn = false;
  brain->armPos = Arm::SCORE;
  pros::delay(800);
  //drive backwards to line up with mogo
  ch->pid_drive_set(-16, DRIVE_SPEED);
  pros::delay(100);
  brain->armPos = Arm::DOCK;
  ch->pid_wait();
  //drive into mogo
  ch->pid_turn_set(-47, TURN_SPEED);
  ch->pid_wait();
  ch->pid_drive_set(-11, 50);
  ch->pid_wait_quick_chain();
  //clamp mogo
  brain->mogoOn = true;
  pros::delay(350);
  //turn towards ring stack
  ch->pid_turn_set(-145, TURN_SPEED);
  ch->pid_wait();
  //intake ring
  brain->intakeOn = true;
  ch->pid_drive_set(24, DRIVE_SPEED);
  ch->pid_wait();
  pros::delay(500);
  //turn towards middle ring stack
  ch->pid_turn_set(-115, TURN_SPEED);
  ch->pid_wait();
  ch->pid_drive_set(-72, DRIVE_SPEED);
  ch->pid_wait();
  brain->intakeOn = false;
} */

void blueAWP() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(false);
  ch->slew_drive_set(true);

  //move forward and score on alliance stake
  brain->armPos = Arm::LOAD;
  brain->intakeOn = true;
  pros::delay(550);
  ch->pid_drive_set(4, 50);
  brain->intakeOn = false;
  brain->armPos = Arm::SCORE;
  pros::delay(700);

  //move back into mogo
  brain->armPos = Arm::DOCK;
  ch->pid_drive_set(-11, 75);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-45, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-18, 60);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;
  pros::delay(90);

  //move towards ring stack
  ch->pid_turn_set(-115, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = true;
  ch->pid_drive_set(21, 75);
  ch->pid_wait_quick_chain();

  //move towards middle ring stack going forwrd
  ch->pid_turn_set(-335, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(42, DRIVE_SPEED);
  ch->pid_wait();
  ch->pid_drive_set(44, 80);
  ch->pid_wait();

  //drops the mogo
  pros::delay(800);
  brain->mogoOn = false;
  brain->intakeOn = false;

  //move towards second mogo
  ch->pid_turn_set(-35, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-27, 70);
  ch->pid_wait_quick_chain();

  //grabs mogo
  brain->mogoOn = true;
  pros::delay(100);

  //moves towards rings
  ch->pid_turn_set(40, TURN_SPEED);
  ch->pid_wait_quick_chain();

  //grabs rings
  brain->intakeOn = true;
  ch->pid_drive_set(30, 60);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-140, TURN_SPEED);
  ch->pid_wait_quick_chain();

  //drives into stake
  ch->pid_drive_set(44, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

}

void red4Ring() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  DRIVE_SPEED = 115;

  //score alliancew staKE
  brain->armPos = Arm::LOAD;
  brain->intakeOn = true;
  pros::delay(600);
  ch->pid_drive_set(2.5, DRIVE_SPEED);
  brain->intakeOn = false;
  brain->armPos = Arm::SCORE;
  pros::delay(600);

  //grab alliance ring 
  ch->pid_drive_set(-12, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->armPos = Arm::DOCK;
  brain->intakeLiftOn = true;
  ch->pid_turn_set(35, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = true;
  ch->pid_drive_set(19, DRIVE_SPEED - 30);
  ch->pid_wait_quick_chain();
  brain->intakeLiftOn = false;
  pros::delay(300);
  brain->rollerOnly = true;
  pros::delay(200);
  ch->pid_drive_set(-11, DRIVE_SPEED - 30);
  ch->pid_wait_quick_chain();

  //grab mogo 
  ch->pid_turn_set(-45, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-25, DRIVE_SPEED - 40);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;
  brain->rollerOnly = false;
  pros::delay(200);

  //grab ring stack
  ch->pid_turn_set(-137, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(24, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  //go to corner
  ch->pid_turn_set(-55, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(25, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  ch->pid_turn_set(-95, TURN_SPEED);
  ch->pid_wait_quick_chain();

  //go into corner
  ch->pid_drive_set(8, DRIVE_SPEED - 50);
  ch->pid_wait();
  pros::delay(200);

  //back away
  ch->pid_drive_set(-10, DRIVE_SPEED);
  ch->pid_wait();
  ch->pid_drive_set(4, DRIVE_SPEED - 30);
  ch->pid_wait();
  pros::delay(200);

  //drive in and lift intake
  brain->intakeLiftOn = true;
  ch->pid_drive_set(10, DRIVE_SPEED - 20);
  ch->pid_wait();
  brain->intakeLiftOn = false;
  pros::delay(500);
  ch->pid_drive_set(-12, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  //drop mogo
  ch->pid_turn_set(30, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-5, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->mogoOn = false;
  ch->pid_turn_set(-50, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-30, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

}

void redPosAWP() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  //score alliancew staKE
  brain->armPos = Arm::LOAD;
  brain->intakeOn = true;
  pros::delay(400);
  ch->pid_drive_set(2, 50);
  brain->intakeOn = false;
  brain->armPos = Arm::SCORE;
  pros::delay(700);

  //move back into mogo
  ch->pid_drive_set(-7, 75);
  pros::delay(200);
  brain->armPos = Arm::DOCK;
  ch->pid_wait_quick_chain();

  ch->pid_turn_set(-45, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-21, DRIVE_SPEED - 30);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;
  pros::delay(300);

  //turn towards allliance stake ring
  ch->pid_turn_set(-20, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeLiftOn = true;
  ch->pid_drive_set(13, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  ch->pid_turn_set(45, TURN_SPEED);
  ch->pid_wait_quick_chain();

  brain->intakeOn = true;
  pros::delay(300);
  ch->pid_drive_set(9, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeLiftOn = false;
  pros::delay(300);

  ch->pid_drive_set(-7, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  pros::delay(400);

  ch->pid_turn_set(135, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = false;
  ch->pid_drive_set(19, DRIVE_SPEED);
  ch->pid_wait_quick_chain();


  ch->pid_turn_set(84, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(9, DRIVE_SPEED);
  ch->pid_wait();

  brain->doinkerOn = true;
  pros::delay(200);

  ch->pid_turn_set(100, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-18, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  brain->doinkerOn = false;
  ch->pid_turn_set(95, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeLiftOn = false;
  brain->intakeOn = true;
  ch->pid_turn_set(110, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(10, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  ch->pid_turn_set(-120, TURN_SPEED);
  ch->pid_wait_quick_chain();

  ch->pid_drive_set(22, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->rollerOnly = true;

  ch->pid_turn_set(90, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->mogoOn = false;
  ch->pid_turn_set(-40, TURN_SPEED);
  ch->pid_wait_quick_chain();

  ch->pid_drive_set(-22, DRIVE_SPEED - 50);
  ch->pid_wait();
  brain->mogoOn = true;
  pros::delay(500);
  brain->rollerOnly = false;

}

void bluePosAWP() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(false);
  ch->slew_drive_set(true);

  //score alliancew staKE
  brain->armPos = Arm::LOAD;
  brain->intakeOn = true;
  pros::delay(600);
  ch->pid_drive_set(2, 50);
  brain->intakeOn = false;
  brain->armPos = Arm::SCORE;
  pros::delay(700);

  //move back into mogo
  ch->pid_drive_set(-7, 75);
  pros::delay(200);
  brain->armPos = Arm::DOCK;
  ch->pid_wait_quick_chain();

  ch->pid_turn_set(45, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-21, DRIVE_SPEED - 30);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;
  pros::delay(300);

  //turn towards allliance stake ring
  ch->pid_turn_set(20, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeLiftOn = true;
  ch->pid_drive_set(12, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  ch->pid_turn_set(-45, TURN_SPEED);
  ch->pid_wait_quick_chain();

  brain->intakeOn = true;
  ch->pid_drive_set(9, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeLiftOn = false;
  pros::delay(300);

  ch->pid_drive_set(-7, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  ch->pid_turn_set(-135, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = false;
  ch->pid_drive_set(12, DRIVE_SPEED);
  ch->pid_wait_quick_chain();


  ch->pid_turn_set(-87, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(16, DRIVE_SPEED);
  ch->pid_wait();

  brain->rushArmOn = true;
  pros::delay(200);

  ch->pid_turn_set(-100, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-18, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  brain->rushArmOn = false;
  ch->pid_turn_set(-95, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeLiftOn = false;
  brain->intakeOn = true;
  ch->pid_turn_set(-120, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(8, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  pros::delay(300);

  ch->pid_turn_set(135, TURN_SPEED);
  ch->pid_wait_quick_chain();

  ch->pid_drive_set(24, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->rollerOnly = true;
  ch->pid_drive_set(-2, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  

  ch->pid_turn_set(145, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->mogoOn = false;
  ch->pid_turn_set(55, TURN_SPEED);
  ch->pid_wait_quick_chain();

  ch->pid_drive_set(-17, DRIVE_SPEED - 60);
  ch->pid_wait();
  brain->mogoOn = true;
  pros::delay(500);
  brain->rollerOnly = false;

}

void redAWP() {

  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  DRIVE_SPEED = 115;
  TURN_SPEED = 100;

  //move forward and score on alliance stake
  brain->armPos = Arm::LOAD;
  brain->intakeOn = true;
  pros::delay(400);
  ch->pid_drive_set(5, 50);
  brain->intakeOn = false;
  brain->armPos = Arm::SCORE;
  pros::delay(700);

  //move back into mogo
  ch->pid_drive_set(-6, 75);
  pros::delay(200);
  brain->armPos = Arm::DOCK;
  ch->pid_wait_quick_chain();

  ch->pid_turn_set(45, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-24, DRIVE_SPEED - 30);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;
  pros::delay(200);

  //move to ring stack
  ch->pid_turn_set(148, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = true;
  ch->pid_drive_set(18, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  //back up
  ch->pid_drive_set(-16, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(190, TURN_SPEED);
  ch->pid_wait_quick_chain();

  //go into middle 8 rings
  ch->pid_drive_set(14.5, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(147, TURN_SPEED);
  ch->pid_wait_quick_chain();

  //intake rings
  ch->pid_drive_set(16, DRIVE_SPEED - 35);
  ch->pid_wait_quick_chain();

  //back up
  ch->pid_swing_set(ez::RIGHT_SWING, 225, SWING_SPEED, 25);
  ch->pid_wait_quick_chain();

  //turn towards middle stack and move
  ch->pid_turn_set(25, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(27, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  ch->pid_turn_set(-42, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeLiftOn = true;
  ch->pid_drive_set(40, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  //drop mogo
  brain->intakeLiftOn = false;
  ch->pid_turn_set(-180, TURN_SPEED);
  ch->pid_wait();
  brain->mogoOn = false;
  brain->intakeOn = false;
  pros::delay(100);

  //turn towards mogo
  ch->pid_turn_set(40, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-12, DRIVE_SPEED - 20);
  ch->pid_wait_quick_chain();

  //clamp mogo
  brain->mogoOn = true;
  pros::delay(150);

  //grab ring
  ch->pid_turn_set(-40, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = true;
  ch->pid_drive_set(26, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  //go towards ladder
  ch->pid_turn_set(150, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(41, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(10, 10);
  ch->pid_wait_quick_chain();

  pros::delay(10000);

  //turn towards middle stack
  ch->pid_turn_set(10, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(40, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  //align paralell with wall and get the ring
  ch->pid_turn_set(-45, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(45, 80);
  ch->pid_wait();
  pros::delay(1000);

  //drop mogo
  brain->mogoOn = false;
  brain->intakeOn = false;
  pros::delay(50);

  //turn towards next mogo
  ch->pid_drive_set(2.5, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(10, TURN_SPEED);
  ch->pid_wait_quick_chain();

  //driuve into mogo
  ch->pid_drive_set(-17, 60);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;

}

void blueHalfAWP() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(false);
  ch->slew_drive_set(true);

  //move forward and score on alliance stake
  brain->armPos = Arm::LOAD;
  brain->intakeOn = true;
  pros::delay(500);
  ch->pid_drive_set(3, 50);
  brain->intakeOn = false;
  brain->armPos = Arm::SCORE;
  pros::delay(1000);

  //move back into mogo
  ch->pid_drive_set(-8, 75);
  pros::delay(200);
  brain->armPos = Arm::DOCK;
  ch->pid_wait_quick_chain();

  ch->pid_turn_set(-50, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-20, 60);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;
  pros::delay(200);

  //move to ring stack
  ch->pid_turn_set(-160, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = true;
  ch->pid_drive_set(22, 75);
  ch->pid_wait_quick_chain();

  //drive to ladder
  ch->pid_turn_set(40, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(40, 75);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(40, 20);
  ch->pid_wait_quick_chain();
}

void blue3RingAWP() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(false);
  ch->slew_drive_set(true);

  //move forward and score on alliance stake
  brain->armPos = Arm::LOAD;
  brain->intakeOn = true;
  pros::delay(500);
  ch->pid_drive_set(3, 50);
  brain->intakeOn = false;
  brain->armPos = Arm::SCORE;
  pros::delay(1000);

  //move back into mogo
  ch->pid_drive_set(-8, 75);
  pros::delay(200);
  brain->armPos = Arm::DOCK;
  ch->pid_wait_quick_chain();

  ch->pid_turn_set(-50, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-20, 60);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;
  ch->drive_angle_set(-180_deg);
  pros::delay(200);

  //move to ring stack
  ch->pid_turn_set(90, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = true;
  ch->pid_drive_set(18, 75);
  ch->pid_wait_quick_chain();

  // go for middle ring
  ch->pid_turn_set(0, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(17, 75);
  ch->pid_wait_quick_chain();

  //ladder
  ch->pid_drive_set(-5, 75);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-90, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(30, 75);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(50, 20);
  ch->pid_wait_quick_chain();

}

void red3RingAWP() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  //move forward and score on alliance stake
  brain->armPos = Arm::LOAD;
  brain->intakeOn = true;
  pros::delay(500);
  ch->pid_drive_set(3, 50);
  brain->intakeOn = false;
  brain->armPos = Arm::SCORE;
  pros::delay(1000);

  //move back into mogo
  ch->pid_drive_set(-8, 75);
  pros::delay(200);
  brain->armPos = Arm::DOCK;
  ch->pid_wait_quick_chain();

  ch->pid_turn_set(50, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-20, 60);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;
  ch->drive_angle_set(-180_deg);
  pros::delay(200);

  //move to ring stack
  ch->pid_turn_set(-90, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = true;
  ch->pid_drive_set(18, 75);
  ch->pid_wait_quick_chain();

  // go for middle ring
  ch->pid_turn_set(0, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(17, 75);
  ch->pid_wait_quick_chain();

  //ladder
  ch->pid_drive_set(-5, 75);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(90, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(30, 75);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(50, 20);
  ch->pid_wait_quick_chain();

}

void blueRingRushElim() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(false);
  ch->slew_drive_set(true);

  //rush the rings
  ch->drive_angle_set(24_deg);
  ch->pid_drive_set(41, 120, false);
  brain->doinkerOn = true;
  brain->intakeOn = true;
  ch->pid_wait();
  pros::delay(200);
  brain->rollerOnly = true;

  //pull the rings back into the mogo
  ch->pid_turn_set(60, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-23, DRIVE_SPEED - 20);
  ch->pid_wait_quick_chain();
  brain->doinkerOn = false;
  brain->mogoOn = true;
  brain->rollerOnly = false;

  //turn turn to solo ring stack
  ch->pid_turn_set(80_deg, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(26, DRIVE_SPEED - 30);
  ch->pid_wait_quick_chain();

  //grab preloa
  ch->pid_turn_set(233_deg, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(50, DRIVE_SPEED);
  ch->pid_wait();
  ch->pid_turn_set(211_deg, TURN_SPEED);
  //brain->armPos = Arm::LOAD;
  ch->pid_wait_quick_chain();

  //colour sort middle rings
  ch->pid_drive_set(-5, DRIVE_SPEED);
  ch->pid_wait();
  ch->pid_turn_set(-90_deg, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(30, 50);
  ch->pid_wait();



  // //score on alliance stake
  // pros::delay(1000);
  // brain->intakeOn = false;
  // //brain->armPos = Arm::SCORE;
  // pros::delay(2000);
  // ch->pid_drive_set(-4, DRIVE_SPEED);
  // ch->pid_wait();
  // //brain->armPos = Arm::DOCK;

  // //drive to ladder
  // ch->pid_turn_set(-15_deg, TURN_SPEED);
  // ch->pid_wait_quick_chain();
  // ch->pid_drive_set(30, 70);
  // ch->pid_wait_quick_chain();

  // //back up to get middle stack
  // ch->pid_drive_set(-16, DRIVE_SPEED);
  // ch->pid_wait();
  // brain->intakeOn = true;
  // brain->armPos = Arm::DOCK;
  // //drive to pos corner
  // ch->pid_turn_set(-110_deg, TURN_SPEED);
  // ch->pid_wait_quick_chain();
  // ch->pid_drive_set(48, DRIVE_SPEED);
  // ch->pid_wait_quick_chain();
  // ch->pid_turn_set(-90_deg, TURN_SPEED);
  // ch->pid_wait_quick_chain();
  // brain->rushArmOn = true;
  // ch->pid_drive_set(22, 40);
  // ch->pid_wait_quick_chain();


}

void RedRingRushCorner() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  //rush the rings
  ch->drive_angle_set(-24_deg);
  ch->pid_drive_set(39, 120, false);
  brain->rushArmOn = true;
  brain->intakeOn = true;
  ch->pid_wait();
  pros::delay(200);
  brain->rollerOnly = true;

  //pull the rings back into the mogo
  ch->pid_turn_set(-60, TURN_SPEED - 30);
  ch->pid_wait();
  ch->pid_drive_set(-23, DRIVE_SPEED - 40);
  ch->pid_wait_quick_chain();
  brain->rushArmOn = false;
  brain->mogoOn = true;
  brain->rollerOnly = false;
  pros::delay(100);

  //turn turn to solo ring stack
  ch->pid_turn_set(-80_deg, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(22, DRIVE_SPEED - 30);
  ch->pid_wait_quick_chain();

  //turn to corner stack
  ch->pid_turn_set(-170_deg, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(37, DRIVE_SPEED);
  ch->pid_wait();
  ch->pid_turn_set(-135_deg, TURN_SPEED);
  ch->pid_wait_quick_chain();

  //go into corner
  ch->pid_drive_set(8, DRIVE_SPEED - 60);
  ch->pid_wait();
  pros::delay(200);

  //back away
  ch->pid_drive_set(-10, DRIVE_SPEED - 85);
  ch->pid_wait();
  ch->pid_drive_set(2, DRIVE_SPEED - 60);
  ch->pid_wait();
  pros::delay(400);
  //drive in and lift intake
  brain->intakeLiftOn = true;
  ch->pid_drive_set(10, DRIVE_SPEED - 70);
  ch->pid_wait();
  brain->intakeLiftOn = false;
  pros::delay(500);
  ch->pid_drive_set(-12, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  //go to middle stakc
  ch->pid_turn_set(90_deg, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(20, DRIVE_SPEED);
  ch->pid_wait();

  brain->intakeLiftOn = true;
  ch->pid_drive_set(8, DRIVE_SPEED - 30);
  ch->pid_wait();
  brain->intakeLiftOn = false;

  ch->pid_drive_set(8, DRIVE_SPEED - 30);
  ch->pid_wait();


}

void BlueRingRushCorner() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(false);
  ch->slew_drive_set(true);

  //rush the rings
  ch->drive_angle_set(24_deg);
  ch->pid_drive_set(42, 120, false);
  brain->doinkerOn = true;
  brain->intakeOn = true;
  ch->pid_wait();
  brain->rollerOnly = true;

  //pull the rings back into the mogo
  ch->pid_turn_set(60, TURN_SPEED - 30);
  ch->pid_wait();
  ch->pid_drive_set(-23, DRIVE_SPEED - 40);
  ch->pid_wait_quick_chain();
  brain->doinkerOn = false;
  brain->mogoOn = true;
  brain->rollerOnly = false;
  pros::delay(100);

  //turn turn to solo ring stack
  ch->pid_turn_set(80_deg, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(22, DRIVE_SPEED - 30);
  ch->pid_wait_quick_chain();

  //turn to corner stack
  ch->pid_turn_set(170_deg, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(36, DRIVE_SPEED);
  ch->pid_wait();
  ch->pid_turn_set(139_deg, TURN_SPEED);
  ch->pid_wait_quick_chain();

  //go into corner
  ch->pid_drive_set(8, DRIVE_SPEED - 60);
  ch->pid_wait();
  pros::delay(200);

  //back away
  ch->pid_drive_set(-10, DRIVE_SPEED);
  ch->pid_wait();
  ch->pid_drive_set(4, DRIVE_SPEED - 60);
  ch->pid_wait();
  pros::delay(400);
  //drive in and lift intake
  brain->intakeLiftOn = true;
  ch->pid_drive_set(10, DRIVE_SPEED - 70);
  ch->pid_wait();
  brain->intakeLiftOn = false;
  pros::delay(500);
  ch->pid_drive_set(-12, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  //go to middle stakc
  ch->pid_turn_set(-90_deg, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(20, DRIVE_SPEED);
  ch->pid_wait();

  brain->intakeLiftOn = true;
  ch->pid_drive_set(8, DRIVE_SPEED - 30);
  ch->pid_wait();
  brain->intakeLiftOn = false;

  ch->pid_drive_set(8, DRIVE_SPEED - 30);
  ch->pid_wait();


}

void redHalfAWP() {

  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  //move forward and score on alliance stake
  brain->armPos = Arm::LOAD;
  brain->intakeOn = true;
  pros::delay(500);
  ch->pid_drive_set(3, 50);
  brain->intakeOn = false;
  brain->armPos = Arm::SCORE;
  pros::delay(1000);

  //move back into mogo
  ch->pid_drive_set(-8, 75);
  pros::delay(200);
  brain->armPos = Arm::DOCK;
  ch->pid_wait_quick_chain();

  ch->pid_turn_set(50, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-20, 60);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;
  pros::delay(200);

  //move to ring stack
  ch->pid_turn_set(160, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = true;
  ch->pid_drive_set(22, 75);
  ch->pid_wait_quick_chain();

  //drive to ladder
  ch->pid_turn_set(-40, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(40, 75);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(40, 10);
  ch->pid_wait_quick_chain();

}

void redRingRushElim() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  //rush the rings
  ch->drive_angle_set(0_deg);
  ch->pid_drive_set(16, 120, false);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(26, TURN_SPEED);
  brain->doinkerOn = true;
  brain->intakeOn = true;
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(18, 120, false);
  ch->pid_wait();
  brain->rollerOnly = true;

  //pull the rings back into the mogo
  ch->pid_turn_set(-65, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-26, DRIVE_SPEED - 30);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;
  brain->rollerOnly = false;


  //turn turn to solo ring stack
  ch->pid_turn_set(-105_deg, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->doinkerOn = false;
  pros::delay(150);
  ch->pid_turn_set(-90_deg, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(22, DRIVE_SPEED - 30);
  ch->pid_wait_quick_chain();


  //grab preloa
  ch->pid_turn_set(-180_deg, TURN_SPEED);
  ch->pid_wait_quick_chain();
  pros::delay(500);
  brain->armPos = Arm::LOAD;
  ch->pid_drive_set(21, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(90_deg, TURN_SPEED);
  ch->pid_wait();

  //drive to allinace stake
  ch->pid_drive_set(53.5, DRIVE_SPEED - 50);
  ch->pid_wait();
  ch->pid_turn_set(-180_deg, TURN_SPEED);
  brain->rollerOnly = true;
  brain->armPos = Arm::REMOTE;
  ch->pid_wait();

  //score on alliance stake
  ch->pid_drive_set(-3, DRIVE_SPEED);
  ch->pid_wait();
  ch->pid_drive_set(8, 120);
  ch->pid_wait();
  // pros::delay(500);
  // ch->drive_angle_set(-180_deg);
  // pros::delay(500);
  ch->pid_drive_set(-9, DRIVE_SPEED - 55);
  ch->pid_wait();
  brain->armPos = Arm::SCORE;
  pros::delay(1000);
  ch->pid_drive_set(-2, DRIVE_SPEED - 40);
  brain->armPos = Arm::DOCK;
  ch->pid_wait();

  //drive to ladder
  ch->pid_turn_set(0_deg, TURN_SPEED);
  ch->pid_wait();
  ch->pid_drive_set(12, DRIVE_SPEED - 40);
  ch->pid_wait();
}

void OLDskills() {
  DRIVE_SPEED = 90;

  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  // score on ally stake
  brain->mogoOn = false;
  brain->intakeOn = true;
  ch->pid_drive_set(-1.5, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  pros::delay(230);
  ch->pid_drive_set(9, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  brain->mogoOn = true;

  //drive into 1st mogo 
  ch->pid_turn_set(-90, TURN_SPEED);
  ch->pid_wait();
  ch->pid_drive_set(-19.6, 60);
  ch->pid_wait_quick_chain();
  brain->mogoOn = false;
  brain->intakeOn = true;
  pros::delay(250);

  //drives to first ring and scores
  ch->pid_turn_set(0, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(14, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  //drives to next ring and loads it
  ch->pid_turn_set(25, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(54.3, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->armPos = Arm::LOAD;

  //drives and scores wallstake
  ch->pid_drive_set(-22.5, 60);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(89, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = false;
  brain->armPos = Arm::REMOTE;
  ch->pid_drive_set(20, 60);
  ch->pid_wait_quick_chain();
  brain->intakeOn = true;
  brain->armPos = Arm::SCORE;
  pros::delay(250);

  //gets corners rings 
  ch->pid_drive_set(-6.3, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->armPos = Arm::DOCK;
  ch->pid_turn_set(180, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(20, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(40, 45);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-10.6, DRIVE_SPEED);
  ch->pid_wait();
  ch->pid_turn_set(75, 70);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(11, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  //puts mogo into 1st corner
  ch->pid_drive_set(-9.3, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-52, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-26.5, DRIVE_SPEED - 20);
  ch->pid_wait();
  brain->mogoOn = true;

  //drives to next 2ndcorner
  ch->pid_drive_set(11, DRIVE_SPEED);
  ch->pid_wait();
  ch->pid_turn_set(0, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->armPos = Arm::LOAD;
  ch->pid_drive_set(77.5, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(15, 35);
  ch->pid_wait_quick_chain();

  //grabs next mogo
  ch->pid_turn_set(115, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-22.5, 70);
  ch->pid_wait_quick_chain();
  brain->mogoOn = false;
  pros::delay(550);

  //puts mogo in 2nd corner
  ch->pid_turn_set(250, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;
  ch->pid_drive_set(-33, 80);
  ch->pid_wait();
  ch->pid_turn_set(240, TURN_SPEED);
  ch->pid_wait_quick_chain();

  //grabs 3rd mogo
  ch->pid_drive_set(27.5, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = false;
  brain->armPos = Arm::REMOTE;
  ch->pid_turn_set(86, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-22, DRIVE_SPEED - 30);
  ch->pid_wait_quick_chain();
  brain->mogoOn = false;
  pros::delay(400);
  ch->pid_drive_set(3, DRIVE_SPEED - 30);
  ch->pid_wait_quick_chain();

  //scores on ally stake
  ch->pid_turn_set(3, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(19, DRIVE_SPEED - 20);
  ch->pid_wait();
  pros::delay(200);
  ch->pid_drive_set(-8, DRIVE_SPEED - 30);
  ch->pid_wait();
  pros::delay(100);
  brain->armPos = Arm::SCORE;
  pros::delay(700);


  //drives to next ring
  ch->pid_drive_set(-2, DRIVE_SPEED - 20);
  ch->pid_wait_quick_chain();
  brain->armPos = Arm::DOCK;
  brain->intakeOn = true;
  ch->pid_turn_set(125, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(24, DRIVE_SPEED);
  ch->pid_wait_quick_chain();


  //drives under ladder
  ch->pid_turn_set(225, TURN_SPEED);
  ch->pid_wait_quick_chain();
  pros::delay(800);
  brain->rollerOnly = true;
  ch->pid_drive_set(59, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->rollerOnly = false;
  ch->pid_drive_set(40, DRIVE_SPEED - 30);
  ch->pid_wait_quick_chain();

  //gets corner rings
  ch->pid_turn_set(180, TURN_SPEED - 20);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(10, DRIVE_SPEED - 20);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-2, DRIVE_SPEED - 20);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-60, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(10, DRIVE_SPEED - 20);
  ch->pid_wait_quick_chain();

  //drops mogo in corner
  ch->pid_turn_set(10, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-16, DRIVE_SPEED - 30);
  ch->pid_wait_quick_chain();
  pros::delay(200);
  brain->mogoOn = true;
  pros::delay(200);

  //grabs ring and loads it 
  brain->armPos = Arm::LOAD;
  ch->pid_turn_set(15, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(2, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(18, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(18, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(15, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-30, TURN_SPEED);
  ch->pid_wait_quick_chain();

  //grabs mogo 
  ch->pid_drive_set(-40, DRIVE_SPEED - 25);
  ch->pid_wait_quick_chain();
  brain->mogoOn = false;
  pros::delay(400);

  //drive to 2nd wall stake
  ch->pid_turn_set(-30, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(46, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-92, TURN_SPEED);
  ch->pid_wait_quick_chain();

  //scores wall stake
  brain->rollerOnly = true;
  brain->armPos = Arm::REMOTE;
  ch->pid_drive_set(19, DRIVE_SPEED);
  ch->pid_wait();
  brain->armPos = Arm::SCORE;
  pros::delay(100);
  brain->rollerOnly = false;
  pros::delay(500);
  //back away from 2nd wallstake
  ch->pid_drive_set(-9, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->armPos = Arm::DOCK;
  ch->pid_turn_set(45, TURN_SPEED);
  ch->pid_wait_quick_chain();

  //drives to next ring
  ch->pid_drive_set(21, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-90, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(16, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-3, TURN_SPEED);
  ch->pid_wait_quick_chain();

  //last ring stacks
  ch->pid_drive_set(39, DRIVE_SPEED - 50);
  ch->pid_wait();
  ch->pid_turn_set(125, TURN_SPEED - 30);
  ch->pid_wait_quick_chain();
  pros::delay(200);
  //back up then corner
  ch->pid_drive_set(-3, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  pros::delay(400);
  brain->mogoOn = true;
  ch->pid_drive_set(-9, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  //hang
  ch->pid_turn_set(135, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(30, DRIVE_SPEED);
  brain->armPos = Arm::REACH;
  brain->intakeOn = false;
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-46, TURN_SPEED);
  ch->pid_wait_quick_chain();
  //drive into bar
  ch->pid_drive_set(-28, 55);
  pros::delay(1300);
  ch->pid_drive_set(5, 30);
  ch->drive_brake_set(MOTOR_BRAKE_COAST);
  //PLEASSE


}

void skills() {
  //BACKWARDS MOGO ACTIVATION
  DRIVE_SPEED = 90;

  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  // score on ally stake
  brain->mogoOn = true;
  brain->intakeOn = true;
  ch->pid_drive_set(-1.5, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  pros::delay(230);
  ch->pid_drive_set(9, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  brain->mogoOn = false;

  //drive into 1st mogo 
  ch->pid_turn_set(-90, TURN_SPEED);
  ch->pid_wait();
  ch->pid_drive_set(-19.6, 60);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;
  brain->intakeOn = true;
  pros::delay(250);

  //drives to first ring and scores
  ch->pid_turn_set(0, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(14, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  //drives to next ring and loads it
  ch->pid_turn_set(25, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(54.3, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->armPos = Arm::LOAD;

  //drives and scores wallstake
  ch->pid_drive_set(-22.5, 60);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(89, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = false;
  brain->armPos = Arm::REMOTE;
  ch->pid_drive_set(20, 60);
  ch->pid_wait_quick_chain();
  brain->intakeOn = true;
  brain->armPos = Arm::SCORE;
  pros::delay(250);

  //gets corners rings 
  ch->pid_drive_set(-6.3, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->armPos = Arm::DOCK;
  ch->pid_turn_set(180, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(20, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(40, 45);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-10.6, DRIVE_SPEED);
  ch->pid_wait();
  ch->pid_turn_set(75, 70);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(11, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  //puts mogo into 1st corner
  ch->pid_drive_set(-9.3, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-52, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-26.5, DRIVE_SPEED - 20);
  ch->pid_wait();
  brain->mogoOn = false;

  //drives to next 2ndcorner
  ch->pid_drive_set(11, DRIVE_SPEED);
  ch->pid_wait();
  ch->pid_turn_set(0, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->armPos = Arm::LOAD;
  ch->pid_drive_set(77.5, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(15, 35);
  ch->pid_wait_quick_chain();

  //grabs next mogo
  ch->pid_turn_set(115, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-22.5, 70);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;
  pros::delay(550);

  //puts mogo in 2nd corner
  ch->pid_turn_set(250, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->mogoOn = false;
  ch->pid_drive_set(-33, 80);
  ch->pid_wait();
  ch->pid_turn_set(240, TURN_SPEED);
  ch->pid_wait_quick_chain();

  //grabs 3rd mogo
  ch->pid_drive_set(27.5, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = false;
  brain->armPos = Arm::REMOTE;
  ch->pid_turn_set(86, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-22, DRIVE_SPEED - 30);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;
  pros::delay(400);
  ch->pid_drive_set(3, DRIVE_SPEED - 30);
  ch->pid_wait_quick_chain();

  //scores on ally stake
  ch->pid_turn_set(3, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(19, DRIVE_SPEED - 20);
  ch->pid_wait();
  pros::delay(200);
  ch->pid_drive_set(-8, DRIVE_SPEED - 30);
  ch->pid_wait();
  pros::delay(100);
  brain->armPos = Arm::SCORE;
  pros::delay(700);


  //drives to next ring
  ch->pid_drive_set(-2, DRIVE_SPEED - 20);
  ch->pid_wait_quick_chain();
  brain->armPos = Arm::DOCK;
  brain->intakeOn = true;
  ch->pid_turn_set(125, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(24, DRIVE_SPEED);
  ch->pid_wait_quick_chain();


  //drives under ladder
  ch->pid_turn_set(225, TURN_SPEED);
  ch->pid_wait_quick_chain();
  pros::delay(800);
  brain->rollerOnly = true;
  ch->pid_drive_set(59, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->rollerOnly = false;
  ch->pid_drive_set(40, DRIVE_SPEED - 30);
  ch->pid_wait_quick_chain();

  //gets corner rings
  ch->pid_turn_set(180, TURN_SPEED - 20);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(10, DRIVE_SPEED - 20);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-2, DRIVE_SPEED - 20);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-60, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(10, DRIVE_SPEED - 20);
  ch->pid_wait_quick_chain();

  //drops mogo in corner
  ch->pid_turn_set(10, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-16, DRIVE_SPEED - 30);
  ch->pid_wait_quick_chain();
  pros::delay(200);
  brain->mogoOn = false;
  pros::delay(200);

  //grabs ring and loads it 
  brain->armPos = Arm::LOAD;
  ch->pid_turn_set(15, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(2, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(18, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(18, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(15, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-30, TURN_SPEED);
  ch->pid_wait_quick_chain();

  //grabs mogo 
  ch->pid_drive_set(-40, DRIVE_SPEED - 25);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;
  pros::delay(400);

  //drive to 2nd wall stake
  ch->pid_turn_set(-30, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(46, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-92, TURN_SPEED);
  ch->pid_wait_quick_chain();

  //scores wall stake
  brain->rollerOnly = true;
  brain->armPos = Arm::REMOTE;
  ch->pid_drive_set(19, DRIVE_SPEED);
  ch->pid_wait();
  brain->armPos = Arm::SCORE;
  pros::delay(100);
  brain->rollerOnly = false;
  pros::delay(500);
  //back away from 2nd wallstake
  ch->pid_drive_set(-9, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->armPos = Arm::DOCK;
  ch->pid_turn_set(45, TURN_SPEED);
  ch->pid_wait_quick_chain();

  //drives to next ring
  ch->pid_drive_set(21, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-90, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(16, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-3, TURN_SPEED);
  ch->pid_wait_quick_chain();

  //last ring stacks
  ch->pid_drive_set(39, DRIVE_SPEED - 50);
  ch->pid_wait();
  ch->pid_turn_set(125, TURN_SPEED - 30);
  ch->pid_wait_quick_chain();
  pros::delay(200);
  //back up then corner
  ch->pid_drive_set(-3, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  pros::delay(400);
  brain->mogoOn = false;
  ch->pid_drive_set(-9, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  //hang
  ch->pid_turn_set(135, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(30, DRIVE_SPEED);
  brain->armPos = Arm::REACH;
  brain->intakeOn = false;
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-46, TURN_SPEED);
  ch->pid_wait_quick_chain();
  //drive into bar
  ch->pid_drive_set(-28, 55);
  pros::delay(1300);
  ch->pid_drive_set(5, 30);
  ch->drive_brake_set(MOTOR_BRAKE_COAST);
  //PLEASSE


}

void redMogoRush() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);
  //starting angle
  ch->drive_angle_set(20_deg);

  //rush towards center mogo
  brain->rushArmOn = true;
  brain->intakeOn = true;
  brain->rollerOnly = true;
  ch->pid_drive_set(35, 125, false);
  ch->pid_wait_quick_chain();

  //clamp on it and back away
  brain->rushClampOn = true;
  ch->pid_drive_set(-12, DRIVE_SPEED);
  pros::delay(100);
  brain->rushArmOn = false;
  ch->pid_wait();

  //turn around and clamp middle mogo
  brain->rushClampOn = false;
  brain->rushArmOn = true;
  ch->pid_drive_set(-3, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->rushArmOn = false;
  ch->pid_turn_set(180, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-19, DRIVE_SPEED - 40);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;
  pros::delay(200);

  //score one ring and bring mogo near corner
  brain->rollerOnly = false;
  ch->pid_turn_set(-45, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->rollerOnly = true;
  ch->pid_drive_set(-16, DRIVE_SPEED - 40);
  ch->pid_wait_quick_chain();
  brain->mogoOn = false;

  //go towards next mogo
  ch->pid_turn_set(100, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-27, DRIVE_SPEED - 40);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;
  pros::delay(200);

  //turn towards pos corner
  ch->pid_turn_set(132, TURN_SPEED);
  ch->pid_wait_quick_chain();





}

void redMogoRushHalfAWP() {

  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  ch->drive_angle_set(30);

  //rush towards center mogo
  brain->rushArmOn = true;
  //brain->doinkerOn = true;
  brain->intakeOn = true;
  brain->rollerOnly = true;
  ch->pid_drive_set(35, 125, false);
  ch->pid_wait_quick_chain();

  //clamp on it and back away
  brain->rushClampOn = true;
  ch->pid_drive_set(-12, DRIVE_SPEED);
  pros::delay(250);
  brain->rushArmOn = false;
  ch->pid_wait();

  //turn around and clamp middle mogo
  brain->rushClampOn = false;
  brain->rushArmOn = true;
  ch->pid_drive_set(-3, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->rushArmOn = false;
  ch->pid_turn_set(195, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-19, DRIVE_SPEED - 40);
  ch->pid_wait_quick_chain();
  brain->mogoOn = true;
  pros::delay(200);

  //score one ring and bring mogo near corner
  brain->rollerOnly = false;
  ch->pid_turn_set(-45, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->rollerOnly = true;
  ch->pid_drive_set(-12, DRIVE_SPEED - 40);
  ch->pid_wait_quick_chain();
  brain->mogoOn = false;

  //go towards next mogo
  ch->pid_turn_set(90, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-24, DRIVE_SPEED - 40);
  ch->pid_wait_quick_chain();


}

/*
// void skills() {
//   DRIVE_SPEED = 80;

//   Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
//   brain = new AutonBrain(robot);
//   pros::Task tickTask(brainTick);
//   brain->SetAllianceAsRed(true);
//   ch->slew_drive_set(true);

//   // score on stake
//   brain->armPos = Arm::LOAD;
//   pros::delay(200);
//   brain->intakeOn = true;
//   pros::delay(500);
//   brain->intakeOn = false;
//   brain->armPos = Arm::SCORE;
//   pros::delay(700);
//   brain->armPos = Arm::DOCK;
//   ch->pid_drive_set(-6.5, 75);
//   ch->pid_wait();

//   //drive into 1st mogo
//   ch->pid_turn_set(90, TURN_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(-19.6, 60);
//   ch->pid_wait_quick_chain();
//   brain->mogoOn = true;
//   brain->intakeOn = true;
//   pros::delay(550);

//   // drive to 1st ring
//   ch->pid_turn_set(180, TURN_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(25, DRIVE_SPEED - 30);
//   ch->pid_wait();

//   // drive to second ring
//   ch->pid_turn_set(270, TURN_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(28, DRIVE_SPEED - 30);
//   ch->pid_wait();

//   // drive to wall stake
//   ch->pid_turn_set(180, TURN_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(19, DRIVE_SPEED - 30);
//   ch->pid_wait();

//   //score on wall stake
//   brain->armPos = Arm::LOAD;
//   ch->pid_turn_set(270, TURN_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(4, DRIVE_SPEED);
//   ch->pid_wait();
//   pros::delay(800);
//   brain->intakeOn = false;
//   brain->armPos = Arm::SCORE;
//   pros::delay(900);
//   //back away from wall stake
//   ch->pid_drive_set(-12, DRIVE_SPEED);
//   ch->pid_wait();

//   // drives to corner rings
//   brain->armPos = Arm::DOCK;
//   brain->intakeOn = true;
//   ch->pid_turn_set(0, TURN_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(24, DRIVE_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(35, DRIVE_SPEED - 40);
//   ch->pid_wait_quick_chain();

//   //back up and get third ring
//   ch->pid_drive_set(-1, DRIVE_SPEED);
//   ch->pid_wait_quick_chain();
//   ch->pid_turn_set(-150, TURN_SPEED - 20);
//   ch->pid_wait();
//   ch->pid_drive_set(16, DRIVE_SPEED - 20);
//   ch->pid_wait();

//   //put mogo in corner
//   ch->pid_turn_set(169, TURN_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(-19, DRIVE_SPEED);
//   ch->pid_wait();
//   pros::delay(500);

//   brain->mogoOn = false;
//   pros::delay(300);

//   //drive to 2nd mogo
//   ch->pid_drive_set(4.5, DRIVE_SPEED);
//   ch->pid_wait();
//   ch->pid_turn_set(269, TURN_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(-50, DRIVE_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(-27, DRIVE_SPEED - 40);
//   ch->pid_wait_quick_chain();
//   brain->mogoOn = true;
//   pros::delay(500);

//   // drive to 1st ring
//   ch->pid_turn_set(180, TURN_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(18, DRIVE_SPEED);
//   ch->pid_wait();

//   // drive to 2nd
//   ch->pid_turn_set(90, TURN_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(23, DRIVE_SPEED);
//   ch->pid_wait();

//   // drive to wall stake
//   ch->pid_turn_set(135, TURN_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(28, DRIVE_SPEED);
//   ch->pid_wait();
//   ch->pid_turn_set(90, TURN_SPEED);
//   ch->pid_wait();


//   //score on wall stake
//   brain->armPos = Arm::LOAD;
//   ch->pid_drive_set(10, DRIVE_SPEED);
//   ch->pid_wait();
//   pros::delay(1100);
//   brain->intakeOn = false;
//   brain->armPos = Arm::SCORE;
//   pros::delay(900);
//   //back away from wall stake
//   ch->pid_drive_set(-14, DRIVE_SPEED);
//   ch->pid_wait();

//   //drive to corner rings
//   brain->armPos = Arm::DOCK;
//   brain->intakeOn = true;
//   ch->pid_turn_set(0, TURN_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(24, DRIVE_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(35, DRIVE_SPEED - 40);
//   ch->pid_wait();

//   //back up and get third ring
//   ch->pid_drive_set(-1, DRIVE_SPEED);
//   ch->pid_wait_quick_chain();
//   ch->pid_turn_set(150, TURN_SPEED - 20);
//   ch->pid_wait();
//   ch->pid_drive_set(15, DRIVE_SPEED);
//   ch->pid_wait();

//   //put mogo in corner
//   ch->pid_turn_set(-169, TURN_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(-20, DRIVE_SPEED);
//   ch->pid_wait();

//   pros::delay(5000);
//   brain->mogoOn = false;
//   brain->intakeOn = false;

//   //surprise
//   ch->pid_turn_set(180, TURN_SPEED);
//   ch->pid_wait();
//   brain->intakeOn = true;
//   brain->armPos = Arm::LOAD;
//   ch->pid_drive_set(70, DRIVE_SPEED + 20);
//   ch->pid_wait();
//   ch->pid_turn_set(250, TURN_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(63, 60);
//   ch->pid_wait_quick_chain();
//   brain->intakeOn = false;
//   ch->pid_turn_set(180, TURN_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(25, DRIVE_SPEED);
//   ch->pid_wait();
//   ch->pid_drive_set(-6, DRIVE_SPEED);
//   ch->pid_wait();
//   brain->armPos = Arm::SCORE;
// }
*/

#pragma region other autons
// ///
// // Drive Example
// ///
// void drive_example() {
//     // The first parameter is target inches
//     // The second parameter is max speed the robot will drive at
//     // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
//     // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

//     //pros::Task sortTask(brainTick);

//     //brain.intakeOn = true;

//     chassis.pid_drive_set(24_in, DRIVE_SPEED);
//     chassis.pid_wait();

//     chassis.pid_turn_set(90_deg, TURN_SPEED);
//     chassis.pid_wait_quick_chain();

//     //brain.armPos = Arm::DESCORE;

//     chassis.pid_drive_set(24_in, DRIVE_SPEED);
//     chassis.pid_wait();
// }


// /////   chassis.pid_turn_set(45_deg, TURN_SPEED);
//   chassis.pid_wait_quick_chain();

//   chassis.pid_drive_set(6_in, DRIVE_SPEED, true);
//   chassis.pid_wait_quick_chain();

//   chassis.pid_turn_set(-45_deg, TURN_SPEED);
//   chassis.pid_wait_quick_chain();

//   chassis.pid_drive_set(6_in, DRIVE_SPEED, true);
//   chassis.pid_wait_quick_chain();

//   chassis.pid_turn_set(0_deg, TURN_SPEED);
//   chassis.pid_wait_quick_chain();

//   // Your final motion should still be a normal pid_wait
//   chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
//   chassis.pid_wait();
// // Turn Example
// ///
// void turn_example() {
//     // The first parameter is the target in degrees
//     // The second parameter is max speed the robot will drive at
//   //   chassis.pid_drive_set(24_in, DRIVE_SPEED + 17);
//   //   chassis.pid_wait_quick_chain();

//   //   chassis.pid_turn_set(180_deg, TURN_SPEED);
//   //   chassis.pid_wait_quick_chain();

//   //   chassis.pid_drive_set(24_in, DRIVE_SPEED + 17);
//   //   chassis.pid_wait_quick_chain();

//   //   chassis.pid_turn_set(0_deg, TURN_SPEED);
//   //   chassis.pid_wait();


//     chassis.pid_swing_set(ez::LEFT_SWING, 90_deg, SWING_SPEED / 2, 0);
//     chassis.pid_wait();

//     //   chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
//     //   chassis.pid_wait();

//     //   chassis.pid_swing_set(ez::RIGHT_SWING, 90_deg, SWING_SPEED, 45);
//     //   chassis.pid_wait();

//     chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED / 2, 0);
//     chassis.pid_wait();

// }

// ///
// // Combining Turn + Drive
// ///
// void drive_and_turn() {
//   chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
//   chassis.pid_wait();

//   chassis.pid_turn_set(45_deg, TURN_SPEED);
//   chassis.pid_wait();

//   chassis.pid_turn_set(-45_deg, TURN_SPEED);
//   chassis.pid_wait();

//   chassis.pid_turn_set(0_deg, TURN_SPEED);
//   chassis.pid_wait();

//   chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
//   chassis.pid_wait();
// }

// ///
// // Wait Until and Changing Max Speed
// ///
// void wait_until_change_speed() {
//   // pid_wait_until will wait until the robot gets to a desired position

//   // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
//   chassis.pid_drive_set(24_in, 30, true);
//   chassis.pid_wait_until(6_in);
//   chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
//   chassis.pid_wait();

//   chassis.pid_turn_set(45_deg, TURN_SPEED);
//   chassis.pid_wait();

//   chassis.pid_turn_set(-45_deg, TURN_SPEED);
//   chassis.pid_wait();

//   chassis.pid_turn_set(0_deg, TURN_SPEED);
//   chassis.pid_wait();

//   // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
//   chassis.pid_drive_set(-24_in, 30, true);
//   chassis.pid_wait_until(-6_in);
//   chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
//   chassis.pid_wait();
// }

// ///
// // Swing Example
// ///
// void swing_example() {
//   // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
//   // The second parameter is the target in degrees
//   // The third parameter is the speed of the moving side of the drive
//   // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

//   chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
//   chassis.pid_wait();

//   chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
//   chassis.pid_wait();

//   chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
//   chassis.pid_wait();

//   chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
//   chassis.pid_wait();
// }

// ///
// // Motion Chaining
// ///
// void motion_chaining() {
//   // Motion chaining is where motions all try to blend together instead of individual movements.
//   // This works by exiting while the robot is still moving a little bit.
//   // To use this, replace pid_wait with pid_wait_quick_chain.
//   chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
//   chassis.pid_wait();

//   chassis.pid_turn_set(45_deg, TURN_SPEED);
//   chassis.pid_wait_quick_chain();

//   chassis.pid_turn_set(-45_deg, TURN_SPEED);
//   chassis.pid_wait_quick_chain();

//   chassis.pid_turn_set(0_deg, TURN_SPEED);
//   chassis.pid_wait_quick_chain();

//   // Your final motion should still be a normal pid_wait
//   chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
//   chassis.pid_wait();
// }

// ///
// // Auto that tests everything
// ///
// void combining_movements() {
//   chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
//   chassis.pid_wait();

//   chassis.pid_turn_set(45_deg, TURN_SPEED);
//   chassis.pid_wait();

//   chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
//   chassis.pid_wait();

//   chassis.pid_turn_set(0_deg, TURN_SPEED);
//   chassis.pid_wait();

//   chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
//   chassis.pid_wait();
// }

// ///
// // Interference example
// ///
// void tug(int attempts) {
//   for (int i = 0; i < attempts - 1; i++) {
//     // Attempt to drive backward
//     printf("i - %i", i);
//     chassis.pid_drive_set(-12_in, 127);
//     chassis.pid_wait();

//     // If failsafed...
//     if (chassis.interfered) {
//       chassis.drive_sensor_reset();
//       chassis.pid_drive_set(-2_in, 20);
//       pros::delay(1000);
//     }
//     // If the robot successfully drove back, return
//     else {
//       return;
//     }
//   }
// }

// // If there is no interference, the robot will drive forward and turn 90 degrees.
// // If interfered, the robot will drive forward and then attempt to drive backward.
// void interfered_example() {
//   chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
//   chassis.pid_wait();

//   if (chassis.interfered) {
//     tug(3);
//     return;
//   }

//   chassis.pid_turn_set(90_deg, TURN_SPEED);
//   chassis.pid_wait();
// }

// ///
// // Odom Drive PID
// ///
// void odom_drive_example() {
//   // This works the same as pid_drive_set, but it uses odom instead!
//   // You can replace pid_drive_set with pid_odom_set and your robot will
//   // have better error correction.

//   chassis.pid_odom_set(24_in, DRIVE_SPEED, true);
//   chassis.pid_wait();

//   chassis.pid_odom_set(-12_in, DRIVE_SPEED);
//   chassis.pid_wait();

//   chassis.pid_odom_set(-12_in, DRIVE_SPEED);
//   chassis.pid_wait();
// }

// ///
// // Odom Pure Pursuit
// ///
// void odom_pure_pursuit_example() {
//   // Drive to 0, 30 and pass through 6, 10 and 0, 20 on the way, with slew
//   chassis.pid_odom_set({ {{6_in, 10_in}, fwd, DRIVE_SPEED},
//                         {{0_in, 20_in}, fwd, DRIVE_SPEED},
//                         {{0_in, 30_in}, fwd, DRIVE_SPEED} },
//     true);
//   chassis.pid_wait();

//   // Drive to 0, 0 backwards
//   chassis.pid_odom_set({ {0_in, 0_in}, rev, DRIVE_SPEED },
//     true);
//   chassis.pid_wait();
// }

// ///
// // Odom Pure Pursuit Wait Until
// ///
// void odom_pure_pursuit_wait_until_example() {
//   chassis.pid_odom_set({ {{0_in, 24_in}, fwd, DRIVE_SPEED},
//                         {{12_in, 24_in}, fwd, DRIVE_SPEED},
//                         {{24_in, 24_in}, fwd, DRIVE_SPEED} },
//     true);
//   chassis.pid_wait_until_index(1);  // Waits until the robot passes 12, 24
//   // Intake.move(127);  // Set your intake to start moving once it passes through the second point in the index
//   chassis.pid_wait();
//   // Intake.move(0);  // Turn the intake off
// }

// ///
// // Odom Boomerang
// ///
// void odom_boomerang_example() {
//   chassis.pid_odom_set({ {0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED },
//     true);
//   chassis.pid_wait();

//   chassis.pid_odom_set({ {0_in, 0_in, 0_deg}, rev, DRIVE_SPEED },
//     true);
//   chassis.pid_wait();
// }

// ///
// // Odom Boomerang Injected Pure Pursuit
// ///
// void odom_boomerang_injected_pure_pursuit_example() {
//   chassis.pid_odom_set({ {{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
//                         {{12_in, 24_in}, fwd, DRIVE_SPEED},
//                         {{24_in, 24_in}, fwd, DRIVE_SPEED} },
//     true);
//   chassis.pid_wait();

//   chassis.pid_odom_set({ {0_in, 0_in, 0_deg}, rev, DRIVE_SPEED },
//     true);
//   chassis.pid_wait();
// }

// ///
// // Calculate the offsets of your tracking wheels
// ///
// void measure_offsets() {
//   // Number of times to test
//   int iterations = 10;

//   // Our final offsets
//   double l_offset = 0.0, r_offset = 0.0, b_offset = 0.0, f_offset = 0.0;

//   // Reset all trackers if they exist
//   if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->reset();
//   if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->reset();
//   if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->reset();
//   if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->reset();

//   for (int i = 0; i < iterations; i++) {
//     // Reset pid targets and get ready for running an auton
//     chassis.pid_targets_reset();
//     chassis.drive_imu_reset();
//     chassis.drive_sensor_reset();
//     chassis.drive_brake_set(MOTOR_BRAKE_HOLD);
//     chassis.odom_xyt_set(0_in, 0_in, 0_deg);
//     double imu_start = chassis.odom_theta_get();
//     double target = i % 2 == 0 ? 90 : 270;  // Switch the turn target every run from 270 to 90

//     // Turn to target at half power
//     chassis.pid_turn_set(target, 63, ez::raw);
//     chassis.pid_wait();
//     pros::delay(250);

//     // Calculate delta in angle
//     double t_delta = util::to_rad(fabs(util::wrap_angle(chassis.odom_theta_get() - imu_start)));

//     // Calculate delta in sensor values that exist
//     double l_delta = chassis.odom_tracker_left != nullptr ? chassis.odom_tracker_left->get() : 0.0;
//     double r_delta = chassis.odom_tracker_right != nullptr ? chassis.odom_tracker_right->get() : 0.0;
//     double b_delta = chassis.odom_tracker_back != nullptr ? chassis.odom_tracker_back->get() : 0.0;
//     double f_delta = chassis.odom_tracker_front != nullptr ? chassis.odom_tracker_front->get() : 0.0;

//     // Calculate the radius that the robot traveled
//     l_offset += l_delta / t_delta;
//     r_offset += r_delta / t_delta;
//     b_offset += b_delta / t_delta;
//     f_offset += f_delta / t_delta;
//   }

//   // Average all offsets
//   l_offset /= iterations;
//   r_offset /= iterations;
//   b_offset /= iterations;
//   f_offset /= iterations;

//   // Set new offsets to trackers that exist
//   if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->distance_to_center_set(l_offset);
//   if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->distance_to_center_set(r_offset);
//   if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->distance_to_center_set(b_offset);
//   if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->distance_to_center_set(f_offset);
// }

// // . . .
// // Make your own autonomous functions here!
// // . . .
#pragma endregion