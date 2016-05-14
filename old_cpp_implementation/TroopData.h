#ifndef TROOPDATA_H
#define TROOPDATA_H

#include <fstream>
#include <string>
#include <map>
#include <bitset>

class TroopData
{
    public:
        TroopData();
        TroopData(std::ifstream& in, unsigned version);
        virtual ~TroopData();

        std::string get_name() const { return name_; };
        std::string get_display_name() const { return display_name_; };
        std::string get_display_name_plural() const { return display_name_plural_; };
        unsigned get_upgrade1() const { return upgrade1_; };
        unsigned get_upgrade2() const { return upgrade2_; };
        unsigned get_level() const { return level_; };
        unsigned get_strength() const { return strength_; };
        unsigned get_agility() const { return agility_; };
        unsigned get_prof_1h() const { return prof_1h_; };
        unsigned get_prof_2h() const { return prof_2h_; };
        unsigned get_prof_polearms() const { return prof_polearms_; };
        unsigned get_prof_archery() const { return prof_archer_; };
        unsigned get_prof_crossbow() const { return prof_crossbow_; };
        unsigned get_prof_throwing() const { return prof_throwing_; };
        unsigned get_prof_fire() const { return prof_fire_; };
        bool is_mounted() const { return flags_ & 16777216; };
        bool is_ranged() const { return flags_ & 67108864; };

        std::string get_troop_description(std::string template_string);

    private:
        static void remove_underscores(std::string& string_with_underscores);

        std::string name_, display_name_, display_name_plural_;
        unsigned faction_id_;
        unsigned flags_;
        unsigned upgrade1_, upgrade2_;
        unsigned strength_, agility_, intelligence_, charisma_, level_;
        unsigned prof_1h_, prof_2h_, prof_polearms_, prof_archer_, prof_crossbow_, prof_throwing_, prof_fire_;
};

#endif // TROOPDATA_H
