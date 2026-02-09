R2_INCDIR := $(shell r2 -H R2_INCDIR 2>/dev/null)
R2_LIBDIR := $(shell r2 -H R2_LIBDIR 2>/dev/null)
CC      ?= gcc
AR      ?= ar
CFLAGS  += -Wall -Wextra -std=c99 -fPIC -I$(R2_INCDIR) -Isrc
LDFLAGS += -L$(R2_LIBDIR) -lr_core -lr_cons -lr_util

SRC     := $(wildcard src/*.c)
OBJ     := $(SRC:.c=.o)
LIB     := libr2ui.a

EXAMPLES_SRC := $(wildcard examples/*.c)
EXAMPLES_BIN := $(EXAMPLES_SRC:.c=.so)

all: lib examples

lib: $(LIB)

$(LIB): $(OBJ)
	$(AR) rcs $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

examples: lib $(EXAMPLES_BIN)

examples/%.so: examples/%.c $(LIB)
	$(CC) $(CFLAGS) -shared -fPIC $< -o $@ -L. -lr2ui $(LDFLAGS)

clean:
	rm -f $(OBJ) $(LIB) $(EXAMPLES_BIN)

.PHONY: all lib examples clean
