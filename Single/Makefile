CXX=g++

SOURCES:=./*.cpp

OBJS:=./*.o

all: $(OBJS)
	$(CXX) -o main $+ -O3 -std=c++11 -Wall -Wextra

%.o: %.cpp
	$(CXX) -std=c++11 -Wall -Wextra -O3 -c $+
