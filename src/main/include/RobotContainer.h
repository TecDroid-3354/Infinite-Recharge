/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/Command.h>

#include "subsystems/Panel.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Auto.h"
#include "subsystems/Shooter.h"
#include "subsystems/Tower.h"
#include "subsystems/Elevator.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "frc/XboxController.h"
#include "frc2/command/button/Button.h"
#include "frc/Timer.h"

using namespace frc2;
using namespace frc;

/*Clase que contiene los subsistemas del robot y controla funciones generales.*/
class RobotContainer
{
public:
	RobotContainer();

	Command *GetAutonomousCommand();

	/*Mover chasis*/
	void Drive();

	/*Obtener el sistema autónomo*/
	Auto *GetAuto();

	/*Resetear torre y disparador*/
	void Reset();

	/*Bajar intake*/
	void Lower();

	/*Desactivar autónomo*/
	void Disable();

	void Test();

	/*Temporizador*/
	frc::Timer timer;

private:
	// The robot's subsystems and commands are defined here...

	/*Objeto del subsistema para controlar la rueda*/
	Panel panel;

	// Objeto de control
	XboxController control{0};

	/*Objeto de chasis*/
	Drivetrain chasis;

	/*Objeto de disparador*/
	Shooter shooter;

	/*Objeto de elevador*/
	Elevator elevator;

	/*Objeto de torre*/
	Tower tower;

	/*Objeto del autónomo*/
	Auto *auton = new Auto(chasis, tower, shooter);

	/*Botón para rotar el panel*/
	Button bRotatePanel{[&]
						{ return control.GetRawButton(cButtonA); }};

	/*Botón para alinear el panel al color recibido*/
	Button bAlignPanel{[&]
					   { return control.GetRawButton(cButtonB); }};

	/*Botón para preparar el disparador*/
	Button bPrepare{[&]
					{ return control.GetRawButton(cRightBumper); }};

	/*Función para configurar las acciones relacionadas a cada botón*/
	void ConfigureButtonBindings();
};
