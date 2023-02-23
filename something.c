#include <stdio.h>

void foo() {
    printf("%s\n", "foo");
}

int bar(int a, int b) {
    return a * b + b;
}

int baz(float x) {
    return (int)x;
}

int main(int argc, char *argv[]) {

    foo();
    int abb = bar(3, 5);
    printf("%d\n", abb);
    int r = baz(3.14f);
    printf("%d\n", r);
    return 0;
}
