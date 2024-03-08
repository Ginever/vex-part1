/**
 * @file Student_Code.c
 * @author Lachlan Dean & Zac Ginever
 * @brief this file provides the logic and control systems for prototyping an autonomous robotic solution for the 
 * Dairy Industry Cooperative for delivering stock/payload
 * @version 0.2
 * @date 2024-03-06
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

/*
________________________________ TODO ________________________________
                              Group  E12

    done  Write convertPower function - Lachlan 
    done  Write driveUntilBlack function - Zac
    done  Write armTime function - Zac
    done  Write driveTime function - Zac
    done  Determine what motor powers we are using - in Lab
    done  Find motor power offsets - in Lab
    done  Find BLACKCOLORLEVEL and figure out logic for driveUntilBlack() - in Lab
    done  WWrite Logic for navigating around map
    todo Fiqure out timing for a 90 degree turn
    todo Fiqure out drive times for non-driveUntilBlack distances
*/

void student_Main()
{
    //Putting arm in required position
    armUp(5000);
    delay(200);
    armTime(-30, 2000);

    //* I have put the drive offsets into the functions
    driveUntilBlack(FORWARDDRIVESPEED);

    //picking up payload
    armUp(3000);

    //Drive to turn position
    //* I have put the drive offsets into the functions
    driveTime(FORWARDDRIVESPEED, FORWARDDRIVESPEED, 500);
    driveUntilBlack(FORWARDDRIVESPEED);

    //Turn 90 degrees to face the direction of the drop off point
    driveTime(FORWARDDRIVESPEED, REVERSEDRIVESPEED, 1000);

    driveUntilBlack(FORWARDDRIVESPEED);

    //drop payload
    armTime(-30, 2000);

    //Reverse away from payload to get arm clear
    driveTime(REVERSEDRIVESPEED, REVERSEDRIVESPEED, 500);

    armUp(3000);

    //turn 180 degrees
    driveTime(FORWARDDRIVESPEED, REVERSEDRIVESPEED, 2000);

    driveUntilBlack(FORWARDDRIVESPEED);

    //Turn 90 degrees
    driveTime(FORWARDDRIVESPEED, REVERSEDRIVESPEED, 1000);

    //drive until in charging zone
    driveTime(FORWARDDRIVESPEED, FORWARDDRIVESPEED, 4000);

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
        leftPower = leftPower * FORWARDMOTORPOWEROFFSET;
    } else {
        leftPower = leftPower * REVERSEMOTORPOWEROFFSET;
    }

    //Set motors to required power level
    motorPower(LeftMotor, leftPower);
    motorPower(RightMotor, rightPower);

    //Wait until infrared light sensors detect black
    while(getAverageLightLevel() < BLACKCOLORLEVEL){
        lcd_print(LCDLine2, "%d %d %d a: %d", readSensor(LeftLight), readSensor(MidLight), readSensor(RightLight), getAverageLightLevel());
        delay(50);
    }

    //Stop motors
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
    // Doing int calculation is fine as float accuracy isn't needed
    return (readSensor(RightLight) + readSensor(MidLight) + readSensor(LeftLight))/3;
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
        leftPower = leftPower*FORWARDMOTORPOWEROFFSET;
    } else if (rightPower == leftPower){
        leftPower = leftPower*REVERSEMOTORPOWEROFFSET;
    }

    //Set motor power
    motorPower(LeftMotor, leftPower);
    motorPower(RightMotor, rightPower);

    //Stop wheels after specified delay
    delay(milliseconds);
    motorPower(LeftMotor, 0);
    motorPower(RightMotor, 0);
}