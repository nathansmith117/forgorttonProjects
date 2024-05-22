#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>

#include <sys/types.h>

namespace RPS {
	enum GAME_OBJECTS {
		NONE = -1,
		ROCK,
		PAPER,
		SCISSORS,
		DUAL
	};

	typedef int8_t OBJECT;

	struct RPSLog {
		OBJECT p1_choice;
		OBJECT p2_choice;
	};

	struct RPSStats {
		int rock_count;
		int paper_count;
		int scissors_count;
	};

	constexpr OBJECT ROCK_BEATS = SCISSORS;
	constexpr OBJECT PAPER_BEATS = ROCK;
	constexpr OBJECT SCISSORS_BEATS = PAPER;

	constexpr OBJECT BEATS_ROCK = PAPER;
	constexpr OBJECT BEATS_PAPER = SCISSORS;
	constexpr OBJECT BEATS_SCISSORS = ROCK;

	OBJECT what_it_beats(OBJECT obj);
	OBJECT what_beats_it(OBJECT obj);
	OBJECT who_won(OBJECT a, OBJECT b);
	OBJECT who_won(RPSLog log);
	bool is_game_object(OBJECT obj);
	int obj_to_string(OBJECT obj, char * buf, size_t buf_size);
	int update_rps_stat(RPSStats * stats, OBJECT new_obj); // Update the stats structure.
}
