#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>

#include "rps.h"
#include "rps_logger.h"

RPS::OBJECT char_to_obj(char input_char) {
	switch (input_char) {
		case 'r':
			return RPS::ROCK;
		case 'p':
			return RPS::PAPER;
		case 's':
			return RPS::SCISSORS;
		default:
			return RPS::NONE;
	}
}

int main() {
	char buf[NAME_MAX];

	char input_buf[NAME_MAX];
	char input_char;

	RPS::RPSLogger * game_logger = new RPS::RPSLogger();
	RPS::RPSLog game_log;
	RPS::OBJECT out_come;

	while (!feof(stdin)) {
		// Player one.
		printf("Enter p1 value rps: ");
		memset(input_buf, 0, NAME_MAX);
		fgets(input_buf, NAME_MAX, stdin);
		input_char = input_buf[0];

		game_log.p1_choice = char_to_obj(input_char);

		// Player two.
		printf("Enter p2 value rps: ");
		memset(input_buf, 0, NAME_MAX);
		fgets(input_buf, NAME_MAX, stdin);
		input_char = input_buf[0];

		game_log.p2_choice = char_to_obj(input_char);

		// Get out come.
		out_come = RPS::who_won(game_log);
		RPS::obj_to_string(out_come, buf, NAME_MAX);

		game_logger->add_log(game_log);

		printf("Out come: %s, p1 wins: %d, p2 wins: %d, duals: %d\n", buf, game_logger->get_p1_wins(), game_logger->get_p2_wins(), game_logger->get_duals());
	}

	return 0;
}
