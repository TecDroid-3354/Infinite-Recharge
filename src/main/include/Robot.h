/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include <frc/VictorSP.h>
#include "RobotContainer.h"
#include "frc/MedianFilter.h"
#include "cameraserver/CameraServer.h"
using namespace cs;

/*
	Clase que controla las eetapas del robot
*/
class Robot : public frc::TimedRobot
{
public:
	void RobotInit() override;
	void RobotPeriodic() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestInit();
	void TestPeriodic() override;

public:
	/*Objeto del contenedor del robot*/
	RobotContainer m_container;

	/*Objeto del sistema autónomo*/
	Auto *auton = m_container.GetAuto();

	/*Variables para el autónomo*/
	int step = 0;
	float p, i, d;
};
