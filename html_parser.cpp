#include "html_parser.h"
#include <regex>
#include <algorithm>

//提取链接
std::vector<std::string> HTMLParser::extractLinks(const std::string& html,const std::string& baseUrl)
{
    std::vector<std::string> links;//存储找到的链接

    // 正则表达式，匹配<a href="...">标签
    // icess:忽略大小写
    std::regex linkRegex("<a\\s+[^>]*href\\s*=\\s*[\"']([^\"']*)[\"'][^>]*>",std::regex_constants::icase);

    //使用正则表达式迭代器查找所有匹配
    std::sregex_iterator it(html.begin(),html.end(),linkRegex);
    std::sregex_iterator end;//结果迭代器

    while(it!=end)
    {
        std::string link=(*it)(1).str();//获取第一个捕获组(href的值)

        //处理相对链接(如果不是以http开头)
    }

}