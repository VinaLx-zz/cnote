#include "Infra/StrVector.h"
#include <stdio.h>

StrVector v1, v2, v3;

void printVector(const StrVector *v) {
    printf("size: %lu\n", VectorSize(v));
    for (size_t i = 0; i <= VectorSize(v); ++i) {
        printf("%s\n", VectorGetConstCstring(v, i));
    }
    puts("");
}

void testInit() {
    puts("test init\n");
    VectorInitDefault(&v1);
    VectorInitDefault(&v2);
    VectorInitDefault(&v3);
    printVector(&v1);
    printVector(&v2);
    printVector(&v3);
}

void testPushCstring() {
    puts("\ntest push cstring\n");
    VectorPushCstring(&v1, "hello");
    printVector(&v1);
    VectorPushCstring(&v1, "hello1");
    printVector(&v1);
    VectorPushCstring(&v1, "hello2");
    printVector(&v1);
    VectorPushCstring(&v1, "hello3");
    printVector(&v1);
}

void testPushString() {
    puts("\ntest push string\n");
    VectorPushString(&v2, VectorGetConstString(&v1, 3));
    printVector(&v2);
    VectorPushString(&v2, VectorGetConstString(&v1, 2));
    printVector(&v2);
    VectorPushString(&v2, VectorGetConstString(&v1, 1));
    printVector(&v2);
    VectorPushString(&v2, VectorGetConstString(&v1, 0));
    printVector(&v2);
}

void testClear() {
    puts("\ntest clear\n");
    VectorClear(&v1);
    VectorClear(&v2);
    VectorClear(&v3);
    printVector(&v1);
    printVector(&v2);
    printVector(&v3);
}

void testDestroy() {
    VectorDestroy(&v1);
    VectorDestroy(&v2);
    VectorDestroy(&v3);
}

int main(int argc, char const *argv[]) {
    testInit();
    testPushCstring();
    testPushString();
    testClear();
    testDestroy();
    return 0;
}
