/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Prepare.h"
#include "Constants.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/DriverStation.h>
#include <frc/Timer.h>



Prepare::Prepare(Shooter* shooter_,Tower* tower_)
    : shooter{shooter_},tower{tower_} {
    AddRequirements({shooter,tower});

}

void Prepare::Initialize(){
 
    shooter->timer.Reset();
    shooter->timer.Start();
    shooter->Light(true);
}

void Prepare::Execute(){
    
   /* bool climbMode = SmartDashboard::GetBoolean("Climb Mode",false);
    if(!climbMode){
        shooter->SetMotor(kShooterSpeed);
        shooter->Open();
    }
    */
    
}

bool Prepare::IsFinished(){
   bool climbMode = SmartDashboard::GetBoolean("Climb Mode",false);
   return shooter->timer.Get()>kPrepareTime||climbMode;
}

void Prepare::End(bool interrupted){
    //tower->SetMotor(0);
    
}

