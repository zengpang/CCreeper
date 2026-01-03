#pragma once
#include <string>
#include <vector>
#include <regex> //正则表达式
class HTMLParser
{
public:
    // 提取所有链接
    // html:HTML内容
    //  baseUrl:基础URL(用于处理相对链接)
    static std::vector<std::string> extractLinks(const std::string& html,const std::string& baseUrl="");

    //提取所有图片链接
    static std::vector<std::string> extractImages(const std::string& html);

    //提取纯文本(去除所有HTML标签)
    static std::string extractText(const std::string& html);

    //提取特定标签的内容(示例方法)
    static std::vector<std::string> extractTags(const std::string& html,const std::string& tagName);
};
