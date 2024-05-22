/*
 * jsi (Joystick interface) c libray
*/

#include "jsi.h"
#include <stdio.h>
#include <signal.h>

jsi_joystick a_joystick;

void handle_sig(int sig) {
	jsi_close_joystick(a_joystick);
	putchar('\n');
	exit(0);
}

int main() {
	signal(SIGINT, handle_sig);

	puts("test");
	printf("joystick count: %d\n", jsi_joy_count());

	if (jsi_get_joystick(0, &a_joystick) == -1) {
		perror("Couldn't get joystick");
		return -1;
	}

	printf("axes: %d, buttons: %d, name: %s\n", a_joystick.layout.axes, 
			a_joystick.layout.buttons, a_joystick.layout.name);

	struct jsi_event a_event;

	while (JSI_TRUE) {

		if (jsi_get_event(a_joystick, &a_event) == -1) {
			perror("Error getting input");
			return -1;
		}

		printf("value: %hx, type: %hx, num: %hx\n", a_event.value, a_event.type, a_event.num);
	}

	jsi_close_joystick(a_joystick);
	return 0;
}
