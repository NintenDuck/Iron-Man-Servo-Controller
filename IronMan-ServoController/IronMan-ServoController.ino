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

    Servo_Left.attach(  9 );
    Servo_Right.attach( 10 );

    Servo_Left.setEasingType(   EASE_CUBIC_IN_OUT );
    Servo_Right.setEasingType(  EASE_CUBIC_IN_OUT );

    synchronizeAllServosStartAndWaitForAllServosToStop();
}



void loop() {
}
