include config.mk

CLI_PORT_SRC := $(shell find src/client -mindepth 1 -type d | sed 's/$$/.c/')
SHARE_PORT_SRC := $(shell find src/share -mindepth 1 -type d | sed 's/$$/.c/')
SRV_PORT_SRC := $(shell find src/server -mindepth 1 -type d | sed 's/$$/.c/')

CFLAGS += -Isrc/share -DCLIENT_NAME=\"$(CLI_TARGET)\" -DSERVER_NAME=\"$(SRV_TARGET)\"

SHARE_SRC := $(wildcard src/share/*.c) $(SHARE_PORT_SRC)
CLI_SRC := $(wildcard src/client/*.c) $(CLI_PORT_SRC)
SRV_SRC := $(wildcard src/server/*.c) $(SRV_PORT_SRC)

# Remove *-test.c files
SHARE_SRC := $(SHARE_SRC:%-test.c=)
CLI_SRC := $(CLI_SRC:%-test.c=)
SRV_SRC := $(SRV_SRC:%-test.c=)

# Remove main.c
CLI_SRC := $(CLI_SRC:src/client/main.c=)
SRV_SRC := $(SRV_SRC:src/server/main.c=)

CLI_OBJ := $(CLI_SRC:.c=.o)
SRV_OBJ := $(SRV_SRC:.c=.o)
SHARE_OBJ := $(SHARE_SRC:.c=.o)

SHARE_TEST_SRC := $(wildcard src/share/*-test.c)
CLI_TEST_SRC := $(wildcard src/client/*-test.c)
SRV_TEST_SRC := $(wildcard src/server/*-test.c)

SHARE_TEST_OBJ := $(SHARE_TEST_SRC:.c=.o)
CLI_TEST_OBJ := $(CLI_TEST_SRC:.c=.o)
SRV_TEST_OBJ := $(SRV_TEST_SRC:.c=.o)

SHARE_TESTS := $(SHARE_TEST_SRC:.c=)
CLI_TESTS := $(CLI_TEST_SRC:.c=)
SRV_TESTS := $(SRV_TEST_SRC:.c=)

.PHONY: clean $(SRV_PORT_SRC) $(CLI_PORT_SRC) $(SHARE_PORT_SRC)

all: $(CLI_TARGET) $(SRV_TARGET)

tests: $(SHARE_TESTS) $(CLI_TESTS) $(SRV_TESTS)

clean:
	rm -f $(CLI_TARGET) $(SRV_TARGET) $(SHARE_OBJ) $(CLI_OBJ) $(SRV_OBJ) $(SHARE_TESTS) $(CLI_TESTS) $(SRV_TESTS) $(SHARE_TEST_OBJ) $(CLI_TEST_OBJ) $(SRV_TEST_OBJ) src/client/main.o src/server/main.o $(SHARE_PORT_SRC) $(CLI_PORT_SRC) $(SRV_PORT_SRC)

$(CLI_TARGET): $(CLI_OBJ) $(SHARE_OBJ) src/client/main.o
	@echo CC -o $@
	@$(CC) $(CFLAGS) $(CLI_OBJ) $(SHARE_OBJ) src/client/main.o -o $@ $(CLI_LDFLAGS) $(SHARE_LDFLAGS)

$(SRV_TARGET): $(SRV_OBJ) $(SHARE_OBJ) src/server/main.o
	@echo CC -o $@
	@$(CC) $(CFLAGS) $(SRV_OBJ) $(SHARE_OBJ) src/server/main.o -o $@ $(SRV_LDFLAGS) $(SHARE_LDFLAGS)

$(SHARE_TESTS): $(SHARE_TEST_OBJ) $(SHARE_OBJ)
	@echo CC -o $@
	@$(CC) $(CFLAGS) $(SHARE_OBJ) $< -o $@ $(SHARE_LDFLAGS)
	@./$@ && echo "$@: success"

$(CLI_TESTS): $(CLI_TEST_OBJ) $(SHARE_OBJ) $(CLI_OBJ)
	@echo CC -o $@
	@$(CC) $(CFLAGS) $(SHARE_OBJ) $(CLI_OBJ) $< -o $@ $(SHARE_LDFLAGS) $(CLI_LDFLAGS)
	@./$@ && echo "$@: success"

$(SRV_TESTS): $(SRV_TEST_OBJ) $(SHARE_OBJ) $(SRV_OBJ)
	@echo CC -o $@
	@$(CC) $(CFLAGS) $(SHARE_OBJ) $(SRV_OBJ) $< -o $@ $(SHARE_LDFLAGS) $(SRV_LDFLAGS)
	@./$@ && echo "$@: success"

$(SRV_PORT_SRC) $(CLI_PORT_SRC) $(SHARE_PORT_SRC):
	$(eval dir=$(shell echo $@ | sed 's/.c$$//'))
	$(eval unit=$(shell basename $(dir)))
	$(eval selection=$(dir)/$($(unit)).c)
	@test -f $(selection) || (echo "usage: $(unit)=("$$(find $(dir) -type f | sed 's/\.c//;s/^.*\///')") make" > /dev/stderr; exit 1)
	@rm -f $(dir).o
	@cp -f $(selection) $@

%.o: %.c
	@echo CC $<
	@$(CC) $(CFLAGS) -c $< -o $@
