#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

// Add 4 types of phoenixDown to Item Type enum

enum ItemType
{ /* TODO: */
  Antidote = 0,
  PhoenixDownI,
  PhoenixDownII,
  PhoenixDownIII,
  PhoenixDownIV,
  PHOENIX
};

class BaseKnight;
class Events;

class BaseItem
{
public:
    virtual bool canUse(BaseKnight *knight) = 0;
    virtual void use(BaseKnight *knight) = 0;
    virtual ItemType getType() const;
    virtual ItemType getGeneralType() const;

    virtual void setType(ItemType itemType) {
        this->typeOfItem = itemType;
    }

    // virtual BaseItem(){};
    virtual ~BaseItem() {};

    // SetType for each item

    // virtual void setType() = 0;

protected:
    //General type to find the nearest PhoenixDown
    ItemType generalType = PHOENIX;
    ItemType typeOfItem;

    // In case we need general type to find the nearest item in linkedList
    // And typeOfItem to use in print function
    //    ItemType generalType;
};

class BaseBag
{
private:
    // Initialize Linked list for BaseBag slots

    struct Node
    {
        // Value of node will be BaseItem pointer
        BaseItem *nodeItem;
        Node *next;

        // Using constructor to insert incase of nodeSize > 0 && < maximumSize
        Node(BaseItem *itemInitial, Node *nextPtr = nullptr)
            : nodeItem(itemInitial), next(nextPtr)
        {
        }

        // Overloading Node structure to only take 1 parameter in case nodeSize == 0

        Node(BaseItem *itemInitial)
            : nodeItem(itemInitial)
        {
        }

        ~Node()
        {
            delete nodeItem;
        }
    };

    int nodeSize;
    int maximumSize;
    Node *head;
    // BaseItem itemType;
    // BaseItem *itemToUse;

public:
    virtual bool insertFirst(BaseItem *item);

    //original
    // virtual BaseItem *get(ItemType itemType);

    // Overload *get function to make checking functionality available
    virtual BaseItem *get(ItemType itemType, BaseKnight *knight);

    virtual string toString() const;
    // virtual BaseItem getType() const;
    // virtual useItem(ItemType itemType, BaseKnight *knight);

    // since class method Delete 3 items function it has access to the protected member variable head  and can modify it directly without the need to pass by reference, So we dont have to add ( Node * &head ) parameter to this function
    virtual void delete3Items();

    virtual void deleteAfterUsing()
    {
        Node *tempNode = head;
        head = head->next;
        --nodeSize;

        delete tempNode;
    };

    void setMaximumSize( int maxSize)
    {
        maximumSize = maxSize; 
    }

    // Use constructor as a way to create linked list

    BaseBag(BaseKnight *knight, int phoenixDownI, int antidote);

    virtual int getNodeSize() const {
        return this->nodeSize;
    }

    virtual int getMaximumSize() const {
        return this->maximumSize;
    }
};

class BaseOpponent
{

public:
    // BaseOpponent(int id, int opponentGil, int opponentBaseDamage)
    //     : id(id), gil(opponentGil), baseDamage(opponentBaseDamage)
    // {
    // }

    BaseOpponent()
    {}

    virtual ~BaseOpponent(){};

    // virtual int getID() = 0;

    // Dont need to turn getLevel into pure virtual function, since every opponent will use the same getLevel function without any specifically changes
    int getLevel(int eventIndex, Events *eventPtr);

    virtual int getGil() {
        return gil;
    };

    int getBaseDamage(int eventIndex, Events *eventPtr);

    // Return opponent id;

    // int getID(int eventIndex) const;

    // Each opponent should have unique id

    //check later


    // virtual void setID() = 0;

    // dont need virtual function
    //  getLevel, getBaseDamage;

    // Need virtual function
    //  getGill;

protected:
    int level;
    // Maybe id is unecessary
    int id;
    int gil;
    int baseDamage;

    // Use this to access event index
    // Events *eventPtr;
};

enum KnightType
{
    PALADIN = 0,
    LANCELOT,
    DRAGON,
    NORMAL
};

class BaseKnight
{
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag *bag;
    KnightType knightType;

public:
    static BaseKnight *create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() ;

    // getHP, getGil, getType need to be virtual function in baseClass, For scenario like BaseKnight *newKnight = Vehicle::create('hp', 'dragon',...),then another function with parameter like BaseKnight *newKnight implement knight-> getHP() it will return hp of that type of knight, in this case Dragon type
    virtual int getHP() const;
    virtual int getGil() const;
    virtual KnightType getType() const;
    virtual int getMaxHp() const;
    virtual int getAntidote() const;
    virtual void setAntidote(int newAntidote);
    virtual void setHP(int addedAmount);

    //getLevel method

    int getLevel() const {
        return level;
    }

    BaseBag *getBag() const
    {
        return bag;
    }

    virtual void setGil(int gilToSet);

    // HP < 0 handler, 2 steps: first PHOENIX, second GIL
    virtual void hpBelow0Handler();

    // General case for winning and losing these type of villains

    // event handler 1 to 5
    void winMadBearToTroll(BaseOpponent *opponent);
    void loseMadBearToTroll(BaseOpponent *opponent, int eventIndex, Events *eventPtr);

    void winTornbery(BaseOpponent *opponent);
    void loseTornbery(BaseOpponent *opponent, int eventIndex, Events *eventPtr);

    void winQueenOfCards(BaseOpponent *opponent);
    void loseQueenOfCards(BaseOpponent *opponent);

    void winOmegaWeapon(BaseOpponent *opponent);
    void loseOmegaWeapon(BaseOpponent *opponent);

    void winHades(BaseOpponent *opponent);
    void loseHades(BaseOpponent *opponent);

    void meetNina();

    void lostInDurianGarden();

    // fight method need to be pure virtual function

    // check later
    //  virtual void fight(BaseOpponent *opponent, int eventIndex, Events *eventPtr) = 0;

    // Should be only 1 virtual void fight(BaseOpponent * opponent, int eventIndex, Events *eventPtr); for BaseKnight method only
};

class ArmyKnights
{
public:
    ArmyKnights(const string &file_armyknights);
    ~ArmyKnights();

    //original
    // bool fight(BaseOpponent *opponent);

    // Overload ArmyKnights::fight function to receive 2 more parameters (BaseOpponent *opponent,int eventIndex, Events *eventPtr) to symmetric with each knight fighting method

    bool fight( int knightIndex, int eventIndex, Events *eventPtr);

    //original
    // bool adventure(Events *events);

    // Overload adventure to make it take BaseOpponent parameter
    bool adventure( Events *events);

    int count() const;
    BaseKnight *lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;

    // Delete knight when unable to revive anymore

    void deleteKnight(int position);

    // passing gil to previous knight

    void passGil();

protected:
    // BaseKnight** army;
    BaseKnight **knight;
    int realArmyKnightSize = 0;
    int knightCounter = 0;
    BaseOpponent *opponent;

    // Conditional variable;

    bool hasShield = false, hasSpear = false, hasHair = false, hasSword = false, metOmega = false, metHades = false, defeatUltimecia = false;
};

// class BaseItem
// {
// public:
//     virtual bool canUse(BaseKnight *knight) = 0;
//     virtual void use(BaseKnight *knight) = 0;
//     virtual ItemType getType() const;

//     //SetType for each item

//     virtual void setType() = 0;

// protected:
//    ItemType typeOfItem;

//    //In case we need general type to find the nearest item in linkedList
//    //And typeOfItem to use in print function
//    ItemType generalType
// };

class Events
{
public:
    Events(const string &file_events);
    ~Events();

    int count() const;
    int get(int i) const;

protected:
    // Declare eventID as pointer in
    int *eventID;
    // Declare int type event size but in int type
    int eventRealSize;
};

class KnightAdventure
{
private:
    ArmyKnights *armyKnights;
    Events *events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

bool isPrime(int const &number);
bool isPythagoras(int const &number);

// Define 4 derived knight type from baseKnight class

class PaladinKnight : public BaseKnight
{

    // construct PaladinKnight
public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    {
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->level = level;
        this->gil = gil;
        this->antidote = antidote;
        // bag instance

        this->knightType = PALADIN;

        this->bag = new BaseBag(this, phoenixdownI, antidote );

        // this->knightType = PALADIN;
    }
    // virtual void fight(BaseOpponent * opponent, int eventIndex, Events *eventPtr) override;
};

class LancelotKnight : public BaseKnight
{

    // construct LancelotKnight
public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    {
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->level = level;
        this->gil = gil;
        this->antidote = antidote;
        // bag instance

        this->knightType = LANCELOT;

        this->bag = new BaseBag(this, phoenixdownI, antidote );
    
        // this->knightType = LANCELOT;
    }
    // virtual void fight(BaseOpponent * opponent, int eventIndex, Events *eventPtr) override;
};

class DragonKnight : public BaseKnight
{

    // construct DragonKnight
public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    {
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->level = level;
        this->gil = gil;
        this->antidote = antidote;
        // bag instance
        this->knightType = DRAGON;

        this->bag = new BaseBag(this, phoenixdownI, antidote );

        // this->knightType = DRAGON;
    }
    // virtual void fight(BaseOpponent * opponent, int eventIndex, Events *eventPtr) override;
};

class NormalKnight : public BaseKnight
{

    // construct normal Knight
public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    {
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->level = level;
        this->gil = gil;
        this->antidote = antidote;
        // bag instance

        //Need to initialize knightType before this->bag because inside bag Constructor does consider knightType to create maxSize
        this->knightType = NORMAL;

        this->bag = new BaseBag(this, phoenixdownI, antidote );

        // this->knightType = NORMAL;
    }
    // virtual void fight(BaseOpponent * opponent, int eventIndex, Events *eventPtr) override;
};

// Derived class of baseOpponent - classes MadBear, Bandit, LordLupin, Elf, Troll, Tornbery, QueenOfCards, NinaDeRings, DurianGarden, OmegaWeapon, Hades

class MadBear : public BaseOpponent
{
public:
    MadBear();
    // int getGil() override;
};
class Bandit : public BaseOpponent
{
public:
    Bandit();
    // int getGil() override;
};

class LordLupin : public BaseOpponent
{
public:
    LordLupin();
    // int getGil() override;
};

class Elf : public BaseOpponent
{
public:
    Elf();
    // int getGil() override;
};

class Troll : public BaseOpponent
{
public:
    Troll();
    // int getGil() override;
};

class Tornbery : public BaseOpponent
{
public:
    Tornbery();
    // int getGil() override;
};

// Queen of card should have new getGil
class QueenOfCards : public BaseOpponent
{
public:
    // Double knight's gill when winning
    QueenOfCards();
    // int getGil() override;
};

class NinaDeRings : public BaseOpponent
{
public:
    // int getGil() override;
    NinaDeRings();
};

class DurianGarden : public BaseOpponent
{
public:
    // int getGil() override;
    DurianGarden();
};

class OmegaWeapon : public BaseOpponent
{
public:
    OmegaWeapon();
    // int getGil() override;
};

class Hades : public BaseOpponent
{
public:
    // int getGil() override;
    Hades();
};

// Derived class from BaseItem class - Antidote, PhoenixDownI, PhoenixDownII, PhoenixDownIII, PhoenixDownIV

class Antidote : public BaseItem
{
public:
    Antidote()
        {
            this->generalType = ::Antidote;
            this->typeOfItem = ::Antidote;
        }

    bool canUse(BaseKnight *knight) override;
    virtual void use(BaseKnight *knight) override;
};

class PhoenixDownI : public BaseItem
{
public:
    PhoenixDownI()
        {
            
            this->typeOfItem = ::PhoenixDownI;
        };

    bool canUse(BaseKnight *knight) override;
    virtual void use(BaseKnight *knight) override;
};

class PhoenixDownII : public BaseItem
{
public:
    PhoenixDownII()
        {
            this->typeOfItem = ::PhoenixDownII;
        };

    bool canUse(BaseKnight *knight) override;
    virtual void use(BaseKnight *knight) override;
};

class PhoenixDownIII : public BaseItem
{
public:
    PhoenixDownIII()
        {
            this->typeOfItem = ::PhoenixDownIII;
        };
    bool canUse(BaseKnight *knight) override;
    virtual void use(BaseKnight *knight) override;
};

class PhoenixDownIV : public BaseItem
{
public:
    PhoenixDownIV()
        {
            this->typeOfItem = ::PhoenixDownIV;
        };
    bool canUse(BaseKnight *knight) override;
    virtual void use(BaseKnight *knight) override;
};

// enum ItemType
// { /* TODO: */
//   ANTIDOTE = 0,
//   PHOENIX,
//   Antidote,
//   PhoenixDownI,
//   PhoenixDownII,
//   PhoenixDownIII,
//   PhoenixDownIV
// };

#endif // __KNIGHT2_H__