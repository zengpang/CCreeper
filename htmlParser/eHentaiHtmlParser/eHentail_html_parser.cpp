#include "eHentai_html_parser.h"
#include <regex>
#include <iostream>

std::string EHentaiHtmlParser::extractNextPageLink(const std::string &html,const std::string &url)
{
    std::string nextPageLinkStr;
    std::smatch matches;
    std::regex nextPageLinkRegex(R"(next=(\d+))"); // 匹配 
    // std::cout<<"原始HTML"<<html<<std::endl;
    if (std::regex_search(html, matches, nextPageLinkRegex))
    {
        std::cout<<"已匹配下一页链接"<<std::endl;
        nextPageLinkStr =(url+"?next="+matches[1].str());

    };
    return nextPageLinkStr;
}