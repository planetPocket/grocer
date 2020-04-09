// reflection.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Person.h"
#include "Alice.h"
int main()
{
    Person* alice = getNewInstance<Person>("Alice");
    if (alice == nullptr) {
        return 1;
    }
    alice->show();
    delete alice;
    system("pause");
    return 0;
}
