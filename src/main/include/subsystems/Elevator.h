
#pragma once

#include <frc2/command/SubsystemBase.h>
#include "frc/VictorSP.h"
#include "frc/XboxController.h"
#include "Constants.h"
#include "frc/DigitalInput.h"

using namespace frc;

// Clase para manejar el elevador
class Elevator : public frc2::SubsystemBase
{
public:
	Elevator();

	// Función que ocurre todo el tiempo
	void Periodic() override;

	// Subir elevador
	void Elevate(float speed);

	// Mover deslizador del gancho
	void Slide(float speed);

	// Subir robot
	void Climb(float speed);

private:
	// Control
	XboxController control{0};

	// Motor del elevador
	VictorSP elevator{mElevator};

	// Motor del deslizador
	VictorSP balancer{mBalancer};

	// Motor del escalador
	VictorSP climber{mClimber};

	// Limit Switch que detecta si el elevador ha llegado a su límite
	DigitalInput limit{sElevatorSwitch};
};
