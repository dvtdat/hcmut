#include "knight2.h"

/* * * BEGIN implementation of miscellaneous functions * * */
bool isPrime(int maxHP)
{
    if (maxHP <= 1) return false;
    for (int i = 2; i <= maxHP / 2; ++i)
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
    // TODO
    // WARNING: COULD BREAK CODE WHEN DELETE NODES
}

int getBagSize(BaseItem* head)
{
    if (head == nullptr) return 0;
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

bool BaseBag::insertFirst(ItemType type)
{
    if (size <= getBagSize(headItem)) return false;

    if (type == ANTIDOTE) headItem = new Antidote(headItem);
    if (type == PHOENIXI) headItem = new PhoenixDownI(headItem);    
    if (type == PHOENIXII) headItem = new PhoenixDownII(headItem);
    if (type == PHOENIXIII) headItem = new PhoenixDownIII(headItem);
    if (type == PHOENIXIV) headItem = new PhoenixDownIV(headItem);

    return true;
}

void BaseBag::dropFirst()
{
    if (headItem == nullptr) return;
    BaseItem* tmp = headItem;
    headItem = headItem->next;
    delete tmp;
}

void BaseBag::swapItem(BaseItem* item)
{
    if (headItem == item) return;
    BaseItem* pre = headItem;
    BaseItem* cur;
    if (headItem->next == item)
    {
        cur = pre->next;
        pre->next = pre->next->next;
        cur->next = pre;
    }
    else
    {
        while (pre->next != item) pre = pre->next;
        cur = pre->next;
        BaseItem* tmp = cur->next;
        cur->next = headItem->next;
        pre->next = headItem;
        headItem->next = tmp;
    }
    headItem = cur; 
}

BaseItem* BaseBag::get(ItemType type)
{
    if (headItem == nullptr) return nullptr;
    
    BaseItem* pre = headItem;
    while (pre != nullptr)
    {
        if (pre->getType() == type) return pre;
        pre = pre->next;
    }

    return nullptr;
}

BaseItem* BaseBag::getPhoenixDown(BaseKnight* knight)
{
    if (headItem == nullptr) return nullptr;
    ItemType type[4] = {PHOENIXI, PHOENIXII, PHOENIXIII, PHOENIXIV};

    BaseItem* pre = headItem;
    while (pre != nullptr)
    {
        for (int i = 0; i < 4; ++i) if (pre->getType() == type[i] && pre->canUse(knight)) return pre;
        pre = pre->next;
    }

    return nullptr;
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
    int code = opponent->getCode();
    if (1 <= code && code <= 5) return true;
    if (code == 6)
    {
        if (level >= (idx + code) % 10 + 1) return true;
        return false;
    }
    if (code == 7)
    {
        if (level >= (idx + code) % 10 + 1) changeGil(gil * 2);
        return true;
    }

    if (code == 8)
    {
        if (HP < maxHP / 3) changeHP(HP + maxHP / 5); 
        return true;
    }

    if (code == 9)
    {
        changeHP(maxHP);
        return true;
    }

    if (code == 10)
    {
        if (getLevel() == 10 && getHP() == getMaxHP())
        {
            changeLevel(10);
            changeGil(MAXGIL);
            return true;
        }
        changeHP(0);
        return false;
    }

    if (code == 11)
    {
        if (getLevel() >= 8) return true;
        changeHP(0);
        return false;
    }
    return false;
}

bool LancelotKnight::fight(BaseOpponent* opponent, int idx)
{
    int code = opponent->getCode();
    if (1 <= code && code <= 5) return true;
    if (code == 6)
    {
        if (level >= (idx + code) % 10 + 1) return true;
        return false;
    }

    if (code == 7)
    {
        if (level >= (idx + code) % 10 + 1) changeGil(gil * 2);
        else changeGil(gil / 2);
        return true;
    }

    if (code == 8)
    {
        if (gil >= 50 && HP < maxHP / 3)
        {
            changeGil(gil - 50);
            changeHP(HP + maxHP / 5);
        } 
        return true;
    }

    if (code == 9)
    {
        changeHP(maxHP);
        return true;
    }

    if (code == 10)
    {
        if (getLevel() == 10 && getHP() == getMaxHP())
        {
            changeLevel(10);
            changeGil(MAXGIL);
            return true;
        }
        changeHP(0);
        return false;
    }

    if (code == 11)
    {
        if (getLevel() == 10) return true;
        changeHP(0);
        return false;
    }
    return false;
}

bool DragonKnight::fight(BaseOpponent* opponent, int idx)
{
    int code = opponent->getCode();
    if (1 <= code && code <= 5)
    {
        if (level >= (idx + code) % 10 + 1) return true;
        changeHP(HP - opponent->getBaseDamage() * ((idx + code) % 10 + 1 - level));
        return false;
    }

    if (code == 6)
    {
        if (level >= (idx + code) % 10 + 1) return true;
        return false;
    }

    if (code == 7)
    {
        if (level >= (idx + code) % 10 + 1) changeGil(gil * 2);
        else changeGil(gil / 2);
        return true;
    }

    if (code == 8)
    {
        if (gil >= 50 && HP < maxHP / 3)
        {
            changeGil(gil - 50);
            changeHP(HP + maxHP / 5);
        } 
        return true;
    }

    if (code == 9)
    {
        changeHP(maxHP);
        return true;
    }

    if (code == 10)
    {
        changeLevel(10);
        changeGil(MAXGIL);
        return true;
    }

    if (code == 11)
    {
        if (getLevel() == 10) return true;
        changeHP(0);
        return false;
    }
    return false;
}

bool NormalKnight::fight(BaseOpponent* opponent, int idx)
{
    int code = opponent->getCode();
    if (1 <= code && code <= 5)
    {
        if (level >= (idx + code) % 10 + 1) return true;
        changeHP(HP - opponent->getBaseDamage() * ((idx + code) % 10 + 1 - level));
        return false;
    }

    if (code == 6)
    {
        if (level >= (idx + code) % 10 + 1) return true;
        return false;
    }

    if (code == 7)
    {
        if (level >= (idx + code) % 10 + 1) changeGil(gil * 2);
        else changeGil(gil / 2);
        return true;
    }

    if (code == 8)
    {
        if (gil >= 50 && HP < maxHP / 3)
        {
            changeGil(gil - 50);
            changeHP(HP + maxHP / 5);
        } 
        return true;
    }

    if (code == 9)
    {
        changeHP(maxHP);
        return true;
    }

    if (code == 10)
    {
        if (getLevel() == 10 && getHP() == getMaxHP())
        {
            changeLevel(10);
            changeGil(MAXGIL);
            return true;
        }
        changeHP(0);
        return false;
    }

    if (code == 11)
    {
        if (getLevel() == 10) return true;
        changeHP(0);
        return false;
    }
    return false;
}
/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights(const string & file_armyknights)
{
    ifstream input;
    input.open(file_armyknights);
    input >> nKnight;

    knights = new BaseKnight*[nKnight + 1]{nullptr};
    for (int i = 1; i <= nKnight; ++i)
    {
        int maxHP, level, phoenixDownI, gil, antidote;
        input >> maxHP >> level >> phoenixDownI >> gil >> antidote;
        knights[i - 1] = BaseKnight::create(i, maxHP, level, gil, antidote, phoenixDownI);
    }
    nCurKnight = nKnight;
    input.close();
}

ArmyKnights::~ArmyKnights()
{
    for (int i = 0; i < nKnight; ++i) delete knights[i];
    delete[] knights;
    knights = nullptr;
}

bool ArmyKnights::fight(BaseOpponent* opponent, int idx)
{
    int code = opponent->getCode();

    if (code == CODEULTIMECIA)
    {
        int opponentHP = 5000;
        if (hasExcaliburSword()) return true;
        if (!hasThreeTreasure()) goto end;

        for (int i = nCurKnight - 1; i >= 0; --i)
        {
            bool flag = false;
            if (knights[i] != nullptr && knights[i]->getType() != NORMAL)
            {
                int damage = knights[i]->getHP() * knights[i]->getLevel();
                if (knights[i]->getType() == DRAGON) damage = damage * 0.075;
                if (knights[i]->getType() == PALADIN) damage = damage * 0.06;
                if (knights[i]->getType() == LANCELOT) damage = damage * 0.05;

                opponentHP = opponentHP - damage;
                
                if (opponentHP <= 0) return true;
                
                if (knights[i] == nullptr) continue;
                delete knights[i];
                knights[i] = nullptr;
            }
        }
    
    end:
        for (int i = 0; i < nKnight; ++i)
        {
            if (knights[i] == nullptr) continue;
            delete knights[i];
            knights[i] = nullptr;
        }
        return false;
    }

    BaseKnight* lKnight = lastKnight();

    if (code == CODEHADES && hasMetHades()) return true;
    if (code == CODEOMEGA && hasMetOmega()) return true;


    if (lKnight->fight(opponent, idx) == false)
    {
        if (code == CODETORNBERY && lKnight->getType() != DRAGON)
        {
            if (lKnight->getBag()->get(ANTIDOTE) != nullptr)
            {
                lKnight->getBag()->swapItem(lKnight->getBag()->get(ANTIDOTE));
                lKnight->getBag()->dropFirst();
                return true;
            }
            lKnight->getBag()->dropFirst(); 
            lKnight->getBag()->dropFirst(); 
            lKnight->getBag()->dropFirst();
            lKnight->changeHP(lKnight->getHP() - 10);
        }

        if (lKnight->getHP() <= 0)
        {
            BaseItem* tmp = lKnight->getBag()->getPhoenixDown(lKnight);
            if (tmp != nullptr)
            {    
                tmp->use(lKnight);
                lKnight->getBag()->swapItem(tmp);
                lKnight->getBag()->dropFirst();
                if (lKnight->getHP() > 0) return true;
            }

            if (lKnight->getGil() >= 100)
            {
                lKnight->changeHP(lKnight->getMaxHP() / 2);
                lKnight->changeGil(lKnight->getGil() - 100);
                if (lKnight->getHP() > 0) return true;
            }

            excessGil = lKnight->getGil();
            killLastKnight();
            if (count() > 0) return true;
            else return false;
        }

        BaseItem* tmp = lKnight->getBag()->getPhoenixDown(lKnight);
        if (tmp != nullptr)
        {    
            tmp->use(lKnight);
            lKnight->getBag()->swapItem(tmp);
            lKnight->getBag()->dropFirst();
        }
        return true;
    }

    if (code == CODEOMEGA)
    {
        setOmega();
        return true;
    }
    if (code == CODEHADES)
    {
        setHades();
        setTreasure(PALADINSHIELD);
        return true;
    }

    lKnight->changeLevel(lKnight->getLevel() + opponent->getLevelOptain());
    lKnight->changeGil(lKnight->getGil() + opponent->getGilOptain());
    excessGil = max(0, lKnight->getGil() - MAXGIL); 
    lKnight->changeGil(min(lKnight->getGil(), MAXGIL));
    if (excessGil > 0) distrubuteGil();
    return true;
}

bool ArmyKnights::adventure(Events* events)
{
    bool defeatUltimecia = false;
    for (int i = 0; i < events->count(); ++i)
    {
        if (count() <= 0) break;

        int code = events->get(i);
        if (code == 1) fight(new MadBear, i);
        if (code == 2) fight(new Bandit, i);
        if (code == 3) fight(new LordLupin, i);
        if (code == 4) fight(new Elf, i);
        if (code == 5) fight(new Troll, i);
        if (code == 6) fight(new Tornbery, i);
        if (code == 7) fight(new QueenOfCards, i);
        if (code == 8) fight(new NinaDeRings, i);
        if (code == 9) fight(new DurianGarden, i);
        if (code == 10) fight(new OmegaWeapon, i);
        if (code == 11) fight(new Hades, i);

        if (code == 95) setTreasure(PALADINSHIELD);
        if (code == 96) setTreasure(LANCELOTSPEAR);
        if (code == 97) setTreasure(GUINEVEREHAIR);
        if (code == 98 && hasThreeTreasure()) setTreasure(EXCALIBURSWORD);

        if (code > 110)
        {
            ItemType tmp;
            if (code == 112) tmp = PHOENIXII;
            if (code == 113) tmp = PHOENIXIII;
            if (code == 114) tmp = PHOENIXIV;
            int i = nCurKnight - 1;
            while(!knights[i]->getBag()->insertFirst(tmp) && i >= 0) i--;
        }

        if (code == 99) defeatUltimecia = fight(new Ultimecia, i);
        printInfo();
    }

    printResult(defeatUltimecia);
}

int ArmyKnights::count() const
{
    int cnt = 0;
    for (int i = 0; i < nKnight; ++i)
    {
        if (knights[i]) cnt++;
    }
    return cnt;
}

BaseKnight* ArmyKnights::lastKnight() const
{
    for (int i = nKnight; i >= 0; --i)
    {
        if (knights[i] != nullptr) return knights[i];
    }
}

void ArmyKnights::killLastKnight()
{
    delete knights[nCurKnight - 1];
    knights[nCurKnight - 1] = nullptr;
    nCurKnight--;
}

void ArmyKnights::distrubuteGil()
{
    for (int i = count() - 2; i >= 0; --i)
    {
        if (excessGil <= 0) return;
        knights[i]->changeGil(knights[i]->getGil() + excessGil);
        excessGil = max(0, knights[i]->getGil() - MAXGIL);
        knights[i]->changeGil(min(MAXGIL, knights[i]->getGil()));
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
    
    input >> nEvent;

    event = new int[nEvent];

    for (int i = 0; i < nEvent; ++i) input >> event[i];
        
    input.close();
}

Events::~Events()
{
    delete event;
    event = nullptr;
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
    armyKnights->adventure(events);
}
/* * * END implementation of class KnightAdventure * * */