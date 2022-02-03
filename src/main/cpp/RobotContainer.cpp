/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
#include "commands/RotatePanel.h"
#include "commands/AlignPanel.h"
#include "commands/Prepare.h"
#include "frc2/command/button/JoystickButton.h"
#include "frc/smartdashboard/SmartDashboard.h"

// Al iniciar el robot, configurar los botones
RobotContainer::RobotContainer()
{
	ConfigureButtonBindings();
}

// Configurar los comandos según el botón
void RobotContainer::ConfigureButtonBindings()
{

	// Al presionar A, girar el panel
	bRotatePanel.WhenPressed(new RotatePanel(&panel));

	// Al presionar B, alinear el panel
	bAlignPanel.WhenPressed(new AlignPanel(&panel));

	// Al presionar right bumper, preparar el disparador
	bPrepare.WhenPressed(new Prepare(&shooter, &tower));
}

// Funciones de manejo del robot
void RobotContainer::Drive()
{
	// Manejar el robot según el control
	chasis.Drive();

	// Mover la torre según el control
	tower.Move();

	// Disparar según el control
	shooter.Move();
}

// Obtener el objeto del autónomo
Auto *RobotContainer::GetAuto()
{
	return auton;
}

// Resetear los subsistemas
void RobotContainer::Reset()
{
	shooter.Reset();
	tower.Reset();
}

// Bajar la torre
void RobotContainer::Lower()
{
	tower.Lower();
}

void RobotContainer::Test()
{
}
