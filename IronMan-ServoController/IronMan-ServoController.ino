#include "ServoEasing.hpp"

// ================================================== *
//			DECLARACION DE VARIABLES
// ================================================== *

// ===== Variables para el servo motor =====

ServoEasing servo_right;
ServoEasing servo_left;

// ===== Declaracion de pines =====

int BUTTON_PIN			= 1;
int SERVO_LEFT_PIN		= 2;
int SERVO_RIGHT_PIN		= 3;

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

int open_angle					= 180;
int close_angle					= 0;

int servo_speed					= 150;

// ================================================== *
//			DECLARACION DE METODOS PERSONALES
// ================================================== *

void open_mask() {
	// Serial.println("Opening mask");
	// Serial.println("Opening right servo");
	servo_right.easeTo(open_angle, servo_speed);
	// Serial.println("Opening left servo");
	servo_left.easeTo(open_angle, servo_speed);
}
void close_mask() {
	// Serial.println("Closing mask");
	// Serial.println("Closing right servo");
	servo_right.easeTo(close_angle, servo_speed);
	// Serial.println("Closing left servo");
	servo_left.easeTo(close_angle, servo_speed);
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
	servo_left.attach( SERVO_LEFT_PIN, 0);
	servo_right.attach(	SERVO_RIGHT_PIN, 0);

	servo_left.setEasingType(	EASE_CUBIC_IN_OUT );
	servo_right.setEasingType(	EASE_CUBIC_IN_OUT );

	delay(3000);
	open_mask();
	delay(3000);
	close_mask();

	// synchronizeAllServosStartAndWaitForAllServosToStop();
}



void loop() {
	button_pin_data = digitalRead(BUTTON_PIN);
	Serial.println(button_pin_data);

	if ( button_pin_data == 0 ) {
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
