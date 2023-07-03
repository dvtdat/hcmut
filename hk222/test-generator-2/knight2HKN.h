#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType {Antidote = 0, PhoenixI, PhoenixII, PhoenixIII, PhoenixIV};

class BaseItem;
class BaseKnight;
class Events;

class BaseBag {
private:
    BaseKnight *knight;
    BaseItem *items;
    int size_bag_max;
public:
    BaseBag(BaseKnight*knight_base,int num_phoenixdownI,int num_antidote);
    int get_size_max() const{
        return this->size_bag_max;
    };
    BaseItem *items_get(){
        return this->items;
    };

    void set_items(BaseItem *items){
        this->items = items;
    };

    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
};

class BaseOpponent;

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    int phoenixdownI;
    bool poisoned_state = false;
    bool usedAntidote =  false;
    BaseBag * bag;
    KnightType knightType;

public:
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;

    void usingAntidote();
    bool useAntidote();
    void notuseAntidote();

    void set_gil(string);
    int get_gil();
    void setgil(int);

    int get_level();
    void set_level(int);

    int get_HP();
    int get_MaxHP();
    void set_HP(int);

    void set_type(KnightType);

    bool get_poisoned_state() const;
    void knight_poisoned();
    void knight_get_normal();

    bool PaladinCheck(int);
    bool DragonCheck(int);
    KnightType Knighttype();

    BaseBag *get_bag(){
        return this->bag;
    };
};



class PaladinKnight : public BaseKnight{
    public:
        PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
        ~PaladinKnight(){};
};
class LancelotKnight : public BaseKnight{
    public:
        LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
        ~LancelotKnight(){};
};
class DragonKnight : public BaseKnight{
    public:
        DragonKnight(int id, int maxhp, int level,int gil ,int antidote, int phoenixdownI);
        ~DragonKnight(){};
        
};
class NormalKnight : public BaseKnight {
    public:
        NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
        ~NormalKnight(){};
};


class ArmyKnights {
private:
    int n;
    BaseKnight **baseknight;
    bool has_Paladin_Shield = false;
    bool has_Excalibur_Sword = false;
    bool has_Guinevere_Hair = false;
    bool has_Lancelot_Spear = false;
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights(){};
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


int SizeBag(BaseItem *a); //check tmp = a
void delete_item_first(BaseItem *&a);
void delete_item_last(BaseItem *&a);
void delete_item_middle(BaseItem *&a, int pos);
void insert_First(BaseItem *&a, ItemType x);
void insert_Last(BaseItem *&a, ItemType x);
void insertMiddle(BaseItem *&a, ItemType x, int pos);
int searchItem(BaseItem *a, ItemType x);

class BaseItem {
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
    ItemType type;
    BaseItem *next;
    BaseItem(ItemType type) : type(type), next(nullptr){};
    virtual ~BaseItem(){};
};

class antidote : virtual public BaseItem{
    private:
        bool getPoisoned = false;
    public:
        antidote(BaseItem *&headitem) : BaseItem(Antidote){ 
            next = headitem;
            headitem = this;
        };
        bool canUse(BaseKnight *knight)
        {
            if (knight->Knighttype() == DRAGON && this->type == ItemType::Antidote) return false;
            if (knight->get_poisoned_state() == true) return true; 
            return false;
        };
        void use(BaseKnight *knight)
        {
            knight->knight_get_normal();
        };
        ~antidote() {};
};

class PhoenixDownI : virtual public BaseItem {
    public:
        PhoenixDownI(BaseItem *&headitem) : BaseItem(PhoenixI){
            next = headitem;
            headitem = this;
        };
        bool canUse(BaseKnight *knight){
            int HP = knight->get_HP();
            if (HP <= 0) return true;
            return false;
        };
        void use(BaseKnight *knight){
            int HP = knight->get_HP(), maxHP = knight->get_MaxHP();
            if (HP <= 0){
                knight->set_HP(maxHP);
            }
        };
        ~PhoenixDownI(){};
};

class PhoenixDownII: virtual public BaseItem {
    public:
        PhoenixDownII(BaseItem *&headitem) : BaseItem(PhoenixII){
            next = headitem;
            headitem = this;
        };
            bool canUse(BaseKnight *knight){
                int HP = knight->get_HP(), maxHP = knight->get_MaxHP();
                if (HP < maxHP/4) return true;
                return false;
            };
            void use(BaseKnight *knight){
                int HP = knight->get_HP(), maxHP = knight->get_MaxHP();
                if (HP < maxHP/4){
                    knight->set_HP(maxHP);
                }
            };
        ~PhoenixDownII(){};
};

class PhoenixDownIII: virtual public BaseItem {
    public:
        PhoenixDownIII(BaseItem *&headitem) : BaseItem(PhoenixIII){
            next = headitem;
            headitem = this;
        };
            bool canUse(BaseKnight *knight){
                int HP = knight->get_HP(), maxHP = knight->get_MaxHP();
                if (HP < maxHP/3) return true;
                return false;
            };
            void use(BaseKnight *knight){
                int HP = knight->get_HP(), maxHP = knight->get_MaxHP();
                if (HP <= 0){
                    maxHP /= 3;
                    knight->set_HP(maxHP);
                }
                else {
                    HP += maxHP/4; 
                    knight->set_HP(HP);
                }   
            };
        ~PhoenixDownIII(){};
};

class PhoenixDownIV: virtual public BaseItem {
    public:
        PhoenixDownIV(BaseItem *&headitem) : BaseItem(PhoenixIV){
            next = headitem;
            headitem = this;
        };
        bool canUse(BaseKnight *knight){
            int HP = knight->get_HP(), maxHP = knight->get_MaxHP();
            if (HP < maxHP/2) return true;
            return false;
        };
        void use(BaseKnight *knight){
            int HP = knight->get_HP(), maxHP = knight->get_MaxHP();
            if (HP <= 0){
                HP = maxHP/2;
                knight->set_HP(HP);
            }
            else {
                HP += maxHP/5;
                knight->set_HP(HP);
            }
        };
        ~PhoenixDownIV(){};
};
//====================Derived Bag=====================
class PaladinBag : virtual public BaseBag{
    public:
        PaladinBag(BaseKnight*knight,int phoenixI, int antidote) : BaseBag(knight,phoenixI,antidote){};
        //~PaladinBag(){};
        bool insertFirst(BaseItem *item){
            return true;
        };
};

class LancelotBag : virtual public BaseBag{
    public:
        LancelotBag(BaseKnight*knight, int phoenixI, int antidote) : BaseBag(knight,phoenixI,antidote){};
        //~LancelotBag() {};
        bool insertFirst(BaseItem *item){
            if (SizeBag(item) < this->get_size_max()) return true;
            return false;
        };
};

class DragonBag : virtual public BaseBag{
    public:
        DragonBag(BaseKnight*knight, int phoenixI, int antidote) : BaseBag(knight,phoenixI,antidote){};
        //~DragonBag() {};
        bool insertFirst(BaseItem *item)
        {
            if (SizeBag(item) < this->get_size_max()) {
                return true;
            }
            return false;
        };
};

class NormalBag : virtual public BaseBag{
    public:
        NormalBag(BaseKnight*knight, int phoenixdownI, int antidote) : BaseBag(knight,phoenixdownI,antidote){};
        //~NormalBag(){};
        bool insertFirst(BaseItem *item){
            if (SizeBag(item) < this->get_size_max()) {
                return true;
            }
            return false;
        };
};

class BaseOpponent{
    private:
        int levelO;
    public:
        BaseOpponent(int id, int event_id) : levelO((id + event_id)%10 + 1) {};
        virtual ~BaseOpponent() {};
        virtual bool checkLevel(BaseKnight *a) = 0;
        virtual void KnightWin(BaseKnight*a) = 0;
        virtual void DoSth(BaseKnight*a) = 0;
        virtual void UsingGil(BaseKnight*a) = 0;
        int getLevelO() {return levelO;};
        virtual void getPhoenix(BaseKnight*a){
            BaseItem *item = a->get_bag()->items_get();
            int pos_phoenixI = searchItem(item, PhoenixI);
            int pos_phoenixII = searchItem(item, PhoenixII);
            int pos_phoenixIII = searchItem(item, PhoenixIII);
            int pos_phoenixIV = searchItem(item, PhoenixIV);
            int pos[4] = {pos_phoenixI,pos_phoenixII,pos_phoenixIII,pos_phoenixIV};
            for(int i=0; i < 4; i++)
            {
                for(int j=i+1; j<4; j++) { 
                    if(pos[j] < pos[i])
                    {
                        int tmp = pos[i];
                        pos[i] = pos[j];
                        pos[j] = tmp;
                    }
                }
            }
            BaseItem *takeitem = nullptr;
            for (int i = 0; i < 4; i++){
                if (pos[i] > 0){
                    if (pos[i] == pos_phoenixI){
                        takeitem = new PhoenixDownI(takeitem);
                        if (takeitem->canUse(a)) {
                            takeitem = a->get_bag()->get(PhoenixI);
                            takeitem->use(a);
                            break;
                        }  
                    }
                    else if (pos[i] == pos_phoenixII) {
                        takeitem = new PhoenixDownII(takeitem);
                        if (takeitem->canUse(a)) {
                            takeitem = a->get_bag()->get(PhoenixII);
                            takeitem->use(a);
                            break;
                        }  
                    } 
                    else if (pos[i] == pos_phoenixIII) {
                        takeitem = new PhoenixDownIII(takeitem);
                        if (takeitem->canUse(a)) {
                            takeitem = a->get_bag()->get(PhoenixIII);
                            takeitem->use(a);
                            break;
                        }  
                    } 
                    else if (pos[i] == pos_phoenixIV) {
                        takeitem = new PhoenixDownIV(takeitem);
                        if (takeitem->canUse(a)) {
                            takeitem = a->get_bag()->get(PhoenixIV);
                            takeitem->use(a);
                            break;
                        }  
                    } 
                }
            }
        };
};

class MadBear : virtual public BaseOpponent{
    public:
        MadBear(int id, int event_id) : BaseOpponent(id,event_id) {};
        bool checkLevel(BaseKnight *a){
            int level = a->get_level(), level_O = getLevelO();
            if (level >= level_O || a->Knighttype() == LANCELOT || a->Knighttype() == PALADIN) return true;
            return false;
        };
        void KnightWin(BaseKnight *a){
            a->set_gil("Madbear");
            
        };
        void DoSth(BaseKnight*a){
            int HP = a->get_HP();
            HP = HP - 10*(getLevelO() - a->get_level());
            a->set_HP(HP);
        };
        void UsingGil(BaseKnight*a)
        { //when HP <=0    
            int HP = a->get_HP(), gil = a->get_gil(), maxHP = a->get_MaxHP(); 
            if (HP > 0) return;
            else if (HP <= 0 && gil >= 100) {
                gil -= 100;
                HP = maxHP/2;
                a->set_HP(HP);
                a->setgil(gil);
            }
        };
        ~MadBear() {};
};
class Bandit : virtual public BaseOpponent{
    public:
        Bandit(int id, int event_id) : BaseOpponent(id,event_id) {};
        bool checkLevel(BaseKnight *a){
            if (a->get_level() >= getLevelO() || a->Knighttype() == LANCELOT || a->Knighttype() == PALADIN) return true;
            //else if (a->get_level() < getLevelO()) return -1;
            return false;
        };
        void KnightWin(BaseKnight *a){
            a->set_gil("Bandit");
        };
        void DoSth(BaseKnight*a){
            int HP = a->get_HP();
            HP = HP - 15*(getLevelO() - a->get_level());
            a->set_HP(HP);
            a->get_level();
        };
        void UsingGil(BaseKnight*a){ //when HP <=0
            //BaseItem *tmp = a->get_bag()->get(PhoenixI); //not sure;
            int HP = a->get_HP(), gil = a->get_gil(), maxHP = a->get_MaxHP(); 
            if (HP > 0) return;
            else if (HP <= 0 && gil >= 100) {
                gil -= 100;
                HP = maxHP/2;
                a->set_HP(HP);
                a->setgil(gil);
            }
        };
        ~Bandit() {};
};
class LordLupin : virtual public BaseOpponent{
    public:
    LordLupin(int id, int event_id) : BaseOpponent(id,event_id) {};
        bool checkLevel(BaseKnight *a){
            if (a->get_level() >= getLevelO() || a->Knighttype() == LANCELOT || a->Knighttype() == PALADIN) return true;
            return false;
        };
        void KnightWin(BaseKnight *a){
            a->set_gil("LordLupin");
        };
        void DoSth(BaseKnight*a){
            int HP = a->get_HP();
            HP = HP - 45*(getLevelO() - a->get_level());
            a->set_HP(HP);
        };
        void UsingGil(BaseKnight*a){ 
            int HP = a->get_HP(), gil = a->get_gil(), maxHP = a->get_MaxHP(); 
            if (HP > 0) return;
            else if (HP <= 0 && gil >= 100) {
                gil -= 100;
                HP = maxHP/2;
                a->set_HP(HP);
                a->setgil(gil);
            }
        };
        ~LordLupin() {};
};
class Elf : virtual public BaseOpponent{
    public:
        Elf(int id, int event_id) : BaseOpponent(id,event_id) {};
        bool checkLevel(BaseKnight *a){
            if (a->get_level() >= getLevelO() || a->Knighttype() == LANCELOT || a->Knighttype() == PALADIN) return true;
            //else if (a->get_level() < getLevelO()) return -1;
            return false;
        };
        void KnightWin(BaseKnight *a){
            a->set_gil("Elf");
        };
        void DoSth(BaseKnight*a){
            int HP = a->get_HP();
            HP = HP - 75*(getLevelO() - a->get_level());
            a->set_HP(HP);
        };
        void UsingGil(BaseKnight*a)
        { //when HP <=0    ;
            int HP = a->get_HP(), gil = a->get_gil(), maxHP = a->get_MaxHP(); 
            if (HP > 0) return;
            else if (HP <= 0 && gil >= 100) {
                gil -= 100;
                HP = maxHP/2;
                a->set_HP(HP);
                a->setgil(gil);
            }
        };
        ~Elf() {};
};
class Troll: virtual public BaseOpponent{
    public:
        Troll(int id, int event_id) : BaseOpponent(id,event_id) {};
        bool checkLevel(BaseKnight *a)
        {
            if (a->get_level() >= getLevelO() || a->Knighttype() == PALADIN || a->Knighttype() == LANCELOT) return true;
            //else if (a->get_level() < getLevelO()) return -1;
            return false;
        };
        void KnightWin(BaseKnight *a){
            a->set_gil("Troll");
        };
        void DoSth(BaseKnight*a){
            int HP = a->get_HP();
            HP = HP - 95*(getLevelO() - a->get_level());
            a->set_HP(HP);
        };
        void UsingGil(BaseKnight*a)
        { 
            int HP = a->get_HP(), gil = a->get_gil(), maxHP = a->get_MaxHP(); 
            if (HP > 0) return;
            else if (HP <= 0 && gil >= 100) 
            {
                gil -= 100;
                HP = maxHP/2;
                a->set_HP(HP);
                a->setgil(gil);
            }
        };
        ~Troll() {};
};
class Tornbery: virtual public BaseOpponent{
    public:
        Tornbery(int id, int event_id) : BaseOpponent(id, event_id) {};
        bool checkLevel(BaseKnight *a){
            if (a->get_level() >= getLevelO()) return true;
            //if (a->get_level() < getLevelO()) return -1;
            return false;
        };
        void KnightWin(BaseKnight*a){
            int level = a->get_level();
            if (level < 10) ++level;
            a->set_level(level);
        };
        void DoSth(BaseKnight*a){
            a->knight_poisoned();
            if (a->Knighttype() != DRAGON){
                BaseItem *tmp = a->get_bag()->get(Antidote); 
                if (tmp != nullptr && tmp->canUse(a)){
                    a->usingAntidote();
                    tmp->use(a);
                }
            }
            else {
                a->usingAntidote();
                a->knight_get_normal(); //a is dragon knight
            }
            //if knight gets poisoned
            if (a->get_poisoned_state()) 
            {
                BaseItem *itemcopy = a->get_bag()->items_get();
                for (int i = 1; i <= 3; i++){
                    delete_item_first(itemcopy);
                }
                a->get_bag()->set_items(itemcopy);
                int HP = a->get_HP(); 
                HP -= 10;
                a->set_HP(HP);
                a->knight_get_normal();
            }
        };
        void UsingGil(BaseKnight*a){
            int HP = a->get_HP(), gil = a->get_gil(), maxHP = a->get_MaxHP(); 
            if (HP > 0) return;
            else if (HP <= 0 && gil >= 100) {
                gil -= 100;
                HP = maxHP/2;
                a->set_HP(HP);
                a->setgil(gil); 
            }
        };
        ~Tornbery() {};
};
class QueenOfCard : virtual public BaseOpponent{
    public:
        QueenOfCard(int id, int event_id) : BaseOpponent(id, event_id) {};
        bool checkLevel(BaseKnight *a){
            if (a->get_level() >= getLevelO()) return true;
            //else if (a->get_level() < getLevelO()) return -1;
            return false;
        };
        void KnightWin(BaseKnight*a){
            int gil = a->get_gil();
            gil *= 2;
            a->setgil(gil);
        };
        void DoSth(BaseKnight*a)
        {
            if (a->Knighttype() == PALADIN) return;
            int gil = a->get_gil();
            gil /= 2;
            a->setgil(gil);
        };
        void getPhoenix(BaseKnight *a){
            return;
        };
        void UsingGil(BaseKnight*a){
            return;
        };
        ~QueenOfCard() {};
};
class NinaDeRings : virtual public BaseOpponent{ 
// check this situation: when HP increase in this opponent but still lower than MaxHP. Need to use phoenix??? 
    public:
        NinaDeRings(int id, int event_id) : BaseOpponent(id,event_id){};
        bool checkLevel(BaseKnight*a){return true;};
        void KnightWin(BaseKnight*a){
            int gil = a->get_gil(), HP = a->get_HP(), maxHP = a->get_MaxHP();
            if (gil < 50 && a->Knighttype() != PALADIN) return;
            else if (gil < 50 && HP < maxHP/3 && a->Knighttype() == PALADIN){
                HP += maxHP/5;
                a->set_HP(HP);
            }
            else if (gil >= 50 && HP < maxHP/3)
            {
                if (a->Knighttype() != PALADIN) gil -= 50;
                a->setgil(gil);
                HP += maxHP/5;
                a->set_HP(HP);
            }
        };
        void DoSth(BaseKnight*a)
        {
            return;
        };
        void UsingGil(BaseKnight*a) {
            return;
        };
        ~NinaDeRings() {};
};
class DurianGarden : virtual public BaseOpponent{
    public:
        DurianGarden(int id, int event_id) : BaseOpponent(id,event_id) {};
        bool checkLevel(BaseKnight*a){return true;};
        void KnightWin(BaseKnight*a){
            int HP = a->get_HP(), maxHP = a->get_MaxHP();
            HP = maxHP;
            a->set_HP(HP);
        };
        void DoSth(BaseKnight*a){
            return;
        };
        void UsingGil(BaseKnight*a){
            return;
        };
        ~DurianGarden() {};
};
class OmegaWeapon : virtual public BaseOpponent{
    public:
        OmegaWeapon(int id, int event_id) : BaseOpponent(id,event_id) {};
        bool checkLevel(BaseKnight*a){
            int level = a->get_level(), HP = a->get_HP(), maxHP = a->get_MaxHP(), gil = a->get_gil();
            KnightType type = a->Knighttype();
            if ((level == 10 && HP == maxHP) || type == DRAGON) 
            {
                return true;
            }
            return false;
        };
        void KnightWin(BaseKnight*a){
            a->set_level(10);
            a->setgil(999);
        };
        void DoSth(BaseKnight*a){
            a->set_HP(0);
        };
        void UsingGil(BaseKnight *a){
            int HP = a->get_HP(), gil = a->get_gil(), maxHP = a->get_MaxHP(); 
            if (HP > 0) return;
            else if (HP <= 0 && gil >= 100) 
            {
                gil -= 100;
                HP = maxHP/2;
                a->set_HP(HP);
                a->setgil(gil);
            }
            return;
        };
        ~OmegaWeapon() {};
};
class Hades : virtual public BaseOpponent{
    public:
        Hades(int id, int event_id) : BaseOpponent(id,event_id) {};
        bool checkLevel(BaseKnight*a){
            if (a->get_level() == 10 || (a->Knighttype() == PALADIN && a->get_level() >= 8)) return true;
            return false;
        };
        void KnightWin(BaseKnight*a){
            return;
        };
        void DoSth(BaseKnight*a){
            a->set_HP(0);
        };
        void UsingGil(BaseKnight*a){
            int HP = a->get_HP(), gil = a->get_gil(), maxHP = a->get_MaxHP(); 
            if (HP > 0) return;
            else if (HP <= 0 && gil >= 100) 
            {
                gil -= 100;
                HP = maxHP/2;
                a->set_HP(HP);
                a->setgil(gil);
            }
        };
        ~Hades() {};
};


class Events {
private:
    int num_events;
    int *event_code;
public:
    Events(const string& file_event){
        ifstream fe;
        fe.open(file_event);
            string num_string;
            int e, eventcode = -1, cnt = 0;
            getline(fe,num_string);
            stringstream ss_e(num_string); 
            ss_e >> e;
           // fe >> e; 
            this->num_events = e;
            event_code = new int[e];
            string event_string;
            getline(fe,event_string);
            stringstream ss_ec(event_string);
            for (int i = 0; i < e; i++){
                ss_ec >> eventcode;
                event_code[i] = eventcode;
            }
        fe.close();
    };
    int count() const{
        return this->num_events;
    };
    int get(int i) const{
        return event_code[i];
    };
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