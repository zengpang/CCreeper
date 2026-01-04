#pragma once
#include "../baseHtmlParser/html_parser.h" // 包含HTML解析器
#include <vector>
class EHentaiHtmlParser : HTMLParser
{
public:
    // 提取漫画标题
    static std::string extractComicTitle(const std::string &html);
    // 提取漫画下载链接
    static std::vector<std::string> extractComicDownLinks(const std::string &html);
    // 提取漫画标签信息
    static std::vector<std::string> extractComicTags(const std::string &html);
    // 提取漫画作者信息
    static std::vector<std::string> extractComicAuthorInfos(const std::string &html);
    // 提取漫画大小
    static std::string extractComicSize(const std::string &html);
    // 获取下一个分页链接
    static std::string extractNextPageLink(const std::string &html);
};