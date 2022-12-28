#include "ServoEasing.hpp"

// ================================================== *
//			DECLARACION DE VARIABLES
// ================================================== *

// ===== Variables para el servo motor =====

ServoEasing servo_right;
ServoEasing servo_left;

// ===== Declaracion de pines =====

int BUTTON_PIN					= 1;
int SERVO_LEFT_PIN				= 2;
int SERVO_RIGHT_PIN				= 3;

int button_pin_data				= 0;

// ===== Variables de control de estados =====


int current_servo_state			= 0;	// Estados de servo:
										// 0: Detenido
										// 1: Moviendose

int current_mask_state			= 0;	// Estados de mascara:
										// 0: Abajo
										// 1: Arriba

// ===== Variables Auxiliares =====

int servo_speed					= 150;

// ================================================== *
//			DECLARACION DE METODOS PERSONALES
// ================================================== *

void open_mask() {
	// Serial.println("Opening mask");
	servo_right.setEaseTo( 0, servo_speed);
	servo_left.setEaseTo( 180, servo_speed);
	synchronizeAllServosStartAndWaitForAllServosToStop();
}
void close_mask() {
	// Serial.println("Closing mask");
	servo_right.setEaseTo( 180, servo_speed);
	servo_left.setEaseTo( 0, servo_speed);
	synchronizeAllServosStartAndWaitForAllServosToStop();
}

int get_servo_state() {
	if ( servo_right.isMoving() || servo_left.isMoving() ) {
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

	servo_left.attach( 	SERVO_LEFT_PIN, 	180 );
	servo_right.attach(	SERVO_RIGHT_PIN, 	0 );

	servo_left.setEasingType(	EASE_CUBIC_IN_OUT );
	servo_right.setEasingType(	EASE_CUBIC_IN_OUT );

	delay(3000);
	open_mask();
	delay(3000);
	close_mask();
}



void loop() {
	button_pin_data = digitalRead(BUTTON_PIN);

	if ( button_pin_data == HIGH ) {
		// Serial.println("Entered button_pin_data if");
		current_servo_state = get_servo_state();

		if ( current_servo_state == 0 ) {
			// Serial.println("Entered current_ser if");
			if ( current_mask_state == 0 ) {
				open_mask();
			}
			else {
				close_mask();
			}
		}
	}
}
