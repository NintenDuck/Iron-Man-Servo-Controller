#include "ServoEasing.h"

// ================================================== *
//          DECLARACION DE VARIABLES
// ================================================== *

// ===== Variables para el servo motor =====

ServoEasing Servo_Right;
ServoEasing Servo_Left;

// ===== Variables de control de estados =====


int currentServoState       = 0;        // Estados de servo:
                                        // 0: Detenido
                                        // 1: Moviendose

int currentMaskState        = 0;        // Estados de mascara:
                                        // 0: Abajo
                                        // 1: Arriba

// ===== Variables Auxiliares =====

int maxAngle                = 135;


// ================================================== *
//          INIT SETTING Y LOOP DEL PROYECTO
// ================================================== *

void setup() {
    Serial.being( 9600 );

    Servo1.attach( Servo_Left,   9 );
    Servo2.attach( Servo_Right,  10 );

    Servo1.setEasingType(EASE_CUBIC_IN_OUT);
    Servo2.setEasingType(EASE_CUBIC_IN_OUT);

    synchronizeAllServosStartAndWaitForAllServosToStop();
}



void loop() {
}
