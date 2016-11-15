#include "Infra/String.h"
#include <stdio.h>

String s1, s2, s3, s4, s5;

void print_str(const char *name, String *s) {
    printf("%s: %s -- length: %lu\n", name, StringData(s), StringSize(s));
}

void test_init() {
    puts("Test init:\n");

    puts("Defualt Initialize:");
    StringInitDefault(&s1);
    print_str("s1", &s1);

    puts("\nC-String initialize:");
    StringInitCstring(&s2, "hello string");
    StringInitCstring(&s3, "");
    print_str("s2", &s2);
    print_str("s3", &s3);

    puts("\nString initialize:");
    StringInitString(&s4, &s2);
    StringInitString(&s5, &s1);
    print_str("s4", &s4);
    print_str("s5", &s5);
}

void test_assign() {
    puts("\nTest Assign:\n");

    StringAssignCstring(&s1, "hello my strings hi");
    StringAssignString(&s2, &s1);
    StringAssignString(&s3, &s4);
    StringAssignString(&s5, &s4);
    StringAssignCstring(&s4, "");

    print_str("s1", &s1); // hello my strings hi
    print_str("s2", &s2); // hello my strings hi
    print_str("s3", &s3); // hello string
    print_str("s4", &s4); //
    print_str("s5", &s5); // hello string
}

void test_append() {
    puts("\nTest Append:\n");

    puts("First Round!\n");

    StringAppendChar(&s1, '!');
    StringAppendString(&s2, &s3);
    StringAppendCstring(&s3, " what?");
    StringAppendString(&s4, &s5);
    StringAppendCstring(&s5, "");

    print_str("s1", &s1);
    print_str("s2", &s2);
    print_str("s3", &s3);
    print_str("s4", &s4);
    print_str("s5", &s5);

    puts("Second Round!\n");

    StringAppendString(&s1, &s2);
    StringAppendCstring(&s2, "wakakakakakakakakakakakakakakakakaka");
    StringAppendString(&s3, &s2);
    StringAppendString(&s4, &s1);
    StringAppendCstring(&s5, "abc");

    print_str("s1", &s1);
    print_str("s2", &s2);
    print_str("s3", &s3);
    print_str("s4", &s4);
    print_str("s5", &s5);
}

void test_substring() {
    puts("\nTest Substr:\n");
    StringAssignCstring(&s1, "hello world");
    StringAssignCstring(&s2, "");
    StringAssignCstring(&s3, "wowow");

    print_str("s1", &s1);
    print_str("s2", &s2);
    print_str("s3", &s3);

    String s6, s7, s8;
    StringInitDefault(&s6);
    StringInitDefault(&s7);
    StringInitDefault(&s8);

    StringSubstr(&s1, 0, 5, &s6);
    StringSubstr(&s2, 0, 1, &s7);
    StringSubstr(&s3, 1, 10, &s8);

    puts("");

    print_str("s6", &s6);
    print_str("s7", &s7);
    print_str("s8", &s8);

    StringDestroy(&s6);
    StringDestroy(&s7);
    StringDestroy(&s8);
}

int main(int argc, char const *argv[]) {
    test_init();
    test_assign();
    test_append();
    test_substring();

    StringDestroy(&s1);
    StringDestroy(&s2);
    StringDestroy(&s3);
    StringDestroy(&s4);
    StringDestroy(&s5);
    return 0;
}
