#include "YahooAPI.h"
#include <string>
#include <curl/curl.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <stdio.h>


YahooAPI::YahooAPI()
{
    std::cout << "HERE" << std::endl;
    m_baseURL = 
        "https://query1.finance.yahoo.com/v8/finance/chart/{ticker}?symbol={ticker}&period1={start_time}&period2={end_time}&interval={interval}";

    std::cout << m_baseURL << std::endl;
}

void YahooAPI::test(std::string ticker, std::string start, std::string stop)
{
    auto url = buildURL(ticker, start, stop);

    CURL *curl;
    FILE* fp;
    CURLcode res;
    curl = curl_easy_init();

    if(curl)
    {
        fp = fopen("test.json", "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        fclose(fp);
    }
}

std::string YahooAPI::timestamp(std::string date)
{
    struct std::tm time = {0,0,0,0,0,0,0,0,0};
    std::istringstream ss(date);
    ss >> std::get_time(&time, "%Y-%m-%d");
    if(ss.fail())
    {
        std::cerr << "ERROR " << std::endl;
        exit(1);
    }
    time.tm_hour = 0;
    time.tm_min = 0;
    time.tm_sec = 0;
    std::time_t epoch = std::mktime(&time);

    return std::to_string(epoch);
}

std::string YahooAPI::buildURL(std::string ticker, std::string start, std::string end)
{
    auto url = m_baseURL;
    stringReplace(url, "{ticker}", ticker);
    stringReplace(url, "{start_time}", timestamp(start));
    stringReplace(url, "{end_time}", timestamp(end));
    stringReplace(url, "{interval}", "1d");

    std::cout << "RETURN " << url << std::endl;
    return url;
}

bool YahooAPI::stringReplace(std::string& str, const std::string from, const std::string to)
{
    size_t start = str.find(from);
    if(start == std::string::npos)
    {
        return false;
    }

    str.replace(start, from.length(), to);
    return true;
}


