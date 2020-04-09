#include "Alice.h"

REFLECT(Alice);

Alice::Alice()
{
    printf("alice()\n");
}

Alice::~Alice()
{
    printf("~alice()\n");
}

void Alice::show()
{
    printf("this is alice()\n");
}

