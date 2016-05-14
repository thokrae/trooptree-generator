#include "Html_List_Renderer.h"

Html_List_Renderer::Html_List_Renderer(Troop_Data_Collection& troop_data)
:   troop_data_(troop_data)
{

}

Html_List_Renderer::~Html_List_Renderer()
{

}

void Html_List_Renderer::render(Configuration& config)
{
    std::ofstream out(config.get_value("output").c_str());

    out<<"<html><head><title>";
    out<<"Troop Tree";
    out<<"</title></head><body>"<<std::endl;

    std::vector<unsigned> roots = troop_data_.get_roots();

    for(unsigned i=0; i<roots.size(); ++i)
    {
        out<<"<ul>"<<std::endl;
        render(roots[i], out, config);
        out<<"</ul>"<<std::endl;
    }

    out<<"</body></html>";
}

void Html_List_Renderer::render(unsigned troop_id, std::ofstream& out, Configuration& config)
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

    out<<"<li><div style=\"color: "<<backcolor<<"\">"<<troop_data.get_troop_description(text)<<"</div></li>"<<std::endl;

    out<<"<ul>"<<std::endl;
    if(troop_data.get_upgrade1() != 0) render(troop_data.get_upgrade1(), out, config);
    if(troop_data.get_upgrade2() != 0) render(troop_data.get_upgrade2(), out, config);
    out<<"</ul>"<<std::endl;
}
