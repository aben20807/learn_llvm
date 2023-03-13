include ../consts.mk

all:
	$(Q)mkdir -p build
	$(Q)cd build && \
	cmake -G Ninja .. && \
	ninja && \
	clang -flegacy-pass-manager -Xclang -load -Xclang inject/libInjectPass.so ../../something.c 2>|$(OUT1) && \
	./a.out 1>|$(OUT2) 2>|$(OUT3) && \
	sed -i '/```{$(OUT1)}/,/```/{//!d;}' ../README.md && sed -i '/```{$(OUT1)}/r./$(OUT1)' ../README.md && \
	sed -i '/```{$(OUT2)}/,/```/{//!d;}' ../README.md && sed -i '/```{$(OUT2)}/r./$(OUT2)' ../README.md && \
	sed -i '/```{$(OUT3)}/,/```/{//!d;}' ../README.md && sed -i '/```{$(OUT3)}/r./$(OUT3)' ../README.md
