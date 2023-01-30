#ifndef PWM_H
#define PWM_H

#include <Arduino.h>
#include "../../Config.h"


class PWM {
	private:
		int OutputPin;
		bool State;

		static unsigned int Resolution;

		float DutyCycle;
		float Period_us_;
		float PulseWidth_us_;

	public:
		PWM () {};
		~PWM() {};

		void ANALOGPIN_Setup(int Pin, bool state = OFF);
		void ANALOGPIN_Update();

		void setState(bool state);
		void toggleState();
		bool getState();

		void setDutyCycle(float CycleRate);
		float getDutyCycle();
		void setPeriod(float _us_); //in us
		float getPeriod(); //in us
		void setPulseWidth(float us);
		float getPulseWidth();
};

extern PWM pwm;


#endif PWM_H