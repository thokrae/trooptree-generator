#include <iostream>
#include <stdexcept>
#include <string>

#include "Troop_Data_Collection.h"
#include "Configuration.h"
#include "Troop_Tree_Renderer.h"
#include "Text_Renderer.h"
#include "Graph_Renderer.h"
#include "Html_List_Renderer.h"
#include "BBC_Renderer.h"

int main(int argc, const char* argv[])
{
    try
    {
        for(int i=1; i<argc; ++i)
        {
            if(std::string(argv[i]) == "-version")
            {
                std::cout<<"Troop Tree Generator"<<std::endl;
                std::cout<<"Version: 9.07.05"<<std::endl;
                std::cout<<L"Author: Thomas Krämer"<<std::endl;
                return 0;
            }
        }

        // select and load configuration
        std::vector<std::string> config_names = Configuration::get_config_names();
        std::string config_name;

        if(config_names.size() == 0) throw std::logic_error("");
        else if(config_names.size() == 1) config_name = config_names[0];
        else
        {
            unsigned choice = 0;
            while (choice<1 || choice>config_names.size())
            {
                std::cout<<"choose configuration:"<<std::endl;

                for(unsigned i=0; i<config_names.size(); ++i)
                {
                    std::cout<<i+1<<".\t"<<config_names[i]<<std::endl;
                }

                std::cin.clear();
                std::cin.ignore(std::cin.rdbuf()->in_avail());
                std::cin>>choice;
            }

            config_name = config_names[choice-1];
        }

        Configuration config(config_name);

        // load troop data
        Troop_Data_Collection troop_data(config.get_value("input"));

        // render troop tree
        Troop_Tree_Renderer* renderer = 0;

        if(config.get_value("renderer") == "text") renderer = new Text_Renderer(troop_data);
        else if(config.get_value("renderer") == "bbc") renderer = new BBC_Renderer(troop_data);
        else if(config.get_value("renderer") == "graphviz") renderer = new Graph_Renderer(troop_data);
        else renderer = new Html_List_Renderer(troop_data);

        renderer->render(config);

        delete renderer;
    }
    catch (std::exception& e)
    {
        std::cerr<<"aborting: "<<e.what()<<std::endl;
    }

    return 0;
}
