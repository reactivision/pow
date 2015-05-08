CLI_TARGET := pow
SRV_TARGET := powd

CFLAGS := -Wall -Wextra -pedantic -O2

CLI_LDFLAGS := -lSDL -lGL
SRV_LDFLAGS :=
SHARE_LDFLAGS :=
