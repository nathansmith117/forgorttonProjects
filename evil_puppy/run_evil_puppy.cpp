#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>

#ifdef _WIN32
	#include <Windows.h>
#else
	#include <unistd.h>
#endif

#define least_time 60
#define max_time 600

using namespace std;

int random_range(int x, int y) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(x, y);

	return distr(gen);
}

int main() {

	while (true) {
		time_t when_it_happens = random_range(least_time, max_time);
		sleep(when_it_happens);
		system("/usr/local/bin/fluffy_puppy");
	}

	return 0;
}
