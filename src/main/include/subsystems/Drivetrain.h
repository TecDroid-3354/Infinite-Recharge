
#pragma once

#include <frc2/command/SubsystemBase.h>
#include "frc/VictorSP.h"
#include "frc/Timer.h"
#include "frc/Encoder.h"
#include "Constants.h"
#include "frc/drive/DifferentialDrive.h"
#include "frc/XboxController.h"
#include <adi/ADIS16448_IMU.h>
#include <frc/BuiltInAccelerometer.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/SerialPort.h>
#include <frc/PIDSource.h>

using namespace frc;

// Clase para manejar el chasis
class Drivetrain : public frc2::SubsystemBase
{
public:
	Drivetrain();

	// Función que ocurre todo el tiempo
	void Periodic() override;

	// Manejar según el control
	void Drive();

	// Manejar según valores específicos
	void Drive(float y, float x);

	// Activar/Desactivar seguridad
	void SetSafetyEnabled(bool state);

	// Alinear
	void Align(float speed);

private:
	// Motor frente derecho
	VictorSP frontRight{mChasisFrontRight};

	// Motor frente izquierdo
	VictorSP frontLeft{mChasisFrontLeft};

	// Motor trasero derecho
	VictorSP backRight{mChasisBackRight};

	// Motor trasero izquierdo
	VictorSP backLeft{mChasisBackLeft};

	// Controlador de motores derechos
	// Esto se hace para que dos motores hagan el mismo movimiento
	SpeedControllerGroup right{frontRight, backRight};

	// Controlador de motores izquierdos
	SpeedControllerGroup left{frontLeft, backLeft};

	// Control
	XboxController control{0};

	// Objeto de control diferencial
	DifferentialDrive chasis{right, left};

	bool flag = true;

	// Control de modo de escalada
	bool climbMode = false;
};
