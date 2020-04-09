#pragma once
/*
通过宏+template 实现的简单C++反射机制.
主要思想就是为每个需要实现反射机制的class
添加对应的工厂,工厂作用就是创建新的实例.
使用工厂的好处在于方便删改.
并且把该工厂保存在Reflection类的m_reflectionmap中,
每当有人需要获取对象,只需要通过getNewInstance()模板函数
去获取singleton模式的Refection类中的工厂函数,让工厂返回一个新的对象,
并且根据template的typename来实现dynamic_cast.
*/
#include <map>
#include <string>

class reflectionObject
{
public:
    virtual ~reflectionObject() {}
};

//aim to create object which store in map for refelction
class ObjectFactory
{
public:
    ObjectFactory() {};
    virtual reflectionObject *newInstance() = 0;
    virtual ~ObjectFactory(){}
};


//singleton mode
class Reflection
{
public:
    static Reflection& getInstance() {
        static Reflection reflection;
        return reflection;
    }

    reflectionObject* getFeflectionObject(std::string name) {
        auto it = m_reflectionmap.find(name);
        if (it == m_reflectionmap.end()) {
            printf("pls register first\n");
            return nullptr;
        }
        return it->second->newInstance();
    }
    void registerFactory(std::string classname,ObjectFactory *of) {
        m_reflectionmap[classname] = of;
    }
private:
    Reflection() {};
    ~Reflection() {
        for (auto re : m_reflectionmap) {
            delete re.second;
        }
    }
    std::map<std::string, ObjectFactory*> m_reflectionmap;
};

//auto res = Reflection::getInstance();

//using shared_ptr? 
#define REFLECT(name)\
class ObjectFactory_##name:public ObjectFactory{\
public:\
    ~ObjectFactory_##name(){}\
    reflectionObject* newInstance() {\
        return new name();\
    }\
};\
class Register_##name\
{\
public:\
    Register_##name(){\
        Reflection::getInstance().registerFactory(#name,new ObjectFactory_##name());\
    }\
};\
Register_##name register_##name;



//global function  for getting class which had been reflecting
template<typename T>
T* getNewInstance(const std::string& classname) {
    return dynamic_cast<T*>(Reflection::getInstance().getFeflectionObject(classname));
}
