/*
 * jsi (Joystick interface) c libray
*/

#ifdef _WIN32

#include <Windows.h>

#else

// Linux header.
#include <linux/types.h>
#include <linux/input.h>
#include <linux/joystick.h>

// Unix headers.
#include <fcntl.h>
#include <unistd.h>

#endif

// OS headers.
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

// C.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#ifndef JSI_H
#define JSI_H

#define JSI_VERSION "Still in making"

#define JSI_TRUE 1
#define JSI_FALSE 0
#define JSI_NAME_MAX 128

#define JSI_UP 0x0
#define JSI_DOWN 0x1

#define JSI_TYPE_BUTTON 0x1
#define JSI_TYPE_AXIS 0x2
#define JSI_TYPE_INIT 0x80

struct jsi_joy_layout {
	int axes;
	int buttons;
	char name[JSI_NAME_MAX];
};

typedef struct {
	int fd;
	int num;
	int joystick_count_init;
	struct jsi_joy_layout layout;
} jsi_joystick;

struct jsi_event {
	int value;
	int type;
	int num;
};

int jsi_get_joystick(int joy_num, jsi_joystick * joystick_data);
void jsi_close_joystick(jsi_joystick joystick_data);
int jsi_joy_count();
int jsi_get_event(jsi_joystick joystick_data, struct jsi_event * event_data);

#endif // JSI_H
