/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Tower.h"
#include <frc/smartdashboard/smartdashboard.h>

#include "Constants.h"
using namespace frc;


Tower::Tower() {
  
}

void Tower::Periodic() {

}

void Tower::Move(){ 
  bool climbMode = SmartDashboard::GetBoolean("Climb Mode",false);
  if(!climbMode){
      SetMotor((control.GetRawAxis(cRightTrigger)-control.GetRawAxis(cLeftTrigger))*0.85);
  }
}
void Tower::SetMotor(float speed){
  motor.Set(speed);
}

void Tower::Lower(){
  intake.Set(DoubleSolenoid::kForward);
}

void Tower::Reset(){
  intake.Set(DoubleSolenoid::kReverse);
  intake.Set(DoubleSolenoid::kOff);
}