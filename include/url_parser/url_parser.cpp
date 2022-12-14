//
// Created by chiya on 7/26/22.
//

#include "url_parser.h"

#include <string>
#include <iostream>
#include <optional>
#include <regex>

std::optional<URL> parse_url(const std::string &url) //with boost
{
    std::regex ex(R"((http|https)://([^/ :]+):?([^/ ]*)(/?[^ #?]*)\x3f?([^ #]*)#?([^ ]*))");
    std::smatch what;

    if(std::regex_match(url, what, ex))
    {
        std::string protocol = std::string(what[1].first, what[1].second);
        std::string domain   = std::string(what[2].first, what[2].second);
        std::string port     = std::string(what[3].first, what[3].second);
        std::string path     = std::string(what[4].first, what[4].second);
        std::string query    = std::string(what[5].first, what[5].second);
        if (port.empty() && protocol == "https")
            port = "443";
        else if (port.empty() && protocol == "http")
            port = "80";
        return {{protocol, domain, port, path, query}};
    }
    return std::nullopt;
}