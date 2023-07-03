#include "knight2HKN.h"

int SizeBag(BaseItem *a){
    int count = 0;
    BaseItem *tmp = a;
    while(tmp != nullptr){
        count++;
        tmp = tmp->next;
    }
    return count;
}

void delete_item_first(BaseItem *&a){
    if (a == nullptr) return;
    a = a->next;
}

void delete_item_last(BaseItem *&a)
{
    if (a == nullptr) return;
        BaseItem *pre = nullptr, *post = a;
        while(post->next != nullptr)
        {
            pre = post;
            post = post->next;
        }
    if (pre == nullptr) a = nullptr;
    else{
        pre->next = nullptr;
    }
}

void delete_item_middle(BaseItem *&a, int pos)
{ 
    BaseItem *pre = nullptr, *post = a;
    if (post == nullptr) return;
    for (int i = 1; i < pos; i++){
        pre = post;
        post = post->next;
    }
    if (pre == nullptr) a = a->next;
    else{
        pre->next = post->next;
    }
}

void insert_First(BaseItem *&a, ItemType x){
    BaseItem *tmp = nullptr;
    if (x == Antidote) {
        tmp = new antidote(tmp);
    }
    else if (x == PhoenixI){
        tmp = new PhoenixDownI(tmp);
    }
    else if (x == PhoenixII){
        tmp = new PhoenixDownII(tmp);
    }
    else if (x == PhoenixIII){
        tmp = new PhoenixDownIII(tmp);
    }
    else tmp = new PhoenixDownIV(tmp);
    if(a == NULL){
        a = tmp;
    }
    else{
        tmp->next = a;
        a = tmp;
    }
}

void insert_Last(BaseItem *&a, ItemType x)
{
    BaseItem *tmp = nullptr;
    if (x == Antidote) {
        tmp = new antidote(tmp);
    }
    else if (x == PhoenixI){
        tmp = new PhoenixDownI(tmp);
    }
    else if (x == PhoenixII){
        tmp = new PhoenixDownII(tmp);
    }
    else if (x == PhoenixIII){
        tmp = new PhoenixDownIII(tmp);
    }
    else tmp = new PhoenixDownIV(tmp);
    if (a == nullptr)
    {
        a = tmp;
    }
    else {
        BaseItem* p = a;
        while (p->next != nullptr)
        {
            p = p->next;
        }
        p->next = tmp;
    }
}

void insertMiddle(BaseItem *&a, ItemType x, int pos)
{
    BaseItem* p = a;
    for (int i = 1; i < pos - 1; i++)
    {
        p = p->next;
    }
    BaseItem *tmp = nullptr;
    if (x == Antidote) {
        tmp = new antidote(tmp);
    }
    else if (x == PhoenixI){
        tmp = new PhoenixDownI(tmp);
    }
    else if (x == PhoenixII){
        tmp = new PhoenixDownII(tmp);
    }
    else if (x == PhoenixIII){
        tmp = new PhoenixDownIII(tmp);
    }
    else tmp = new PhoenixDownIV(tmp);
    tmp->next = p->next; 
    p->next = tmp; 
}

int searchItem(BaseItem *a, ItemType x) 
{
    BaseItem *tmp = a;
    int cnt = 1;
    while(tmp != nullptr){
        if(tmp->type == x) {
            return cnt;
        } 
        tmp = tmp->next;
        cnt++;
    }
    return 0;
}

/* * * BEGIN implementation of class BaseBag * * */
BaseBag::BaseBag(BaseKnight*knight_base, int num_phoenixdownI, int num_antidote){
    //this->items = nullptr;
    //this->size_bag_max = 0;
    this->knight = knight_base;
    if(knight_base->Knighttype() ==  DRAGON) size_bag_max = 14;
    else if (knight_base->Knighttype() == LANCELOT) size_bag_max = 16;
    else if (knight_base->Knighttype() == NORMAL) size_bag_max = 19;
    BaseItem *head = nullptr;
    //cout << "result: " << num_phoenixdownI;
    for (int i = 0; i < num_phoenixdownI; i++)
    {
        if (i < size_bag_max || knight->Knighttype() == PALADIN) head = new PhoenixDownI(head);
    }
    for (int i = 0; i < num_antidote; i++)
    {
        if (i + num_phoenixdownI < size_bag_max || knight->Knighttype() == PALADIN) head = new antidote(head);  
    }
    this->items = head;
}    
bool BaseBag::insertFirst(BaseItem *item){
    if (SizeBag(item) < this->get_size_max()) {
        return true;
    }
    return false;
}
string BaseBag::toString() const{
    string type_bag[5] = {"Antidote","PhoenixI","PhoenixII","PhoenixIII","PhoenixIV"};
    string s_type = "";
    BaseItem* tmp = this->items;
    for (int i = 1; i <= SizeBag(items); i++){
        s_type += type_bag[tmp->type];
        tmp = tmp->next;
        if (i != SizeBag(items)) s_type += ",";
    }
    string s = "";
    s += "Bag[count=" + to_string(SizeBag(items))
    + ";" + s_type + "]";
    return s;
}

BaseItem *BaseBag::get(ItemType itemType){
    BaseItem *tmp = this->items_get();
    BaseItem *head = tmp;
    int pos = searchItem(tmp, itemType);
    if (pos == 1){
        delete_item_first(tmp);
    }
    else if (pos == SizeBag(tmp) && SizeBag(tmp) > 0){
        delete_item_last(tmp);
        insert_Last(tmp,head->type);
        delete_item_first(tmp);
    }
    else if (1 < pos && pos < SizeBag(tmp)){
        delete_item_middle(tmp, pos);
        insertMiddle(tmp,head->type,pos);
        delete_item_first(tmp);
    }
    
    if (0 < pos && pos <= SizeBag(this->items_get()) && SizeBag(this->items_get()) > 0){
        set_items(tmp);
        if (itemType == Antidote) return new antidote(tmp);
        if (itemType == PhoenixI) return new PhoenixDownI(tmp);
        if (itemType == PhoenixII) return new PhoenixDownII(tmp);
        if (itemType == PhoenixIII) return new PhoenixDownIII(tmp);
        if (itemType == PhoenixIV) return new PhoenixDownIV(tmp);
    }
    return nullptr;
}

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
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

BaseKnight *BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){ 
    BaseKnight *tmp = new BaseKnight();
    if (tmp->PaladinCheck(maxhp)) return new PaladinKnight(id,maxhp,level, gil,antidote,phoenixdownI);
    if (maxhp == 888) return new LancelotKnight(id,maxhp,level, gil,antidote,phoenixdownI);
    if (tmp->DragonCheck(maxhp)) return new DragonKnight(id,maxhp,level,gil, antidote ,phoenixdownI); 
    return new NormalKnight(id,maxhp,level, gil,antidote,phoenixdownI);
}

void BaseKnight::usingAntidote() {
    this->usedAntidote = true;
}
bool BaseKnight::useAntidote() {
    return this->usedAntidote;
}
void BaseKnight::notuseAntidote(){
    this->usedAntidote = false;
}


void BaseKnight::set_gil(string s)
{    
    if (s == "Madbear") this->gil += 100;
    else if (s == "Bandit") this->gil += 150;
    else if (s == "LordLupin") this->gil += 450;
    else if (s == "Elf") this->gil += 750;
    else if (s == "Troll") this->gil += 800;
}
int BaseKnight::get_gil(){
    return this->gil;
}
void BaseKnight::setgil(int gil)
{
    this->gil = gil;
}

int BaseKnight::get_level(){
    return this->level;
}
void BaseKnight::set_level(int level){
    this->level = level;
}

int BaseKnight::get_HP(){
    return this->hp;
}
int BaseKnight::get_MaxHP(){
    return this->maxhp;
}
void  BaseKnight::set_HP(int HP){
    this->hp = HP;
}

void BaseKnight::set_type(KnightType x){
    this->knightType = x;
}

bool BaseKnight::get_poisoned_state() const{
    return this->poisoned_state;
}
void BaseKnight::knight_poisoned(){
    this->poisoned_state = true;    
}
void BaseKnight::knight_get_normal(){
    this->poisoned_state = false;
}

bool BaseKnight::PaladinCheck(int HP){
    if (HP == 0 || HP == 1) return false;
    else if (HP == 2) return true;
    else
    {
        for (int i = 2; i < HP/2 + 1; i++)
        {
            if (HP % i == 0) return false;
        }
    }
    return true;
}

bool BaseKnight::DragonCheck(int HP){ 
    int digit[3], cnt = 2, num_length = 0; 
    while (num_length <= 3)
    {
        digit[cnt--] = HP % 10;
        HP /= 10;
        ++num_length;
    }
    
    int a = digit[0], b = digit[1], c = digit[2];
    
    if ((a > 0) && (b > 0) & (c > 0) && (a * a + b * b == c * c || b * b + c * c == a * a || c * c + a * a == b * b)) {
        return true;
    }
    return false;
}

KnightType BaseKnight::Knighttype() { 
    return this->knightType;
}

PaladinKnight::PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this->id = id;
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->knightType = PALADIN;
    this->bag = new PaladinBag(this,phoenixdownI,antidote);
}

LancelotKnight::LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this->id = id;
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->knightType = LANCELOT;
    this->bag = new LancelotBag(this,phoenixdownI,antidote);
}

DragonKnight::DragonKnight(int id, int maxhp, int level,int gil, int antidote, int phoenixdownI){
    this->id = id;
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    //cout << phoenixdownI;
    this->phoenixdownI = phoenixdownI;
    this->knightType = DRAGON;
    this->bag = new DragonBag(this,phoenixdownI,0);
}


NormalKnight::NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    this->id = id;
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->knightType = NORMAL;
    this->bag = new NormalBag(this,phoenixdownI,antidote);  
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
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

int ArmyKnights::count() const{
    return this->n;
}

BaseKnight *ArmyKnights::lastKnight() const{
        if (this->count() == 0) return nullptr;
        return baseknight[this->count() - 1]; 
}

ArmyKnights::ArmyKnights(const string& file_armyknights)
{
    int num_knights,hp,maxhp, level, phoenixdownI, gil, antidote,id;
    string num_string;
    ifstream fa;
    fa.open(file_armyknights);
        fa >> num_knights;
        this->n = num_knights;
        baseknight = new BaseKnight*[num_knights];
        for (int i = 0; i < num_knights; i++)
        {
            id = i + 1;
            fa >> hp >> level >> phoenixdownI >> gil >> antidote;           
            maxhp = hp; 
            baseknight[i] = baseknight[i]->create(id,maxhp,level,gil,antidote,phoenixdownI);
        }
    fa.close();
}

bool ArmyKnights::hasExcaliburSword() const{
    return has_Excalibur_Sword;
}

bool ArmyKnights::hasGuinevereHair() const{
    return has_Guinevere_Hair;
}

bool ArmyKnights::hasLancelotSpear() const{
    return has_Lancelot_Spear;
}

bool ArmyKnights::hasPaladinShield() const{
    return has_Paladin_Shield;
}

bool ArmyKnights::fight(BaseOpponent *opponent)
{  
    int check_level = opponent->checkLevel(baseknight[this->count() - 1]);
    //knight win
    if (check_level) 
    {
        opponent->KnightWin(baseknight[this->count() - 1]); 
        int remain = 0;
        if (baseknight[this->count() - 1]->get_gil() > 999) {
            int num_knights_idx = this->count() - 1;
            remain = baseknight[num_knights_idx]->get_gil() - 999;
            baseknight[num_knights_idx]->setgil(999);
            while (--num_knights_idx >= 0){
                if (baseknight[num_knights_idx]->get_gil() < 999){
                    int gil_knight = baseknight[num_knights_idx]->get_gil();
                    gil_knight += remain;
                    remain = 0; 
                    baseknight[num_knights_idx]->setgil(gil_knight);
                }
                if (baseknight[num_knights_idx]->get_gil() > 999){
                    int gil_redundant = baseknight[num_knights_idx]->get_gil();
                    remain += gil_redundant - 999;
                    baseknight[num_knights_idx]->setgil(999);
                }
            }
        }
        return true;
    }
    //knight lose
    opponent->DoSth(baseknight[this->count() - 1]);
    if (baseknight[this->count() - 1]->useAntidote() == true){
        baseknight[this->count() - 1]->notuseAntidote();
        return false;
    }  //event 6 if had used antidote then stop using phoenix
    opponent->getPhoenix(baseknight[this->count() - 1]);
    opponent->UsingGil(baseknight[this->count() - 1]);
    return false;
}


bool ArmyKnights::adventure(Events *events){
    bool first_time_Omega = true, first_time_hades = true , fightcheck;
    for (int i = 0; i < events->count(); i++)
    {
        if (events->get(i) == 1){
            BaseOpponent *madbear = new MadBear(i,events->get(i));
            fightcheck = this->fight(madbear);
            if (!fightcheck && baseknight[this->count() - 1]->get_HP() <= 0) this->n--;
        }
        else if (events->get(i) == 2){
            BaseOpponent *bandit = new Bandit(i,events->get(i));
            fightcheck = this->fight(bandit);
            if (!fightcheck && baseknight[this->count() - 1]->get_HP() <= 0) this->n--;
        }
        else if (events->get(i) == 3){
            BaseOpponent *lordlupin = new LordLupin(i,events->get(i));
            fightcheck = this->fight(lordlupin);
            if (!fightcheck && baseknight[this->count() - 1]->get_HP() <= 0) this->n--;
        }
        else if (events->get(i) == 4){
            BaseOpponent *elf = new Elf(i,events->get(i));
            fightcheck = this->fight(elf);
            if (!fightcheck && baseknight[this->count() - 1]->get_HP() <= 0) this->n--;
        }
        else if (events->get(i) == 5){
            BaseOpponent *troll = new Troll(i,events->get(i));
            fightcheck = this->fight(troll);
            if (!fightcheck && baseknight[this->count() - 1]->get_HP() <= 0) this->n--;
        }
        else if (events->get(i) == 6){
            BaseOpponent *tornbery = new Tornbery(i,events->get(i));
            fightcheck = this->fight(tornbery);
            if (!fightcheck && baseknight[this->count() - 1]->get_HP() <= 0) this->n--;
        }
        else if (events->get(i) == 7){
            BaseOpponent *queenofcard = new QueenOfCard(i,events->get(i));
            fightcheck = this->fight(queenofcard);
        }
        else if (events->get(i) == 8){
            BaseOpponent *nina = new NinaDeRings(i,events->get(i));
            fightcheck = this->fight(nina);
        }
        else if (events->get(i) == 9){
            BaseOpponent *durian = new DurianGarden(i,events->get(i));
            fightcheck = this->fight(durian);
        }
        else if (events->get(i) == 10 && first_time_Omega){
            BaseOpponent *omega = new OmegaWeapon(i,events->get(i));
            fightcheck = this->fight(omega);
            if (fightcheck) first_time_Omega = false;
            else if (!fightcheck && lastKnight()->get_HP() <= 0) this->n--;
        }
        else if (events->get(i) == 11 && first_time_hades)
        {
            BaseOpponent *hades = new Hades(i,events->get(i));
            fightcheck = this->fight(hades);
            if (fightcheck) {
                this->has_Paladin_Shield = true;
                first_time_hades = false;    
            }
            else if (!fightcheck && lastKnight()->get_HP() <= 0) this->n--;
        }
        else if (events->get(i) == 95  && this->hasPaladinShield() == false){
            this->has_Paladin_Shield = true;
        }
        else if (events->get(i) ==  96){
            this->has_Lancelot_Spear = true;
        }
        else if (events->get(i) == 97){
            this->has_Guinevere_Hair = true;
        }
        else if (events->get(i) == 98 && this->hasPaladinShield() && this->hasLancelotSpear() && this->hasGuinevereHair()){
            this->has_Excalibur_Sword = true;
        }
        else if (events->get(i) == 99){
            int HP_ultmecia = 5000, damage = 0;
            if (this->hasExcaliburSword()) {
                this->printInfo();
                continue;
            }
            else if (this->hasPaladinShield() && this->hasGuinevereHair() && this->hasLancelotSpear()){    
                int cnt_index_count = 0,index_count[1000];
                for (int i = this->count() - 1; i >= 0; i--){
                    if (baseknight[i]->Knighttype() == DRAGON || baseknight[i]->Knighttype() == LANCELOT || baseknight[i]->Knighttype() == PALADIN){
                        index_count[cnt_index_count++] = i;
                    }
                }
                if (cnt_index_count == 0) {
                    this->n = 0;
                }
                else {
                    for (int i = 0; i < cnt_index_count; i++){
                        int idx = index_count[i];
                        if (baseknight[idx]->Knighttype() == LANCELOT) damage = (baseknight[idx]->get_HP()) * (baseknight[idx]->get_level()) * 0.05; 
                        else if (baseknight[idx]->Knighttype() == PALADIN) damage = (baseknight[idx]->get_HP()) * (baseknight[idx]->get_level()) * 0.06;
                        else if (baseknight[idx]->Knighttype() == DRAGON) damage = (baseknight[idx]->get_HP()) * (baseknight[idx]->get_level()) * 0.075;
                        // cout << damage << " ";
                        // cout << "\n";
                        HP_ultmecia -= damage;
                        //cout << HP_ultmecia << endl;
                        if (HP_ultmecia <= 0) break;
                        else {
                            int a = index_count[i];
                            for (int j = a; j < n - 1; j++){
                                baseknight[j] = baseknight[j + 1];
                            }
                            this->n--; 
                        } 
                    }
                    if (HP_ultmecia > 0) this->n = 0;   
                }
            }
            else this->n = 0; // if the army doesn't have enough 3  
        }
        else if (events->get(i) == 112){ 
            int num = this->count() - 1; bool insertPhoenixII;
            BaseItem *itemcopy = baseknight[num]->get_bag()->items_get();
            insertPhoenixII = baseknight[num]->get_bag()->insertFirst(itemcopy);

            while (insertPhoenixII == false)
            {
                --num;
                if (num >= 0){
                    itemcopy = baseknight[num]->get_bag()->items_get();
                    insertPhoenixII = baseknight[num]->get_bag()->insertFirst(itemcopy);
                } 
                else {
                    ++num;
                    break;
                }
            }
            if (insertPhoenixII == true) insert_First(itemcopy,PhoenixII);
            baseknight[num]->get_bag()->set_items(itemcopy);

        }
        else if (events->get(i) == 113){
            int num = this->count() - 1; bool insertPhoenixIII;
            BaseItem *itemcopy = baseknight[num]->get_bag()->items_get();
            insertPhoenixIII = baseknight[num]->get_bag()->insertFirst(itemcopy);

            while (insertPhoenixIII == false)
            {
                --num;
                if (num >= 0){
                    itemcopy = baseknight[num]->get_bag()->items_get();
                    insertPhoenixIII = baseknight[num]->get_bag()->insertFirst(itemcopy);
                } 
                else {
                    ++num;
                    break;
                }
            }
            if (insertPhoenixIII == true) insert_First(itemcopy,PhoenixIII);
            baseknight[num]->get_bag()->set_items(itemcopy);

        }
        else if (events->get(i) == 114){
            int num = this->count() - 1; bool insertPhoenixIV;
            BaseItem *itemcopy = baseknight[num]->get_bag()->items_get();
            insertPhoenixIV = baseknight[num]->get_bag()->insertFirst(itemcopy);

            while (insertPhoenixIV == false)
            {
                --num;
                if (num >= 0){
                    itemcopy = baseknight[num]->get_bag()->items_get();
                    insertPhoenixIV = baseknight[num]->get_bag()->insertFirst(itemcopy);
                } 
                else {
                    ++num;
                    break;
                }
            }
            if (insertPhoenixIV == true) insert_First(itemcopy,PhoenixIV);
            baseknight[num]->get_bag()->set_items(itemcopy);
        }
        this->printInfo();
        if (this->n == 0) break;
    }
    if (this->lastKnight() == nullptr) return false;
    return true;
}
/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

void KnightAdventure::loadArmyKnights(const string & file_armyknights){
    armyKnights = new ArmyKnights(file_armyknights);
}

void KnightAdventure::loadEvents(const string & file_event){
    events = new Events(file_event);
}

void KnightAdventure::run(){
    bool tmp = armyKnights->adventure(events);
    armyKnights->printResult(tmp);    
}

KnightAdventure::~KnightAdventure() {
    delete armyKnights;
    delete events;
}
/* * * END implementation of class KnightAdventure * * */