#include <iostream>
#include <stdexcept>
#include <boost/lexical_cast.hpp>

#include "Troop_Data_Collection.h"

Troop_Data_Collection::Troop_Data_Collection(const std::string& filename)
{
    std::ifstream in(filename.c_str(), std::ios::binary);
    if(!in) throw std::invalid_argument(filename + " could not be read");

    std::string buffer;

    std::getline(in, buffer);
    buffer.erase(buffer.length()-1);

    unsigned version = 1;

    if (buffer != "troopsfile version 1")
    {
        if (buffer == "troopsfile version 2")
        {
            version = 2;
            std::cout<<"warband file detected"<<std::endl;
        } else throw std::invalid_argument("unknown troops.txt version or corrupt file");
    }

    std::getline(in, buffer);
    buffer.erase(buffer.length()-1);

    buffer.erase(buffer.length()-1);
    unsigned entryCount = boost::lexical_cast<unsigned>(buffer);

    std::cout<<"reading troop data ... "<<entryCount<<" entries expected"<<std::endl;

    unsigned troop_id = 0;

    while (troop_id < entryCount && in)
    {
        (*this)[troop_id] = TroopData(in, version);
        ++troop_id;
    }

    std::cout<<troop_id<<" troops loaded"<<std::endl<<std::endl;

    std::cout<<"verifying upgrade targets ... ";

    // test for invalid upgrade targets
    Troop_Data_Collection::const_iterator it = begin();
    while (it!=end())
    {
        if (find(it->second.get_upgrade1()) == end())
        {
            throw new std::logic_error("unknown upgrade target " + boost::lexical_cast<std::string>(it->second.get_upgrade1()) + " for " + it->second.get_display_name() + " detected");
        }

        if (find(it->second.get_upgrade2()) == end())
        {
            throw new std::logic_error("unknown upgrade target " + boost::lexical_cast<std::string>(it->second.get_upgrade2()) + " for " + it->second.get_display_name() + " detected");
        }

        ++it;
    }

    std::cout<<"ok"<<std::endl<<std::endl;
}

Troop_Data_Collection::~Troop_Data_Collection()
{

}

std::vector<unsigned> Troop_Data_Collection::get_roots() const
{
    std::cout<<"determinig roots:"<<std::endl;

    std::vector<unsigned> roots;

    Troop_Data_Collection::const_iterator it = begin();
    while (it!=end())
    {
        if (it->second.get_upgrade1() != 0 || it->second.get_upgrade2() != 0)
        {
            bool isRoot = true;

            Troop_Data_Collection::const_iterator it2 = begin();
            while (it2!=end())
            {
                if (it2->second.get_upgrade1() == it->first || it2->second.get_upgrade2() == it->first)
                {
                    isRoot = false;
                    break;
                }

                ++it2;
            }

            if (isRoot)
            {
                std::cout<<it->second.get_display_name()<<" ("<<it->first<<") is a root"<<std::endl;
                roots.push_back(it->first);
            }
        }

        ++it;
    }

    std::cout<<std::endl;

    return roots;
}
