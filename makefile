TARGET=./jiaguomeng

INC=
LIB_PATH=
LIB=

CFLAGS:=-std=c++11 -Wall -g -O0 -lrt -rdynamic -fPIC -Wl,-rpath=./ $(INC) $(LIB_PATH)
CPPFLAGS:=$(CFLAGS)

SRC=$(shell echo Building.cpp Calc.cpp Config.cpp main.cpp)
OBJ=$(patsubst %.cpp,%.o,$(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $^ $(CFLAGS) $(LIB) -o $@

clean:
	rm -f $(OBJ)
	rm -f $(TARGET)
