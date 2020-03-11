TOP:=$(shell pwd)/
BIN:=$(TOP)bin/
SRC:=$(TOP)src/

.PHONY:all

all: $(BIN)vector $(BIN)map
$(BIN)%:$(SRC)%.cpp
	mkdir -p $(dir $@)
	g++ -o $@ $^
.PHONY:clean
.DELETE_ON_ERROR:
.SECONDARY:
