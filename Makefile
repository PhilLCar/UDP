CC     = gcc
CXX    = g++
CFLAGS = -Iinc -Icommon/inc -Iclient/inc -Iserver/inc -Wall -pthread

LIBRARIES = lib/
BINARIES  = bin/
OBJECTS   = obj/
SRC       = common/src/common client/src/udpclient server/src/udpserver

ifeq "$(LANG)" "C++"
	CMP      = $(CXX)
	MAIN     = test/main.cpp
	LANG_SRC = $(SRC:=.cpp)
	TARGET   = test_cpp
	LIB      = libudp++.a
	OBJ      = *.o
	PRE      = make test LANG=C
else
	CMP      = $(CC)
	MAIN     = test/main.c
	LANG_SRC = $(SRC:=.c)
	TARGET   = test_c
	LIB      = libudp.a
	OBJ      = *.c.o
endif

OBJ_LIST  = $(LANG_SRC:=.o)

.PHONY: test clean clean-lib clean-obj clean-bin lib bin obj

%.cpp.o: %.cpp
	$(CXX) -c -o $(OBJECTS)$(notdir $@) $< $(CFLAGS)

%.c.o: %.c
	$(CC) -c -o $(OBJECTS)$(notdir $@) $< $(CFLAGS)

$(LIBRARIES)$(LIB):
	ar rcs $@ $(OBJECTS)$(OBJ)

lib: $(LIBRARIES)$(LIB)

clean-bin:
	rm -f $(BINARIES)$(TARGET)

clean-obj:
	rm -f $(OBJECTS)$(OBJ)

clean-lib:
	rm -f $(LIBRARIES)$(LIB)

clean: clean-lib clean-obj clean-bin

test: clean $(eval CFLAGS+=-g) $(OBJ_LIST)
	$(PRE)
	$(CMP) -o $(BINARIES)$(TARGET) $(MAIN) $(OBJECTS)$(OBJ) $(CFLAGS)