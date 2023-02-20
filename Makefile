CFLAGS = -g3 -Wall -Wextra -Wconversion -Wcast-qual -Wcast-align -g
CFLAGS += -Winline -Wfloat-equal -Wnested-externs
CFLAGS += -pedantic -std=gnu99 -Werror

PROMPT = -DPROMPT

EXECS = passcrack

.PHONY: clean

passcrack: main.c
	$(CC) $(CFLAGS) -DPROMPT $^ -o $@
all: passcrack
clean:
	rm -f $(EXECS)