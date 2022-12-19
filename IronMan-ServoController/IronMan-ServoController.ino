#include "ServoEasing.hpp"

// ================================================== *
//          DECLARACION DE VARIABLES
// ================================================== *

// ===== Variables para el servo motor =====

ServoEasing Servo_Right;
ServoEasing Servo_Left;

// ===== Declaracion de pines =====

int BUTTON_PIN              = 1;
int button_pin_data         = 0;

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
//          DECLARACION DE METODOS PERSONALES
// ================================================== *

void open_mask() {
    Serial.println( "opening mask!" );
}
void close_mask() {
    Serial.println( "closing mask!" );
}

int get_servo_state() {
    if ( Servo_Right.isMoving() ) {
        return 1;
    } else {
        return 0;
    }
}

// ================================================== *
//          INIT SETTING Y LOOP DEL PROYECTO
// ================================================== *

void setup() {
    Serial.begin( 9600 );

    // ===== Setup de boton =====
    
    pinMode(BUTTON_PIN, INPUT);

    // ===== Setup de servo motores =====
    Servo_Left.attach(  9 );
    Servo_Right.attach( 10 );

    Servo_Left.setEasingType(   EASE_CUBIC_IN_OUT );
    Servo_Right.setEasingType(  EASE_CUBIC_IN_OUT );

    synchronizeAllServosStartAndWaitForAllServosToStop();
}



void loop() {
    button_pin_data = analogRead(BUTTON_PIN);


    if ( button_pin_data == HIGH ) {
        currentServoState = get_servo_state();

        if ( currentServoState == 0 ) {
            if ( currentMaskState == 0 ) {
                open_mask();
            }
            else {
                close_mask();
            }
        }
    }
}
