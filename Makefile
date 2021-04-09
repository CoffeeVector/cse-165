all: main_cmd.out

%.out: %.cpp
	g++ -o $@ -g $<

main_cmd.out: Tetris.h
