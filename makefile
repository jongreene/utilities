OUT_O_DIR=build
dir_guard=@mkdir -p $(OUT_O_DIR)
CC=g++
CPPFLAGS=-std=c++11

programs := uart change_base

$(OUT_O_DIR)/%.o: %.cpp
	$(dir_guard)
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $(patsubst %.o,%,$@)

.PHONY : all clean $(programs)

uart: build/uart.o

change_base: build/change_base.o

all: clean $(programs)

clean:
	rm -rf build/
