#include "TroopData.h"

#include <iostream>
#include <stdexcept>
#include <boost/lexical_cast.hpp>

/*
trp_swadian_militia Swadian_Militia Swadian_Militia FLAGS 0 0 FACTIONID UPGRADE1 UPGRADE2
  124 0 269 0 270 0 328 0 400 0 374 0 194 0 156 0 235 0 236 0 232 0 138 0 133 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0
  STR AGI INT CHA LEVEL
 PROF_1H PROF_2H PROF_POLEARMS PROF_ARCHER PROF_XBOW PROF_THROW PROF_FIRE
274 131072 0 1 0 0
  17179869185 1315051091194281984 1835136 0 50465891015 7916447985573822463 2031036 0

*/

TroopData::TroopData()
{
}

TroopData::TroopData(std::ifstream& in, unsigned version)
{
    in>>name_;
    std::cout<<name_<<":"<<std::endl;

    in>>display_name_;
    remove_underscores(display_name_);
    std::cout<<"\tname: "<<display_name_<<std::endl;

    in>>display_name_plural_;
    remove_underscores(display_name_plural_);
    std::cout<<"\tname (plural): "<<display_name_plural_<<std::endl;

    std::string buffer;

    if(version == 2)
    {
        in>>buffer;
    }

    in>>flags_;
    std::cout<<"\tflags: "<<flags_<<std::endl;

    in>>buffer;
    in>>buffer;

    in>>faction_id_;
    std::cout<<"\tfaction ID: "<<faction_id_<<std::endl;

    in>>upgrade1_;
    std::cout<<"\tupgrade ID 1: "<<upgrade1_<<std::endl;

    in>>upgrade2_;
    std::cout<<"\tupgrade ID 2: "<<upgrade2_<<std::endl;

    getline(in, buffer);

    std::cout<<"\titems: ";
    for(unsigned i=0; i < (version == 1 ? 47 : 64); ++i)
    {
        in>>buffer;
        std::cout<<buffer;

        in>>buffer;
        std::cout<<" ("<<buffer<<") ";
    }
    std::cout<<std::endl;

    getline(in, buffer);

    in>>strength_;
    std::cout<<"\tstrength: "<<strength_<<std::endl;

    in>>agility_;
    std::cout<<"\tagility: "<<agility_<<std::endl;

    in>>intelligence_;
    std::cout<<"\tintelligence: "<<intelligence_<<std::endl;

    in>>charisma_;
    std::cout<<"\tcharisma: "<<charisma_<<std::endl;

    in>>level_;
    std::cout<<"\tlevel: "<<level_<<std::endl;

    getline(in, buffer);

    in>>prof_1h_;
    std::cout<<"\t1H: "<<prof_1h_<<std::endl;

    in>>prof_2h_;
    std::cout<<"\t2H: "<<prof_2h_<<std::endl;

    in>>prof_polearms_;
    std::cout<<"\tpolearms: "<<prof_polearms_<<std::endl;

    in>>prof_archer_;
    std::cout<<"\tarchery: "<<prof_archer_<<std::endl;

    in>>prof_crossbow_;
    std::cout<<"\tcrossbows: "<<prof_crossbow_<<std::endl;

    in>>prof_throwing_;
    std::cout<<"\tthrowing: "<<prof_throwing_<<std::endl;

    in>>prof_fire_;
    std::cout<<"\tfirearms: "<<prof_fire_<<std::endl;

    getline(in, buffer);

    getline(in, buffer);
    getline(in, buffer);
    getline(in, buffer);

    std::cout<<std::endl;
}

TroopData::~TroopData()
{

}

void TroopData::remove_underscores(std::string& string_with_underscores)
{
    std::string::size_type pos = string_with_underscores.find("_");
    while(pos != std::string::npos)
    {
        string_with_underscores[pos] = ' ';
        pos = string_with_underscores.find("_");
    }
}

std::string TroopData::get_troop_description(std::string template_string)
{
    std::map<std::string, std::string> placeholders;

    placeholders["$NAME$"] = display_name_;
    placeholders["$NAME_PLURAL$"] = display_name_plural_;
    placeholders["$ID$"] = name_;

    placeholders["$STRENGTH$"] = boost::lexical_cast<std::string>(strength_);
    placeholders["$AGILITY$"] = boost::lexical_cast<std::string>(agility_);
    placeholders["$INTELLIGENCE$"] = boost::lexical_cast<std::string>(intelligence_);
    placeholders["$CHARISMA$"] = boost::lexical_cast<std::string>(charisma_);
    placeholders["$LEVEL$"] = boost::lexical_cast<std::string>(level_);

    placeholders["$PROF_1H$"] = boost::lexical_cast<std::string>(prof_1h_);
    placeholders["$PROF_2H$"] = boost::lexical_cast<std::string>(prof_2h_);
    placeholders["$PROF_POLEARMS$"] = boost::lexical_cast<std::string>(prof_polearms_);
    placeholders["$PROF_ARCHERY$"] = boost::lexical_cast<std::string>(prof_archer_);
    placeholders["$PROF_CROSSBOWS$"] = boost::lexical_cast<std::string>(prof_crossbow_);
    placeholders["$PROF_THROWING$"] = boost::lexical_cast<std::string>(prof_throwing_);
    placeholders["$PROF_FIREARMS$"] = boost::lexical_cast<std::string>(prof_fire_);

    for(std::map<std::string, std::string>::iterator it = placeholders.begin(); it != placeholders.end(); ++it)
    {
        std::string::size_type pos = template_string.find(it->first);
        while(pos != std::string::npos)
        {
            template_string.replace(pos, it->first.length(), it->second);
            pos = template_string.find(it->first);
        }
    }

    return template_string;
}
