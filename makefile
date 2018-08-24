CC = g++
CFLAGS = -Wall -std=c++1y
DEPS = util.h list.h cursor_control.h normal_mode.h keymap.h
OBJ = util.o list.o normal_mode.o cursor_control.o main.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

trex: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o trex	

