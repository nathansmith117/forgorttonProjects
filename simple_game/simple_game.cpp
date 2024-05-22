// FLTK headers.
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Output.H>
#include <FL/fl_draw.H>
#include <FL/x.H>

// C/C++ headers.
#include <cstdio>
#include <cstdlib>
#include <random>
#include <string>

#define MAX_ROCKS 3
#define MAX_BULLETS 5

#define UPDATE_SPEED 60.0
#define FPS 120.0

#define PLAYER_SPEED 10
#define BULLET_SPEED 10
#define METDOR_SPEED 2

#define BULLET_WIDTH 3
#define BULLET_HEIGHT 10
#define BULLET_COLOR FL_BLACK

#define PLAYER_WIDTH 100
#define PLAYER_HEIGHT 100

#define METDOR_MAX 200
#define METDOR_MIN 50

#define SCORE_BOX_WIDTH 200

struct Direction {
	bool right, left;
};

struct MainData {
	Fl_Double_Window * win;
	Fl_PNG_Image * rock_image;
	Fl_PNG_Image * ship_image;
	Fl_Widget * player;
	Fl_Output * score_box;

	Fl_Widget * metdors[MAX_ROCKS + 1];
	int metdor_count = -1;

	Fl_Widget * bullets[MAX_BULLETS + 1];
	int bullet_count = -1;

	int score = 0;
};

int random_range(int x, int y) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(x, y);

	return distr(gen);
}

bool object_collision(Fl_Widget * obj1, Fl_Widget * obj2) {
	if (obj1->x() + obj1->w() >= obj2->x() &&
			obj1->x() <= obj2->x() + obj2->w() &&
			obj1->y() + obj1->h() >= obj2->y() &&
			obj1->y() <= obj2->y() + obj2->h())
		return true;

	return false;
}

class Metdor : public Fl_Widget {
	public:
		Metdor(MainData * md, int X, int Y, int W, int H) : Fl_Widget(X, Y, W, H) {
			mdata = md;
		}

		void draw();
	private:
		MainData * mdata;
};

void Metdor::draw() {
	if (!active())
		return;

	image()->draw(x(), y());
}

class Player : public Fl_Widget {
	public:
		Player(MainData * md, int X, int Y) : Fl_Widget(X, Y, PLAYER_WIDTH, PLAYER_HEIGHT) {
			mdata = md;
		}

		void draw();
	private:
		MainData * mdata;
};

void Player::draw() {
	image()->copy(w(), h())->draw(x(), y());
}

class Bullet : public Fl_Widget {
	public:
		Bullet(MainData * md, int X, int Y) : Fl_Widget(X, Y, BULLET_WIDTH, BULLET_HEIGHT) {
			mdata = md;
			color(BULLET_COLOR);
		}

		void draw();
	private:
		MainData * mdata;
};

void Bullet::draw() {
	if (!active())
		return;

	fl_rectf(x(), y(), w(), h(), color());
}

class GameWindow : public Fl_Double_Window {
	public:
		GameWindow(MainData * md, int W, int H, const char * l=0) : Fl_Double_Window(W, H, l) {
			mdata = md;
			dir = {false, false};

			Fl::add_timeout(1.0 / UPDATE_SPEED, time_cb, (void*)this);
			Fl::add_timeout(1.0 / FPS, draw_loop, (void*)this);
		}

		static void time_cb(void * d) {
			GameWindow * win = (GameWindow*)d;
			win->real_time_cb();
			Fl::repeat_timeout(1.0 / UPDATE_SPEED, time_cb, d);
		}
		
		static void draw_loop(void * d) {
			GameWindow * win = (GameWindow*)d;
			win->redraw();
			Fl::repeat_timeout(1.0 / FPS, draw_loop, d);
		}

		void real_time_cb();

		int handle(int event);
	private:
		MainData * mdata;
		Direction dir;
};

void GameWindow::real_time_cb() {
	int i, b;
	int rock_size;

	// Update ship.
	if (dir.right && mdata->player->x() + mdata->player->w() < w())
		mdata->player->position(mdata->player->x() + PLAYER_SPEED, mdata->player->y());
	if (dir.left && mdata->player->x() > 0)
		mdata->player->position(mdata->player->x() - PLAYER_SPEED, mdata->player->y());

	// Update bullet.
	if (mdata->bullet_count != -1) {

		for (i = 0; i < MAX_BULLETS; i++)
			mdata->bullets[i]->position(mdata->bullets[i]->x(), 
					mdata->bullets[i]->y() - BULLET_SPEED);

		// Remove bullets that leave window.
		if (mdata->bullets[mdata->bullet_count]->y() <= 0) {
			mdata->bullets[mdata->bullet_count]->deactivate();
			mdata->bullet_count--;
		}
	}

	// Update metdors.
	if (mdata->metdor_count == -1) {

		for (i = 0; i < MAX_ROCKS; i++) {
			mdata->metdor_count++;
			rock_size = random_range(METDOR_MIN, METDOR_MAX);

			mdata->metdors[i]->resize(random_range(0, w() - rock_size), -rock_size, rock_size, rock_size);
			mdata->metdors[i]->image(mdata->rock_image->copy(rock_size, rock_size));
			mdata->metdors[i]->activate();
		}

	} else {

		if (mdata->metdor_count != -1) {
			for (i = 0; i < MAX_ROCKS; i++) {

				// Check for collision with bullet.
				for (b = 0; b < MAX_BULLETS; b++) {

					if (object_collision(mdata->bullets[b], mdata->metdors[i]) 
								&& mdata->bullets[b]->active() 
								&& mdata->metdors[i]->active()) {

						mdata->bullets[b]->deactivate();
						mdata->metdors[i]->deactivate();
						mdata->score++;
						mdata->score_box->value(std::to_string(mdata->score).c_str());
					}
				}

				// Collision with player.
				if (object_collision(mdata->metdors[i], mdata->player) 
						&& mdata->metdors[i]->active()) {
					mdata->score -= MAX_ROCKS;
					mdata->metdor_count = -1;
					mdata->score_box->value(std::to_string(mdata->score).c_str());

					for (b = 0; b < MAX_ROCKS; b++)
						mdata->metdors[b]->deactivate();

					break;
				}

				mdata->metdors[i]->position(mdata->metdors[i]->x(), 
						mdata->metdors[i]->y() + METDOR_SPEED);
			}

			if (mdata->metdors[mdata->metdor_count]->y() >= h()) {

				if (mdata->metdors[mdata->metdor_count]->active()) {
					mdata->score--;
					mdata->score_box->value(std::to_string(mdata->score).c_str());
				}

				mdata->metdors[mdata->metdor_count]->deactivate();
				mdata->metdor_count--;
			}
		}

	}
}

int GameWindow::handle(int event) {
	switch (event) {
		case FL_UNFOCUS:
		case FL_FOCUS:
			return 1;
		case FL_KEYDOWN:
			
			switch (Fl::event_key()) {
				case FL_Escape:
					hide();
				case ' ':
					if (mdata->bullet_count >= MAX_BULLETS - 1)
						break;

					mdata->bullet_count++;

					mdata->bullets[mdata->bullet_count]->position(
							mdata->player->x() + (mdata->player->w() / 2), 
							mdata->player->y());
					mdata->bullets[mdata->bullet_count]->activate();

					break;
				case FL_Right:
					dir.right = true;
					break;
				case FL_Left:
					dir.left = true;
					break;
				default:
					break;
			}

			return 1;
		case FL_KEYUP:

			switch (Fl::event_key()) {
				case FL_Right:
					dir.right = false;
					break;
				case FL_Left:
					dir.left = false;
					break;
				default:
					break;
			}

			return 1;
		default:
			return 0;
	}
}

int main(int argc, char ** argv) {
	int i;
	MainData mdata;

	mdata.win = new GameWindow(&mdata, Fl::w() / 2, Fl::h() / 2, "Game");

	// Load images.
#ifdef _WIN32
	mdata.rock_image = new Fl_PNG_Image("images\\rock.png");
#else
	mdata.rock_image = new Fl_PNG_Image("images/rock.png");
#endif

	if (mdata.rock_image->fail()) {
		perror("Error loading rock.png");
		exit(0);
	}

#ifdef _WIN32
	mdata.ship_image = new Fl_PNG_Image("images\\ship.png");
#else
	mdata.ship_image = new Fl_PNG_Image("images/ship.png");
#endif

	if (mdata.ship_image->fail()) {
		perror("Error loading ship.png");
		exit(0);
	}

	// Add player.
	mdata.player = new Player(&mdata, (mdata.win->w() / 2) - (PLAYER_WIDTH / 2), 
			mdata.win->h() - PLAYER_HEIGHT);
	mdata.player->image(mdata.ship_image);

	// Add Bullets.
	for (i = 0; i < MAX_BULLETS; i++) {
		mdata.bullets[i] = new Bullet(&mdata, 0, 0);
		mdata.bullets[i]->deactivate();
	}

	// Add Metdors.
	for (i = 0; i < MAX_ROCKS; i++) {
		mdata.metdors[i] = new Metdor(&mdata, 0, 0, 0, 0);
		mdata.metdors[i]->deactivate();
	}

	// Score box.
	mdata.score_box = new Fl_Output((mdata.win->w() / 2) - (SCORE_BOX_WIDTH / 2), 
			0, SCORE_BOX_WIDTH, 30, "Score");
	mdata.score_box->value(std::to_string(mdata.score).c_str());


	mdata.win->end();
	mdata.win->resizable(mdata.win);

	mdata.win->show(argc, argv);
	return Fl::run();
}
