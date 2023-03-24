#include <string>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

using namespace std;

#include "Parser.h"
#include "json.h"

using namespace qwm::json;

Parser::Parser()
{

}

Parser::~Parser()
{

}

void Parser::load(const string & str)
{
    m_str=str;
    m_idx=0;
}

void Parser::skip_white_space()//跳过无效字符
{
    while(m_str[m_idx]==' '||m_str[m_idx]=='\t'||m_str[m_idx]=='\n'||m_str[m_idx]=='\r')
    {
        m_idx++;
    }
}

char Parser::get_next_token()
{
    skip_white_space();//跳过没用的
    if(m_idx==m_str.size())
    {
        throw logic_error("unexpected end of input");
    }
    return m_str[m_idx++];
}

Json Parser::parse()
{
    char ch=get_next_token();//获取下一个有效字符
    switch(ch)
    {
        case 'n':
            m_idx--;
            return parse_null();
        case 't':
        case 'f':
        return parse_bool();
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            m_idx--;
            return parse_number();
        case '"':
            return Json(parse_string());
        case '[':
            return parse_array();
        case '{':
            return parse_object();
        default:
            break;
    }
    throw std::logic_error("unexpected character in parse json");
}

Json Parser::parse_null()
{
    if(m_str.compare(m_idx,4,"null")==0)
    {
        m_idx+=4;
        return Json();
    }
    throw std::logic_error("parse_null error");
}

Json Parser::parse_bool()
{
    if(m_str.compare(m_idx,4,"true")==0)
    {
        m_idx+=4;
        return Json(true);
    }
    if(m_str.compare(m_idx,5,"false")==0)
    {
        m_idx+=5;
        return Json(false);
    }
    throw std::logic_error("parse_bool error");
}

Json Parser::parse_number()
{
    size_t pos=m_idx;

    if(m_str[m_idx]=='-')
    {
        m_idx++;
    }
    if(m_str[m_idx]=='0')
    {
        m_idx++;
    }
    else if(in_range(m_str[m_idx],'1','9'))
    {
        m_idx++;//数字往后移
        while(in_range(m_str[m_idx],'1','9'))
        {
            m_idx++;
        }
    }
    else{
        throw logic_error("parse_number error");
    }
    if(m_str[m_idx]!='.')
    {
        return Json(std::atoi(m_str.c_str()+pos));
    }
    m_idx++;
    if(!in_range(m_str[m_idx],'0','9'))
    {
        throw logic_error("parse_number error one");
    }
    while(in_range(m_str[m_idx],'0','9'))
    {
        m_idx++;
    }
    return Json(std::atoi(m_str.c_str()+pos));

}



string Parser::parse_string()
{
    int pos=m_idx;
    while(true)
    {
        if(m_idx==m_str.size())
        {
            throw std::logic_error("unexpected end of input in string");
        }
        char ch=m_str[m_idx++];
        if(ch=='"')
        {
            break;
        }
        if(ch=='\\')
        {
            switch(ch)
            {
                case 'b':
                case 't':
                case 'n':
                case 'f':
                case 'r':
                case '"':
                case '\\':
                    break;
                case 'u':
                    m_idx+=4;
                    break;
                default:
                    break;
            }
        }
    }
    return m_str.substr(pos,m_idx-pos-1);
}

Json Parser::parse_array()
{
    Json arr(Json::json_array);
    char ch=get_next_token();
    if(ch==']')
    {
        return arr;
    }
    m_idx--;
    while(true)
    {
        arr.append(parse());
        ch=get_next_token();
        if(ch==']')
        {
            break;
        }
        if(ch==',')
        {
            throw std::logic_error("expected ',' in array");
        }
    }
    return arr;
}

Json Parser::parse_object()
{
    Json obj(Json::json_object);
    char ch=get_next_token();
    if(ch==']')
    {
        return obj;
    }
    m_idx--;
    while(true)
    {
        ch==get_next_token();
        if(ch!='"')
        {
            throw std::logic_error("expected '\"' in object");
        }
        string key=parse_string();
        ch=get_next_token();
        if(ch=='}')
        {
            break;
        }
        if(ch!=',')
        {
            throw logic_error("expected ',' in object");
        }
    }
    return obj;
}

