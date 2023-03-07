OUT1=out1.res

all:
	mkdir -p build
	cd build && \
	cmake -G Ninja .. && \
	ninja && \
	clang -flegacy-pass-manager -Xclang -load -Xclang debug/libDebugPass.so ../../something.c 2>|$(OUT1) && \
	sed -i '/```{$(OUT1)}/,/```/{//!d;}' ../README.md && sed -i '/```{$(OUT1)}/r./$(OUT1)' ../README.md