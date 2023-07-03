#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

class BaseItem;
class BaseBag;
class Events;
class Phoenixdown;
class Antidote;
class BaseKnight;


enum ItemType {ANTIDOTE = 0, PHOENIXDOWN};

class BaseItem {
    protected:
    ItemType itemtype;
public:
    // BaseItem * next;
    // BaseItem * item;
    // BaseItem() {
    //     item = NULL;
    //     next = NULL;
    //     }
    // BaseItem(item) ()


    virtual ItemType getItemType() {return itemtype;}
    virtual string turntostring() = 0;
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};

class Phoenixdown : public BaseItem {
    protected:
    int type_of_phoenixdown;
public:
    void setType(int type_of_phoenixdown) {this->type_of_phoenixdown = type_of_phoenixdown;}
    Phoenixdown(int type = 1) {
        this->itemtype = PHOENIXDOWN;
        type_of_phoenixdown = type;
    }
    ~Phoenixdown() {}
    string turntostring() {
        string arr[4];
        arr[0] = "I";
        arr[1] = "II";
        arr[2] = "III";
        arr[3] = "IV";
        return "Phoenix" + arr[type_of_phoenixdown - 1];
    }

    bool canUse(BaseKnight* knight);


    void use(BaseKnight* knight);
};

class Antidote : public BaseItem {
    public:
    string turntostring() { return "Antidote"; }
    Antidote() {
    this->itemtype = ANTIDOTE;
    }
    ~Antidote() {};
    bool canUse(BaseKnight* knight)
    {
        return true;
    }

    void use(BaseKnight* knight)
    {
        return;
    }
};

class BaseBag {
    
class Node {
    public:
    BaseItem * item;
    Node * next;
    Node(BaseItem * i, Node * nextptr = nullptr) {item = i; next = nextptr;}
    ~Node() { delete item; delete next;}
    };
    
    Node *head = nullptr;
    int num_item_in_bag = 0;
    int max_slot;

public:
    BaseBag(int phoenixdownI, int antidote, int max);
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
    virtual bool useItem(ItemType itemType, BaseKnight* knight);
    virtual void dropItem();
    virtual BaseItem * swap(ItemType ItemType, BaseKnight* knight);
};


class BaseOpponent {
    int levelO;
    int baseDamage;
    int gil_get_if_win;
    int event_id;
    public:
    BaseOpponent(int level, int base, int gil, int id) {levelO = level; baseDamage = base; gil_get_if_win = gil; event_id = id;}
    int getLevelO() {return levelO;}
    int getBaseDamage() {return baseDamage;}
    int getGilGetIfWin() {return gil_get_if_win;}
    int getEventId() {return event_id;}
    int num_knights;

};

class MadBear : public BaseOpponent {


};

class Bandit : public BaseOpponent {

};

class LordLupin : public BaseOpponent {

};

class Elf : public BaseOpponent {

};

class Troll : public BaseOpponent {

};

enum KnightType { PALADIN = 0, LANCELOT = 1 , DRAGON = 2 , NORMAL = 3 };

class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    int phoenixdownI;
    BaseBag * bag;
    KnightType knightType;

public:

    
    int getId() const { return id; }
    void setId(int id) { this -> id = id; }

    int getHp() const { return hp; }
    void setHp(int hp) { this -> hp = hp; }

    int getMaxhp() const { return maxhp; }
    void setMaxhp(int maxhp) { this -> maxhp = maxhp; }

    int getLevel() const { return level; }
    void setLevel(int level) { this -> level = level; }

    int getGil() const { return gil; }
    void setGil(int gil) { this -> gil = gil; }

    int getAntidote() const { return antidote; }
    void setAntidote(int antidote) { this -> antidote = antidote; }

    int getPhoenixdownI() const { return phoenixdownI; }
    void setPhoenixdownI(int phoenixdownI) { this -> phoenixdownI = phoenixdownI; }

    BaseBag *getBag() {return bag;}

    KnightType getType() const {return knightType;}
    virtual void fight(BaseOpponent* opponent) = 0;

    virtual bool handleWhenHpDown();

    void win_MadBear(BaseOpponent* opponent) {
        this->gil += opponent->getGilGetIfWin();
    }

    void lose_MadBear(BaseOpponent* opponent) {
        int baseDamage = opponent->getBaseDamage();
        int levelO = opponent->getLevelO();
        this->hp -=  baseDamage * (levelO - this->level);
        handleWhenHpDown();
    }

    void win_Bandit(BaseOpponent* opponent) {
        this->gil += opponent->getGilGetIfWin();
    }

    void lose_Bandit(BaseOpponent* opponent) {
        int baseDamage = opponent->getBaseDamage();
        int levelO = opponent->getLevelO();
        this->hp -=  baseDamage * (levelO - this->level);
        handleWhenHpDown();
    }

    void win_LordLupin(BaseOpponent* opponent) {
        this->gil += opponent->getGilGetIfWin();
    }

    void lose_LordLupin(BaseOpponent* opponent) {
        int baseDamage = opponent->getBaseDamage();
        int levelO = opponent->getLevelO();
        this->hp -=  baseDamage * (levelO - this->level);
        handleWhenHpDown();
    }

    void win_Elf(BaseOpponent* opponent) {
        this->gil += opponent->getGilGetIfWin();
    }

    void lose_Elf(BaseOpponent* opponent) {
        int baseDamage = opponent->getBaseDamage();
        int levelO = opponent->getLevelO();
        this->hp -=  baseDamage * (levelO - this->level);
        handleWhenHpDown();
    }

    void win_Troll(BaseOpponent* opponent) {
        this->gil += opponent->getGilGetIfWin();
    }

    void lose_Troll(BaseOpponent* opponent) {
        int baseDamage = opponent->getBaseDamage();
        int levelO = opponent->getLevelO();
        this->hp -=  baseDamage * (levelO - this->level);
        handleWhenHpDown();
    }

    void win_Tornbery(BaseOpponent* opponent) {
        this->level += 1;
        if (this->level>10) setLevel(10); 
    }

    void lose_Tornbery(BaseOpponent* opponent) {
        // cout << "yes" << endl;
        if (antidote > 0) {
            antidote--;
            bag->useItem(ANTIDOTE, this);
            }
        else {
            for (int i{ 0 }; i < 3; ++i) bag->dropItem();
            this->hp -= 10;
        handleWhenHpDown();
            }
    }

    void win_QueenofCards(BaseOpponent* opponent) {
        this->gil *= 2;
    }

    void lose_QueenofCards(BaseOpponent* opponent) {
        this->gil /= 2;
    }

    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
};

class LancelotKnight : public BaseKnight {
    public:
    LancelotKnight(int id, int maxhp, int level,int gil, int antidote, int phoenixdownI);
    void fight(BaseOpponent *opponent);
    };

class PaladinKnight : public BaseKnight {
    public:
    PaladinKnight(int id, int maxhp, int level,int gil, int antidote, int phoenixdownI);
    void fight(BaseOpponent *opponent);
    };

class DragonKnight : public BaseKnight {
    public:
    DragonKnight(int id, int maxhp, int level,int gil, int antidote, int phoenixdownI);
    void fight(BaseOpponent *opponent);
    };

class NormalKnight : public BaseKnight {
    public:
    NormalKnight(int id, int maxhp, int level,int gil, int antidote, int phoenixdownI);
    void fight(BaseOpponent *opponent);
    };

class ArmyKnights;

class ArmyKnights {
private:
    void defeated_knight(int i) {
        if (arr_army && arr_army[i]) {
        delete arr_army[i];
        arr_army[i] = nullptr;
        num_knight--;
        }
    }
public:
    bool has_Paladin_Shield=false, has_Lancelot_Spear=false, has_Guinver_Hair=false, has_Excalibur_Sword=false;
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
    bool fight_MadBear(int i, int id_event);
    bool fight_Bandit(int i, int id_event);
    bool fight_LordLupin(int i, int id_event);
    bool fight_Elf(int i, int id_event);
    bool fight_Troll(int i, int id_event);
    bool fight_Tornbery(int i, int id_event);
    bool fight_QueenofCards(int i, int id_event);
    bool meet_NinaDeRings();
    bool meet_DurianGarden();
    bool fight_OmegaWeapon();
    bool fight_Hades();
    bool fight_Ultimecia();
    void take_phoenixdown(int type) {
        BaseItem* tmp = new Phoenixdown(type);
        for (int i = num_knight-1; i >= 0; --i)
        {
            if (arr_army[i]->getBag()->insertFirst(tmp)) return;
        }
        delete tmp;
        return;
        }

    void passGil(int gil, int knight_index);


    BaseKnight **arr_army;
    int size_army;
    int num_knight;
    bool win_Omega=false;
    bool win_Hades=false;

    void printInfo() const;
    void printResult(bool win) const;
};


class Events {
public:
    int count() const;
    int get(int i) const;
    BaseOpponent * opponent;
    
    int *arr_event;
    int size_event;
    Events(const string &file_events);
    ~Events();
};

class KnightAdventure {
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