#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "ui.h"

int main()
{
    start_app();
    _CrtDumpMemoryLeaks();
    return 0;
}
