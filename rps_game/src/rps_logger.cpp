#include "rps_logger.h"

namespace RPS {

	RPSLogger::RPSLogger() {
		clear();
	}

	void RPSLogger::clear() {
		logs.clear();

		p1_stats = {0, 0, 0};
		p2_stats = {0, 0, 0};

		p1_wins = 0;
		p2_wins = 0;
		duals = 0;
	}

	void RPSLogger::add_log(RPS::RPSLog log) {
		logs.push_back(log);
		update_rps_stat(&p1_stats, log.p1_choice);
		update_rps_stat(&p2_stats, log.p2_choice);

		RPS::OBJECT out_come = RPS::who_won(log);

		// Add to win count.  I saddly can't use a switch here ):
		if (out_come == RPS::NONE)
			return;
		if (out_come == RPS::DUAL)
			duals++;
		if (out_come == log.p1_choice)
			p1_wins++;
		if (out_come == log.p2_choice)
			p2_wins++;
	}
}
