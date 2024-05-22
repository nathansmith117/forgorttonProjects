#include "rps.h"

namespace RPS {
	OBJECT what_it_beats(OBJECT obj) {
		switch (obj) {
			case ROCK:
				return ROCK_BEATS;
			case PAPER:
				return PAPER_BEATS;
			case SCISSORS:
				return SCISSORS_BEATS;
			default:
				return NONE;
		}
	}

	OBJECT what_beats_it(OBJECT obj) {
		switch (obj) {
			case ROCK:
				return BEATS_ROCK;
			case PAPER:
				return BEATS_PAPER;
			case SCISSORS:
				return BEATS_SCISSORS;
			default:
				return NONE;
		}
	}

	OBJECT who_won(OBJECT a, OBJECT b) {
		// Check for weird stuff.
		if (!is_game_object(a) || !is_game_object(b))
			return NONE;
		if (a == b)
			return DUAL;

		return (what_it_beats(a) == b) ? a : b;
	}
	
	OBJECT who_won(RPSLog log) {
		return who_won(log.p1_choice, log.p2_choice);
	}

	bool is_game_object(OBJECT obj) {
		return obj == ROCK || obj == PAPER || obj == SCISSORS;
	}

	int obj_to_string(OBJECT obj, char * buf, size_t n) {
		int res;

		// Check for stuff.
		if (n <= 0 || buf == NULL)
			return -1;

		memset(buf, 0, n);

		switch (obj) {
			case ROCK:
				strncat(buf, "rock", n);
				break;
			case PAPER:
				strncat(buf, "paper", n);
				break;
			case SCISSORS:
				strncat(buf, "scissors", n);
				break;
			case DUAL:
				strncat(buf, "dual", n);
				break;
			default:
				strncat(buf, "none", n);
				break;
		}

		return 0;
	}

	int update_rps_stat(RPSStats * stats, OBJECT new_obj) {
		// Check stuff.
		if (stats == NULL)
			return -1;

		switch (new_obj) {
			case ROCK:
				stats->rock_count++;
				break;
			case PAPER:
				stats->paper_count++;
				break;
			case SCISSORS:
				stats->scissors_count++;
				break;
			default:
				return -1;
		}

		return 0;
	}
}
