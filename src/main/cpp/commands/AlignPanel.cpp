/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AlignPanel.h"
#include "Constants.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/DriverStation.h>
#include <frc/Timer.h>



AlignPanel::AlignPanel(Panel* subsystem)
    : panel{subsystem} {
    AddRequirements({subsystem});

}

void AlignPanel::Initialize(){
    currentColor = panel->GetColor();
    goalColor = DriverStation::GetInstance().GetGameSpecificMessage();
    if(goalColor=="R") goalColor = "B";
    else if(goalColor=="B") goalColor = "R";
    else if(goalColor=="G") goalColor = "Y";
    else if(goalColor=="Y") goalColor = "G";
    
    for(int start = 0;start<7;start++){
        if(panelColors[start]==currentColor){
            for(int goal = start;goal<7;goal++){
                
                if(panelColors[goal] == goalColor){
                    
                    int distance = goal-start;
                    if(distance == 3) direction = 1;
                    else direction = -1;
                    break;
                }
            }
            break;
        }
    }
    
    

}

void AlignPanel::Execute(){
    
    detectingColor = panel->GetColor();
    panel->SetMotor(0.7*direction);
}

bool AlignPanel::IsFinished(){
    bool climbMode = SmartDashboard::GetBoolean("Climb Mode",false);
    return detectingColor == goalColor||climbMode;

}

void AlignPanel::End(bool interrupted){
    bool climbMode = SmartDashboard::GetBoolean("Climb Mode",false);
    if(!climbMode){
        Timer time;
        time.Reset();
        time.Start();
        panel->SetMotor(0);
    }
    else{
        panel->SetMotor(0);
    }
    
}

