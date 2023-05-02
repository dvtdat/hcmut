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

void BaseKnight::print()
{
    cout << maxHP << ' ' << level << ' ' << gil << ' ' << knightType << '\n';
    cout << bag->toString();
    cout << '\n';
}

bool PaladinKnight::fight(BaseOpponent* opponent, int idx)      //defeat all from 1 to 5, not lose gil to QoC, trade with Nina for free
{
    int code = opponent->getCode();
    
    if (CODEMADBEAR <= code && code <= CODETROLL)
    {
        if (level > (idx + code) % 10 + 1)
        {
            changeGil(gil + opponent->getGilOptain());
            return true;
        }
        else if (level < (idx + code) % 10 + 1)
        {
            changeHP(HP - opponent->getBaseDamage() * ((idx + code) % 10 + 1 - level));
            return false;
        }
    }

    if (code == CODETORNBERY)
    {
        if (level > (idx + code) % 10 + 1) 
        {
            changeLevel(level + 1);
            return true;
        }
        else if (level < (idx + code) % 10 + 1)
        {
            for (BaseItem* ptr = getBag()->headItem; ptr; ptr = ptr->next)
            {
                if (ptr->getType() == ANTIDOTE)
                {
                    this->getBag()->get(ANTIDOTE);
                    return true;
                }
            }

            this->getBag()->dropLastItem();
            this->getBag()->dropLastItem();
            this->getBag()->dropLastItem();
            changeHP(HP - 10);
            return false;
        }
    }

    if (code == CODEQUEEN)
    {
        if (level > (idx + code) % 10 + 1)
        {
            changeGil(gil * 2);
            return true;
        }
        else if (level < (idx + code) % 10 + 1)
        {
            changeGil(gil / 2);
            return false;
        }
    }

    if (code == CODENINA)
    {
        if (getGil() >= 50 && getHP() < getMaxHP() / 3)
        {
            changeGil(getGil() - 50);
            changeHP(getHP() + getMaxHP() / 5);
            return true;
        }
        return false;
    }

    if (code == CODEDURIAN)
    {
        changeHP(getMaxHP());
        return true;
    }

    if (code == CODEOMEGA)
    {
        if ((getLevel() == 10 && getHP() == getMaxHP()) || getType() == DRAGON)
        {
            changeLevel(MAXLEVEL);
            changeGil(MAXGIL);
            return true;
        }
        else
        {
            changeHP(0);
            return false;
        }
    }

    if (code == CODEHADES)
    {
        if ((getType() == NORMAL && getLevel() == 10) || (getType() == PALADIN)) return true;
        return false;
    }
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

    input.close();
}

bool ArmyKnights::fight(BaseOpponent* opponent, int idx)
{
    return knights[count() - 1]->fight(opponent, idx);
}

bool ArmyKnights::adventure(Events* events)
{
    for (int i = 0; i < events->count(); ++i)
    {
        int code = events->get(i);
        if (code == 1)          while (count() > 0 && !fight(new MadBear, i))         killLastKnight();
        if (code == 2)          while (count() > 0 && !fight(new Bandit, i))          killLastKnight();
        if (code == 3)          while (count() > 0 && !fight(new LordLupin, i))       killLastKnight();
        if (code == 4)          while (count() > 0 && !fight(new Elf, i))             killLastKnight();
        if (code == 5)          while (count() > 0 && !fight(new Troll, i))           killLastKnight();
        if (code == 6)          while (count() > 0 && !fight(new Tornbery, i))        killLastKnight();
        if (code == 7)          while (count() > 0 && !fight(new QueenOfCards, i))    killLastKnight();
        if (code == 8)          while (count() > 0 && !fight(new NinaDeRings, i))     killLastKnight();
        if (code == 9)          fight(new DurianGarden, i);
        if (code == 10)
        {
            if (hasMetOmega()) continue;
            while (count() > 0 && !fight(new OmegaWeapon, i)) killLastKnight();
            if (count() > 0) setOmega();
        }
        if (code == 11)
        {
            if (hasMetHades()) continue;
            while (count() > 0 && !fight(new Hades, i)) killLastKnight();
            if (count() > 0)
            {
                setTreasure(PALADINSHIELD);
                setHades();
            }
        }
        if (code > 110 && code % 110 == 2);      
        if (code > 110 && code % 110 == 3);
        if (code > 110 && code % 110 == 4);

        if (code == 95)                         setTreasure(PALADINSHIELD);
        if (code == 96)                         setTreasure(LANCELOTSPEAR);
        if (code == 97)                         setTreasure(GUINEVEREHAIR);
        if (code == 98 && hasThreeTreasure())   setTreasure(EXCALIBURSWORD);
        
        if (knights[count() - 1]->getGil() > MAXGIL)
        {
            setExcessGil(knights[count() - 1]->getGil() - MAXGIL);
            knights[count() - 1]->changeGil(MAXGIL);
            distrubuteGil();
        }
        printInfo();
    }

    // return (if Ultimecia die)
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
    BaseKnight* tmp = lastKnight();
    delete tmp;
    tmp = nullptr;
}

void ArmyKnights::distrubuteGil()
{
    for (int i = count() - 2; i >= 0; --i)
    {
        if (excessGil <= 0) return;
        int tmp = knights[i]->getGil() + excessGil - 999;
        knights[i]->changeGil(min(knights[i]->getGil() + excessGil, 999));
        excessGil = tmp;
    }
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
    
    nEvent = new int;
    input >> *nEvent;

    event = new int[*nEvent];

    for (int i = 0; i < *nEvent; ++i)
    {
        int value; input >> value;
        event[i] = value;
    }
    input.close();
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
    armyKnights->adventure(events);
}
/* * * END implementation of class KnightAdventure * * */