#include "Text_Renderer.h"

#include <iostream>

Text_Renderer::Text_Renderer(Troop_Data_Collection& troop_data)
:   troop_data_(troop_data)
{

}

Text_Renderer::~Text_Renderer()
{

}

void Text_Renderer::render(Configuration& config)
{
    std::ofstream out(config.get_value("output").c_str());

    std::vector<unsigned> roots = troop_data_.get_roots();

    for(unsigned i=0; i<roots.size(); ++i)
    {
        render(roots[i], 0, out);
        out<<std::endl;
    }
}

void Text_Renderer::render(unsigned troop_id, unsigned level, std::ofstream& out)
{
    for(unsigned i=0; i<level; ++i) out<<"\t";
    out<<troop_data_[troop_id].get_display_name()<<std::endl;

    if(troop_data_[troop_id].get_upgrade1() != 0) render(troop_data_[troop_id].get_upgrade1(), level+1, out);
    if(troop_data_[troop_id].get_upgrade2() != 0) render(troop_data_[troop_id].get_upgrade2(), level+1, out);
}
