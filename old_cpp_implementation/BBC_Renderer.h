#ifndef BBC_RENDERER_H
#define BBC_RENDERER_H

#include "Troop_Tree_Renderer.h"

class BBC_Renderer : public Troop_Tree_Renderer
{
    public:
        BBC_Renderer(Troop_Data_Collection& troop_data);
        virtual ~BBC_Renderer();

        virtual void render(Configuration& config);

    private:
        void render(unsigned troop_id, std::ofstream& out, unsigned level, Configuration& config);

        Troop_Data_Collection& troop_data_;
};

#endif // BBC_RENDERER_H
