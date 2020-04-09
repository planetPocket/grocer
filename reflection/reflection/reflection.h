#pragma once
/*
ͨ����+template ʵ�ֵļ�C++�������.
��Ҫ˼�����Ϊÿ����Ҫʵ�ַ�����Ƶ�class
��Ӷ�Ӧ�Ĺ���,�������þ��Ǵ����µ�ʵ��.
ʹ�ù����ĺô����ڷ���ɾ��.
���ҰѸù���������Reflection���m_reflectionmap��,
ÿ��������Ҫ��ȡ����,ֻ��Ҫͨ��getNewInstance()ģ�庯��
ȥ��ȡsingletonģʽ��Refection���еĹ�������,�ù�������һ���µĶ���,
���Ҹ���template��typename��ʵ��dynamic_cast.
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
