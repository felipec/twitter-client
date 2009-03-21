CC := gcc

EXTRA_WARNINGS := -Wextra -ansi -std=c99 -Wno-unused-parameter

TG_LIBS := $(shell pkg-config --libs twitter-glib-1.0 gthread-2.0)
TG_CFLAGS := $(shell pkg-config --cflags twitter-glib-1.0 gthread-2.0)

test: test.o
test: CFLAGS := $(TG_CFLAGS)
test: LIBS := $(TG_LIBS)
binaries += test

all: $(binaries)

$(binaries):
	$(CC) $(LDFLAGS) $(LIBS) -o $@ $^

%.o:: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(binaries)
	find . -name "*.o" | xargs rm -rf
