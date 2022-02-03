/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Shooter.h"
#include <frc/smartdashboard/smartdashboard.h>
#include <frc/Timer.h>
#include "Constants.h"
using namespace frc;

Shooter::Shooter() {

  
}

void Shooter::Periodic() {
    

    
}


void Shooter::Move(){
  bool climbMode = SmartDashboard::GetBoolean("Climb Mode",false);
  if(!climbMode){
    if(control.GetRawButton(cRightBumper)){
      Open();
      if(timer.Get()<1.5){
        SetMotor(kShooterSpeed*timer.Get()/1.5);
        SmartDashboard::PutNumber("Speed",kShooterSpeed/timer.Get()*1.5);
      }
      else{
        SetMotor(kShooterSpeed);
      }
    }
    else{
      motor.Set(0);
      Reset();
    }
    if(control.GetRawButton(cLeftBumper)){
      Open();
    }
    else if(control.GetRawButtonReleased(cLeftBumper)){
      Reset();
    }
  }
}
 
  
void Shooter::SetMotor(float speed){
  motor.Set(speed);
}

void Shooter::Reset(){
  stopper.Set(DoubleSolenoid::kReverse);
}

void Shooter::Open(){
  stopper.Set(DoubleSolenoid::kForward);
}

void Shooter::Light(bool on){
  light.Set(on);
}