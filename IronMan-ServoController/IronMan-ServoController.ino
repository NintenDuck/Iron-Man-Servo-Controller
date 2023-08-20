#include "ServoEasing.hpp"
#include "time.h"

// ================================================== *
//			DECLARACION DE VARIABLES
// ================================================== *

// ===== Variables para el Servo Motor =====

ServoEasing servo_right;
ServoEasing servo_left;

// ===== Declaracion de Pines =====

const int SERVO_RIGHT_PIN 			= 12;
const int SERVO_LEFT_PIN 				= 11;
const int BUTTON_POWER 				= 10;
const int BUTTON_PIN 					= 5;
const int EYE_PIN 					= 3;

// ===== Variables de Control de Estados =====

int current_servo_state 		= 0; // Estados de servo:
							 		 // 0: Detenido
							 		 // 1: Moviendose

int current_mask_state 			= 0; // Estados de mascara:
									 // 0: Abajo
									 // 1: Arriba

// ===== Variables de Servos =====

const int LEFT_OPEN_ANGLE 		= 0;
const int RIGHT_OPEN_ANGLE 		= 180;
const int LEFT_CLOSE_ANGLE 		= 90;
const int RIGHT_CLOSE_ANGLE 	= 90;

const int SERVO_CLOSE_SPD 		= 110;
const int SERVO_OPEN_SPD 		= 130;

// ===== Variables de Ojos =====

const int EYE_SPEED 			= 1;
const int BLINK_SPEED_MIN		= 0;
const int BLINK_SPEED_MAX		= 6;


// ===== Variables de Boton =====

int button_pin_data 			= LOW;

// ================================================== *
//			DECLARACION DE METODOS PERSONALES
// ================================================== *

inline int randInt( int min, int max ) { return ( rand() % ( max - min ) ) + min; }

void randomize_eye_light()
{
	int ranNum = randInt( BLINK_SPEED_MIN, BLINK_SPEED_MAX );
	digitalWrite( EYE_PIN, LOW );
	for ( int i = 0; i < ranNum; i++ )
	{
		digitalWrite( EYE_PIN, HIGH );
		delay( randInt( 25, 150 ) );
		digitalWrite( EYE_PIN, LOW );
		delay( randInt( 10, 150 ) );
	}
}

void smooth_led_light( char led_action = 'u' )
{
	int i;

	switch ( led_action )
	{
	case 'u':
		i = 0;
		while ( i < 255 )
		{
			analogWrite( EYE_PIN, i++ );
			delay( EYE_SPEED );
		}
		break;
	default:
		i = 255;
		while ( i >= 0 )
		{
			analogWrite( EYE_PIN, i-- );
			delay( EYE_SPEED );
		}
	}
}

void turn_eyes_on()
{
	randomize_eye_light();
	smooth_led_light( 'u' );
}

void turn_eyes_off()
{
	smooth_led_light( 'd' );
}

void open_mask()
{
	turn_eyes_off();
	servo_right.setEaseTo( RIGHT_OPEN_ANGLE, SERVO_OPEN_SPD );
	servo_left.setEaseTo( LEFT_OPEN_ANGLE, SERVO_OPEN_SPD );
	synchronizeAllServosStartAndWaitForAllServosToStop();
	current_mask_state = 1;
}
void close_mask()
{
	servo_right.setEaseTo( RIGHT_CLOSE_ANGLE, SERVO_CLOSE_SPD );
	servo_left.setEaseTo( LEFT_CLOSE_ANGLE, SERVO_CLOSE_SPD );
	synchronizeAllServosStartAndWaitForAllServosToStop();
	current_mask_state = 0;
	turn_eyes_on();
}

int get_servo_state()
{
	if ( servo_right.isMoving() || servo_left.isMoving() )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// ================================================== *
//		INIT SETTING Y LOOP DEL PROYECTO
// ================================================== *

void setup()
{
	srand( time( 0 ) );
	Serial.begin( 9600 );

	// ===== Setup de boton =====

	pinMode( BUTTON_PIN, INPUT );
	pinMode( BUTTON_POWER, OUTPUT );
	pinMode( EYE_PIN, OUTPUT );

	digitalWrite( BUTTON_POWER, HIGH );

	// ===== Setup de servo motores =====

	servo_left.attach( SERVO_LEFT_PIN, 180 );
	servo_right.attach( SERVO_RIGHT_PIN, 0 );

	servo_left.setEasingType( EASE_CUBIC_IN_OUT );
	servo_right.setEasingType( EASE_CUBIC_IN_OUT );

	close_mask();
}

void loop()
{
	delay( 1000 );
	button_pin_data = digitalRead( BUTTON_PIN );
	if ( button_pin_data == HIGH )
	{
		current_servo_state = get_servo_state();
		if ( current_servo_state == 0 )
		{
			if ( current_mask_state == 0 )
			{
				open_mask();
			}
			else
			{
				close_mask();
			}
		}
	}
}
