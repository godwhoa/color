EXE := color
SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)
DEP := $(OBJ:.o=.d)

CPPFLAGS := -Isfml/include -MMD -MP
CXXFLAGS := -std=c++11 -Wall -W -pedantic
LDFLAGS  := -Lsfml/lib
LDLIBS   := -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	$(RM) $(EXE) $(OBJ) $(DEP)

ifeq "$(MAKECMDGOALS)" ""
-include $(DEP)
endif