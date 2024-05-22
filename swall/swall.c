#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int file_exis(const char * file_name) {
	FILE * fp;

	if ((fp = fopen(file_name, "r"))) {
		fclose(fp);
		return 1;
	}

	return 0;
}

int main(int argc, char ** argv) {
	int i;

	if (argc < 2) {
		fputs("No arguments found.\n", stderr);
		return -1;
	}

	size_t the_size = strlen(argv[1]);
	char msg[the_size];
	memset(msg, 0, the_size);

	strncat(msg, argv[1], sizeof(msg));

	for (i = 2; i < argc; i++) {
		strncat(msg, " ", the_size);
		strncat(msg, argv[i], the_size);
	}

	char com[100];
	char file_msg[15];

	for (i = 0; i < 100; i++) {
		snprintf(file_msg, sizeof(file_msg), "/dev/pts/%d", i);

		if (file_exis(file_msg)) {
			snprintf(com, sizeof(com), "%s > %s", msg, file_msg);
			system(com);
		}

		snprintf(file_msg, sizeof(file_msg), "/dev/tty%d", i);

		if (file_exis(file_msg)) {
			snprintf(com, sizeof(com), "%s > %s", msg, file_msg);
			system(com);
		}
	}


	return 0;
}
