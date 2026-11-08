CXX=g++
CPPFLAGS = -Iincludes
SRCS = src/main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = bin/main
DEBUG = bin/debug

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(OBJS) $(TARGET) $(DEBUG)

run: all
	./$(TARGET)

debug: CPPFLAGS += -g
debug: $(OBJS)
	$(CXX) $(OBJS) -o $(DEBUG)

run_debug: debug
	./$(DEBUG)
gdb: debug
	gdb $(DEBUG)
