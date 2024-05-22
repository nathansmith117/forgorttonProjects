/*
 * The most evil virus of all time.
 * Please mod this virus and make it as bad as possable.
*/

// Fltk header.
#include "FL/Fl.H"
#include "FL/Fl_Double_Window.H"
#include "FL/Fl_PNG_Image.H"
#include <FL/Fl_Box.H>
#include <FL/Fl_Output.H>
#include <FL/Enumerations.H>

// C/C++ libary.
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <random>

using namespace std;

// Make sure the path ends in '/' or '\' on windows.
#define main_dir "./"
#define image_name "dog.png"
//#define make_fullscreen

// Random range.
#define range_min 3
#define range_max 15

// Global Varibles.
int rub_time;
Fl_Double_Window * win;
Fl_Box * the_dogs_msg;
Fl_Box * longer_box;
Fl_Output * output_box;

int funny_strings_size = 3;
const char funny_strings[][25] = {
	"You know you want to.   ",
	"The puppy is waiting.   ",
	"You don't have a choice."
};

int random_range(int x, int y) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(x, y);

	return distr(gen);
}

const char * random_msg() {
	return funny_strings[random_range(0, funny_strings_size - 1)];
}

class DogBox : public Fl_Box {
	public:
		DogBox(int X, int Y, int W, int H, const char * l=0) : 
			Fl_Box(X, Y, W, H, l) {
				started = 0;
				failes = 0;
			}

		int handle(int event);
	private:
		time_t started;
		int failes;
};

int DogBox::handle(int event) {
	switch(event) {
		case FL_PUSH:
			return 1;
		case FL_RELEASE:
			if (time(NULL) - started >= rub_time && started)
				win->hide();

			started = 0;

			if (failes == 2) {
				const char msg_format[] = "At least %d seconds for this dog.";
				char the_msg[strlen(msg_format) + 3];

				sprintf(the_msg, msg_format, rub_time);
				output_box->value(the_msg);
				failes = 3;
				return 1;
			} else if (failes >= 3)
				return 1;

			// Make sure the value changes.
			char old_value[255], new_value[255];
			memset(old_value, 0, sizeof(old_value));
			strcat(old_value, output_box->value());

			while (true) {
				memset(new_value, 0, sizeof(new_value));
				strcat(new_value, random_msg());

				if (strcmp(old_value, new_value))
					break;
			}

			output_box->value((const char*)new_value);
			longer_box->show();
			failes++;
			return 1;
		case FL_DRAG:
			if (!started)
				started = time(NULL);

			return 1;
		default:
			return 0;
	}
}

void window_callback(Fl_Widget * w, void * d) {
	output_box->value("You can't close me!");
}

int main(int argv, char ** args) {
	rub_time = random_range(range_min, range_max);

	// Getting screen size.
	int screen_width, screen_height, x, y;
	Fl::screen_xywh(x, y, screen_width, screen_height);

	// Opening dog image file.
	char image_path[255];
	sprintf(image_path, "%s%s", main_dir, image_name);
	Fl_PNG_Image * dog_image = new Fl_PNG_Image((const char*)image_path);

	if (dog_image->fail()) {
		fprintf(stderr, "Couldn't load '%s'.\n", image_path);
		return 1;
	}

	// Currenting image and widgets.
	int dWidth, dHeight;
	int cur_x, cur_y;
	dWidth = dog_image->w();
	dHeight = dog_image->h();
	cur_x = (screen_width / 2) - dWidth;
	cur_y = (screen_height / 2) - dHeight;

#ifndef make_fullscreen
	screen_width = dWidth * 2;
	screen_height = dHeight * 2;
	cur_x = 0;
	cur_y = 0;
#endif

	// Opening window.
	win = new Fl_Double_Window(screen_width, screen_height, "Rub my belly");

	// Dog box.
	Fl_Box * dog_box = new DogBox(dWidth / 2 + cur_x, 
			dHeight / 2 + cur_y, dWidth, dHeight);
	dog_box->image(dog_image);

	// Text.
	const char the_msg[] = "Rub my belly!"; 
	int text_size = dWidth / strlen(the_msg) * 1.5;
	
	the_dogs_msg = new Fl_Box(dog_box->x(), text_size + cur_y, 
			dWidth, text_size + 10, the_msg);
	the_dogs_msg->box(FL_ROUNDED_BOX);
	the_dogs_msg->labeltype(FL_SHADOW_LABEL);
	the_dogs_msg->labelsize(text_size);

	text_size /= 2;
	output_box = new Fl_Output(dog_box->x(), 
			the_dogs_msg->h() + the_dogs_msg->y() + 10, 
			dWidth, text_size + 10);
	output_box->labelsize(text_size);
	output_box->value(random_msg());

	// Longer box.
	text_size *= 2;
	longer_box = new Fl_Box(5 + cur_x, 5 + cur_y, 5 * text_size, text_size + 10, "Longer!");
	longer_box->labelsize(text_size);
	longer_box->hide();

	win->end();
	win->callback(window_callback);

#ifdef make_fullscreen
	win->fullscreen();
#endif

	win->show(argv, args);
	return Fl::run();
}
