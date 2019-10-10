CXX=g++

SOURCES:=./*.cpp

OBJS:=./*.o

all: $(OBJS)
	$(CXX) -o main $+ -g -std=c++14 -Wall -Wextra

%.o: %.cpp
	$(CXX) -std=c++14 -Wall -Wextra -g -c $+
