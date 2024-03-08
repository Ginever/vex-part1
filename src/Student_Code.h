#ifndef STUDENT_CODE_H
#define STUDENT_CODE_H

/*   Drive Power & Offsets   */
#define FORWARDMOTORPOWEROFFSET 0.9938
#define FORWARDDRIVESPEED 35.0 //percentage
#define REVERSEMOTORPOWEROFFSET 1.071215
#define REVERSEDRIVESPEED -35.0 //percentage

/*   Sensor Thresholds   */
#define BLACKCOLORLEVEL 1450

void student_Main();    // The main entry point to the student code

// Add your function prototypes below
int convertPower(double powerLevel);
void driveUntilBlack(double powerPercent);
int getAverageLightLevel();
void armTime(double powerPercent, int milliseconds);
void driveTime(double leftDrivePower, double rightDrivePower, int milliseconds);




// DO NOT ADD ANY PROTOTYPES AFTER THIS LINE
#endif  // STUDENT_CODE_H