#ifndef TROOP_TREE_RENDERER_H
#define TROOP_TREE_RENDERER_H

#include "Troop_Data_Collection.h"
#include "Configuration.h"

class Troop_Tree_Renderer
{
    public:
        Troop_Tree_Renderer();
        virtual ~Troop_Tree_Renderer();

        virtual void render(Configuration& config) = 0;

    private:
};

#endif // TROOP_TREE_RENDERER_H
