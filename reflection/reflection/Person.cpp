#include "Person.h"

Person::Person()
{
    printf("create person\n");
}

Person::~Person()
{
    printf("deconstruct person\n");
}

void Person::show()
{
    printf("show person\n");
}
