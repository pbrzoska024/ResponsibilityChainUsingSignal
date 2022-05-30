#include <iostream>
#include <string>
#include <boost/signals2.hpp>


using namespace std;
using namespace boost::signals2;

struct Query{
    string creature_name;
    enum Argument { attack, defense } argument;
    int result;

    Query(const string &creatureName, Argument argument, int result) : creature_name(creatureName), argument(argument),
                                                                       result(result) {}


};


struct Game { // mediator
    boost::signals2::signal<void(Query&)> queries;
};

struct Creature {
    Game &game;
    int attack, defense;
    string name;

    Creature(Game &game, int attack, int defense, const string &name) : game(game), attack(attack), defense(defense),
                                                                        name(name) {}
    int get_attack() const {
        Query q{name, Query::Argument::attack, attack};
        game.queries(q);
        return q.result;
    }

    friend ostream &operator<<(ostream &os, const Creature &creature) {
        os << "attack: " << creature.get_attack() <<  " name: " << creature.name;
        return os;
    }
};


class CreatureModifier
{
    Game &game;
    Creature &creature;

public:
    CreatureModifier(Game &game, Creature &creature) : game(game), creature(creature) {}

    virtual ~CreatureModifier() = default;
};

class DoubleAttackModifier : public CreatureModifier{
    connection conn;
public:
    DoubleAttackModifier(Game &game, Creature &creature)
    : CreatureModifier(game, creature)
    {
        conn = game.queries.connect([&](Query &q)
         {
            if (q.creature_name == creature.name && q.argument == Query::Argument::attack)
            {
                q.result *= 2;
            }

         });
    }
    ~DoubleAttackModifier() { conn.disconnect(); }
};

int main() {
    Game game;
    Creature goblin {game, 2, 2, "Strong Goblin",};

    cout << goblin << endl;
    {
        DoubleAttackModifier dam{game, goblin};
        cout << goblin << endl;
    }

    cout << goblin << endl;

    return 0;
}
