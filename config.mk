CLI_TARGET := pow
SRV_TARGET := powd

CFLAGS := -Wall -Wextra -pedantic -O2

CLI_LDFLAGS := -lGL
SRV_LDFLAGS :=
SHARE_LDFLAGS :=

ifeq ($(game), sdl-1.2)
	CFLAGS += -I/usr/include/SDL
	CLI_LDFLAGS += -lSDL
endif
ifeq ($(game), sdl-2.0)
	CFLAGS += -I/usr/include/SDL2
	CLI_LDFLAGS += -lSDL2
endif
