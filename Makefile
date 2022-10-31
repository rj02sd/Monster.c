OUTPUT=monster
CFLAGS=-g -Wall -Wvla -Werror -fsanitize=address

all: $(OUTPUT)

clean:
	rm -f *.o $(OUTPUT)
