/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"
#include <frc/smartdashboard/smartdashboard.h>
#include <frc/Timer.h>
#include "Constants.h"
using namespace frc;

Elevator::Elevator() {


}

void Elevator::Periodic() {

  bool climbMode = SmartDashboard::GetBoolean("Climb Mode",false);
  if(climbMode){  
    if(!limit.Get()){
     Elevate(control.GetRawAxis(cRightTrigger)-control.GetRawAxis(cLeftTrigger));
    }
    else{
     Elevate(-control.GetRawAxis(cLeftTrigger));
    }

    if(control.GetRawButton(cButtonA)){
      Climb(kClimberSpeed);
    }
    else if(control.GetRawButton(cButtonB)){
      Climb(-kClimberSpeed);
      
    }
    else{
      Climb(0);
    }

    if(control.GetRawButton(cRightBumper)){
      Slide(kSliderSpeed);
    }
    else if(control.GetRawButton(cLeftBumper)){
      Slide(-kSliderSpeed);
    }
    else{
      Slide(0);
    }
  }


  
}


void Elevator::Elevate(float speed){
  elevator.Set(speed*kElevatorSpeed);
}

void Elevator::Slide(float speed){
  balancer.Set(speed);
}

void Elevator::Climb(float speed){
  climber.Set(speed);
}


