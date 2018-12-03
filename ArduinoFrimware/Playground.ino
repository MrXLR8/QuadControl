/**
 * Usage, according to documentation(https://www.firediy.fr/files/drone/HW-01-V4.pdf) :
 *     1. Plug your Arduino to your computer with USB cable, open terminal, then type 1 to send max throttle to every ESC to enter programming mode
 *     2. Power up your ESCs. You must hear "beep1 beep2 beep3" tones meaning the power supply is OK
 *     3. After 2sec, "beep beep" tone emits, meaning the throttle highest point has been correctly confirmed
 *     4. Type 0 to send min throttle
 *     5. Several "beep" tones emits, which means the quantity of the lithium battery cells (3 beeps for a 3 cells LiPo)
 *     6. A long beep tone emits meaning the throttle lowest point has been correctly confirmed
 *     7. Type 2 to launch test function. This will send min to max throttle to ESCs to test them
 *
 * @author lobodol <grobodol@gmail.com>
 */
 // ---------------------------------------------------------------------------
#include <Servo.h>
// ---------------------------------------------------------------------------
// Customize here pulse lengths as needed
#define MIN_PULSE_LENGTH 1050 // Minimum pulse length in µs
#define MAX_PULSE_LENGTH 2000 // Maximum pulse length in µs
// ---------------------------------------------------------------------------
Servo mot1;
int data=1000;
// ---------------------------------------------------------------------------

/**
 * Initialisation routine
 */
void setup() {
	Serial.setTimeout(100);
	Serial.begin(9600);
	digitalWrite(13, HIGH);
	mot1.attach(6, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);

	displayInstructions();
	digitalWrite(13, LOW);
}

/**
 * Main function
 */

void loop() {
	if (Serial.available()) {
		data = Serial.parseInt();
		if (data == 1) {
			test();  data = 0;
			
		}
		else { 
			if (data >= 1000) {
				Serial.print("WRITING: ");
				mot1.writeMicroseconds(data);
				Serial.println(data);
			}
		}
	}


	


}

/**
 * Test function: send min throttle to max throttle to each ESC.
 */
void test()
{
	for (int i = MIN_PULSE_LENGTH; i <= 1200; i += 0) {
		Serial.print("Pulse length = ");
		Serial.println(i);
		i += random(-2, 4);
		if (i < 1000) i = 1000;
		mot1.writeMicroseconds(random(1000, 1100));


		delay(random(10,50));
	}

	Serial.println("STOP");
	mot1.writeMicroseconds(MIN_PULSE_LENGTH);

}

/**
 * Displays instructions to user
 */
void displayInstructions()
{
	Serial.println("READY - PLEASE SEND INSTRUCTIONS AS FOLLOWING :");
	Serial.println("\t1 : Test");
}