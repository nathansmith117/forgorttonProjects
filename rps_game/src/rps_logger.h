#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "rps.h"

namespace RPS {

	class RPSLogger {
		public:
			RPSLogger();

			void clear(); // Clear everything.
			size_t size() { return logs.size(); }
			void add_log(RPS::RPSLog log);

			RPS::RPSStats get_p1_stats() { return p1_stats; }
			void set_p1_stats(RPS::RPSStats new_stats) { p1_stats = new_stats; }

			RPS::RPSStats get_p2_stats() { return p2_stats; }
			void set_p2_stats(RPS::RPSStats new_stats) { p2_stats = new_stats; }

			int get_p1_wins() { return p1_wins; }
			int get_p2_wins() { return p2_wins; }
			int get_duals() { return duals; }
		private:
			std::vector<RPS::RPSLog> logs;

			RPS::RPSStats p1_stats;
			RPS::RPSStats p2_stats;

			int p1_wins;
			int p2_wins;
			int duals;
	};
}
