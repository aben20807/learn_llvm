include ../consts.mk

all:
	$(Q)mkdir -p build
	$(Q)cd build && \
	cmake -G Ninja .. && \
	ninja && \
	clang -flegacy-pass-manager -Xclang -load -Xclang debug/libDebugPass.so -g ../../something.c 2>|$(OUT1) && \
	sed -i '/```{$(OUT1)}/,/```/{//!d;}' ../README.md && sed -i '/```{$(OUT1)}/r./$(OUT1)' ../README.md
