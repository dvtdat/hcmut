#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */
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
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
BaseKnight * BaseKnight::create(int id, int maxHP, int level, int gil, int antidote, int phoenixdownI)
{
    BaseKnight * baseKnight;
    BaseBag bag;

    /* Some code of BaseBag */ // TODO

    baseKnight->id = id;
    baseKnight->maxHP = maxHP;
    baseKnight->level = level;
    baseKnight->gil = gil;
    baseKnight->antidote = antidote;
    baseKnight->bag = &bag;
    baseKnight->knightType = NORMAL;
}

string BaseKnight::toString() const 
{
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxHP)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}
/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights(const string & file_armyknights) // constructor
{
    // TODO
}

ArmyKnights::~ArmyKnights() // destructor
{
    // TODO
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
    // TODO
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

void ArmyKnights::printResult(bool win) const 
{
    cout << (win ? "WIN" : "LOSE") << endl;
}
/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() 
{
    armyKnights = nullptr;
    events = nullptr;
}

KnightAdventure::~KnightAdventure()
{
    // TODO
}

void KnightAdventure::loadArmyKnights(const string & tmpFile)
{
    ifstream input;
    input.open(tmpFile);

    input.close();
}

void KnightAdventure::loadEvents(const string & tmpFile)
{
    ifstream input;
    input.open(tmpFile);

    input.close();
}

void KnightAdventure::run()
{
    cout << "hello\n";
}
/* * * END implementation of class KnightAdventure * * */