
#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/util/color.h>
#include "rev/ColorSensorV3.h"
#include "rev/ColorMatch.h"
#include "frc/VictorSP.h"
#include <frc/DigitalInput.h>
#include "Constants.h"
#include "frc/Timer.h"

using namespace frc;
using namespace rev;
using namespace std;

// Clase que controla el rotador del panel
class Panel : public frc2::SubsystemBase
{
public:
	Panel();

	// Función que ocurre todo el tiempo
	void Periodic() override;

	// Resetear
	void Reset();

	// Activar el motor
	void SetMotor(float speed);

	// Obtener el valor del limit switch
	bool GetLimit();

	// Obtener el color del sensor
	string GetColor();

private:
	// Puerto donde se encuentra conectado el sensor de color
	static constexpr auto s_color = frc::I2C::Port::kOnboard;

	// Objeto del sensor de color
	ColorSensorV3 m_colorSensor{s_color};

	// Sistema para detectar el color
	ColorMatch m_colorMatcher;

	// Color actual
	Color currentColor;

	// Color temporal
	Color tempColor;

	// Motor del rotador del panel
	VictorSP motor{mPanel};

	// Limit Switch que detecta los pines del panel
	DigitalInput limit{sPanelSwitch};

	// Confianza del color
	double confidence = 0.0;
};
