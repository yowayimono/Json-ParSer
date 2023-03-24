/*
 * @Author: yowayimono 3485000346@qq.com
 * @Date: 2023-03-23 17:57:46
 * @LastEditors: yowayimono 3485000346@qq.com
 * @LastEditTime: 2023-03-23 23:37:49
 * @FilePath: /Json-Parser/json/Parser.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef PARSER_H
#define PARSER_H


#include <string>
#include "json.h"
namespace qwm{
    namespace json{
class Parser{
public:
    Parser();
    ~Parser();
    void load(const string & str);
    Json parse();

private:
    void skip_white_space();
    char get_next_token();


    Json parse_null();
    Json parse_number();
    Json parse_bool();
    //Json Parse_double()
    string parse_string();
    Json parse_array();
    Json parse_object();


    bool in_range(int x,int lower,int upper)
    {
        return (x>=lower&&x<=upper);
    }


    string m_str;
    size_t m_idx;

};
    }
}



#endif