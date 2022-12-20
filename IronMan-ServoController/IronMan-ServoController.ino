#include "ServoEasing.hpp"

// ================================================== *
//			DECLARACION DE VARIABLES
// ================================================== *

// ===== Variables para el servo motor =====

ServoEasing servo_right;
ServoEasing servo_left;

// ===== Declaracion de pines =====

const BUTTON_PIN			= 1;
int button_pin_data			= 0;

// ===== Variables de control de estados =====


int current_servo_state			= 0;	// Estados de servo:
										// 0: Detenido
										// 1: Moviendose

int current_mask_state			= 0;	// Estados de mascara:
										// 0: Abajo
										// 1: Arriba

// ===== Variables Auxiliares =====

int maxAngle					= 135;


// ================================================== *
//			DECLARACION DE METODOS PERSONALES
// ================================================== *

void open_mask() {
	Serial.println( "opening mask!" );
}
void close_mask() {
	Serial.println( "closing mask!" );
}

int get_servo_state() {
	if ( servo_right.isMoving() ) {
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
	servo_left.attach(	9 );
	servo_right.attach(	10 );

	servo_left.setEasingType(	EASE_CUBIC_IN_OUT );
	servo_right.setEasingType(	EASE_CUBIC_IN_OUT );

	synchronizeAllServosStartAndWaitForAllServosToStop();
}



void loop() {
	button_pin_data = analogRead(BUTTON_PIN);


	if ( button_pin_data == HIGH ) {
		current_servo_state = get_servo_state();

		if ( current_servo_state == 0 ) {
			if ( current_mask_state == 0 ) {
				open_mask();
			}
			else {
				close_mask();
			}
		}
	}
}
