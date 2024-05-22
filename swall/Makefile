all: swall scomm
debug: d_swall d_scomm

swall: swall.c
	gcc -o swall swall.c
d_swall: swall.c
	gcc -o swall swall.c -g
scomm: scomm.c
	gcc -o scomm scomm.c
d_scomm: scomm.c
	gcc -o scomm scomm.c -g
install:
	sudo cp swall /usr/local/bin/
	sudo cp swall.3 /usr/share/man/man3/swall.3
	sudo cp scomm /usr/local/bin/
	sudo cp scomm.3 /usr/share/man/man3/scomm.3
uninstall:
	sudo rm /usr/local/bin/swall
	sudo rm /usr/share/man/man3/swall.3
	sudo rm /usr/local/bin/scomm
	sudo rm /usr/share/man/man3/scomm.3
reinstall: uninstall install
clean:
	rm swall scomm
