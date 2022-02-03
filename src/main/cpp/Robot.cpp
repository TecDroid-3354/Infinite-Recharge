/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <frc/Joystick.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <RobotContainer.h>

// Inicializar el robot
void Robot::RobotInit()
{

	// Obtener cámara 1
	cs::UsbCamera cam = frc::CameraServer::GetInstance()->StartAutomaticCapture(0);

	// Asignar resolución
	cam.SetResolution(640, 480);

	// Asignar FPS
	cam.SetFPS(40);

	// Obtener cámara 2
	cs::UsbCamera cam2 = frc::CameraServer::GetInstance()->StartAutomaticCapture(1);

	// Asignar resolución
	cam2.SetResolution(640, 480);

	// Asignar FPS
	cam2.SetFPS(40);
}

// Periódicamente obtener el siguiente comando
void Robot::RobotPeriodic()
{

	frc2::CommandScheduler::GetInstance().Run();
}

void Robot::DisabledInit()
{
}

// Resetear el robot cuando se desactiva
void Robot::DisabledPeriodic()
{
	m_container.Reset();
}

// Inicializar autónomo
void Robot::AutonomousInit()
{

	// Resetear el paso
	step = 0;

	// Resetear el autónomo
	auton->Reset();
	// Resetear el robot
	m_container.Reset();
}

// Función del autónomo
void Robot::AutonomousPeriodic()
{

	// Bajar la torre
	m_container.Lower();

	// Según el paso en el que va el robot de la lista de movimientos, hacer algo distinto
	switch (movements[step])
	{

	// Moverse
	case 'm':

		// Mover el robot hasta que llega a su meta
		if (auton->Move(targets[step]))
		{
			// Desactivar y resetear
			auton->Disable();
			auton->Reset();

			// Pasar al siguiente paso
			step++;
		}
		break;

	// Moverse y cargar
	case 'l':

		// Mover y cargar hasta que llegue a su meta
		if (auton->MoveLoad(targets[step]))
		{
			// Desactivar y resetear
			auton->Disable();
			auton->Reset();

			// Pasar al siguiente paso
			step++;
		}
		break;

	// Girar
	case 't':
		// Girar hasta que llegue a su ángulo meta
		if (auton->Turn(targets[step]))
		{
			// Desactivar y resetear
			auton->Disable();
			auton->Reset();

			// Pasar al siguiente paso
			step++;
		}
		break;

	// Mover mientras recoge
	case 'i':

		// Mover y recoger hasta que llegue a su meta
		if (auton->Intake(targets[step]))
		{
			// Desactivar y resetear
			auton->Disable();
			auton->Reset();

			// Pasar al siguiente paso
			step++;
		}
		break;

	// Disparar
	case 's':

		// Disparar una vez
		if (auton->Launch())
		{

			step++;
		}
		break;
	// Iniciar
	case 'p':
		// Iniciar autónomo
		if (auton->Start())
			step++;
		break;

	// Desactivar
	default:
		auton->Disable();
		break;
	}
}

// Inicializar teleoperado
void Robot::TeleopInit()
{

	// Desactivar el autónomo
	auton->Disable();
	auton->Reset();

	// Resetear el robot
	m_container.Reset();
}

// Teleoperado
void Robot::TeleopPeriodic()
{
	// Bajar torre
	m_container.Lower();

	// Manejar robot
	m_container.Drive();
}

void Robot::TestInit()
{
}
void Robot::TestPeriodic()
{
}

#ifndef RUNNING_FRC_TESTS
int main()
{
	return frc::StartRobot<Robot>();
}
#endif