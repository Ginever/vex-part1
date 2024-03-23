#ifndef STUDENT_CODE_H
#define STUDENT_CODE_H

/*   Drive Power & Offsets   */
#define FORWARDMOTORPOWEROFFSET 1.02
#define FORWARDDRIVESPEED 50.0 //percentage
#define REVERSEMOTORPOWEROFFSET 1.07
#define REVERSEDRIVESPEED -50.0 //percentage

/*   Sensor Thresholds   */
#define BLACKCOLORLEVEL 1500

void student_Main();    // The main entry point to the student code

// Add your function prototypes below
int convertPower(double powerLevel);
void driveUntilBlack(double powerPercent);
void armTime(double powerPercent, int milliseconds);
void driveTime(double leftDrivePower, double rightDrivePower, int milliseconds);

// DO NOT ADD ANY PROTOTYPES AFTER THIS LINE
#endif  // STUDENT_CODE_H