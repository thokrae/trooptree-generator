#include "Configuration.h"

#include <fstream>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <boost/regex.hpp>

Configuration::Configuration(std::string config_name)
{
    std::cout<<"loading configuration \""<<config_name<<"\"\n"<<std::endl;

    std::ifstream in("TroopTreeGenerator.txt", std::ios::binary);
    if(!in) throw std::invalid_argument("TroopTreeGenerator.txt could not be read");

    // read whole file
    std::string line, file;
	while(in)
	{
		getline(in, line);
        if(line.length() > 0 && line[line.length()-1] == '\r') line.erase(line.length()-1);
		file += line + "\n";
	}

    // find configuration
	boost::regex expression("config\\s+(" + config_name + ").*?\\{(.*?)\\}");

	std::string::const_iterator start = file.begin();
	std::string::const_iterator end = file.end();

	boost::match_results<std::string::const_iterator> what;

	boost::match_flag_type flags = boost::match_default;

	if(regex_search(start, end, what, expression, flags)) file = std::string(what[2].first, what[2].second);

	// read values
	expression = boost::regex("(\\w+)\\s+=\\s+(.+?)\\n");

	start = file.begin();
	end = file.end();

	while(regex_search(start, end, what, expression, flags))
	{
        std::string key = std::string(what[1].first, what[1].second);
        for(unsigned i=0; i<key.size(); ++i) key[i] = tolower(key[i]);

        std::string value = std::string(what[2].first, what[2].second);

        values_[key] = value;

		start = what[0].second;

		flags |= boost::match_prev_avail;
		flags |= boost::match_not_bob;
	}
}

Configuration::~Configuration()
{

}

std::vector<std::string> Configuration::get_config_names()
{
    std::ifstream in("TroopTreeGenerator.txt", std::ios::binary);
    if(!in) throw std::invalid_argument("TroopTreeGenerator.txt could not be read");

    // read whole file
    std::string line, file;
	while(in)
	{
		getline(in, line);
        if(line.length() > 0 && line[line.length()-1] == '\r') line.erase(line.length()-1);
		file += line + "\n";
	}

    // search for configurations
	boost::regex expression("config\\s+(\\w+).*?\\{.*?\\}");

	std::string::const_iterator start = file.begin();
	std::string::const_iterator end = file.end();

	boost::match_results<std::string::const_iterator> what;

	boost::match_flag_type flags = boost::match_default;

    std::vector<std::string> config_names;

	while(regex_search(start, end, what, expression, flags))
	{
        config_names.push_back(std::string(what[1].first, what[1].second));

		start = what[0].second;

		flags |= boost::match_prev_avail;
		flags |= boost::match_not_bob;
	}

	return config_names;
}

std::string Configuration::get_value(std::string key)
{
    if(values_.find(key) != values_.end()) return values_[key];
    else throw std::invalid_argument("configuration does not contain a value for \"" + key + "\"");
}
