/*
 * jsi (Joystick interface) c libray
*/

#include "jsi.h"

int jsi_get_joystick(int joy_num, jsi_joystick * joystick_data) {
	DWORD dw_result;

	switch (joy_num) {
		case 1:
			dw_result = joySetCapture(GetDesktopWindow(), JOYSTICKID1, 0, FALSE);
			break;
		case 2:
			dw_result = joySetCapture(GetDesktopWindow(), JOYSTICKID2, 0, FALSE);
			break;
		default:
			return -1;
	}

	// Check for errors.
	switch (dw_result) {
		case JOYERR_UNPLUGGED:
			return -1;
		case MMSYSERR_NODRIVER:
			return -1;
		case JOYERR_NOCANDO:
			return -1;
		default:
			break;
	}

	return 0;
}

void jsi_close_joystick(jsi_joystick joystick_data) {}

int jsi_joy_count() {
	return (int)joyGetNumDevs();
}

int jsi_get_event(jsi_joystick joystick_data, struct jsi_event * event_data) {
	return -1;
}
