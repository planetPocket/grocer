#pragma once
#include "reflection.h"
class Person :public reflectionObject
{
public:

    Person();
    virtual ~Person();
    virtual void show();
};

