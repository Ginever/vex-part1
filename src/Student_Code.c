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
    todo  Determine what motor powers we are using - in Lab
    todo  Find motor power offsets - in Lab
    todo  Find BLACKCOLORLEVEL and figure out logic for driveUntilBlack() - in Lab
    todo  Write code for navigating around the map and completing the task - TBD
*/

void student_Main()
{
    resetEncoder(RightEncoder);
    resetEncoder(LeftEncoder);
    motorPower(RightMotor, convertPower(FORWARDDRIVESPEED*FORWARDMOTORPOWEROFFSET));
    motorPower(LeftMotor, convertPower(FORWARDDRIVESPEED));

    resetTimer(T_1);

    while(readTimer(T_1) < 5000){
        lcd_print(LCDLine1 , " Motor encoders = %d, %d diffrence: %d" , readSensor(LeftEncoder), readSensor(RightEncoder), readSensor(LeftEncoder)/readSensor(RightEncoder)); 
        lcd_print(LCDLine2, "Light level %d %d %d average: %d", readSensor(LeftLight), readSensor(MidLight), readSensor(RightLight), getAverageLightLevel());
        delay(50);
    }

    motorStopAll();

    //Designed to check if the robot ceases motion after above functions have been completed
    //will help prevent functions breaking other functions when complied together
    //todo remove when testing individual functions is completed
    lcd_print(LCDLine7, "Logic Finished");
    delay(2000);
    lcd_clear_line(LCDLine7);

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
    //Set motors to required power level
    motorPower(LeftMotor, convertPower(power));
    motorPower(RightMotor, convertPower(power));

    //todo adjust values and logic in lab to make it work
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
    motorPower(ArmMotor, convertPower(armPower));
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
    motorPower(LeftMotor, convertPower(leftDrivePower));
    motorPower(RightMotor, convertPower(rightDrivePower));
    delay(milliseconds);
    motorPower(LeftMotor, 0);
    motorPower(RightMotor, 0);
}