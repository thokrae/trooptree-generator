#include "Graph_Renderer.h"

#include <fstream>
#include <iostream>
#include <graphviz/gvc.h>

Graph_Renderer::Graph_Renderer(Troop_Data_Collection& troop_data)
        :   troop_data_(troop_data)
{

}

Graph_Renderer::~Graph_Renderer()
{

}

void Graph_Renderer::render(Configuration& config)
{
    std::string dotfilename = config.get_value("output") + ".dot";

    std::cout<<"writing "<<dotfilename<<" ...";

    std::ofstream out(dotfilename.c_str());

    out<<"digraph G {"<<std::endl;
    out<<"node [shape=box, style=filled, color=black, fillcolor=ghostwhite];"<<std::endl;
    out<<"bgcolor=\"transparent\";"<<std::endl;
    out<<"rankdir=LR;"<<std::endl;

    std::map<unsigned, bool> relevant_troops;
    std::map<unsigned, std::vector<std::string> > troops_per_level;

    Troop_Data_Collection::const_iterator it = troop_data_.begin();
    while (it!=troop_data_.end())
    {
        std::string text = get_text(it->first, config);

        if (it->second.get_upgrade1() != 0)
        {
            std::string upgradeText = get_text(it->second.get_upgrade1(), config);

            out<<"\""<<text<<"\" -> \""<<upgradeText<<"\";"<<std::endl;

            relevant_troops[it->first]=true;
            relevant_troops[it->second.get_upgrade1()]=true;

            troops_per_level[it->second.get_level()].push_back(text);
        }

        if (it->second.get_upgrade2() != 0)
        {
            std::string upgradeText = get_text(it->second.get_upgrade2(), config);

            out<<"\""<<text<<"\" -> \""<<upgradeText<<"\";"<<std::endl;

            troops_per_level[it->second.get_level()].push_back(text);

            relevant_troops[it->first]=true;
            relevant_troops[it->second.get_upgrade2()]=true;
        }

        ++it;
    }

    std::map<unsigned, bool>::const_iterator it2 = relevant_troops.begin();
    while (it2!=relevant_troops.end())
    {
        out<<"\""<<get_text(it2->first, config)<<"\" [fillcolor=\""<<get_color(it2->first, config)<<"\"];"<<std::endl;
        ++it2;
    }

    std::map<unsigned, std::vector<std::string> >::const_iterator it3 = troops_per_level.begin();
    while (it3!=troops_per_level.end())
    {
        out<<"/*{ rank = same; ";
        for(unsigned i=0; i<it3->second.size(); ++i) out<<"\""<<it3->second[i]<<"\";";
        out<<" }*/"<<std::endl;
        ++it3;
    }

    out<<"}"<<std::endl;
    out.close();

    std::cout<<" done\nwriting png ...";
    std::cout.flush();

    GVC_t* gvc = gvContext();

    FILE* in = fopen(dotfilename.c_str(), "r");

    graph_t* g = agread(in);

    fclose(in);

    char dot[] = "dot";
    gvLayout(gvc, g, dot);

    FILE* pngout = fopen(config.get_value("output").c_str(), "w");
    char png[] = "png";
    gvRender(gvc, g, png, pngout);
    fclose(pngout);

    gvFreeLayout(gvc, g);

    agclose(g);

    int error_count = gvFreeContext(gvc);

    std::cout<<" done ("<<error_count<<" errors)"<<std::endl;
}

std::string Graph_Renderer::get_color(unsigned id, Configuration& config)
{
    TroopData troop_data = troop_data_[id];

    std::string backcolor = config.get_value("default_color");

    if (troop_data.is_mounted() && troop_data.is_ranged())
    {
        backcolor = config.get_value("ranged_mounted_color");
    }
    else if (troop_data.is_ranged())
    {
        backcolor = config.get_value("ranged_color");
    }
    else if (troop_data.is_mounted())
    {
        backcolor = config.get_value("mounted_color");
    }

    return backcolor;
}

std::string Graph_Renderer::get_text(unsigned id, Configuration& config)
{
    TroopData troop_data = troop_data_[id];

    std::string text = config.get_value("default_text");

    if (troop_data.is_mounted() && troop_data.is_ranged())
    {
        text = config.get_value("ranged_mounted_text");
    }
    else if (troop_data.is_ranged())
    {
        text = config.get_value("ranged_text");
    }
    else if (troop_data.is_mounted())
    {
        text = config.get_value("mounted_text");
    }

    return troop_data.get_troop_description(text);
}
