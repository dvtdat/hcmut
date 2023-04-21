#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

struct BaseItem;
struct Events;

enum ItemType
{
    Antidote,
    PhoenixI,
    PhoenixII,
    PhoenixIII,
    PhoenixVI,
};

struct Node
{
public:

    Node * next;
};

class BaseBag
{
public:
    BaseKnight knight;
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
};

class DragonKnightBag: public BaseBag
{
public:

    DragonKnightBag(BaseKnight * baseKnight, int antidote, int phoenixDownI)
    {

    }

    bool insertFirst(BaseItem * item)
    {
        
    }

    BaseItem * get(ItemType itemType)
    {

    }
};

class BaseOpponent;

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight
{
protected:
    int id;
    int hp;
    int maxHP;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;

public:
    static BaseKnight * create(int id, int maxHP, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
};

class ArmyKnights
{
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem
{
public:
    virtual bool canUse (BaseKnight * knight) = 0;
    virtual void use (BaseKnight * knight) = 0;
};

class Antidote: public BaseItem
{
public:
    bool canUse(BaseKnight * knight)
    {

    }

    void use(BaseKnight * knight)
    {
        
    }
};

class PhoenixDownI: public BaseItem
{

};

class PhoenixDownII: public BaseItem
{

};

class PhoenixDownIII: public BaseItem
{

};

class PhoenixDownVI: public BaseItem
{

};

class Events
{
public:
    Events(const string & file_events);
    ~Events();

    int count() const;
    int get(int i) const;
};

class KnightAdventure
{
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__