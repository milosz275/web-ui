EMCC = emcc
GCC = g++

SRC_WEB = src/app.cpp src/main.cpp src/renderer.cpp src/background.cpp
OUT_WEB = build/web-ui.js

COMMON_CFLAGS = -std=c++17 -Wall -Wextra -pedantic -O3

EMCC_FLAGS = -Wno-nullability-completeness \
	-Wno-nullability-extension \
	-Wno-gnu-zero-variadic-macro-arguments \
	-Iinclude/web \
	-Iinclude/fonts \
	-I/usr/local/include \
	-I/usr/include/freetype2 \
	-I/usr/include/libpng16

LDFLAGS = -s USE_WEBGL2=1 \
	-s FULL_ES3=1 \
	-s ALLOW_MEMORY_GROWTH=1 \
	-s NO_EXIT_RUNTIME=1 \
	-s WASM=1 \
	-s USE_FREETYPE=1 \
	--shell-file src/index.html

all: web

web: $(OUT_WEB)

$(OUT_WEB): $(SRC_WEB)
	mkdir -p $(dir $(OUT_WEB))
	$(EMCC) $(COMMON_CFLAGS) $(EMCC_FLAGS) $(SRC_WEB) -o $(OUT_WEB) $(LDFLAGS)

clean:
	rm -rf build

.PHONY: all clean
