#include "knight2NTTD.h"

/* * * BEGIN implementation of class BaseBag * * */

bool BaseBag::insertFirst(BaseItem * item) {
    if (num_item_in_bag == 0) {
        head = new Node(item, nullptr);
        num_item_in_bag++;
        return true;
        }


    if (num_item_in_bag < max_slot) {
        Node * newitem = new Node(item, head);
        newitem->item = item;
        newitem->next = head;
        head = newitem;
        num_item_in_bag++;
        return true;
        }
    else return false;
}


BaseItem * BaseBag::get(ItemType  itemType) {
    Node * tmp = head;
    while (tmp) {
        if (tmp->item->getItemType() == itemType) return tmp->item;
        tmp = tmp->next;
        }
    return nullptr;
}


string BaseBag::toString() const {
    string str = "Bag[count=" ;
    str = str + to_string(num_item_in_bag) + ';';
    Node* tmp = head ;
    while (tmp != NULL)
    {
        str = str + tmp->item->turntostring() + ',';
        tmp = tmp->next;
        // cout << tmp->item->toString();
        // cout <<"yes";
    }
    if (str[str.length() - 1] == ',') str[str.length() - 1] = ']';
    else str += ']';
    return str;
}

BaseItem *BaseBag::swap(ItemType itemType, BaseKnight* knight) {
    Node* this_item = head;
    while (this_item != NULL) {
        if (this_item->item->getItemType() == itemType && this_item->item->canUse(knight)) {
            BaseItem* c = this_item->item;
            this_item->item = head->item;
            head->item = c;
            return c;
        }
        this_item = this_item->next;
    }
    return nullptr;
    }

bool BaseBag::useItem(ItemType itemType, BaseKnight* knight) {
    
    BaseItem* itemToUse = swap(itemType, knight);
    if (itemToUse) {
        itemToUse->use(knight);
        Node* tmp = head;
        head = head->next;
        --num_item_in_bag;
        return true;
    }
    return false;
}


void BaseBag::dropItem()
{
    if (num_item_in_bag > 0)
    {
        // Node* temporary = head;
        head = head->next;
        num_item_in_bag--;
    }
}


BaseBag::BaseBag(int phoenixdown, int antidote, int maxSlot) {
    max_slot = maxSlot;
    // num_item_in_bag = 0;
    for (int i=0; i<phoenixdown; i++) {
        if (num_item_in_bag > maxSlot) return;
        BaseItem * newItem = new Phoenixdown();
        this->insertFirst(newItem);
        }
    for (int i=0; i<antidote; i++) {
        if (num_item_in_bag > maxSlot) return;
        BaseItem * newItem = new Antidote();
        this->insertFirst(newItem);
        }
    }


bool Phoenixdown::canUse(BaseKnight* knight)
{
    switch (type_of_phoenixdown) {
        case 1: if (knight->getHp() <= 0) return true;
                else return false;
                break;
        case 2: if (knight->getHp() < (knight->getMaxhp())/4) return true;
                else return false;
                break;
        case 3: if (knight->getHp() < (knight->getMaxhp())/3) return true;
                else return false;
                break;
        case 4: if (knight->getHp() < (knight->getMaxhp())/2) return true;
                return false;
                break;
    }     
}


void Phoenixdown::use(BaseKnight* knight)
{
    int hp, maxhp;
    hp = knight->getHp();
    maxhp = knight->getMaxhp();

        if (type_of_phoenixdown == 1) { knight->setHp(maxhp); }
        if (type_of_phoenixdown == 2) { knight->setHp(maxhp); }
        if (type_of_phoenixdown == 3) { 
            if (hp <= 0) knight->setHp(maxhp/3);
            else knight->setHp(maxhp/4 + hp);
            }
        if (type_of_phoenixdown == 4) {
            // cout<<345<<endl;
            if (hp <= 0) knight->setHp(maxhp/2);
            else knight->setHp(maxhp/5 + hp);
            }
    
}


/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}


bool checkPrime (int hp) {
    if (hp<2) return false;
    if (hp==2) return true;
    for (int i=2; i<hp; i++) {
        if (hp%i==0) return false;
        }
    return true;
    }


bool checkPytago (int hp) {
    if (hp==345 || hp==354 || hp==435 || hp==453 || hp==534 || hp==543) return true;
    return false;
    }


LancelotKnight::LancelotKnight(int id, int maxhp, int level,int gil, int antidote, int phoenixdownI) {
    this->id=id;
    this->maxhp=maxhp;
    this->hp=maxhp;
    this->level=level;
    this->gil=gil;
    this->antidote=antidote;
    this->phoenixdownI=phoenixdownI;
    this->bag=new BaseBag(phoenixdownI, antidote, 16);
    this->knightType=LANCELOT;
    }


PaladinKnight::PaladinKnight(int id, int maxhp, int level,int gil, int antidote, int phoenixdownI) {
    this->id=id;
    this->maxhp=maxhp;
    this->hp=maxhp;
    this->level=level;
    this->gil=gil;
    this->antidote=antidote;
    this->phoenixdownI=phoenixdownI;
    this->bag=new BaseBag(phoenixdownI, antidote, 2147483640);
    this->knightType=PALADIN;
    }


DragonKnight::DragonKnight(int id, int maxhp, int level,int gil, int antidote, int phoenixdownI) {
    this->id=id;
    this->maxhp=maxhp;
    this->hp=maxhp;
    this->level=level;
    this->gil=gil;
    this->antidote=antidote;
    this->phoenixdownI=phoenixdownI;
    this->bag=new BaseBag(phoenixdownI, 0, 14);
    this->knightType=DRAGON;
    }


NormalKnight::NormalKnight(int id, int maxhp, int level,int gil, int antidote, int phoenixdownI) {
    this->id=id;
    this->maxhp=maxhp;
    this->hp=maxhp;
    this->level=level;
    this->gil=gil;
    this->antidote=antidote;
    this->phoenixdownI=phoenixdownI;
    this->bag=new BaseBag(phoenixdownI, antidote, 19);
    this->knightType=NORMAL;
    }


BaseKnight * BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    BaseKnight * m = nullptr;
    if (checkPrime(maxhp)) {
        m = new PaladinKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        }
    if (checkPytago(maxhp)) {
        m = new DragonKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        }
    if (maxhp == 888) {
        m = new LancelotKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        }
    if (!checkPrime(maxhp) && !checkPytago(maxhp) && maxhp != 888) {
        m = new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        }
    return m;
}


BaseKnight *ArmyKnights::lastKnight() const {
    return arr_army[num_knight-1];
}


/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
    // cout<<arr_army[0];
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight();
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}


void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}


ArmyKnights::ArmyKnights(const string &file_armyknights) {
    ifstream read_armyknights;
    read_armyknights.open(file_armyknights);
    read_armyknights >> size_army;
    // string line;
    // getline(read_armyknights, line);
    num_knight = size_army;
    arr_army = new BaseKnight*[size_army];
    int hp, level, phoenixdownI, gil, antidote;
    for (int i=0; i<size_army; i++) {
        string line;
        getline(read_armyknights, line);
        stringstream(s);
        read_armyknights >> hp >> level >> phoenixdownI >> gil >> antidote;
        arr_army[i] = BaseKnight::create(i+1, hp, level, gil, antidote, phoenixdownI);
    }
}


int ArmyKnights::count() const {
    return num_knight;
}


ArmyKnights::~ArmyKnights() {
    for (int i=0; i<size_army; i++) {
        delete arr_army[i];
        }
    delete arr_army;
    arr_army = nullptr;
}


// void ArmyKnights::defeated_knight(int i) {

//     }

void ArmyKnights::passGil(int gil, int knight_index) {
    int gil_resudual = gil - 999;
    arr_army[knight_index]->setGil(999);
    if (num_knight > 1) {
    knight_index--;
    int gil_of_this_knight = arr_army[knight_index]->getGil();
    while (gil_resudual != 0 && knight_index>=0) {
        gil_of_this_knight += gil_resudual;
        if (gil_of_this_knight > 999) {
            gil_resudual = gil_of_this_knight - 999;
            gil_of_this_knight = 999;
            arr_army[knight_index]->setGil(999);
            }
        else arr_army[knight_index]->setGil(gil_of_this_knight);
        knight_index--;
        }
    }
    }


bool ArmyKnights::hasPaladinShield() const
{
    if (has_Paladin_Shield==true) return true;
    return false;
}


bool ArmyKnights::hasLancelotSpear() const
{
    if (has_Lancelot_Spear==true) return true;
    return false;
}


bool ArmyKnights::hasGuinevereHair() const
{
    if (has_Guinver_Hair==true) return true;
    return false;
}


bool ArmyKnights::hasExcaliburSword() const
{
    if (has_Excalibur_Sword==true) return true;
    return false;
}


bool ArmyKnights::fight(BaseOpponent * opponent) {
cout<<33;
}


void PaladinKnight::fight(BaseOpponent* opponent) {
    int event_id = opponent->getEventId();
    if (event_id <= 5 && event_id >= 1) {
        win_MadBear(opponent);
    }
    if (event_id == 6) {
        if (this->level >= opponent->getLevelO()) win_Tornbery(opponent);            
        else lose_Tornbery(opponent);
    }
    if (event_id == 7) {
        if (this->level >= opponent->getLevelO()) win_QueenofCards(opponent);
    }
}


void LancelotKnight::fight(BaseOpponent* opponent) {
    int event_id = opponent->getEventId();
    if (event_id <= 5 && event_id >= 1) {
        win_MadBear(opponent);
    }
    if (event_id == 6) {
        if (this->level >= opponent->getLevelO()) win_Tornbery(opponent);
        else lose_Tornbery(opponent);
    }
    if (event_id == 7) {
        if (this->level >= opponent->getLevelO()) win_QueenofCards(opponent);
        else lose_QueenofCards(opponent);
    }
}


void DragonKnight::fight(BaseOpponent* opponent) {
    int event_id = opponent->getEventId();
    if (event_id <= 5 && event_id >= 1) {
        int levelO = opponent->getLevelO();
        if (this->level >= levelO) {
            switch (event_id){
                case 1: {win_MadBear(opponent);
                    break;
                    }
                case 2: {win_Bandit(opponent);
                break;
                    }
                case 3: {win_LordLupin(opponent);
                break;
                    }
                case 4: {win_Elf(opponent);
                break;
                    }
                case 5: {win_Troll(opponent);
                break;
                    }
                }
            }
        else {
            switch (event_id){
                case 1: {lose_MadBear(opponent);
                break;
                    }
                case 2: {lose_Bandit(opponent);
                break;
                    }
                case 3: {lose_LordLupin(opponent);
                break;
                    }
                case 4: {lose_Elf(opponent);
                break;
                    }
                case 5: {lose_Troll(opponent);
                break;
                    }
                }
            }
    }
    if (event_id == 6) {
        if (this->level >= opponent->getLevelO()) win_Tornbery(opponent);
    }
    if (event_id == 7) {
        if (this->level >= opponent->getLevelO()) win_QueenofCards(opponent);
        else lose_QueenofCards(opponent);
    }

}


void NormalKnight::fight(BaseOpponent* opponent) {
    int event_id = opponent->getEventId();
    if (event_id <= 5 && event_id >= 1) {
        int levelO = opponent->getLevelO();
        if (this->level >= levelO) {
            if (event_id == 1) win_MadBear(opponent);
            if (event_id == 2) win_Bandit(opponent);
            if (event_id == 3) win_LordLupin(opponent);
            if (event_id == 4) win_Elf(opponent);
            if (event_id == 5) win_Troll(opponent);
            }
        else {
            if (event_id == 1) lose_MadBear(opponent);
            if (event_id == 2) lose_Bandit(opponent);
            if (event_id == 3) lose_LordLupin(opponent);
            if (event_id == 4) lose_Elf(opponent);
            if (event_id == 5) lose_Troll(opponent);
            }
    }
    if (event_id == 6) {
        if (this->level >= opponent->getLevelO()) win_Tornbery(opponent);
        else lose_Tornbery(opponent);
    }
    if (event_id == 7) {
        if (this->level >= opponent->getLevelO()) win_QueenofCards(opponent);
        else lose_QueenofCards(opponent);
    }
}


bool ArmyKnights::adventure (Events * events) {
    for (int i=0; i<events->count(); i++) {
        int event_id = events->get(i);
        bool flag;

        if (event_id==1) flag = fight_MadBear(i, event_id);

        if (event_id==2) flag = fight_Bandit(i, event_id);

        if (event_id==3) flag = fight_LordLupin(i, event_id);

        if (event_id==4) flag = fight_Elf(i, event_id);

        if (event_id==5) flag = fight_Troll(i, event_id);

        if (event_id==6) flag = fight_Tornbery(i, event_id);

        if (event_id==7) flag = fight_QueenofCards(i, event_id);

        if (event_id==8) flag = meet_NinaDeRings();

        if (event_id==9) flag = meet_DurianGarden();

        if (event_id==10) flag = fight_OmegaWeapon();

        if (event_id==11) flag = fight_Hades();

        if (event_id==95) {has_Paladin_Shield = true; flag = hasPaladinShield();}
        
        if (event_id==96) {has_Lancelot_Spear = true; flag = hasLancelotSpear();}

        if (event_id==97) {has_Guinver_Hair = true; flag = hasGuinevereHair();}

        if (event_id==98) {if (has_Paladin_Shield == true && has_Lancelot_Spear == true && has_Guinver_Hair == true) {has_Excalibur_Sword = true;} 
                           else flag = true;}

        if (event_id==99) flag = fight_Ultimecia();

        if (event_id==112) { take_phoenixdown(2); flag = true;}

        if (event_id==113) { take_phoenixdown(3); flag = true;}

        if (event_id==114) { take_phoenixdown(4); flag = true;}

        printInfo();
        if (flag==false) {
            return false;
        }
    }
    return true;
}


bool ArmyKnights::fight_MadBear(int i, int id_event) {
    int levelO = (i + id_event)%10 + 1;
    int baseDamage = 10;
    int gil_get_if_win = 100;
    BaseOpponent *MadBear = new BaseOpponent(levelO, baseDamage, gil_get_if_win, id_event);
        arr_army[num_knight-1]->fight(MadBear);
        if (arr_army[num_knight-1]->getHp() <= 0) defeated_knight(num_knight-1);
        else {
            if (arr_army[num_knight-1]->getGil() > 999) {
                passGil(arr_army[num_knight-1]->getGil(), num_knight - 1);
            }
        }
    // delete MadBear;
    if (num_knight <= 0) return false;
    return true;
}


bool ArmyKnights::fight_Bandit(int i, int id_event) {
    int levelO = (i + id_event)%10 + 1;
    int baseDamage = 15;
    int gil_get_if_win = 150;
    BaseOpponent *Bandit = new BaseOpponent(levelO, baseDamage, gil_get_if_win, id_event);
        arr_army[num_knight-1]->fight(Bandit);
        if (arr_army[num_knight-1]->getHp() <= 0) defeated_knight(num_knight-1);
        else {
            int gil = arr_army[num_knight-1]->getGil();
            if (gil > 999) {
                passGil(gil, num_knight - 1);
            }
        }  
    delete Bandit;
    if (num_knight <= 0) return false;
    return true;
}


bool ArmyKnights::fight_LordLupin(int i, int id_event) {
    int levelO = (i + id_event)%10 + 1;
    int baseDamage = 45;
    int gil_get_if_win = 450;
    BaseOpponent *LordLupin = new BaseOpponent(levelO, baseDamage, gil_get_if_win, id_event);
        arr_army[num_knight-1]->fight(LordLupin);
        if (arr_army[num_knight-1]->getHp() <= 0) defeated_knight(num_knight-1);
        else {
            int gil = arr_army[num_knight-1]->getGil();
            if (gil > 999) {
                passGil(gil, num_knight - 1);
            }
        }
    delete LordLupin;
    if (num_knight <= 0) return false;
    return true;
}


bool ArmyKnights::fight_Elf(int i, int id_event) {
    int levelO = (i + id_event)%10 + 1;
    int baseDamage = 75;
    int gil_get_if_win = 750;
    BaseOpponent *Elf = new BaseOpponent(levelO, baseDamage, gil_get_if_win, id_event);

        arr_army[num_knight-1]->fight(Elf);
        if (arr_army[num_knight-1]->getHp() <= 0) defeated_knight(num_knight-1);
        else {
            int gil = arr_army[num_knight-1]->getGil();
            if (gil > 999) {
                passGil(gil, num_knight - 1);
            }
        }
    delete Elf;
    if (num_knight <= 0) return false;
    return true;
}


bool ArmyKnights::fight_Troll(int i, int id_event) {
    int levelO = (i + id_event)%10 + 1;
    int baseDamage = 95;
    int gil_get_if_win = 800;
    BaseOpponent *Troll = new BaseOpponent(levelO, baseDamage, gil_get_if_win, id_event);
        arr_army[num_knight-1]->fight(Troll);
        if (arr_army[num_knight-1]->getHp() <= 0) defeated_knight(num_knight-1);
        else {
            int gil = arr_army[num_knight-1]->getGil();
            if (gil > 999) {
                passGil(gil, num_knight - 1);
            }
        }
    delete Troll;
    if (num_knight <= 0) return false;
    return true;
}


bool ArmyKnights::fight_Tornbery(int i, int event_id) {
    int levelO = (i + event_id)%10 + 1;
    BaseOpponent* Tornbery = new BaseOpponent(levelO, 0, 0, 6);
        arr_army[num_knight-1]->fight(Tornbery);
        if (arr_army[num_knight-1]->getHp() <= 0) defeated_knight(num_knight-1);
        //delete Tornbery;
        if (num_knight<=0) return false;
        return true;
    }


bool ArmyKnights::fight_QueenofCards(int i, int event_id) {
    int levelO = (i + event_id)%10 + 1;
    BaseOpponent* QueenofCards = new BaseOpponent(levelO, 0, 0, 7);
    arr_army[num_knight-1]->fight(QueenofCards);
    int gil = arr_army[num_knight-1]->getGil();
    if (gil>999) passGil(gil, num_knight - 1);
    delete QueenofCards;
    return true;
    }


bool ArmyKnights::meet_NinaDeRings() {
    BaseKnight *knight = this->arr_army[num_knight-1];
    int gil = knight->getGil();
    int hp = knight->getHp();
    int maxhp = knight->getMaxhp();

    if (knight->getType() == PALADIN && hp < maxhp/3) knight->setHp(hp + maxhp/5);
    if (knight->getType() != PALADIN && gil >= 50 && hp < maxhp/3) {
        knight->setHp(hp + maxhp/5);
        knight->setGil(gil - 50);
        }
        return true;
    }


bool ArmyKnights::meet_DurianGarden() {
    BaseKnight *knight = this->arr_army[num_knight-1];
    int maxhp = knight->getMaxhp();
    knight->setHp(maxhp);
    return true;
    }


bool ArmyKnights::fight_OmegaWeapon() {
    if (win_Omega == true ) return true;

        int level = arr_army[num_knight-1]->getLevel();
        if (arr_army[num_knight-1]->getType()==DRAGON || arr_army[num_knight-1]->getType() != DRAGON && level == 10) {

            arr_army[num_knight-1]->setGil(999);
            arr_army[num_knight-1]->setLevel(10);
            win_Omega=true;
            }
        else {
            arr_army[num_knight-1]->setHp(0);
            arr_army[num_knight-1]->handleWhenHpDown();
            if (arr_army[num_knight-1]->getHp() <= 0) defeated_knight(num_knight-1);
        }
        if (num_knight<=0) return false;
        return true;
    }


bool ArmyKnights::fight_Hades() {
    if (win_Hades == true) return true;

        if (arr_army[num_knight-1]->getType() == PALADIN && arr_army[num_knight-1]->getLevel()>=8 || arr_army[num_knight-1]->getLevel()==10) {
            win_Hades = true;
            has_Paladin_Shield = true;
            return true;
            }
        else {
            arr_army[num_knight-1]->setHp(0);
            arr_army[num_knight-1]->handleWhenHpDown();
            if (arr_army[num_knight-1]->getHp() <= 0) defeated_knight(num_knight-1);
            if (num_knight <= 0) return false;
            else return true;
        }
    }


bool ArmyKnights::fight_Ultimecia() {
    if (hasExcaliburSword() == true) return true;
    if (hasGuinevereHair() != true || hasLancelotSpear() != true || hasPaladinShield() != true) {
        num_knight = 0;
        return false;
        }
    int Ultimecia_hp = 5000;
    double knightBaseDamage;
    for (int i=num_knight-1; i>=0; i--) {
        if (arr_army[i]->getType() != NORMAL) {
            switch (arr_army[i]->getType()) {
                case LANCELOT: {knightBaseDamage = 0.05;
                break;
                }
                case PALADIN: {knightBaseDamage = 0.06;
                break;
                }
                case DRAGON: {knightBaseDamage = 0.075; 
                break;
                }
            }
            int damage = arr_army[i]->getHp() * arr_army[i]->getLevel() * knightBaseDamage;
            Ultimecia_hp -= damage;
            if (Ultimecia_hp <= 0) return true;
            defeated_knight(i);
        }
        else {defeated_knight(i);}
    }
    return false;
}


/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}


void KnightAdventure::loadArmyKnights(const string &file_armyknights) {
    armyKnights = new ArmyKnights(file_armyknights);
}


void KnightAdventure::loadEvents(const string &file_events) {
    events = new Events(file_events);
}


void KnightAdventure::run() {
    if (armyKnights && events) {
        bool index = armyKnights->adventure(events);
        armyKnights->printResult(index);
        exit;
    }
}


KnightAdventure::~KnightAdventure() {
    delete armyKnights;
    delete events;
}


/* * * END implementation of class KnightAdventure * * */


Events::Events(const string &file_events) {
    ifstream read_events;
    read_events.open(file_events);
    read_events >> size_event;
    arr_event = new int[size_event];
    
    for (int i=0; i<size_event; i++) {
        int event=0;
        read_events >> event;
        arr_event[i] = event;
    }
    read_events.close();
    
}


bool BaseKnight::handleWhenHpDown()
{
    if (bag->useItem(PHOENIXDOWN, this)) return true;
    if (this->gil >= 100 && this->hp <= 0)
    {
        this->hp = this->maxhp / 2;
        this->gil -= 100;
        return true;
    }
    if (this->hp > 0) return true;
    return false;
}


int Events::count() const {
    return size_event;
    }


int Events::get(int i) const {
    return arr_event[i];
}


Events::~Events() {
    delete arr_event;
}


