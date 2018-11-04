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
#define MIN_PULSE_LENGTH 1000 // Minimum pulse length in µs
#define MAX_PULSE_LENGTH 2000 // Maximum pulse length in µs
// ---------------------------------------------------------------------------
Servo motA, motB, motC, motD;
int data=1000;
// ---------------------------------------------------------------------------

/**
 * Initialisation routine
 */
void setup() {
	Serial.setTimeout(100);
	Serial.begin(9600);

	motA.attach(9, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
	motB.attach(6, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
	motC.attach(5, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
	motD.attach(3, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);



	displayInstructions();
}

/**
 * Main function
 */

void loop() {
	if (Serial.available()) {
		data = Serial.parseInt();


		Serial.print("WRITING: ");
		Serial.println(data);
	}

	motA.writeMicroseconds(data);
	motB.writeMicroseconds(data);
	motC.writeMicroseconds(data);
	motD.writeMicroseconds(data);


}

/**
 * Test function: send min throttle to max throttle to each ESC.
 */
void test()
{
	for (int i = MIN_PULSE_LENGTH; i <= MAX_PULSE_LENGTH; i += 5) {
		Serial.print("Pulse length = ");
		Serial.println(i);

		motA.writeMicroseconds(i);
		motB.writeMicroseconds(i);
		motC.writeMicroseconds(i);
		motD.writeMicroseconds(i);

		delay(200);
	}

	Serial.println("STOP");
	motA.writeMicroseconds(MIN_PULSE_LENGTH);
	motB.writeMicroseconds(MIN_PULSE_LENGTH);
	motC.writeMicroseconds(MIN_PULSE_LENGTH);
	motD.writeMicroseconds(MIN_PULSE_LENGTH);
}

/**
 * Displays instructions to user
 */
void displayInstructions()
{
	Serial.println("READY - PLEASE SEND INSTRUCTIONS AS FOLLOWING :");
	Serial.println("\t0 : Send min throttle");
	Serial.println("\t1 : Send max throttle");
	Serial.println("\t2 : Run test function\n");
}