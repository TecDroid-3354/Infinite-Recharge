#include <frc/util/color.h>

using namespace frc;

#ifndef CONSTANTS_H
#define CONSTANTS_H

//----------------------------Ports----------------------------------
    
    constexpr int mChasisFrontRight = 9;
    constexpr int mChasisBackRight = 7;
    constexpr int mChasisFrontLeft = 8;
    constexpr int mChasisBackLeft = 6;
    constexpr int mPanel = 0;
    constexpr int mShooter = 4;
    constexpr int mElevator = 5;
    constexpr int mClimber = 3;
    constexpr int mBalancer = 2;
    constexpr int mIntake = 1;
    constexpr int pStopperFront = 1;
    constexpr int pStopperBack = 2;
    constexpr int pIntakeFront = 7;
    constexpr int pIntakeBack = 6;

    
//------------------------------Speeds----------------------------------


    constexpr float kPanelSpeed = 1;
    constexpr float kAutoSpeed = 0.7;
    constexpr float kAutoTurn = 0.7;
    constexpr float kAutoBalance = 0.7;
    constexpr float kShooterSpeed = 1;
    constexpr float kTowerSpeed = 1;
    constexpr float kIntakeSpeed = 1;
    constexpr float kClimberSpeed = 0.6;
    constexpr float kSliderSpeed = 1;
    constexpr float kElevatorSpeed = 1;


//------------------------------Sensors----------------------------------

    constexpr int sPanelSwitch = 0;
    constexpr int sElevatorSwitch = 1;
    constexpr int sEncoderA  = 8;
    constexpr int sEncoderB = 9;
    constexpr int sPixy = 2;

//-----------------------------Constants---------------------------------

    constexpr int kPanelHits = 10;
    constexpr float  kPrepareTime = 0.2;
    constexpr float  kShootTime = 4;
    constexpr float  kChargeTime = 1.5;
    constexpr double kEncoderPulse = 3.141592653589*6/2048;
    

//-------------------------------Auto-------------------------------------

    constexpr float targets[] = {0,40,0,30};//{0,142,110,38,95,160,193,0,122,-90};
    constexpr char movements[] ={'p','l','s','m','x'};//,'m','t','i','t','m','t','s','m','t'};
    constexpr float kTurnP = 1;
    constexpr float kTurnI = 2;
    constexpr float kTurnD = 2;
    constexpr float kSpeedP = 1;
    constexpr float kSpeedI = 2;
    constexpr float kSpeedD = 2;
    
//---------------------------Control Map---------------------------------

    constexpr int cButtonA = 1;
    constexpr int cButtonB = 2;
    constexpr int cButtonX = 3;
    constexpr int cButtonY = 4;
    constexpr int cLeftBumper = 5;
    constexpr int cRightBumper = 6;
    constexpr int cSelect = 7;
    constexpr int cStart = 8;
    
    constexpr int cLeftAxisX = 0;
    constexpr int cLeftAxisY = 1;
    constexpr int cLeftTrigger = 2;
    constexpr int cRightTrigger = 3;
    constexpr int cRightAxisX = 4;
    constexpr int cRightAxisY = 5;
    
//------------------------------Colors-----------------------------------
    constexpr Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
    constexpr Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
    constexpr Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
    constexpr Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);
    constexpr Color kBlankTarget = frc::Color(0.236,0.466,0.286);

#endif