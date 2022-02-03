/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Auto.h"
#include <frc/smartdashboard/smartdashboard.h>
#include "Constants.h"
#include <frc/Preferences.h>

using namespace frc;

// Constructor del autónomo a partir del chasis, la torre y el disparador
Auto::Auto(Drivetrain &drivetrain_, Tower &tower_, Shooter &shooter_) : chasis{drivetrain_}, tower(tower_), shooter(shooter_)
{

	// Permitir giro de 360 grados en cualquier dirección
	turn.SetInputRange(-360, 360);

	// Delimitar el rango de velocidades de giro según la constante de velocidad de giro
	turn.SetOutputRange(-kAutoTurn, kAutoTurn);

	// Permitir velocidad de 0 a 360 en cualquier dirección
	speed.SetInputRange(-360, 360);

	// Delimitar el rango de velocidades de avance según la constante de velocidad de avance
	speed.SetOutputRange(-kAutoSpeed, kAutoSpeed);

	// Definir la distancia por pulso del encoder
	encoder.SetDistancePerPulse(kEncoderPulse);

	// Delimitar el autónomo de velocidad en modo de desplacamiento
	speed.SetPIDSourceType(PIDSourceType::kDisplacement);
}

// Poner constantemente los valores del encoder y el gyro en la dashboard
void Auto::Periodic()
{
	SmartDashboard::PutNumber("Encoder", encoder.GetDistance());
	SmartDashboard::PutNumber("Gyrp", gyro.GetAngle());
}

// Resetear sensores y controladores
void Auto::Reset()
{

	// Resetear sensores
	encoder.Reset();
	gyro.Reset();

	// Resetear controladores de movimiento
	turn.Reset();
	speed.Reset();
}

// Mover el robot hasta una distancia específica
bool Auto::Move(float setpoint)
{

	// Indicar el punto al que debe llegar
	speed.SetSetpoint(setpoint);

	// Si se está acercando a la meta, ir a 70% de velocidad
	if (fabs(speed.GetError()) < 6)
		speed.SetOutputRange(-kAutoSpeed * 0.7, kAutoSpeed * 0.7);

	// Si todavía le falta, ir al 100%
	else
		speed.SetOutputRange(-kAutoSpeed, kAutoSpeed);

	// Obtener el punto actual del chasis
	speed.Get();

	// Activar el controlador de velocidad de avance
	speed.Enable();

	// Regresar si se encuentra ya en el punto seleccionado
	return AtDistance();
}

// Mover el robot a la vez que se carga la pelota
bool Auto::MoveLoad(float setpoint)
{

	// Al iniciar el temporizador, ir aumentando la velocidad del disparador progresivamente
	if (timer.Get() < 1.5)
	{
		shooter.SetMotor(kShooterSpeed * timer.Get() / 1.5);
	}

	// Después de 1.5 segundos, activar la velocidad del disparador al 100%
	if (timer.Get() > 1.5)
	{
		shooter.SetMotor(kShooterSpeed);
	}

	// Mover el chasis
	return Move(setpoint);
}

// Activar el recogedor al mismo tiempo que se mueve
bool Auto::Intake(float setpoint)
{

	// Activar el recogedor
	tower.SetMotor(kIntakeSpeed);

	// Mover el robot
	return Move(setpoint);
}

// Girar el chasis hasta un punto específico
bool Auto::Turn(float setpoint)
{

	// Asignar el ángulo al que se quiere llegar
	turn.SetSetpoint(setpoint);

	// Si está a punto de llegar al ángulo, girar al 70% de velocidad
	if (fabs(turn.GetError()) < 10)
		turn.SetOutputRange(-kAutoTurn * 0.7, kAutoTurn * 0.7);

	// Si todavía le falta, girar al 100%
	else
		turn.SetOutputRange(-kAutoTurn, kAutoTurn);

	// Obtener el ángulo actual
	turn.Get();

	// Activar el controlador de giro
	turn.Enable();

	// Regresar si ya se encuentra en el ángulo seleccionado
	return AtAngle();
}

// Determina si ya se encuentra en el punto seleccionado
bool Auto::AtDistance()
{
	// El error de distancia debe ser menor a 0.1
	return fabs(speed.GetError()) < 0.1;
}

// Determina si ya se encuentra en el ángulo seleccionado
bool Auto::AtAngle()
{
	// El error de ángulo debe ser menor a 0.1
	return fabs(turn.GetError()) < 0.1;
}

// Dispara
bool Auto::Launch()
{

	// Después de 3 segundos
	if (timer.Get() > 3)
	{

		// Abrir el disparador
		shooter.Open();

		// Activar la torre para alimentar el disparador
		tower.SetMotor(kTowerSpeed);

		// Después de 4 segundos
		if (timer.Get() > 7)
		{
			// Apagar torre
			tower.SetMotor(0);

			// Apagar disparador
			shooter.SetMotor(0);
			return true;
		}
		else
			return false;
	}
	else
	{
		return false;
	}
}

// Iniciar autónomo
bool Auto::Start()
{

	// Resetear temporizador
	timer.Reset();

	// Iniciar temporizador
	timer.Start();

	// Preparar el asignador de etapas
	prepare->Schedule();
	return true;
}

// Desactivar autónomo
void Auto::Disable()
{

	speed.SetOutputRange(-kAutoSpeed, kAutoSpeed);
	turn.SetOutputRange(-kAutoTurn, kAutoTurn);
	speed.Disable();
	turn.Disable();
}

// Determina si el autónomo está activado
bool Auto::IsActive()
{
	return turn.IsEnabled() || speed.IsEnabled();
}