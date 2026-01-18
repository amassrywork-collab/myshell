#Ahmed Monir Almassri -- 120220138

# Mini-shell (Operating Systems Project)
# Build file is intentionally named `makefile` (lowercase).
# Use: make -f makefile

CC      := gcc
CSTD    := -std=c11
DEFS    := -D_POSIX_C_SOURCE=200809L
WARN    := -Wall -Wextra -Wshadow -Wformat=2 -Wstrict-prototypes -Wmissing-prototypes
DBG     := -g
OPT     := -O2
CFLAGS  := $(CSTD) $(DEFS) $(WARN) $(DBG) $(OPT)
LDFLAGS :=
LDLIBS  :=

TARGET  := myshell
SRCS    := myshell.c utility.c
OBJS    := $(SRCS:.c=.o)
DEPS    := myshell.h

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Compile objects; keep header dependency explicit to avoid stale builds.
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)