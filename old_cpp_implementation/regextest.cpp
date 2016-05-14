#include <iostream>
#include <fstream>
#include <string>
#include <boost/regex.hpp>

int main()
{
	std::ifstream in("troops.txt");

	std::string file, line;

	while(in)
	{
		getline(in, line);
		file += line + "\n";
	}

	std::cout<<"geladen"<<std::endl;

	boost::regex expression(
		"^([^\\s]+?)\\s([^\\s]+?)\\s([^\\s]+?)\\s(\\d+?)\\s(\\d+?)\\s(\\d+?)\\s(\\d+?)\\s(\\d+?)\\s(\\d+?)$"
		);

	std::string::const_iterator start = file.begin();
	std::string::const_iterator end = file.end();

	boost::match_results<std::string::const_iterator> what;

	boost::match_flag_type flags = boost::match_default;

	while(regex_search(start, end, what, expression, flags))
	{ 
		std::cout<<std::string(what[0].first, what[0].second)<<std::endl;
		std::cout<<"\t"<<std::string(what[1].first, what[1].second)<<std::endl;
		std::cout<<"----------------------------------------"<<std::endl;

		// update search position:
		start = what[0].second;

		// update flags:
		flags |= boost::match_prev_avail;
		flags |= boost::match_not_bob;
	}

	return 0;
} 
