CPP=g++
CPPFLAGS= -g3 -Wall -m32

TARGET=test_stroke

LIBRARY_SRC= \
	    arrayTernarySearch.cpp \
	    main.cpp \
	    string.cpp

all: $(TARGET) test

test: $(TARGET)
	./$(TARGET)

$(TARGET): $(LIBRARY_SRC)
	@$(CPP) $(CPPFLAGS) -o $@ $?


clean:
	-rm -rf $(TARGET) user.dic

.PHONY: clean
