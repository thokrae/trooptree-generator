#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <fstream>

#include "Troop_Tree_Renderer.h"

class Text_Renderer : public Troop_Tree_Renderer
{
    public:
        Text_Renderer(Troop_Data_Collection& troop_data);
        virtual ~Text_Renderer();

        virtual void render(Configuration& config);

    private:
        void render(unsigned troop_id, unsigned level, std::ofstream& out);

        Troop_Data_Collection& troop_data_;
};

#endif // TEXT_RENDERER_H
