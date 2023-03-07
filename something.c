#include <stdio.h>

void foo() {
    printf("%s\n", "foo");
}

int bar(int a, int b) {
    if (a > b) {
        return a * b + b;
    }
    return a * b - b;
}

int baz(float x) {
    return (int)x;
}

int main(int argc, char *argv[]) {

    for (int i = 0; i < 10; ++i) {
        foo();
    }
    foo();
    foo();
    int a = 3, b = 5;
    int abb = bar(a, b);
    printf("%d\n", abb);
    float x = 3.14f;
    int r = baz(x);
    printf("%f\n", (float)x);
    printf("%d\n", r);
    return 0;
}
