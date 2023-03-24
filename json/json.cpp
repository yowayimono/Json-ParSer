#include <sstream>

#include <stdexcept>

using std::stringstream;

#include "json.h"

using namespace qwm::json;

#include "Parser.h"


Json::Json():m_type(json_null)
{

}

Json::Json(Type type):m_type(type)
{
    switch (m_type)
    {
    case json_null:
        break;
    case json_bool:
        m_value.m_bool=false;
        break;
    case json_int:
        m_value.m_int=0;
        break;
    case json_double:
        m_value.m_double=0.0;
        break;
    case json_string:
        m_value.m_string="";
        break;
    case json_array:
        m_value.m_array=new list<Json> ();
        break;
    case json_object:
        m_value.m_object=new map<string,Json>();
        break;
    default:
        break;
    }
}


Json::Json(bool value):m_type(json_bool)
{   
    m_value.m_bool=value;
}


Json::Json(const int):m_type(json_int)
{
    m_value.m_int=value;
}

Json::Json(const double value):m_type(json_double)
{
    m_value.m_double=value;
}

Json::Json(const char * value):m_type(json_string)
{
    m_value.m_string = new string(value);
}

Json::Json(const string & value):m_type(json_string)
{
    m_value.m_string=new string(value);
}

Json::Json(const Json & other):m_type(json_null)
{
    copy(other);
}


Json::~Json()
{
    
}

Json::Type Json::type() const{
    return m_type;
}

//返回数据类型

bool Json::isNull() const
{
    return m_type==json_null;
}

bool Json::isInt() const{
    return m_type==json_int;
}

bool Json::isDouble() const{
    return m_type==json_double;
}

bool Json::isString() const{
    return m_type==json_string;
}

bool Json::isObject() const{
    return m_type==json_object;
}

bool Json::isArray() const{
    return m_type==json_array;
}

bool Json::isBool() const{

    return m_type==json_bool;
}

bool Json::asBool() const{
    if(m_type==json_bool)
    {
        return m_value.m_bool;
    }
    throw std::logic_error("function Json::asBool type error");

}

int Json::asInt() const{
    if(m_type==json_int)
    {
        return m_value.m_int;
    }
    throw std::logic_error("function Json::asInt value type error");
}

double Json::asDouble() const{
    if(m_type==json_double)
    {
        return m_value.m_double;
    }
    throw std::logic_error("function Json::asDouble value type error"); 
}

string Json::asString() const{
    if(m_type==m_string)
    {
        return *(m_value.m_string);
    }
    throw std::logic_error("function Json::asString value type error");
}

void Json::copy(const Json & other)
{
    m_type=other.m_type;
    m_value=other.m_value;
}

int Json::size() const{
    switch(m_type)
    {
        case json_array:
            return (m_value.m_array)->size();
        case json_object:
            return (m_value.m_object)->size();
        default:
            break;
    }
    throw std::logic_error("function Json::size value type error");
}

bool Json::empty() const{
    switch(m_type)
    {
        case json_null:
            return true;
        case json_array:
            return (m_value.m_array)->empty();
        case json_object:
            return (m_value.m_object)->empty();
        default:
            break;
    }
    return false;
}

void Json::clear()
{
    switch (m_type)
    {
    case json_null:
        /* code */
    case json_int:
    case json_bool:
    case json_double:
         break;
    case json_string:
        {
            delete m_value.m_string;
        }
        break;
    case json_array:
        {
            for(auto it=(m_value.m_array)->begin();it!=(m_value.m_array)->end();it++)
            {
                it->clear();
            }
            delete m_value.m_array;
        }
        break;
    case json_object:
        {
            for(auto it=(m_value.m_object)->begin();it!=(m_value.m_object)->end();i++)
            {
                it->second.clear();
            }
            delete m_value.m_object;
        }
        break;
    default:
        break;
    }
}