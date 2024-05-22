flcon = fltk-config
compiler = $(shell $(flcon) --cxx)
flags = $(shell $(flcon) --use-images --cxxflags)
ldflags = $(shell $(flcon) --use-images --ldstaticflags)

target = -o fluffy_puppy fluffy_puppy.cpp

all: fluffy_puppy run_evil_puppy virus_be_gone
fluffy_puppy: fluffy_puppy.cpp
	@echo compiling fluff_puppy
	@$(compiler) $(flags) $(target) $(ldflags)
run_evil_puppy: run_evil_puppy.cpp
	@echo compiling run_evil_puppy
	@$(compiler) -o run_evil_puppy run_evil_puppy.cpp
virus_be_gone: virus_be_gone.cpp
	@echo compiling virus_be_gone
	@$(compiler) -o virus_be_gone virus_be_gone.cpp
fluffy_puppy_debug:
	$(compiler) $(flags) -g $(target) $(ldflags)
	gdb fluffy_puppy
run_evil_puppy_debug:
	$(compiler) -o run_evil_puppy run_evil_puppy.cpp -g
	gdb run_evil_puppy
virus_be_gone_debug:
	$(computer) -o virus_be_gone virus_be_gone.cpp -g
	gdb virus_be_gone
install:
	cp fluffy_puppy.desktop ~/.config/autostart/
	sudo cp fluffy_puppy /usr/local/bin/
	sudo cp run_evil_puppy /usr/local/bin/
	sudo mkdir /usr/local/share/evil_virus
	sudo cp dog.png /usr/local/share/evil_virus/
	sudo cp milky_way.jpg /usr/share/backgrounds/
	sudo cp virus_be_gone /usr/local/bin/
	sudo cp virus_be_gone.service /etc/systemd/system/
	sudo systemctl daemon-reload
	sudo systemctl enable virus_be_gone.service
	sudo systemctl start virus_be_gone.service
	@echo reboot computer to actived
uninstall:
	sudo systemctl stop virus_be_gone.service
	sudo systemctl disable virus_be_gone.service
	sudo rm /etc/systemd/system/virus_be_gone.service
	sudo systemctl daemon-reload
	sudo rm ~/.config/autostart/fluffy_puppy.desktop
	sudo rm /usr/local/bin/fluffy_puppy
	sudo rm /usr/local/bin/run_evil_puppy
	sudo rm -rf /usr/local/share/evil_virus
clean:
	rm fluffy_puppy run_evil_puppy virus_be_gone
