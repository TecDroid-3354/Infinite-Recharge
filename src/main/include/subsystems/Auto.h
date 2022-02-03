
#pragma once

#include <frc2/command/SubsystemBase.h>
#include "frc/Timer.h"
#include "frc/Encoder.h"
#include "Constants.h"
#include <adi/ADIS16448_IMU.h>
#include <frc/BuiltInAccelerometer.h>
#include "Drivetrain.h"
#include "Shooter.h"
#include "Tower.h"
#include "commands/Prepare.h"
#include "commands/Shoot.h"
#include "frc/PIDController.h"
#include "frc/PIDOutput.h"
#include "frc/PIDSource.h"
#include "frc/Timer.h"
#include "frc/smartdashboard/SmartDashboard.h"

using namespace frc;

// Clase que controla la velocidad de giro del chasis según un algoritmo PID
class GyroOutput : public frc::PIDOutput
{
public:
	// Recive un objeto de drivetrain
	explicit GyroOutput(Drivetrain &r)
		: m_rd(r)
	{
		// Desactiva el sistema de seguridad del drivetrain
		m_rd.SetSafetyEnabled(false);
	}

	// Hace girar el chasis según lo recibido por el algoritmo PID
	void PIDWrite(double output) override
	{

		// Utiliza la función Drive del chasis en el eje de giro
		m_rd.Drive(0, output); // Agregar signo negativo para cambiar de dirección
	}

private:
	Drivetrain &m_rd;
};

// Clase que controla la velocidad de avance del chasis según un algoritmo PID
class EncoderOutput : public frc::PIDOutput
{
public:
	// Recive un objeto de drivetrain
	explicit EncoderOutput(Drivetrain &r)
		: m_rd(r)
	{
		// Desactiva el sistema de seguridad del drivetrain
		m_rd.SetSafetyEnabled(false);
	}

	// Hace avanzar al robot según lo recibido por el algoritmo PID
	void PIDWrite(double output) override
	{

		// Utiliza la función drive del chasis en el eje de avance
		m_rd.Drive(-output, 0); // Quitar signo negativo para cambiar de dirección
	}

private:
	// Objeto de chasis
	Drivetrain &m_rd;
};

/*Clase para controlar el autónomo*/
class Auto : public frc2::SubsystemBase
{
public:
	/*
	   El autónomo recibe los objetos del chasis, la torre y el disparador para poderlos controlar
	*/
	explicit Auto(Drivetrain &drivetrain_, Tower &tower_, Shooter &shooter_);

	// Función que ocurre todo el tiempo
	void Periodic() override;

	// Resetear
	void Reset();

	// Desactivar
	void Disable();

	// Se encuentra activo?
	bool IsActive();

	// Mover el chasis
	bool Move(float setpoint);

	// Mover mientras prepara el disparador
	bool MoveLoad(float setpoint);

	// Girar
	bool Turn(float setpoint);

	// Activar el intake
	bool Intake(float setpoint);

	// Disparar
	bool Launch();

	// Iniciar
	bool Start();

	// Determinar si recorrió la distancia seleccionada
	bool AtDistance();

	// Determinar si giró el ángulo adecuado
	bool AtAngle();

private:
	// ADIS16448_IMU gyro;
	BuiltInAccelerometer accelerometer;

	// Encoder
	Encoder encoder{sEncoderA, sEncoderB, true, Encoder::EncodingType::k4X};

	// Cámara pixy
	PixySource source;

	// Chasis
	Drivetrain &chasis;

	// Torre
	Tower &tower;

	// Disparador
	Shooter &shooter;

	// Gyro output que controla la velocidad de giro del chasis
	GyroOutput *turnOutput = new GyroOutput(chasis);

	// Encoder output que controla la velocidad de avance del chasis
	EncoderOutput *speedOutput = new EncoderOutput(chasis);

	// Controla la velocidad de giro del chasis  según el PID y el giroscopio
	PIDController turn{kTurnP, kTurnI, kTurnD, &gyro, turnOutput};

	// Controla la velocidad del chasis según el PID y los encoders
	PIDController speed{kSpeedP, kSpeedI, kSpeedD, &encoder, speedOutput};

	// Comando que prepara el disparador y la torre
	Prepare *prepare = new Prepare(&shooter, &tower);

	// Comando que dispara
	Shoot *shoot = new Shoot(&shooter, &tower);

	// Temporizador
	frc::Timer timer;
};
