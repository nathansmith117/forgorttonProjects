/*
 * jsi (Joystick interface) c libray
*/

#include "jsi.h"

int jsi_get_joystick(int joy_num, jsi_joystick * joystick_data) {
	int fd;
	char dev_path[NAME_MAX];

	// Format path.
	snprintf(dev_path, sizeof(dev_path), "/dev/input/js%d", joy_num);

	fd = open(dev_path, O_RDONLY);

	if (fd == -1)
		return -1;

	joystick_data->fd = fd;
	joystick_data->num = joy_num;
	joystick_data->joystick_count_init = jsi_joy_count();

	// Get axes.
	char num_of_axes;

	if (ioctl(fd, JSIOCGAXES, &num_of_axes) == -1)
		return -1;

	joystick_data->layout.axes = (int)num_of_axes;

	// Get buttons.
	char num_of_buttons;

	if (ioctl(fd, JSIOCGBUTTONS, &num_of_buttons) == -1)
		return -1;
	
	joystick_data->layout.buttons = (int)num_of_buttons;

	// Get name.
	char joy_name[JSI_NAME_MAX];

	if (ioctl(fd, JSIOCGNAME(JSI_NAME_MAX), joy_name) == -1)
		return -1;

	strncat(joystick_data->layout.name, joy_name, JSI_NAME_MAX);

	return 0;
}

void jsi_close_joystick(jsi_joystick joystick_data) {
	close(joystick_data.fd);
}

int jsi_joy_count() {
	int joy_count = 0;
	char dev_path[NAME_MAX];
	struct stat dev_stat;

	while (1) {
		// Format path.
		snprintf(dev_path, sizeof(dev_path), "/dev/input/js%d", joy_count);

		if (stat(dev_path, &dev_stat) == -1)
			return joy_count;

		joy_count++;
	}

	return joy_count;
}

int jsi_get_event(jsi_joystick joystick_data, struct jsi_event * event_data) {
	struct js_event jse;

	if (read(joystick_data.fd, &jse, sizeof(jse)) == -1)
		return -1;

	event_data->value = (int)jse.value;
	event_data->type = (int)jse.type;
	event_data->num = (int)jse.number;

	return 0;
}
