CC = g++
CFLAGS = -I. -c -w -Wall -Werror -g -ggdb
LDFLAGS = -lm
LDLIBS = -lcheck

TEST_DIR = tests

# Guard against \r\n line endings only in Cygwin
OSTYPE := $(shell uname)
ifneq ($(OSTYPE),Darwin)
	OSTYPE := $(shell uname -o)
	ifeq ($(OSTYPE),Cygwin)
		TEST_SET_OPTS = igncr
	endif
endif

OBJS = $(wildcard *.c)

test: $(TEST_DIR)/tests.bin
	@set -o $(TEST_SET_OPTS) >/dev/null 2>&1
	@export SHELLOPTS
	@sh runtests.sh $(TEST_DIR)

$(TEST_DIR)/tests.bin: $(TEST_DIR)/tests.o emlist.o
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $(CC_SYMBOLS) $(C_FLAGS) $(INCLUDE_PATHS) -o $@ $^ $(LDLIBS)

clean:
	rm -rf *.o *.bin $(TEST_DIR)/*.o $(TEST_DIR)/*.bin
