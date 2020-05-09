// Example that shows simple usage of the INIReader class

#include <iostream>
#include <sstream>
#include "INIReader.h"

std::string sections(INIReader &reader)
{
    std::stringstream ss;
    std::set<std::string> sections = reader.Sections();
    for (auto & section : sections)
        ss << section << ",";
    return ss.str();
}

int main()
{
    INIReader reader("test.ini");

    if (reader.ParseError() < 0)
    {
        std::cout << "Can't load 'test.ini'\n";
        return 1;
    }
    std::cout << "Config loaded from 'test.ini': found sections=" << sections(reader)
              << " version="
              << reader.GetInteger("protocol", "version", -1) << ", name="
              << reader.Get("user", "name", "UNKNOWN") << ", email="
              << reader.Get("user", "email", "UNKNOWN") << ", multi="
              << reader.Get("user", "multi", "UNKNOWN") << ", pi="
              << reader.GetReal("user", "pi", -1) << ", active="
              << reader.GetBoolean("user", "active", true) << "\n";

    std::cout << reader.Get("config", "value", "UNK") << '\n';

    auto & sections = reader.Sections();
    std::cout << sections.size() << '\n';

    for (auto& section : sections)
    {
        std::cout << "section " << section << '\n';
        for (auto& value : reader.Values(section))
        {
            auto res = reader.Get(section, value);
            std::cout << "config[" << section << "][" << value << "] = " << res << '\n';
        }
    }

    for (auto& value : reader.Values())
    {
        std::cout << "value " << value << '\n';
    }
    return 0;
}
