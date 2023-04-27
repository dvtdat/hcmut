#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

const int INF = 2e9;
const int BAGNORMAL = 16;
const int BAGDRAGON = 14;
const int BAGLANCELOT = 19;
const int BAGPALADIN = INF;

const int DAMAGEMADBEAR = 10,   GILMADBEAR = 100,   CODEMADBEAR = 1;
const int DAMAGEBANDIT = 15,    GILBANDIT = 150,    CODEBANDIT = 2;
const int DAMAGELORDLUPIN = 45, GILLORDLUPIN = 450, CODELORDLUPIN = 3;
const int DAMAGEELF = 75,       GILELF = 750,       CODEELF = 4;
const int DAMAGETROLL = 95,     GILTROLL = 800,     CODETROLL = 5;

class BaseItem;
class BaseKnight;
class BaseBag;
struct Events;

bool isPrime(int);
bool is888(int);
bool isPythagorean(int);

enum ItemType
{
    ANTIDOTE,
    PHOENIXI,
    PHOENIXII,
    PHOENIXIII,
    PHOENIXIV,
};

class BaseBag
{
private:
    BaseKnight* knight;
    BaseItem* headItem;
    int size;
public:
    BaseBag(BaseKnight* knight, int antidote, int phoenixdownI);
    ~BaseBag() {}

    virtual bool insertFirst(BaseItem* item);
    virtual BaseItem* get(ItemType itemType);
    virtual string toString() const;
    void print();
};

class DragonKnightBag: public BaseBag
{
public:
    bool insertFirst(BaseItem* item)
    {

    }
    
    BaseItem* get(ItemType itemType)
    {

    }
    
    string toString() const
    {

    }
};

class BaseOpponent
{
private:
    int HP;
    int baseDamage;
    int gilOptain;
    int code;
public:
    BaseOpponent(int HP, int baseDamage, int gilOptain, int code) : 
        HP(HP), baseDamage(baseDamage), gilOptain(gilOptain), code(code) {}
    ~BaseOpponent() {}
};

class MadBear : virtual public BaseOpponent
{
public:
    MadBear() : BaseOpponent(1, DAMAGEMADBEAR, GILMADBEAR, CODEMADBEAR) {}
    ~MadBear() {}
};

class Bandit : virtual public BaseOpponent
{
public:
    Bandit() : BaseOpponent(1, DAMAGEBANDIT, GILBANDIT, CODEBANDIT) {}
    ~Bandit() {}
};

class LordLupin : virtual public BaseOpponent
{
public:
    LordLupin() : BaseOpponent(1, DAMAGELORDLUPIN, GILLORDLUPIN, CODELORDLUPIN) {}
    ~LordLupin() {}
};

class Elf : virtual public BaseOpponent
{
    Elf() : BaseOpponent(1, DAMAGEELF, GILELF, CODEELF) {}
    ~Elf() {}
};

class Troll : virtual public BaseOpponent
{
    Troll() : BaseOpponent(1, DAMAGETROLL, GILTROLL, CODETROLL) {}
    ~Troll() {}
};

class Tornbery : virtual public BaseOpponent
{
    
};

class QueenOfCards : virtual public BaseOpponent
{
    
};

class NinaDeRings : virtual public BaseOpponent
{
    
};

class DurianGarden : virtual public BaseOpponent
{
    
};

class OmegaWeapon : virtual public BaseOpponent
{
    
};

class Hades : virtual public BaseOpponent
{
    
};

enum KnightType 
{
    PALADIN, 
    LANCELOT, 
    DRAGON, 
    NORMAL 
};

class BaseKnight
{
protected:
    int id;
    int HP;
    int maxHP;
    int level;
    int gil;
    BaseBag* bag;
    KnightType knightType;

public:
    BaseKnight(int id, int maxHP, int level, int gil, int antidote, int phoenixdownI, KnightType knightType) : 
        id(id), maxHP(maxHP), level(level), gil(gil), knightType(knightType) 
    {
        bag = new BaseBag(this, antidote, phoenixdownI);
    }
    ~BaseKnight() {}
    static BaseKnight* create(int id, int maxHP, int level, int gil, int antidote, int phoenixdownI);
    KnightType getType()
    {
        return knightType;
    }
    //virtual void fight() = 0;
    string toString() const;
    void print();
};

class PaladinKnight : virtual public BaseKnight
{
public:
    PaladinKnight(int id, int maxHP, int level, int gil, int antidote, int phoenixdownI) :
        BaseKnight(id, maxHP, level, gil, antidote, phoenixdownI, PALADIN) {}
    ~PaladinKnight() {}
};

class LancelotKnight : virtual public BaseKnight
{
public:
    LancelotKnight(int id, int maxHP, int level, int gil, int antidote, int phoenixdownI) :
        BaseKnight(id, maxHP, level, gil, antidote, phoenixdownI, LANCELOT) {}
    ~LancelotKnight() {}
};

class DragonKnight : virtual public BaseKnight
{
public:
    DragonKnight(int id, int maxHP, int level, int gil, int antidote, int phoenixdownI) :
        BaseKnight(id, maxHP, level, gil, antidote, phoenixdownI, DRAGON) {}
    ~DragonKnight() {}
};

class NormalKnight : virtual public BaseKnight
{
public:
    NormalKnight(int id, int maxHP, int level, int gil, int antidote, int phoenixdownI) :
        BaseKnight(id, maxHP, level, gil, antidote, phoenixdownI, NORMAL) {}
    ~NormalKnight() {}
};

class ArmyKnights
{
private:
    int* nKnight;
    BaseKnight** knights;
public:
    ArmyKnights(const string &file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent* opponent);
    bool adventure (Events* events);
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
protected:
    ItemType type;
    BaseItem* next;
    BaseKnight* knight;
public:
    BaseItem(ItemType type, BaseItem* next) : type(type), next(next) {}
    virtual ~BaseItem() 
    {
        BaseItem* cur = this;
        while (cur)
        {
            BaseItem* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    virtual bool canUse (BaseKnight * knight) = 0;
    virtual void use (BaseKnight * knight) = 0;

    void print()
    {
        for (BaseItem* ptr = this; ptr; ptr = ptr->next)
        {
            cout << ptr->type << ' ';
        }
        cout << '\n';
    }
};

class Antidote: public BaseItem
{
public:
    Antidote(BaseItem* next) : BaseItem(ANTIDOTE, next) {}
    ~Antidote() {}

    bool canUse(BaseKnight* knight)
    {

    }

    void use(BaseKnight* knight)
    {
        
    }
};

class PhoenixDownI : public BaseItem
{
public:
    PhoenixDownI(BaseItem* next) : BaseItem(PHOENIXI, next) {}
    ~PhoenixDownI() {}

    bool canUse(BaseKnight* knight)
    {

    }

    void use(BaseKnight* knight)
    {
        
    }
};

class PhoenixDownII : public BaseItem
{
public:
    PhoenixDownII(BaseItem* next) : BaseItem(PHOENIXII, next) {}
    ~PhoenixDownII() {}

    bool canUse(BaseKnight* knight)
    {

    }

    void use(BaseKnight* knight)
    {
        
    }
};

class PhoenixDownIII : public BaseItem
{
public:
    PhoenixDownIII(BaseItem* next) : BaseItem(PHOENIXI, next) {}
    ~PhoenixDownIII() {}

    bool canUse(BaseKnight* knight)
    {

    }

    void use(BaseKnight* knight)
    {
        
    }
};

class PhoenixDownIV : public BaseItem
{
public:
    PhoenixDownIV(BaseItem* next) : BaseItem(PHOENIXI, next) {}
    ~PhoenixDownIV() {}

    bool canUse(BaseKnight* knight)
    {

    }

    void use(BaseKnight* knight)
    {
        
    }
};

class Events
{
private:
    int* nEvent;
    int* event;
public:
    Events(const string & file_events);
    ~Events();

    int count() const;
    int get(int i) const;
};

class KnightAdventure
{
private:
    ArmyKnights* armyKnights;
    Events* events;
public:
    KnightAdventure();
    ~KnightAdventure();

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};
#endif // __KNIGHT2_H__