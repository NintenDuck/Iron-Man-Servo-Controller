#include "ServoEasing.hpp"
#include "time.h"
// ================================================== *
//			DECLARACION DE VARIABLES
// ================================================== *

// ===== Variables para el servo motor =====

ServoEasing servo_right;
ServoEasing servo_left;

// ===== Declaracion de pines =====

int SERVO_LEFT_PIN				= 7;
int SERVO_RIGHT_PIN				= 6;
int BUTTON_POWER				= 13;
int BUTTON_PIN					= 5;
int EYE_PIN						= 3;

int button_pin_data				= LOW;

// ===== Variables de control de estados =====


int current_servo_state			= 0;	// Estados de servo:
										// 0: Detenido
										// 1: Moviendose

int current_mask_state			= 0;	// Estados de mascara:
										// 0: Abajo
										// 1: Arriba

// ===== Variables Auxiliares =====

int servo_speed					= 150;
int eye_speed					= 1;

// ================================================== *
//			DECLARACION DE METODOS PERSONALES
// ================================================== *

inline int randInt(int min, int max) { return (rand() % (max - min)) + min; }

void randomize_eyes(){
  int ranNum = randInt(0, 6);
  digitalWrite(EYE_PIN, LOW);
  for(int i = 0; i < ranNum; i++) {
    digitalWrite(EYE_PIN, HIGH);
    delay(randInt(25, 150));
    digitalWrite(EYE_PIN, LOW);
    delay(randInt(10, 150));
  }
}

void foo(int init_eyes_val = 0, char to='u') {
	int i = init_eyes_val;

	switch (to) {
		case 'u':
			while ( i < 255 ) {
				analogWrite( EYE_PIN, i++ );
				delay( eye_speed );
			}
			break;
		default:
			while ( i >= 0 ) {
				analogWrite( EYE_PIN, i-- );
				delay( eye_speed );
			}

	}
}

void turn_eyes_on() {
	randomize_eyes();
	foo( 0, 'u' );
}

void turn_eyes_off(){
	foo( 255, 'd' );
}

void open_mask() {
	Serial.println( "Opening mask" );
	servo_right.setEaseTo( 0, servo_speed );
	servo_left.setEaseTo( 180, servo_speed );
	synchronizeAllServosStartAndWaitForAllServosToStop();
	current_mask_state = 1;
	turn_eyes_on();
}
void close_mask() {
	Serial.println("Closing mask");
	turn_eyes_off();
	servo_right.setEaseTo( 180, servo_speed);
	servo_left.setEaseTo( 0, servo_speed);
	synchronizeAllServosStartAndWaitForAllServosToStop();
	current_mask_state = 0;
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
	srand(time(0));
	Serial.begin( 9600 );

	// ===== Setup de boton =====
	
	pinMode( BUTTON_PIN, INPUT );
	pinMode( BUTTON_POWER, OUTPUT );
	pinMode( EYE_PIN, OUTPUT );

	digitalWrite(BUTTON_POWER, HIGH);

	// ===== Setup de servo motores =====

	servo_left.attach( 	SERVO_LEFT_PIN, 	180 );
	servo_right.attach(	SERVO_RIGHT_PIN, 	0 );

	servo_left.setEasingType(	EASE_CUBIC_IN_OUT );
	servo_right.setEasingType(	EASE_CUBIC_IN_OUT );

	open_mask();
}



void loop() {
	delay(1000);
	button_pin_data = digitalRead(BUTTON_PIN);

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
