#ifndef JSON_H
#define JSON_H


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>


#include "Parser.h"


using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::list;
using std::map;


namespace qwm{
    namespace json{
        
class Json
{
public:
    enum Type{//数据类型，共有七种，：空，字符串，布尔，对象，数组，整形和浮点，分别对应js几种数据类型
    //json就是js子集，格式就是对象套对象数组套数组这样子
        json_null=0,
        json_bool,
        json_int,
        json_double,
        json_string,
        json_array,
        json_object

    };
    Json();
    //共有方法，先是构造函数
    Json(Type type);
    Json(bool value); 
    Json(int value);//七种构造方法
    Json(double value);
    Json(const char* value);

    Json(const string& value);
    Json(const Json & other);
    ~Json();//默认虚构函数


    Type type() const;
    bool isNull() const;
    bool isInt() const;
    bool isDouble() const;//判断数据类型
    bool isBool() const;
    bool isArray() const;
    bool isObject() const;
    bool isString() const;

    bool asBool() const;
    int asInt() const;
    double asDouble() const;
    string asString() const;
    int size() const;
    bool empty() const;


    void clear();

    bool has(int index);
    bool has(const char * key);
    bool has(const string & key);

    void remove(int index);
    void remove(const string & key);
    void remove(const char * key);

    void append(const Json & value);

//重载运算符
    Json & operator = (const Json & other);
    bool operator == (const Json & other);
    bool operator != (const Json & other);

    Json & operator [] (int index);
    Json & operator [] (const char * key);
    Json & operator [] (const string & key);

    operator bool();
    operator int();
    operator double();
    operator string();

    using iterator=std::list<Json>::iterator;
    //类型声明

    iterator begin()
    {
        return (m_value.m_array)->begin();//自定义迭代器
    }

    iterator end()
    {
        return (m_value.m_array)->end();
    }
    string str() const;

    void parse(const string & str);


private:
    void copy(const Json & other);
private:
    union Value{
        bool m_bool;
        int m_int;
        double m_double;
        string *m_string;
        list<Json> * m_array;
        map<string,Json> *m_object;
    };

    Type m_type;
    Value m_value;
};

    } 
}


#endif