#include "knight2.h"

/* * * BEGIN implementation of miscellaneous functions * * */
bool isPrime(int maxHP)
{
    if (maxHP <= 1) return false;
    for (int i = 2; i < maxHP / 2; ++i)
    {
        if (maxHP % i == 0) return false;
    }
    return true;
}

bool isPythagorean(int maxHP)
{
    if (maxHP < 100) return false;
    int a = maxHP / 100, b = (maxHP / 10) % 10, c = maxHP % 10;
    return ((a * a + b * b == c * c || a * a + c * c == b * b || b * b + c * c == a * a) && a && b && c);
}

bool is888(int maxHP)
{
    return (maxHP == 888);
}
/* * * END implementation of miscellaneous functions * * */

/* * * BEGIN implementation of class BaseItem * * */

BaseItem::~BaseItem()
{
    delete knight;
    delete next;
}

int getBagSize(BaseItem* head)
{
    if (head->next == nullptr) return 1;
    return 1 + getBagSize(head->next);
}

/* * * END implementation of class BaseItem * * */

/* * * BEGIN implementation of class BaseBag * * */
BaseBag::BaseBag(BaseKnight* knight, int antidote, int phoenixDownI)
{
    this->knight = knight;
    
    KnightType type = knight->getType();
    if (type == DRAGON) size = BAGDRAGON;
    else if (type == NORMAL) size = BAGNORMAL;
    else if (type == LANCELOT) size = BAGLANCELOT;
    else size = BAGPALADIN;

    BaseItem* head = nullptr;

    for (int i = 0; i < phoenixDownI; ++i)
    {
        if (i >= size) goto end;
        head = new PhoenixDownI(head);
    }

    for (int i = 0; i < antidote; ++i)
    {
        if (i + phoenixDownI >= size) goto end;
        head = new Antidote(head);
    }

end:
    this->headItem = head;
}

void BaseBag::searchAntidote()
{
    for (BaseItem* ptr = headItem; ptr; ptr = ptr->next)
    {
        if (ptr->canUse(knight) && ptr->getType() == ANTIDOTE)
        {
            ptr->use(knight);
            return;
        }
    }
}

void BaseBag::searchPhoenixDown()
{
    for (BaseItem* ptr = headItem; ptr; ptr = ptr->next)
    {
        if (ptr->canUse(knight) && ptr->getType() != ANTIDOTE)
        {
            ptr->use(knight);
            return;
        }
    }
}

bool BaseBag::insertFirst(ItemType type)
{
    if (size >= getBagSize(headItem)) return false;

    if (type == ANTIDOTE) headItem = new Antidote(headItem);
    if (type == PHOENIXI) headItem = new PhoenixDownI(headItem);    
    if (type == PHOENIXII) headItem = new PhoenixDownII(headItem);
    if (type == PHOENIXIII) headItem = new PhoenixDownIII(headItem);
    if (type == PHOENIXIV) headItem = new PhoenixDownIV(headItem);

    return true;
}

void BaseBag::dropLastItem()
{
    if (headItem == nullptr) return;
    if (headItem->next == nullptr)
    {
        delete headItem;
        headItem = nullptr;
        return;
    }

    BaseItem* pre = headItem;
    while (pre->next->next)
    {
        pre = pre->next;
    }

    pre->next = nullptr;
    delete(pre->next);
}

BaseItem* BaseBag::get(ItemType type)
{
    if (headItem == nullptr) return nullptr;
    if (headItem->getType() == type)
    {
        BaseItem* tmp = headItem;
        headItem = headItem->next;
        return tmp;
    }

    BaseItem* pre = headItem;
    while (pre->next && pre->next->getType() != type)
    {
        pre = pre->next;
    }
    if (pre->getType() != type && pre->next == nullptr) return nullptr;

    BaseItem* cur = pre->next;
    BaseItem* aft = cur->next;
    pre->next = aft;
    return cur;
}

string BaseBag::toString() const
{
    string out = "Bag[count=";
    out = out + to_string(headItem != nullptr ? getBagSize(headItem) : 0);
    out = out + ";";

    if (headItem == nullptr) goto end;

    for (BaseItem* ptr = headItem; ptr; ptr = ptr->next)
    {
        string tmp;
        if (ptr->getType() == ANTIDOTE) tmp = "Antidote";
        if (ptr->getType() == PHOENIXI) tmp = "PhoenixI";
        if (ptr->getType() == PHOENIXII) tmp = "PhoenixII";
        if (ptr->getType() == PHOENIXIII) tmp = "PhoenixIII";
        if (ptr->getType() == PHOENIXIV) tmp = "PhoenixIV";

        out = out + tmp;
        if (ptr->next) out = out + ",";
    }

end:
    out = out + "]";
    return out;
}

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
BaseKnight* BaseKnight::create(int id, int maxHP, int level, int gil, int antidote, int phoenixdownI)
{
    if (isPrime(maxHP))
    {
        return new PaladinKnight(id, maxHP, level, gil, antidote, phoenixdownI);
    }
    if (is888(maxHP))
    {
        return new LancelotKnight(id, maxHP, level, gil, antidote, phoenixdownI);
    }
    if (isPythagorean(maxHP))
    {
        return new DragonKnight(id, maxHP, level, gil, antidote, phoenixdownI);
    }
    return new NormalKnight(id, maxHP, level, gil, antidote, phoenixdownI);
}

string BaseKnight::toString() const 
{
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    string s("");
    s = "[Knight:id:" + to_string(id) + ",hp:" + to_string(HP) + ",maxhp:" + to_string(maxHP) + ",level:" 
        + to_string(level) + ",gil:" + to_string(gil) + "," + bag->toString() + ",knight_type:" + typeString[knightType] + "]";
    return s;
}

bool PaladinKnight::fight(BaseOpponent* opponent, int idx)
{
    
}

bool LancelotKnight::fight(BaseOpponent* opponent, int idx)
{
    
}

bool DragonKnight::fight(BaseOpponent* opponent, int idx)
{
    
}

bool NormalKnight::fight(BaseOpponent* opponent, int idx)
{
    
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights(const string & file_armyknights)
{
    ifstream input;
    input.open(file_armyknights);
    input >> nKnight;

    knights = new BaseKnight*[nKnight];
    for (int i = 1; i <= nKnight; ++i)
    {
        int maxHP, level, phoenixDownI, gil, antidote;
        input >> maxHP >> level >> phoenixDownI >> gil >> antidote;
        knights[i - 1] = BaseKnight::create(i, maxHP, level, gil, antidote, phoenixDownI);
    }

    printInfo();
    input.close();
}

ArmyKnights::~ArmyKnights()
{
    for (int i = 0; i < nKnight; ++i) delete knights[i];
    delete knights;
    knights = nullptr;
}

bool ArmyKnights::fight(BaseOpponent* opponent, int idx)
{
    // TODO
}

bool ArmyKnights::adventure(Events* events)
{
    // TODO
}

int ArmyKnights::count() const
{
    int cnt = 0;
    for (; knights[cnt]; ++cnt);
    return cnt;
}

BaseKnight* ArmyKnights::lastKnight() const
{
    return knights[count() - 1];
}

void ArmyKnights::killLastKnight()
{
    // TODO
}

void ArmyKnights::distrubuteGil()
{
    // TODO
}

bool ArmyKnights::hasMetOmega() const
{
    return meetOmega;
}

bool ArmyKnights::hasMetHades() const
{
    return meetHades;
}

bool ArmyKnights::hasThreeTreasure() const
{
    return (hasTreasure[PALADINSHIELD] && hasTreasure[LANCELOTSPEAR] && hasTreasure[GUINEVEREHAIR]);
}

bool ArmyKnights::hasPaladinShield() const
{
    return hasTreasure[PALADINSHIELD];
}

bool ArmyKnights::hasLancelotSpear() const
{
    return hasTreasure[LANCELOTSPEAR];
}

bool ArmyKnights::hasGuinevereHair() const
{
    return hasTreasure[GUINEVEREHAIR];
}

bool ArmyKnights::hasExcaliburSword() const
{
    return hasTreasure[EXCALIBURSWORD];
}

void ArmyKnights::printInfo() const 
{
    cout << "No. knights: " << this->count();
    if (this->count() > 0) 
    {
        BaseKnight* lKnight = lastKnight();
        cout << ";" << lKnight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const 
{
    cout << (win ? "WIN" : "LOSE") << endl;
}
/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class Events * * */
Events::Events(const string & file_events)
{
    ifstream input;
    input.open(file_events);
    
    input >> nEvent;

    event = new int[nEvent];

    for (int i = 0; i < nEvent; ++i) input >> event[i];
        
    input.close();
}

Events::~Events()
{
    delete event;
}

int Events::count() const
{
    return nEvent;
}

int Events::get(int i) const
{
    return event[i];
}
/* * * END implementation of class Events * * */


/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() 
{
    armyKnights = nullptr;
    events = nullptr;
}

KnightAdventure::~KnightAdventure()
{
    delete armyKnights;
    delete events;
}

void KnightAdventure::loadArmyKnights(const string & tmpFile)
{
    armyKnights = new ArmyKnights(tmpFile);
}

void KnightAdventure::loadEvents(const string & tmpFile)
{
    events = new Events(tmpFile);
}

void KnightAdventure::run()
{
    cout << "haha";
}
/* * * END implementation of class KnightAdventure * * */