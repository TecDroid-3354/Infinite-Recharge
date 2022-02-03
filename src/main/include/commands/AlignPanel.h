/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/Panel.h"

//@ts-ignore
class AlignPanel: public frc2::CommandHelper<frc2::CommandBase, AlignPanel> {
 public:
  
  explicit AlignPanel(Panel* subsystem);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End(bool interrupted) override;
  
 private:
  Panel* panel;
  string currentColor,goalColor,detectingColor;
  string panelColors[7] = {"R","G","B","Y","R","G","B"};
  
  int direction = -1;
};
