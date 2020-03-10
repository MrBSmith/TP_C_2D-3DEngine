#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "inputkey.h"

int inputkey_main()
{
    printf("Hello world from inputkey.c --> Execution de readkey une fois\n");
    test();
    return 0;
}

void test()
{
    printf("Fonction test execute depuis inputkey.c\n");
}

input readkey()
{
    char key;
    input control;

    getc(key);

    switch (key)
    {
        case 'z':
            (control=UP);
        case 'q':
            (control=LEFT);
        case 'd':
            (control=RIGHT);
        case 's':
            (control=DOWN);
        case 'v':
            (control=CONFIRM);
        case 'n':
            (control=CANCEL);
        default :
            (control=ERROR);
    }

    return control;
}
