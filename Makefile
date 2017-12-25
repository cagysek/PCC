CC = gcc
BIN = dfs.exe
OBJ = date.o edge.o node.o path.o reader.o dfs.o main.o

all: $(BIN) clean

$(BIN): $(OBJ)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $< -o $@
  
clean:	
	rm -f *.o
