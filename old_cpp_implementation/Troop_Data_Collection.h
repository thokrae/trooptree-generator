#ifndef TROOP_DATA_COLLECTION_H
#define TROOP_DATA_COLLECTION_H

#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "TroopData.h"

class Troop_Data_Collection : public std::map<unsigned, TroopData>
{
    public:
        Troop_Data_Collection(const std::string& filename);
        virtual ~Troop_Data_Collection();

        std::vector<unsigned> get_roots() const;

    private:
};

#endif // TROOP_DATA_COLLECTION_H
