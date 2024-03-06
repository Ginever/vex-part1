#ifndef STUDENT_CODE_H
#define STUDENT_CODE_H


#define MOTORPOWEROFFSET 1.02
#define MOTORPOWER 3000
#define BLACKCOLORLEVEL 3000

void student_Main();    // The main entry point to the student code

// Add your function prototypes below
int convertPower(double powerLevel);
void driveUntillBlack(double powerPercent);
int getAverageLightLevel();
void armTime(double powerPercent, int milliseconds);
void driveTime(double leftDrivePower, double rightDrivePower, int milliseconds);




// DO NOT ADD ANY PROTOTYPES AFTER THIS LINE
#endif  // STUDENT_CODE_H