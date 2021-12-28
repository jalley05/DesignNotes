#include <string>


class YahooAPI
{
public:
    YahooAPI();
    ~YahooAPI() = default;
    void test(std::string ticker, std::string start, std::string stop);

private:
    std::string m_baseURL;
    std::string buildURL(std::string ticker, std::string start, std::string end);
    bool stringReplace(std::string& str, const std::string from, const std::string to);
    std::string timestamp(std::string date);
};
