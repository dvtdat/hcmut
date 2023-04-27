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
    int* valid = new int[6];
    valid[0] = 345, valid[1] = 354, valid[2] = 435, valid[3] = 453, valid[4] = 534, valid[5] = 543;
    for (int i = 0; i < 6; ++i)
    {
        if (maxHP == valid[i]) return true;
    }
    delete [] valid; 
    return false;
}

bool is888(int maxHP)
{
    return (maxHP == 888);
}
/* * * END implementation of miscellaneous functions * * */

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

    for (int i = 0; i < antidote; ++i)
    {
        if (i >= size) goto end;
        head = new Antidote(head);
    }

    for (int i = 0; i < phoenixDownI; ++i)
    {
        if (i + antidote >= size) goto end;
        head = new PhoenixDownI(head);
    }

end:
    this->headItem = head;
}

bool BaseBag::insertFirst(BaseItem * item)
{
    return true;
}

BaseItem * BaseBag::get(ItemType itemType)
{
    // TODO
}

string BaseBag::toString() const
{
    // TODO
}

void BaseBag::print()
{
    headItem->print();
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
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(HP) 
        + ",maxhp:" + to_string(maxHP)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}

void BaseKnight::print()
{
    cout << maxHP << ' ' << level << ' ' << gil << ' ' << knightType << '\n';
    bag->print();
    cout << '\n';
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights(const string & file_armyknights)
{
    ifstream input;
    input.open(file_armyknights);
    nKnight = new int;
    input >> *nKnight;

    knights = new BaseKnight*[*nKnight];
    for (int i = 1; i <= *nKnight; ++i)
    {
        int maxHP, level, phoenixDownI, gil, antidote;
        input >> maxHP >> level >> phoenixDownI >> gil >> antidote;
        knights[i - 1] = BaseKnight::create(i, maxHP, level, gil, antidote, phoenixDownI);
    }
    for (int i = 0; i < *nKnight; ++i)
    {
        knights[i]->print();
    }

    input.close();
}

ArmyKnights::~ArmyKnights()
{
    delete [] knights;
}

bool ArmyKnights::fight(BaseOpponent * opponent)
{
    // TODO
}

bool ArmyKnights::adventure(Events * events)
{
    // TODO
}

int ArmyKnights::count() const
{
    return *nKnight;
}

BaseKnight * ArmyKnights::lastKnight() const
{
    // TODO
}

bool ArmyKnights::hasPaladinShield() const
{
    // TODO
}

bool ArmyKnights::hasLancelotSpear() const
{
    // TODO
}

bool ArmyKnights::hasGuinevereHair() const
{
    // TODO
}

bool ArmyKnights::hasExcaliburSword() const
{
    // TODO
}

void ArmyKnights::printInfo() const 
{
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
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
    
    nEvent = new int;
    input >> *nEvent;

    event = new int[*nEvent];

    for (int i = 0; i < *nEvent; ++i)
    {
        int value; input >> value;
        event[i] = value;
        cout << value << ' ';
    }

    input.close();
}

Events::~Events()
{
    delete nEvent;
    delete [] event;
}

int Events::count() const
{
    return *nEvent;
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
    cout << "hello\n";
}
/* * * END implementation of class KnightAdventure * * */