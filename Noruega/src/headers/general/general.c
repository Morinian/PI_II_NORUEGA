#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

const int DISPLAY_WIDTH = 1300;
const int DISPLAY_HEIGHT = 700;//850

void must_init(bool test, const char* description)
{
    if (test) return;

    printf("\nNão foi possivel alocar %s", description);
    exit(-1);
}