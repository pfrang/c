RAYLIB_SRC = ../raylib/src
CFLAGS     = -O2 -I$(RAYLIB_SRC)

LINUX_CC   = gcc
LINUX_LIBS = -lGL -lm -lpthread -ldl -lrt -lX11

WIN_CC     = x86_64-w64-mingw32-gcc
WIN_AR     = x86_64-w64-mingw32-ar
WIN_LIBS   = -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -static -static-libgcc

.PHONY: all linux windows raylib-linux raylib-windows clean

all: linux

# ── Linux ────────────────────────────────────────────────────────────────────

linux: raylib-linux game_linux

raylib-linux:
	$(MAKE) -C $(RAYLIB_SRC) clean
	$(MAKE) -C $(RAYLIB_SRC) PLATFORM=PLATFORM_DESKTOP CC=$(LINUX_CC)

game_linux: main.c
	$(LINUX_CC) $(CFLAGS) main.c -o game_linux $(RAYLIB_SRC)/libraylib.a $(LINUX_LIBS)

# ── Windows (cross-compile) ──────────────────────────────────────────────────

windows: raylib-windows game_windows.exe

raylib-windows:
	$(MAKE) -C $(RAYLIB_SRC) clean
	$(MAKE) -C $(RAYLIB_SRC) PLATFORM=PLATFORM_DESKTOP \
		OS=Windows_NT CC=$(WIN_CC) AR=$(WIN_AR) \
		RAYLIB_RELEASE_PATH=. RAYLIB_LIB_NAME=raylib_win

game_windows.exe: main.c
	$(WIN_CC) $(CFLAGS) main.c -o game_windows.exe $(RAYLIB_SRC)/libraylib_win.a $(WIN_LIBS)

# ── Clean ────────────────────────────────────────────────────────────────────

clean:
	$(MAKE) -C $(RAYLIB_SRC) clean
	rm -f game_linux game_windows.exe
