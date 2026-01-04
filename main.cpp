#include <iostream>
#include "crawler.h"                                          //爬虫类
#include "htmlParser/baseHtmlParser/html_parser.h"            // HTML解析器
#include "htmlParser/eHentaiHtmlParser/eHentai_html_parser.h" // E站 HTML解析器
#include "enums.h"                                            // 包含枚举头文件
#include <sstream>
#include <windows.h>
// 将 UTF-8 转换为 Windows 控制台默认的 GBK
std::string UTF8ToGBK(const std::string& utf8Str) {
    if (utf8Str.empty()) return "";
    
    int wideLen = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, nullptr, 0);
    if (wideLen <= 0) return utf8Str;
    
    wchar_t* wideStr = new wchar_t[wideLen];
    MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, wideStr, wideLen);

    int gbkLen = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, nullptr, 0, nullptr, nullptr);
    if (gbkLen <= 0) {
        delete[] wideStr;
        return utf8Str;
    }
    
    char* gbkStr = new char[gbkLen];
    WideCharToMultiByte(CP_ACP, 0, wideStr, -1, gbkStr, gbkLen, nullptr, nullptr);

    std::string result(gbkStr);
    delete[] wideStr;
    delete[] gbkStr;
    return result;
}
/**
 * 根据 网页类型 获取HTML
 * @param crawler 爬虫实例
 * @param webType 网页类型
 * @param url 网页地址
 * @param headers 设置请求头
 */
std::string getHtmlByWebType(
    WebCrawler crawler,
    int webType,
    std::string url,
    std::map<std::string, std::string> headers)
{
    std::string html;
    switch (webType)
    {
    case CrawlWebType::EHENTAI:
    {
        int pageSize = 10;
        std::cout << "请输入爬取页码数量(默认页码:10)\n";
        std::cin >> pageSize;
        html = crawler.get(url, headers); // 执行GET请求
        break;
    }
    case CrawlWebType::ORGHTTP:
    {
        html = crawler.get(url, headers); // 执行GET请求
        break;
    }
    };
    return html;
}
/**
 * 解析 HTML (E站)
 * @param html 欲解析的html字符串
 */
void eHentaiHtmlAnalysis(
    std::string html,
    std::string url
)
{
    std::string nextPageLink = EHentaiHtmlParser::extractNextPageLink(html,url);
    std::cout << "下一页链接为" << nextPageLink << std::endl;
}
/**
 * 解析 HTML (基础)
 * @param crawler 爬虫实例
 * @param html 欲解析的html字符串
 */
void baseHtmlAnalysis(WebCrawler crawler, std::string html, std::string url)
{
    std::cout << "网页原始内容" << html << std::endl;
    std::cout << "成功获取网页内容(" << html.length() << "字节)" << std::endl;
    std::cout << "响应码：" << crawler.getLastResponseCode() << std::endl;
    std::cout << "请求时间：" << crawler.getLastRequestTime() << std::endl;

    // 解析HTML内容
    std::vector<std::string> links = HTMLParser::extractLinks(html, url);
    std::vector<std::string> images = HTMLParser::extractImages(html);
    std::string text = HTMLParser::extractText(html);

    // 输出结果
    std::cout << "\n找到" << links.size() << " 个链接" << std::endl;
    for (const auto &link : links)
    {
        std::cout << "  -" << link << std::endl;
    }

    std::cout << "\n找到 " << images.size() << " 个图片:" << std::endl;
    for (const auto &img : images)
    {
        std::cout << " -" << img << std::endl;
    }

    std::cout << "\n提取的文本内容" << std::endl;
}
/**
 * 根据 网页类型 解析HTML
 * @param webType 网页类型
 * @param html 欲解析的html字符串
 * @param url 网页地址
 */
void htmlAnalysis(
    WebCrawler crawler,
    int webType,
    std::string html,
    std::string url)
{
    if (!html.empty())
    {
        switch (webType)
        {
        case CrawlWebType::EHENTAI:
            eHentaiHtmlAnalysis(html, url);
            break;
        case CrawlWebType::ORGHTTP:
            baseHtmlAnalysis(crawler, html, url);
            break;
        };
    }
    else
    {
        std::cout << "获取不到网页原始内容" << std::endl;
    }
}
int main()
{
    // setConsoleUTF8();
    // 初始化
    curl_global_init(CURL_GLOBAL_DEFAULT);
    try
    {
        // 异常处理
        WebCrawler crawler; // 创建爬虫实例

        // 设置请求头(模拟游览器)
        std::map<std::string, std::string> headers = {
            {"Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"},
            {"Accept-Language", "en-US,en;q=0.5"},
            {"Connection", "keep-alive"}};

        // 爬取网页
        std::string url;  // 网页地址
        int inputWebType; // 爬取网页类型
        std::cout << "请输入序号，以此选择爬取网页地址\n";
        std::cout << "1:E站(需使用VPN,否则无法爬取信息)\n";
        std::cout << "2:原始HTTP测试站\n";
        std::cin >> inputWebType;
        switch (inputWebType)
        {
        case CrawlWebType::EHENTAI:
        {
            std::cout << "请输入漫画搜索词条\n";
            std::string searchStr;
            std::cin >> searchStr;
            if (!searchStr.empty())
            {
                std::stringstream ss;
                ss << "https://e-hentai.org/" << "?" << "f_search=" << searchStr;
                url=ss.str();
            }
            else
            {

                url = "https://e-hentai.org/";
            }
            // https://e-hentai.org/?f_search=tomgirl
            break;
        }

        case CrawlWebType::ORGHTTP:
        {
            url = "http://httpbin.org/html";
        }
        break;
        }
        if (url.empty())
        {
            std::cout << "爬取目标地址不能为空" << std::endl;
            // 清理libcurl全局环境
            curl_global_cleanup();
            system("pause");
            return 0;
        }
        std::cout << "开始爬取中..." << std::endl;
        std::string html = UTF8ToGBK(crawler.get(url, headers)); // 执行GET请求

        std::cout << "爬取完成" << std::endl;
        if (!html.empty())
        {
            //std::cout<<"原始HTML为"<<html<<std::endl;
            htmlAnalysis(crawler, inputWebType, html, url);
        }
        else
        {
            std::cout << "获取不到网页原始内容" << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "错误: " << e.what() << std::endl;
    }

    // 清理libcurl全局环境
    curl_global_cleanup();
    system("pause");
    return 0;
}