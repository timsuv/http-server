CC = clang
CFLAGS = -Wall -Wextra -std=c11
SRC = src/main.c src/server.c src/http.c src/router.c
TARGET = server

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# make run builds then runs the server
run: $(TARGET)
	./$(TARGET)

# make clean removes the compiled binary
clean:
	rm -f $(TARGET)

.PHONY: all run clean