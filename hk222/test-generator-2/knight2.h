#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

const int INF = 2e9;
const int MAXN = 1010;
const int BAGNORMAL = 19;
const int BAGDRAGON = 14;
const int BAGLANCELOT = 16;
const int BAGPALADIN = INF;

const int DAMAGEMADBEAR = 10,   GILMADBEAR = 100,   CODEMADBEAR = 1;
const int DAMAGEBANDIT = 15,    GILBANDIT = 150,    CODEBANDIT = 2;
const int DAMAGELORDLUPIN = 45, GILLORDLUPIN = 450, CODELORDLUPIN = 3;
const int DAMAGEELF = 75,       GILELF = 750,       CODEELF = 4;
const int DAMAGETROLL = 95,     GILTROLL = 800,     CODETROLL = 5;
const int CODETORNBERY = 6;
const int CODEQUEEN = 7;
const int CODENINA = 8;
const int CODEDURIAN = 9;
const int CODEOMEGA = 10;
const int CODEHADES = 11;
const int CODEULTIMECIA = 99;

const int PALADINSHIELD = 0, LANCELOTSPEAR = 1, GUINEVEREHAIR = 2, EXCALIBURSWORD = 3;
const int CODEPALADINSHIELD = 95, CODELANCELOTSPEAR = 96, CODEGUINEVEREHAIR = 97, CODEEXCALIBURSWORD = 98;
const int MAXGIL = 999, MAXLEVEL = 10, MINHP = 0;

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
    int size;
    BaseKnight* knight;
public:
    BaseItem* headItem;
    BaseBag(BaseKnight* knight, int antidote, int phoenixdownI);
    ~BaseBag() {}

    virtual bool insertFirst(ItemType type);
    virtual void dropFirst();
    virtual void swapItem(BaseItem* item);
    virtual BaseItem* get(ItemType type);
    virtual BaseItem* getPhoenixDown(BaseKnight* knight);
    virtual string toString() const;
    void print();
};

class BaseOpponent
{
private:
    int baseDamage;
    int gilOptain;
    int levelOptain;
    int code;
public:
    BaseOpponent(int baseDamage, int levelOptain, int gilOptain, int code) : baseDamage(baseDamage), levelOptain(levelOptain), gilOptain(gilOptain), code(code) {}
    virtual ~BaseOpponent() {}

    int getBaseDamage() { return baseDamage; }
    int getGilOptain() { return gilOptain; }
    int getLevelOptain() { return levelOptain; }
    int getCode() { return code; }

    void print()
    {
        cout << "The opponent is type " << code << ", have base damage of " << baseDamage 
            << " and when defeated, the knight will gain " << gilOptain << " gil\n";
    }
};

class MadBear : public BaseOpponent
{
public:
    MadBear() : BaseOpponent(DAMAGEMADBEAR, 0, GILMADBEAR, CODEMADBEAR) {}
    ~MadBear() {}
};

class Bandit : public BaseOpponent
{
public:
    Bandit() : BaseOpponent(DAMAGEBANDIT, 0, GILBANDIT, CODEBANDIT) {}
    ~Bandit() {}
};

class LordLupin : public BaseOpponent
{
public:
    LordLupin() : BaseOpponent(DAMAGELORDLUPIN, 0, GILLORDLUPIN, CODELORDLUPIN) {}
    ~LordLupin() {}
};

class Elf : public BaseOpponent
{
public:
    Elf() : BaseOpponent(DAMAGEELF, 0, GILELF, CODEELF) {}
    ~Elf() {}
};

class Troll : public BaseOpponent
{
public:
    Troll() : BaseOpponent(DAMAGETROLL, 0, GILTROLL, CODETROLL) {}
    ~Troll() {}
};

class Tornbery : public BaseOpponent
{
public:
    Tornbery() : BaseOpponent(0, 1, 0, CODETORNBERY) {}
    ~Tornbery() {}
};

class QueenOfCards : public BaseOpponent
{
public:
    QueenOfCards() : BaseOpponent(0, 0, 0, CODEQUEEN) {}
    ~QueenOfCards() {}
};

class NinaDeRings : public BaseOpponent
{
public:
    NinaDeRings() : BaseOpponent(0, 0, 0, CODENINA) {}
    ~NinaDeRings() {}
};

class DurianGarden : public BaseOpponent
{
public:
    DurianGarden() : BaseOpponent(0, 0, 0, CODEDURIAN) {}
    ~DurianGarden() {}
};

class OmegaWeapon : public BaseOpponent
{
public:
    OmegaWeapon() : BaseOpponent(0, 0, 0, CODEOMEGA) {}
    ~OmegaWeapon() {}
};

class Hades : public BaseOpponent
{
public:
    Hades() : BaseOpponent(0, 0, 0, CODEHADES) {}
    ~Hades() {}
};

class Ultimecia : public BaseOpponent
{
public:
    Ultimecia() : BaseOpponent(0, 0, 0, CODEULTIMECIA) {}
    ~Ultimecia() {}
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
        id(id), HP(maxHP), maxHP(maxHP), level(level), gil(gil), knightType(knightType) 
    {
        bag = new BaseBag(this, antidote, phoenixdownI);
    }
    virtual ~BaseKnight() { delete bag; }
    static BaseKnight* create(int id, int maxHP, int level, int gil, int antidote, int phoenixdownI);

    int getHP() { return HP; }
    int getMaxHP() { return maxHP; }
    int getLevel() { return level; }
    int getGil() { return gil; }
    BaseBag* getBag() { return (bag != nullptr ? bag : nullptr); }
    KnightType getType() { return knightType; }

    void changeHP(int newHP) { HP = min(newHP, maxHP); }
    void changeGil(int gilOptain) { gil = gilOptain; }
    void changeLevel(int newLevel) { level = min(MAXLEVEL, newLevel); }

    virtual bool fight(BaseOpponent* opponent, int idx) = 0;
    string toString() const;
    void print();
};

class PaladinKnight : virtual public BaseKnight
{
public:
    PaladinKnight(int id, int maxHP, int level, int gil, int antidote, int phoenixdownI) :
        BaseKnight(id, maxHP, level, gil, antidote, phoenixdownI, PALADIN) {}
    ~PaladinKnight() {}
    bool fight(BaseOpponent* opponent, int idx);
};

class LancelotKnight : virtual public BaseKnight
{
public:
    LancelotKnight(int id, int maxHP, int level, int gil, int antidote, int phoenixdownI) :
        BaseKnight(id, maxHP, level, gil, antidote, phoenixdownI, LANCELOT) {}
    ~LancelotKnight() {}
    bool fight(BaseOpponent* opponent, int idx);
};

class DragonKnight : virtual public BaseKnight
{
public:
    DragonKnight(int id, int maxHP, int level, int gil, int antidote, int phoenixdownI) :
        BaseKnight(id, maxHP, level, gil, 0, phoenixdownI, DRAGON) {}
    ~DragonKnight() {}
    bool fight(BaseOpponent* opponent, int idx);
};

class NormalKnight : virtual public BaseKnight
{
public:
    NormalKnight(int id, int maxHP, int level, int gil, int antidote, int phoenixdownI) :
        BaseKnight(id, maxHP, level, gil, antidote, phoenixdownI, NORMAL) {}
    ~NormalKnight() {}
    bool fight(BaseOpponent* opponent, int idx);
};

class ArmyKnights
{
private:
    int nKnight;
    int nCurKnight;
    BaseKnight** knights;
    int excessGil;
    bool hasTreasure[4] = {false, false, false, false};
    bool meetOmega = false;
    bool meetHades = false;
public:
    ArmyKnights(const string &file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent* opponent, int idx);            // NEED TO FIX
    bool adventure(Events* events);
    int count() const;
    BaseKnight* lastKnight() const;

    void killLastKnight();
    void setExcessGil(int newExcessGil) {excessGil = newExcessGil; }
    void setTreasure(int idx) { hasTreasure[idx] = true; }
    void setOmega() { meetOmega = true; }
    void setHades() { meetHades = true; }
    void distrubuteGil();

    bool hasMetOmega() const;
    bool hasMetHades() const;
    bool hasThreeTreasure() const;
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
    BaseKnight* knight;
public:
    BaseItem* next;
    BaseItem(ItemType type, BaseItem* next) : type(type), next(next) {}
    virtual ~BaseItem();

    ItemType getType() { return type; }

    virtual bool canUse(BaseKnight* knight) = 0;
    virtual void use(BaseKnight* knight) = 0;
};

class Antidote: public BaseItem
{
public:
    Antidote(BaseItem* next) : BaseItem(ANTIDOTE, next) {}
    ~Antidote() {}

    bool canUse(BaseKnight* knight)
    {
        return true;
    }

    void use(BaseKnight* knight)
    {
        BaseItem* item = knight->getBag()->get(ANTIDOTE);
    }
};

class PhoenixDownI : public BaseItem
{
public:
    PhoenixDownI(BaseItem* next) : BaseItem(PHOENIXI, next) {}
    ~PhoenixDownI() {}

    bool canUse(BaseKnight* knight)
    {
        return (knight->getHP() <= 0); 
    }

    void use(BaseKnight* knight)
    {
        knight->changeHP(knight->getMaxHP());
    }
};

class PhoenixDownII : public BaseItem
{
public:
    PhoenixDownII(BaseItem* next) : BaseItem(PHOENIXII, next) {}
    ~PhoenixDownII() {}
    
    bool canUse(BaseKnight* knight)
    {
        return (knight->getHP() < knight->getMaxHP() / 4); 
    }
    
    void use(BaseKnight* knight)
    {
        knight->changeHP(knight->getMaxHP());
    }
};

class PhoenixDownIII : public BaseItem
{
public:
    PhoenixDownIII(BaseItem* next) : BaseItem(PHOENIXIII, next) {}
    ~PhoenixDownIII() {}
    
    bool canUse(BaseKnight* knight)
    {
        return (knight->getHP() < knight->getMaxHP() / 3); 
    }
    
    void use(BaseKnight* knight)
    {
        if (knight->getHP() <= 0) knight->changeHP(knight->getMaxHP() / 3);
        else knight->changeHP(knight->getHP() + knight->getMaxHP() / 4);
    }
};

class PhoenixDownIV : public BaseItem
{
public:
    PhoenixDownIV(BaseItem* next) : BaseItem(PHOENIXIV, next) {}
    ~PhoenixDownIV() {}
    
    bool canUse(BaseKnight* knight)
    {
        return (knight->getHP() < knight->getMaxHP() / 2); 
    }

    void use(BaseKnight* knight)
    {
        if (knight->getHP() <= 0) knight->changeHP(knight->getMaxHP() / 2);
        else knight->changeHP(knight->getHP() + knight->getMaxHP() / 5);
    }
};

class Events
{
private:
    int nEvent;
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