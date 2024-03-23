/**
 * @file Student_Code.c
 * @author Lachlan Dean & Zac Ginever
 * @brief this file provides the logic and control systems for the prototyping of an autonomous robotic solution
 * developed for the Dairy Industry Cooperative to move stock/payload withing their warehouses
 * @version 1.0
 * @date 2024-03-22
 *
 * @copyright Copyright (c) 2024
 *
*/

/* Libraries. DO NOT REMOVE */
#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Student_Code.h"


void student_Main()
{
    //Positioning arm at required position to collect payload
    armUp(5000);
    delay(200);
    armTime(-30, 2750);

    //drive to payload pickup point
    driveUntilBlack(FORWARDDRIVESPEED);

    //Picking up payload
    armUp(3000);
    
    //get off the black line
    driveTime(FORWARDDRIVESPEED, FORWARDDRIVESPEED, 500);
    
    //Drive to turn position
    driveUntilBlack(FORWARDDRIVESPEED);

    //Turn 90 degrees ACW to face the direction of the drop off point
    driveTime(REVERSEDRIVESPEED, FORWARDDRIVESPEED, 1300);

    //Drive to payload drop of location
    driveUntilBlack(FORWARDDRIVESPEED);

    //wait to minimize payload oscillation and improve accuracy
    delay(500);

    //lower payload to ground
    armTime(-30, 2500);

    //raise arm clear of payload
    armTime(30, 200);

    //reverse away from payload
    driveTime(REVERSEDRIVESPEED, REVERSEDRIVESPEED, 2400);

    armUp(5000);

    //Turn 90 degrees CW
    driveTime(REVERSEDRIVESPEED, FORWARDDRIVESPEED, 1200);

    //drive until in charging zone
    driveTime(FORWARDDRIVESPEED, FORWARDDRIVESPEED, 3500);

    motorStopAll();
}


// __[ CONVERT POWER ]________________________________________________
/**
// @brief Coverts a percentage (-100 to 100) to a motor output power
// where 100% is 5000 mV and -100 is 5000 mV
// @param powerLevel a floating point percentage between 100 and -100
// @return an integer voltage in millivolts
*/
int convertPower(double powerLevel){
    //Limit input to between -100 and 100
    double saturatedPowerLevel = saturate(powerLevel, -100, 100);

    //voltage calculation
    int voltagePower = 5000 * (saturatedPowerLevel / 100);
    
    return voltagePower;
}


// __[ DRIVE UNTIL BLACK ]____________________________________________
/**
 * @brief Drive forward at percentage power until the robot is over
 * a black line
 * @param power percentage (-100 to 100) controlling drive speed
*/
void driveUntilBlack(double power){
    //convert percentage power to mV
    int leftPower = convertPower(power);
    int rightPower = leftPower;

    //apply power offset to make the robot drive straight
    if (leftPower > 0){
        rightPower = rightPower * FORWARDMOTORPOWEROFFSET;
    } else {
        rightPower = rightPower * REVERSEMOTORPOWEROFFSET;
    }

    //Set motors to required power level
    motorPower(LeftMotor, leftPower);
    motorPower(RightMotor, rightPower);

    //Wait until infrared light sensors detect black
    while(readSensor(RightLight) < BLACKCOLORLEVEL && readSensor(MidLight) < BLACKCOLORLEVEL && readSensor(LeftLight) < BLACKCOLORLEVEL){
        delay(50);
    }

    //Stop motors
    motorPower(LeftMotor, 0);
    motorPower(RightMotor, 0);

    //Delay to satisfy the requirements of the function
    delay(1000);
}


// __[ ARM TIME ]_____________________________________________________
/**
 * @brief Move arm at percentage power for an amount of time
 * @param armPower Percentage (-100 to 100) controlling arm power
 * @param milliseconds Duration in milliseconds the motor is moving for
*/
void armTime(double armPower, int milliseconds){
    //convert percentage power into mV
    int power = convertPower(armPower);

    //Start arm moving
    motorPower(ArmMotor, power);

    //Stop arm after specifed delay
    delay(milliseconds);
    motorPower(ArmMotor, 0);
}


// __[ DRIVE TIME ]___________________________________________________
/**
 * @brief Move arm at percentage power for an amount of time
 * @param leftDrivePower Percentage (-100 to 100) controlling left drive motor speed
 * @param rightDrivePower Percentage (-100 to 100) controlling right drive motor speed
 * @param milliseconds Duration in milliseconds the robot is driving for
*/
void driveTime(double leftDrivePower, double rightDrivePower, int milliseconds){
    //Convert percentage power to power in mV
    int leftPower = convertPower(leftDrivePower);
    int rightPower = convertPower(rightDrivePower);

    //Apply drive power offset to drive the robot straight if required
    if (leftPower > 0 && rightPower == leftPower){
        rightPower = rightPower*FORWARDMOTORPOWEROFFSET;
    } else if (rightPower == leftPower){
        rightPower = rightPower*REVERSEMOTORPOWEROFFSET;
    }

    //Set motor power
    motorPower(LeftMotor, leftPower);
    motorPower(RightMotor, rightPower);

    //Stop wheels after specified delay
    delay(milliseconds);
    motorPower(LeftMotor, 0);
    motorPower(RightMotor, 0);
}