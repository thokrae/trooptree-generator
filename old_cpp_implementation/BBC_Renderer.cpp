#include "BBC_Renderer.h"

#include <fstream>

BBC_Renderer::BBC_Renderer(Troop_Data_Collection& troop_data)
:   troop_data_(troop_data)
{

}

BBC_Renderer::~BBC_Renderer()
{

}

void BBC_Renderer::render(Configuration& config)
{
    std::ofstream out(config.get_value("output").c_str());

    std::vector<unsigned> roots = troop_data_.get_roots();

    out<<"[hr]"<<std::endl;

    for(unsigned i=0; i<roots.size(); ++i)
    {
        out<<"[list]"<<std::endl;
        render(roots[i], out, 1, config);
        out<<"[/list]"<<std::endl;
        out<<"[hr]"<<std::endl;
    }
}

void BBC_Renderer::render(unsigned troop_id, std::ofstream& out, unsigned level, Configuration& config)
{
    TroopData troop_data = troop_data_[troop_id];

    std::string backcolor = config.get_value("default_color");
    std::string text = config.get_value("default_text");

    if(troop_data.is_mounted() && troop_data.is_ranged())
    {
        backcolor = config.get_value("ranged_mounted_color");
        text = config.get_value("ranged_mounted_text");
    }
    else if(troop_data.is_ranged())
    {
        backcolor = config.get_value("ranged_color");
        text = config.get_value("ranged_text");
    }
    else if(troop_data.is_mounted())
    {
        backcolor = config.get_value("mounted_color");
        text = config.get_value("mounted_text");
    }

    //for(unsigned i=0; i<level; ++i) out<<"\t";
    out<<"[li][color="<<backcolor<<"]"<<troop_data.get_troop_description(text)<<"[/color][/li]"<<std::endl;

    if(troop_data.get_upgrade1() != 0 || troop_data.get_upgrade2() != 0)
    {
        //for(unsigned i=0; i<level; ++i) out<<"\t";
        out<<"[list]"<<std::endl;

        if(troop_data.get_upgrade1() != 0) render(troop_data.get_upgrade1(), out, level + 1, config);
        if(troop_data.get_upgrade2() != 0) render(troop_data.get_upgrade2(), out, level + 1, config);

        //for(unsigned i=0; i<level; ++i) out<<"\t";
        out<<"[/list]"<<std::endl;
    }
}
