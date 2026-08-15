SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)
BIN=code

$(BIN):$(OBJ)
	g++ -o $@ $^
%.o:%.cpp
	g++ -c $<
.PHONY:clean
clean:
	rm -f $(BIN) $(OBJ)

