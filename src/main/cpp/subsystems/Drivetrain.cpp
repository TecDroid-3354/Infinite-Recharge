/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drivetrain.h"
#include <frc/smartdashboard/smartdashboard.h>
#include <math.h>
#include "Constants.h"
#include <iostream>
#include <string.h>

using namespace frc;
using namespace std;

Drivetrain::Drivetrain()
{
}

// Periódicamente determina si se está picando el botón de cambiar modo de escalada
void Drivetrain::Periodic()
{

	// Si se pica el botón, se cambia de modo, pero solamente hasta que el botón se suelta
	// Esto se hace para evitar que se cambie mil veces cada segundo
	if (flag && control.GetRawButton(cStart))
	{
		climbMode = !climbMode;
		flag = false;
	}
	else if (!control.GetRawButton(cStart))
	{
		flag = true;
	}

	// Indicar si está en modo de escalada
	SmartDashboard::PutBoolean("Climb Mode", climbMode);
}

// Manejar el robot según el control
void Drivetrain::Drive()
{

	// El eje X determina el giro
	float x = control.GetRawAxis(cLeftAxisX);

	// El eje Y determina el avance
	float y = -control.GetRawAxis(cLeftAxisY);

	// Utilizar los ejes para moverse, agregar o quitar signos negativos para cambiar de dirección
	chasis.ArcadeDrive(-y, x);
}

// Manejar el robot según valores específicos
void Drivetrain::Drive(float y, float x)
{
	chasis.ArcadeDrive(y, x);
}

// Activar seguridad del chasis
void Drivetrain::SetSafetyEnabled(bool state)
{
	chasis.SetSafetyEnabled(state);
}

// Alinear el robot para que maneje derecho
void Drivetrain::Align(float speed)
{
	Drive(control.GetRawAxis(cLeftAxisY), speed);
}