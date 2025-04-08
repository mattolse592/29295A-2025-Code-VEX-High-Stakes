#include "main.h"
#include "Robot.hpp"
#include "MatthewBrain.hpp"

Robot* robot;


// // Chassis constructor
// Drive chassis(
//     // These are your drive motors, the first motor is used for sensing!
//     { 1, -3, 4},     // Left Chassis Ports (negative port will reverse it!)
//     { -6, 7, -8},  // Right Chassis Ports (negative port will reverse it!)

//     10,      // IMU Port
//     2.75,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
//     450);   // Wheel RPM = cartridge * (motor gear / wheel gear)



/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/        Version 3.2.2
/////

#pragma region initializing conditions
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  ez::ez_template_print();  // Print our branding over your terminal :D

  pros::delay(500);  // Stop the user from doing anything while legacy ports configure

  // // Autonomous Selector using LLEMU

  ez::as::auton_selector.autons_add({
    //{"Test Auton", testAuton},
    //{"red AWP", redAWP},
    //{"Blue AWP", blueAWP},
    //{"Red Baker auto", redPosAWP},
    {"Blue Baker auto", bluePosAWP},
    // {"Red Ring rush Corner", RedRingRushCorner},
    //{"Blue Ring rush Corner", BlueRingRushCorner},
    //{"Blue Ring rush Elim", blueRingRushElim},
    //{"Blue half awp", blueHalfAWP},
    //{"Blue half awp", blue3RingAWP},
   // {"red half awp", red3RingAWP},
    //{"Red half awp", redHalfAWP},
    //{"red Ring rush Elim", redRingRushElim},
    //{"Red Mogo rush", redMogoRush}
    //{"skills", skills},
    //{"Red Side Mogo Rush Half AWP", redMogoRushHalfAWP},
    });

  ez::as::initialize();

  robot = new Robot();

  master.rumble(robot->DriveTrain_.DriveTrain_.Chassis_.drive_imu_calibrated() ? "." : "---");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {

  robot->DriveTrain_.Reset();

  // chassis.odom_xyt_set(0_in, 0_in, 0_deg);    // Set the current position, you can start at a specific position with this
  robot->DriveTrain_.DriveTrain_.Chassis_.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency

  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
}

#pragma region EZ template tasks

/**
 * Ez screen task
 * Adding new pages here will let you view them during user control or autonomous
 * and will help you debug problems you're having
 */
 // void ez_screen_task() {
 //   while (true) {
 //     // Only run this when not connected to a competition switch
 //     if (!pros::competition::is_connected()) {
 //       // Blank page for odom debugging

 //     }

 //     // Remove all blank pages when connected to a comp switch
 //     else {
 //       if (ez::as::page_blank_amount() > 0)
 //         ez::as::page_blank_remove_all();
 //     }

 //     pros::delay(ez::util::DELAY_TIME);
 //   }
 // }
 // pros::Task ezScreenTask(ez_screen_task);

 /**
  * Gives you some extras to run in your opcontrol:
  * - run your autonomous routine in opcontrol by pressing DOWN and B
  *   - to prevent this from accidentally happening at a competition, this
  *     is only enabled when you're not connected to competition control.
  * - gives you a GUI to change your PID values live by pressing X
  */
  // void ez_template_extras() {
  //   // Only run this when not connected to a competition switch
  //   if (!pros::competition::is_connected()) {
  //     // PID Tuner
  //     // - after you find values that you're happy with, you'll have to set them in auton.cpp

  //     // Enable / Disable PID Tuner
  //     //  When enabled:
  //     //  * use A and Y to increment / decrement the constants
  //     //  * use the arrow keys to navigate the constants
  //     if (master.get_digital_new_press(DIGITAL_X))
  //       chassis.pid_tuner_toggle();

  //     // Trigger the selected autonomous routine
  //     if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
  //       pros::motor_brake_mode_e_t preference = chassis.drive_brake_get();
  //       autonomous();
  //       chassis.drive_brake_set(preference);
  //     }

  //     // Allow PID Tuner to iterate
  //     chassis.pid_tuner_iterate();
  //   }

  //   // Disable PID Tuner when connected to a comp switch
  //   else {
  //     if (chassis.pid_tuner_enabled())
  //       chassis.pid_tuner_disable();
  //   }
  // }
#pragma endregion

#pragma endregion

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
  robot->IsAutonomous = false;
  MatthewBrain brain(robot);
  robot->DriveTrain_.DriveTrain_.Chassis_.drive_brake_set(MOTOR_BRAKE_COAST);
  robot->SetAllianceAsRed(false);

  while (true) {
    brain.Tick();

    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}