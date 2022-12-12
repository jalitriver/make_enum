#include "my_enums.h"
#include <stdio.h>

int
main(int argc,
     char* argv[])
{
    int rv = 0;
    enum MyEnum1 e1;
    enum MyEnum2 e2;
    const char* s = NULL;

    // EnumName_FromString()
    s = "FOO";
    if (!MyEnum1_FromString(&e1, s)) {
        fprintf(stderr, "*** Error: MyEnum1_FromString: %s\n", s);
        rv = 1;
        goto out;
    }
    s = "MyEnum2::SPAM";
    if (!MyEnum2_FromString(&e2, s)) {
        fprintf(stderr, "*** Error: MyEnum2_FromString: %s\n", s);
        rv = 1;
        goto out;
    }

    // EnumName_ToString() with and without enum name and element name.
    printf("EnumName_ToString():\n");
    printf("    e1 = %s\n", MyEnum1_ToString(e1, 1, 1));
    printf("    e1 = %s\n", MyEnum1_ToString(e1, 1, 0));
    printf("    e1 = %s\n", MyEnum1_ToString(e1, 0, 1));
    printf("    e2 = %s\n", MyEnum2_ToString(e2, 1, 1));
    printf("    e2 = %s\n", MyEnum2_ToString(e2, 1, 0));
    printf("    e2 = %s\n", MyEnum2_ToString(e2, 0, 1));

    printf("-----\n");

    // EnumName_IsValidEnum()
    printf("EnumName_IsValidEnum():\n");
    printf("    (MyEnum1)2 -> %d\n", MyEnum1_IsValid((enum MyEnum1)2));
    printf("    (MyEnum2)2 -> %d\n", MyEnum2_IsValid((enum MyEnum2)2));

 out:

    return rv;
}
