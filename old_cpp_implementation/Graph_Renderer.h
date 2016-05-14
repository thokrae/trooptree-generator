#ifndef GRAPH_RENDERER_H
#define GRAPH_RENDERER_H

#include "Troop_Tree_Renderer.h"

class Graph_Renderer : public Troop_Tree_Renderer
{
    public:
        Graph_Renderer(Troop_Data_Collection& troop_data);
        virtual ~Graph_Renderer();

        virtual void render(Configuration& config);

    private:
        std::string get_color(unsigned id, Configuration& config);
        std::string get_text(unsigned id, Configuration& config);

        Troop_Data_Collection& troop_data_;
};

#endif // GRAPH_RENDERER_H
