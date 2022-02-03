/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RotatePanel.h"
#include "Constants.h"
#include "frc/smartdashboard/SmartDashboard.h"

RotatePanel::RotatePanel(Panel* subsystem)
    : panel{subsystem} {
    AddRequirements({subsystem});

}

void RotatePanel::Initialize(){
    hits = 0;
    limit_off = true;
    panel->timer.Reset();
}

void RotatePanel::Execute(){
    

    panel->SetMotor(kPanelSpeed);

    if(limit_off&&!panel->GetLimit()){
        hits++;
        limit_off = false;
    }
    else if(!limit_off&&panel->GetLimit()){
        limit_off = true;
    }
}

bool RotatePanel::IsFinished(){
    bool climbMode = SmartDashboard::GetBoolean("Climb Mode",false);
    return hits>kPanelHits*3||climbMode;
}

void RotatePanel::End(bool interrupted){
    panel->SetMotor(0);
}