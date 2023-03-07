OUT1=out1.res
OUT2=out2.res
OUT3=out3.res

all:
	mkdir -p build
	cd build && \
	cmake -G Ninja .. && \
	ninja && \
	clang -flegacy-pass-manager -Xclang -load -Xclang pgo/libPGOPass.so -fprofile-instr-generate ../../something.c 2>|$(OUT1) && \
	./a.out 1>|$(OUT2) && \
	llvm-profdata merge -o default.profdata default.profraw && \
	clang -flegacy-pass-manager -Xclang -load -Xclang pgo/libPGOPass.so -fprofile-instr-use=default.profdata ../../something.c 2>|$(OUT3) && \
	sed -i '/```{$(OUT1)}/,/```/{//!d;}' ../README.md && sed -i '/```{$(OUT1)}/r./$(OUT1)' ../README.md && \
	sed -i '/```{$(OUT2)}/,/```/{//!d;}' ../README.md && sed -i '/```{$(OUT2)}/r./$(OUT2)' ../README.md && \
	sed -i '/```{$(OUT3)}/,/```/{//!d;}' ../README.md && sed -i '/```{$(OUT3)}/r./$(OUT3)' ../README.md