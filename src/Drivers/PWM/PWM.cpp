#include "PWM.hpp"






void ANALOGPIN_Setup(int Pin, bool state = OFF){};
void ANALOGPIN_Update(){};

void setState(bool state){};
void toggleState(){};
bool getState(){};

void setDutyCycle(float CycleRate){};

/** Return the current output duty-cycle setting, measured as a percentage (float)
   83      *
   84      *  @returns
   85      *    A floating-point value representing the current duty-cycle being output on the pin,
   86      *    measured as a percentage. The returned value will lie between
   87      *    0.0f (representing on 0%) and 1.0f (representing on 100%).
   88      *
   89      *  @note
   90      *  This value may not match exactly the value set by a previous write().
   91      */
float getDutyCycle(){};
void setPeriod(float _us_){}; //in us
float getPeriod(){}; //in us
void setPulseWidth(float us){};
float getPulseWidth(){};