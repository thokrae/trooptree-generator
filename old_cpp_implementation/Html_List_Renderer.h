#ifndef HTML_LIST_RENDERER_H
#define HTML_LIST_RENDERER_H

#include <fstream>

#include "Troop_Tree_Renderer.h"

class Html_List_Renderer : public Troop_Tree_Renderer
{
    public:
        Html_List_Renderer(Troop_Data_Collection& troop_data);
        virtual ~Html_List_Renderer();

        virtual void render(Configuration& config);

    private:
        void render(unsigned troop_id, std::ofstream& out, Configuration& config);

        Troop_Data_Collection& troop_data_;
};

#endif // HTML_LIST_RENDERER_H
