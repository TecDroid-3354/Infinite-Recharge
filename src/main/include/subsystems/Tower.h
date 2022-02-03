
#pragma once

#include <frc2/command/SubsystemBase.h>
#include "frc/VictorSP.h"
#include "frc/XboxController.h"
#include "Constants.h"
#include "frc/DoubleSolenoid.h"

using namespace frc;

// Clase que controla la torre
class Tower : public frc2::SubsystemBase
{
public:
	Tower();

	// Función que ocurre todo el tiempo
	void Periodic() override;

	// Activar motor
	void SetMotor(float speed);

	// Bajar intake
	void Lower();

	// Resetear
	void Reset();

	// Mover las bandas de la torre
	void Move();

private:
	// Control
	XboxController control{0};

	// Motor de la torre
	VictorSP motor{mIntake};

	// Solenoide que sube y baja el intake
	DoubleSolenoid intake{pIntakeFront, pIntakeBack};
};
