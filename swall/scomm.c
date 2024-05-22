#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int echomod = 0;
	char msg[50], com[100];

	while (!feof(stdin)) {

		if (echomod)
			printf("echo ");
		else
			printf("--> ");

		memset(msg, 0, sizeof(msg));
		memset(com, 0, sizeof(com));
		fgets(msg, sizeof(msg), stdin);

		if (!strncmp(msg,"\n", sizeof(msg)))
			continue;
		else if (!strncmp(msg, "exit\n", sizeof(msg))) {

			if (echomod) {
				echomod = 0;
				continue;
			}

			break;
		} else if (!strncmp(msg, "echomod\n", sizeof(msg))) {

			if (echomod)
				echomod = 0;
			else
				echomod = 1;

			continue;
		} else if (!strncmp(msg, "clsme\n", sizeof(msg))) {
			system("clear");
			continue;
		} else if (!strncmp(msg, "clear\n", sizeof(msg))) {
			system("swall clear");
			continue;
		}

		if (echomod)
			snprintf(com, sizeof(com), "swall echo %s", msg);
		else
			snprintf(com, sizeof(com), "swall %s", msg);

		system(com);
	}

	return 0;
}
