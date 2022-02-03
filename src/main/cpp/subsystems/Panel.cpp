/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Panel.h"
#include <frc/smartdashboard/smartdashboard.h>
#include <frc/Timer.h>
#include "Constants.h"
using namespace frc;
using namespace rev;
using namespace std;

Panel::Panel() {
  m_colorMatcher.AddColorMatch(kBlueTarget);
  m_colorMatcher.AddColorMatch(kGreenTarget);
  m_colorMatcher.AddColorMatch(kRedTarget);
  m_colorMatcher.AddColorMatch(kYellowTarget);
  m_colorMatcher.AddColorMatch(kBlankTarget);
  
}

void Panel::Periodic() {
    
    SmartDashboard::PutBoolean("Limit",GetLimit());
}


string Panel::GetColor(){
  double confidence = 0.0;
  Color detectedColor = m_colorSensor.GetColor();
  Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);
  string colorString;
  if (matchedColor == kBlueTarget) colorString = "B";
  else if (matchedColor == kRedTarget) colorString = "R";
  else if (matchedColor == kGreenTarget) colorString = "G";
  else if (matchedColor == kYellowTarget) colorString = "Y";
  else colorString = "X";
  return colorString;
}

bool Panel::GetLimit(){
  return limit.Get();
}
void Panel::SetMotor(float speed){
  motor.Set(speed);
}


