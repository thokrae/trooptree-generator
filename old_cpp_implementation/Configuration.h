#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <vector>
#include <string>
#include <map>

class Configuration
{
    public:
        Configuration(std::string config_name);
        virtual ~Configuration();

        static std::vector<std::string> get_config_names();

        std::string get_value(std::string key);

    private:
        std::map<std::string, std::string> values_;
};

#endif // CONFIGURATION_H
