CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -O3 -fsanitize=address,undefined
NAZVY_SOUBORU = math shell
SRC = $(foreach modul,$(NAZVY_SOUBORU),$(wildcard $(modul)/*.c) $(wildcard $(modul)/*.h))
SRC += shell.c shell.h
TARGET = devShell

# Debug 
# CFLAGS
all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

test:
	$(CC) tests/test.c math/math.c -o test
	./test
	rm -f test


debug:
	$(CC) -Wall -Wextra -Werror -g3 -O3 -fsanitize=address,undefined $(SRC) -o $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

