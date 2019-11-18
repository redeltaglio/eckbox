main: eckbox.cpp eckboxcalib.cpp eckbox.h bw.cpp
	g++ -o ./eckbox ./eckbox.cpp -O3 -lvga
	g++ -o ./eckboxcalib ./eckboxcalib.cpp -O3
	g++ -o ./bw ./bw.cpp -O3 -lvga
install:
	cp ./eckbox /usr/local/bin/eckbox
	cp ./eckboxcalib /usr/local/bin/eckboxcalib
	cp ./eckbox.man /usr/man/man1/eckbox.1
