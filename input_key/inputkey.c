#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "inputkey.h"
int main()
{
    return 0;
}

input readkey ()
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




}