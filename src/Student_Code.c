/**
 * @file Student_Code.c
 * @author your name (you@domain.com)
 * @brief description of this file
 * @version 0.1
 * @date yyyy-mm-dd
 *
 * @copyright Copyright (c) 2023
 *
 */

/* Libraries. DO NOT REMOVE */
#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Student_Code.h"



// ---------------------- Defining physical robot parameters --------------------------
// Update these numbers to match the physical robot (information found in the lab manual)
// int drivingWheelDiameter = 0;	    // diameter of the driving wheels [mm]
// int robotWidth = 0;					// width of the robot including the wheel thickness [mm]
// int wheelWidth = 0;					// width of the driving wheel [mm]
// double drivingWheelRatio = 0.0;	    // ratio of wheel shaft rotations to wheel motor shaft rotations
// double armRatio = 0.0;				// ratio of arm shaft rotations to arm motor shaft rotations
// double encCountPerRev = 0.0;	    // number of encoder ticks per 1 revolution of the motor shaft
// ------------------------------------------------------------------------------------

/* Write your code in the function below. You may add helper functions below the studentCode function. */
void student_Main()
{
    resetEncoder(RightEncoder);
    resetEncoder(LeftEncoder);
    motorPower(RightMotor, (int)MOTORPOWER*MOTORPOWEROFFSET);
    motorPower(LeftMotor, 2000);//*0.9895833);

    resetTimer(T_1);

    while(readTimer(T_1) < 5000){
        lcd_print ( LCDLine1 , " Motor encoders = %d, %d " , readSensor(LeftEncoder), readSensor(RightEncoder)); 
        delay(50);
    }

    motorStopAll();
}



//Lachlan
// __[ CONVERT POWER ]________________________________________________
/**
// @brief Coverts a percentage (-100 to 100) to a motor output power
// where 100% is @param MOTOR_CEILING mV and -100 is @param MOTOR_FLOOR mV
// @param powerLevel a floating point percentage between 100 and -100
// @return an integer voltage in millivolts
*/
int convertPower(double powerLevel){

}

// __[ DRIVE UNTILL BLACK ]___________________________________________
/**
 * @brief Drive forward at percentage power until the robot is over
 * a black line
 * @param power percentage (-100 to 100) controlling drive speed
*/
void driveUntillBlack(double power){
    motorPower(LeftMotor, convertPower(power));
    motorPower(RightMotor, convertPower(power));

    //todo adjust values and logic to make it work
    while(getAverageLightLevel() < BLACKCOLORLEVEL){
        delay(50);
    }
    motorPower(LeftMotor, 0);
    motorPower(RightMotor, 0);
}

// __[ GET AVERAGE LIGHT LEVEL]_______________________________________
/**
 * @brief gets average sensed value across all three infrared sensors
 * @param none
 * @return Average light level detected
*/
int getAverageLightLevel(){
    return (readSensor(RightLight) + readSensor(MidLight) + readSensor(LeftLight))/3;
}

//Zac
// __[ ARM TIME ]_____________________________________________________
/**
 * @brief Move arm at percentage power for an amount of time
 * @param armPower Percentage (-100 to 100) controlling arm power
 * @param milliseconds Duration in milliseconds the motor is moving for
*/
void armTime(double armPower, int milliseconds){
    motorPower(ArmMotor, convertPower(armPower));
    delay(milliseconds);
    motorPower(ArmMotor, 0);
}

// __[ DRIVE TIME ]_____________________________________________________
/**
 * @brief Move arm at percentage power for an amount of time
 * @param leftDrivePower Percentage (-100 to 100) controlling left drive motor speed
 * @param rightDrivePower Percentage (-100 to 100) controlling right drive motor speed
 * @param milliseconds Duration in milliseconds the robot is driving for
*/
void driveTime(double leftDrivePower, double rightDrivePower, int milliseconds){
    motorPower(LeftMotor, convertPower(leftDrivePower));
    motorPower(RightMotor, convertPower(rightDrivePower));
    delay(milliseconds);
    motorPower(LeftMotor, 0);
    motorower(RightMotor, 0);
}
// ----------------------------------------------- Function defintions go here  -----------------------------------------------//
// Don't forget to add your function prototypes to Student_Code.h
