# See LICENSE file for copyright and license details.

include config.mk

SRC = main.c
OBJ = $(SRC:.c=.o)

all: sarsa

sarsa: $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ)

.c.o:
	@$(CC) $(CFLAGS) -c $<

clean:
	@rm -f sarsa $(OBJ)
