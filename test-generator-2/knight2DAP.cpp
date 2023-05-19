#include "knight2DAP.h"

/* * * BEGIN implementation of class BaseBag * * */

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() 
{
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s = "";

    KnightType type = this->getType();

    int mapIndex = static_cast<int>(type);

    s += "[Knight:id:"
        + to_string(id) 
        + ",hp:" + to_string(hp)
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil) + ","
        + bag->toString()
        + ",knight_type:"
        + typeString[mapIndex]
        + "]";

    return s;
};

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const
{
    cout << "No. knights: " << this->count();
    if (this->count() > 0)
    {
        BaseKnight *lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
         << ";LancelotSpear:" << this->hasLancelotSpear()
         << ";GuinevereHair:" << this->hasGuinevereHair()
         << ";ExcaliburSword:" << this->hasExcaliburSword()
         << endl
         << string(50, '-') << endl;
};

void ArmyKnights::printResult(bool win) const
{
    cout << (win ? "WIN" : "LOSE") << endl;
};

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure()
{
    armyKnights = nullptr;
    events = nullptr;
};

KnightAdventure::~KnightAdventure()
{
    if (armyKnights != NULL)
        delete armyKnights;

    if (events != NULL)
        delete events;
};

void KnightAdventure::loadArmyKnights(const string &armyKnightsFile)
{
    armyKnights = new ArmyKnights(armyKnightsFile);
};

void KnightAdventure::loadEvents(const string &eventsFile)
{
    events = new Events(eventsFile);
};

void KnightAdventure::run()
{
    if (armyKnights != NULL && events != NULL)
    {
        // armyKnights->printResult(armyKnights->adventure(events));
        armyKnights->printResult(armyKnights->adventure(events));
    }
};

/* * * END implementation of class KnightAdventure * * */

// class Events
// {
// public:
    Events::Events(const string &file_events)
    {
        // Read file_events and store all of events ID in dynamic array
        ifstream file(file_events);

        string eventSize = "";
        string eventIDList = "";

        

        if (file.is_open())
        {
            getline(file, eventSize);
            getline(file, eventIDList);
        }

        file.close();

        // use string stream object to change type of 2 vars eventSize, and eventIDList to corresponding int type, and array type int
        stringstream stringStream1(eventSize);
        stringstream stringStream2(eventIDList);

        stringStream1 >> this->eventRealSize;

        // Allocate eventID pointer to dynamic array;
        eventID = new int[eventRealSize];
        // Read file_events and store all of events ID in dynamic array

        for (int counter = 0; counter < eventRealSize; ++counter)
            stringStream2 >> eventID[counter];
    };

    Events::~Events()
    {
        delete[] eventID;
        eventID = nullptr;
    };

    int Events::count() const
    {
        // Return number of event which is a copy of eventRealSize
        return eventRealSize;
    };

    int Events::get(int i) const
    {

        // parameter i is for eventIndex at each cell not the event ID, which need to access through array pointer
        //  return ID of event at i
        return eventID[i];
    };

// private:
//     // Declare eventID as pointer in
//     int *eventID;
//     // Declare int type event size but in int type
//     int eventRealSize;
// };

BaseKnight *BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    BaseKnight *knight = nullptr;

    // knight->id = id;
    // knight->maxhp = maxhp;
    // knight->level = level;
    // knight->antidote = antidote;
    // BaseBag *knightBaseBag = new BaseBag();

    // Paladin class
    if (isPrime(maxhp))
    {
        knight = new PaladinKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }

    // Lancelot
    else if (maxhp == 888)
    {
        knight = new LancelotKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }

    // Dragon knight
    else if (isPythagoras(maxhp))
    {
        knight = new DragonKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }

    // Normal knight
    else
    {
        knight = new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }

    // return pointer to newly created instance

    return knight;
};

// getHP to return hp function

// These function with virtual keyword will return instance of base class rather than superclass when calling with pointer to BaseKnight type
 int BaseKnight::getHP() const
{
    return hp;
};

 int BaseKnight::getGil() const
{
    return gil;
};

 KnightType BaseKnight::getType() const
{
    return knightType;
};

 int BaseKnight::getMaxHp() const
{
    return maxhp;
};

 void BaseKnight::setHP(int addedAmount)
{
    hp = addedAmount;
};

 int BaseKnight::getAntidote() const
{
    return antidote;
};

 void BaseKnight::setAntidote(int newQuantity)
{
    antidote = newQuantity;
};

bool isPrime(int const &number)
{
    if (number < 2)
        return false;

    for (int counter = 2; counter <= number / 2; ++counter)
    {
        if (number % counter == 0)
            return false;
    }

    return true;
};

bool isPythagoras(int const &number)
{

    int firstSide = number / 100;
    int secondSide = (number % 100) / 10;
    int thirdSide = number % 10;

    if ((firstSide * firstSide + secondSide * secondSide == thirdSide * thirdSide) || (secondSide * secondSide + thirdSide * thirdSide == firstSide * firstSide) || (thirdSide * thirdSide + firstSide * firstSide == secondSide * secondSide))
        return true;

    else
        return false;
};

// class ArmyKnights
// {
// public:
    ArmyKnights::ArmyKnights(const string &file_armyknights)
    {
        //check again
        knight = nullptr;

        // Read from armyKnights file
        string armyKnightSize = "";

        // int realArmyKnightSize = 0; comment because this var will be used by another function in this class

        ifstream file(file_armyknights);
        if (file.is_open())
            getline(file, armyKnightSize);

        stringstream stringStream1(armyKnightSize);

        stringStream1 >> realArmyKnightSize;

        string knightsStat[realArmyKnightSize];

        int index = 0;

        // component stat of each knight will be store in outside array
        int componentStat[5] = {0 ,0 , 0, 0, 0};

        // Store each knight into allocated array
        // In this case, new BaseKnight * [realArmyKnightSize] will point to the first element of an array of n pointers to BaseKnight object, and each elements in an array is a pointer to BaseKnight object cause we added * charater earlier
        knight = new BaseKnight *[realArmyKnightSize];

        // Read each knight status, and store it in array of string
        while (!file.eof())
        {
            getline(file, knightsStat[index]);
            ++index;

            // For example knightStat[0] will be a string of "172 4 0 100 0"
        }

        for (int counter = 0; counter < realArmyKnightSize; ++counter)
        {
            stringstream knightStream(knightsStat[counter]);

            for (int componentIndex = 0; componentIndex < 5; ++componentIndex)
                knightStream >> componentStat[componentIndex];

            // Using knight pointer with type BaseKnight to attach each stat to each knight instance
            // Dynamic allocation but accessing method with . ?
            // Stick phoenixDown, but not phoenixDownI to create method ? Need to consider this ambiguous point again
            knight[counter] = BaseKnight::create((counter + 1), componentStat[0], componentStat[1], componentStat[3], componentStat[4], componentStat[2]);
        }

        // Initialize knightCounter to be realSizeOfArmy

        this->knightCounter = this->realArmyKnightSize;
    };

    ArmyKnights::~ArmyKnights()
    {
        // delete each knight pointer;

        for (int counter = 0; counter < realArmyKnightSize; ++counter)
        {
            if (knight[counter] != NULL)
                delete knight[counter];
        }

        // Delete the allocated array in knight variable

        delete[] knight;
    };
    bool ArmyKnights::fight( int knightIndex, int eventIndex, Events *eventPtr)
    {
        
        //Don't need to make redundant step like opponent->getID(eventIndex), instead use eventPtr->get(eventIndex);
        int eventID = eventPtr->get(eventIndex); 
        BaseKnight *knightPtr = knight[knightIndex];

        int knightOrder = knightIndex;

        if (eventID <= 5)
        {
            if (eventID == 1)
                opponent = new MadBear();

            else if (eventID == 2)
                opponent = new Bandit();

            else if (eventID == 3)
                opponent = new LordLupin();

            else if (eventID == 4)
                opponent = new Elf();

            else if (eventID == 5)
                opponent = new Troll();

            if (knightPtr->getLevel() >= opponent->getLevel(eventIndex, eventPtr) || knightPtr->getType() == PALADIN || knightPtr->getType() == LANCELOT)
            {
                knightPtr->winMadBearToTroll(opponent);

                delete opponent;
                return true;
            }

            else
            {
                knightPtr->loseMadBearToTroll(opponent, eventIndex, eventPtr);

                delete opponent;

                //If hp > 0 after using hpBelows0Handler, return true;
                
                if ( knightPtr->getHP() > 0)
                    return true;
            }

            return false;
        }

        else if (eventID == 6)
        {
            opponent = new Tornbery();

            if (knightPtr->getLevel() >= opponent->getLevel(eventIndex, eventPtr))
            {
                knightPtr->winTornbery(opponent);

                delete opponent;
            }

            else
            {
                knightPtr->loseTornbery(opponent, eventIndex, eventPtr);

                delete opponent;

                if( knightPtr->getHP() <= 0)
                    return false;
            }

            return true;
        }

        else if (eventID == 7)
        {
            opponent = new QueenOfCards();

            if (knightPtr->getLevel() >= opponent->getLevel(eventIndex, eventPtr))
            {
                knightPtr->winQueenOfCards(opponent);

                delete opponent;
            }

            else
            {
                knightPtr->loseQueenOfCards(opponent);

                delete opponent;
            }

            return true;
        }

        else if (eventID == 8)
        {
            opponent = new NinaDeRings();

            knightPtr->meetNina();

            delete opponent;

            return true;
        }

        else if (eventID == 9)
        {
            opponent = new DurianGarden();

            knightPtr->lostInDurianGarden();

                delete opponent;
            return true;
        }

        else if (eventID == 10)
        {
            opponent = new OmegaWeapon();

            if ((knightPtr->getLevel() == 10 && knightPtr->getHP() == knightPtr->getMaxHp()) || (knightPtr->getType() == DRAGON))
            {
                knightPtr->winOmegaWeapon(opponent);
                metOmega = true;

                delete opponent; 
            }

            else
            {
                knightPtr->loseOmegaWeapon(opponent);

                delete opponent;

                if (knightPtr->getHP() <= 0)
                    return false;    
            }

            return true;
        }

        else if (eventID == 11)
        {
            opponent = new Hades();

            if (knightPtr->getLevel() == 10 || (knightPtr->getLevel() >= 8 && knightPtr->getType() == PALADIN))
            {
                knightPtr->winHades(opponent);
                metHades = true;
                hasShield = true;

                delete opponent;
            }

            else
            {
                knightPtr->loseHades(opponent);

                delete opponent;

                if(knightPtr->getHP() <= 0)
                    return false;
                
            }

            return true;
        }

        else if (eventID == 95)
        {
            hasShield = true;
            return true;
        }

        else if (eventID == 96)
        {
            hasSpear = true;
            return true;
        }

        else if (eventID == 97)
        {
            hasHair = true;
            return true;
        }

        else if (eventID == 98)
        {
            if (hasShield && hasSpear && hasHair)
            {
                hasSword = true;
            }

                return true;
        }

        else if (eventID == 99)
        {
            // Dont have to create Ultimecia instance;

            int ultimeciaHP = 5000;

            double knightBaseDamage = 0.0;

            if (hasSword)
            {
                defeatUltimecia = true;
                return true;
            }

            else if (!hasShield || !hasSpear || !hasHair)
            {
                for (int counter = this->count() - 1; counter >= 0; --counter)
                {
                    // Delete every knight

                    this->deleteKnight(counter);
                }

                // return false;
            }

            else if(hasShield && hasSpear && hasHair)
            {
                for (int counter = this->count() - 1; counter >= 0; --counter)
                {
                    // Set BaseDamage for each Knight;

                    int damage = 0;

                    if (knight[counter]->getType() != NORMAL)
                    {
                        if (knight[counter]->getType() == LANCELOT)
                            knightBaseDamage = 0.05;

                        else if (knight[counter]->getType() == PALADIN)
                            knightBaseDamage = 0.06;

                        else if (knight[counter]->getType() == DRAGON)
                            knightBaseDamage = 0.075;

                        damage = ultimeciaHP * (knight[counter]->getLevel()) * knightBaseDamage;
                        ultimeciaHP -= damage;

                        if (ultimeciaHP > 0)
                        {
                            // Delete knight, or could --knightCounter instead, and delete it later
                            this->deleteKnight(counter);
                            // this->knightCounter--;
                        }

                        else
                        {
                            defeatUltimecia = true;
                            return true;
                        }
                    }
                }

                return false;
            }

            return true;
        }



        else if (eventID == 112)
        {
            BaseItem *newPhoenixDownII = new class PhoenixDownII();

            
            if(knightPtr->getBag()->getNodeSize() < knightPtr->getBag()->getMaximumSize())
                knightPtr->getBag()->insertFirst(newPhoenixDownII);

            // newPhoenixDownII->setType(PhoenixDownII);

            else
            {
                while(knightOrder >= 0)
                {
                    if(knight[knightOrder]->getBag()->getNodeSize() < knight[knightOrder]->getBag()->getMaximumSize())
                       {
                             knight[knightOrder]->getBag()->insertFirst(newPhoenixDownII);
                             --knightOrder;
                       }
                }
            }


            //Keep the delete newPhoenixDownII will cause segmentation fault;
            // delete newPhoenixDownII;

            return true;
        }

        else if (eventID == 113)
        {
            BaseItem *newPhoenixDownIII = new class PhoenixDownIII();


            if(knightPtr->getBag()->getNodeSize() < knightPtr->getBag()->getMaximumSize())
            knightPtr->getBag()->insertFirst(newPhoenixDownIII);

            // delete newPhoenixDownIII;


            else
            {
                while(knightOrder >= 0)
                {
                    if(knight[knightOrder]->getBag()->getNodeSize() < knight[knightOrder]->getBag()->getMaximumSize())
                       {
                             knight[knightOrder]->getBag()->insertFirst(newPhoenixDownIII);
                             --knightOrder;
                       }
                }
            }

            return true;
        }

        else if (eventID == 114)
        {
            BaseItem *newPhoenixDownIV = new class PhoenixDownIV();

            if(knightPtr->getBag()->getNodeSize() < knightPtr->getBag()->getMaximumSize())
                knightPtr->getBag()->insertFirst(newPhoenixDownIV);

            // delete newPhoenixDownIV;

            else
            {
                while(knightOrder >= 0)
                {
                    if(knight[knightOrder]->getBag()->getNodeSize() < knight[knightOrder]->getBag()->getMaximumSize())
                       {
                             knight[knightOrder]->getBag()->insertFirst(newPhoenixDownIV);
                             --knightOrder;
                       }
                }
            }

            return true;
        }

        return false;
    };

    bool ArmyKnights::adventure( Events *events)
    {
        int knightIndex = this->count() - 1;


        //Outer loop for increment the event array
        
        for (int counter = 0; (counter < events->count() && this->count() - 1 >= 0); ++counter)
        {
            //Guarantee that, fighting Ultimecia is the last Event so

            if(counter == events->count()-1)
                {
                    bool finalResult = this->fight( this->count() - 1 , counter, events);

                    if(!defeatUltimecia)
                        {
                            for (int knightQueue = (this->count() - 1); knightQueue >= 0; --knightQueue)
                            {
                                this->deleteKnight(knightQueue);
                            }
                        }

                    this->printInfo();
                    return defeatUltimecia;
                }


            //Inner loop for decrement knight, since this army fights backward, note: this will be used to handle event before Ultimecia

            
            for (int knightQueue = (this->count() - 1); knightQueue >= 0; --knightQueue)
            {
                bool result = this->fight( knightQueue, counter, events);

                // If result is false and haven't defeated ultimecia yet, then !result is true;

                //Early exit in case not defeating ultimecia 

                if (!result && !defeatUltimecia)
                {
                    this->deleteKnight(knightQueue);
                }

                else if (result && !defeatUltimecia)
                {
                    // Deallocate memory

                    this->passGil();

                    // delete opponent;
                    // this->printInfo();
                }

                 //if knight is dead, change the last knight by previous knight and exit this event early to come to next event
                 break;

                // this->passGil();
            }

            // Deallocate memory

            // delete opponent;

        //after each event whether knight live or dead, we still need to call printInfo();
            this->printInfo();
        }

        return this->defeatUltimecia;
    };
    int ArmyKnights::count() const
    {
        return knightCounter;
    };
    BaseKnight * ArmyKnights::lastKnight() const
    {
        if (knight[knightCounter - 1] != NULL)
            return knight[knightCounter - 1];

        else
            return knight[knightCounter - 1];
    };

    bool ArmyKnights::hasPaladinShield() const
    {
        return hasShield;
    };
    bool ArmyKnights::hasLancelotSpear() const
    {
        return hasSpear;
    };
    bool ArmyKnights::hasGuinevereHair() const
    {
        return hasHair;
    };
    bool ArmyKnights::hasExcaliburSword() const
    {
        return hasSword;
    };


    // BaseOpponent::BaseOpponent(int id, int opponentGil, int opponentBaseDamage)
    //     : id(id), gil(opponentGil), baseDamage(opponentBaseDamage)
    // {
    // }

    int BaseOpponent::getLevel(int eventIndex, Events *eventPtr)
    {
        // Formula for opponent level levelO = (i + eventid)%10 + 1
        int levelO = (eventIndex + eventPtr->get(eventIndex)) % 10 + 1;

        // Assign level with levelO;
        level = levelO;
        return level;
    };

    int BaseOpponent::getBaseDamage(int eventIndex, Events *eventPtr)
    {
        // Adjust baseDamage base on eventID;

        // MadBear baseDamage
        if (eventPtr->get(eventIndex) == 1)
            baseDamage = 10;

        // Bandit baseDamage
        else if (eventPtr->get(eventIndex) == 2)
            baseDamage = 15;

        // LordLupin baseDamage;
        else if (eventPtr->get(eventIndex) == 3)
            baseDamage = 45;

        // Elf baseDamage;
        else if (eventPtr->get(eventIndex) == 4)
            baseDamage = 75;

        // Troll baseDamage;
        else if (eventPtr->get(eventIndex) == 5)
            baseDamage = 95;

        return baseDamage;
    };

    // Doesn't need this line, but if not do so, program will show error
    // int  BaseOpponent::getGil() = 0;

// Todo derived classes MadBear, Bandit, LordLupin, Elf, Troll, Tornbery, QueenOfCards, NinaDeRings, DurianGarden, OmegaWeapon, Hades

// int BaseOpponent::getID(int eventIndex) const
// {
//     // return id;

    
//     return eventPtr->get(eventIndex);
// };

    // Must call this function to be available to access level after modify level in base class;
    // Another function can call getLevel, and getBaseDamage by simply following this example
    //  MadBear bear1
    // bear1.getLevel(10, eventPtr ) bear1.getBaseDamage(10, eventPtr) with corresponding arguments

    // int MadBear::getGil() override
    // {
    //     // gil = 100;

    //     return gil;
    // };

    MadBear::MadBear()
    {
        this->id = 1;
        this->gil = 100;
        this->baseDamage = 10;
    };

    Bandit::Bandit()
    {
        this->id = 2;
        this->gil = 150;
        this->baseDamage = 15;
    };

    LordLupin::LordLupin()
    {
        this->id = 3;
        this->gil = 450;
        this->baseDamage = 45;
    };


    Elf::Elf()
    {
        this->id = 4;
        this->gil = 750;
        this->baseDamage = 75;
    };


    Troll::Troll()
    {
        this->id = 5;
        this->gil = 800;
        this->baseDamage = 95;
    };


    Tornbery::Tornbery()
    {
        this->id = 6;
        this->gil = 0;
        this->baseDamage = 0;
    };

    QueenOfCards::QueenOfCards()
    {
        this->id = 7;
        this->gil = 0;
        this->baseDamage = 0;
    };


    NinaDeRings::NinaDeRings()
    {
        this->id = 8;
        this->gil = 0;
        this->baseDamage = 0;
    };

// DurianGarden dont have to give back gil at any condition;
    DurianGarden::DurianGarden()
    {
        this->id = 9;
        this->gil = 0;
        this->baseDamage = 0;
    };

    OmegaWeapon::OmegaWeapon()
        // : id(10), gil(999), baseDamage(0)
    {
        this->id = 10;
        this->gil = 999;
        this->baseDamage = 0;
    };

// Hades wont give back any gil

    Hades::Hades()
        // : id(11), gil(0), baseDamage(0)
    {
        this->id = 11;
        this->gil = 0;
        this->baseDamage = 0;
    };

// Use constructor as a way to create linked list

// Create a nodes of phoenixDownI, b nodes of antidote
BaseBag::BaseBag(BaseKnight *knight, int phoenixDownI, int antidote)
{
    // Indicate maximumSize of baseBag rely on Knight's type

    
    // Dragon: 14, LanceLot: 16, Normal: 19
    if (knight->getType() == DRAGON)
    {
        maximumSize = 14;
    }

    else if (knight->getType() == LANCELOT)
    {
        maximumSize = 14;
    }

    else if (knight->getType() == NORMAL)
    {
        maximumSize = 19;
    }

    else if (knight->getType() == PALADIN)
    {
        maximumSize = 100000;
    }


    // Paladin has infinite inventory, so maxsize = infinity

    // Insert at the first both phoenix and antidote
    if (phoenixDownI > 0)
        for (int counter = 0; counter < phoenixDownI; ++counter)
        {
            BaseItem *phoenixItem = new class PhoenixDownI();
            insertFirst(phoenixItem);

            // phoenixItem->setType( PhoenixDownI ); 
        }

    if (antidote > 0 && knight->getType() != DRAGON)
        for (int counter = 0; counter < antidote; ++counter)
        {
            //IDE suggests putting class before Antidote to avoid misunderstanding with enum type Antidote

            //./knight2.h:15:3: note: class 'PhoenixDownI' is hidden by a non-type declaration of 'PhoenixDownI' here PhoenixDownI,
            BaseItem *antidoteItem = new class Antidote();
            insertFirst(antidoteItem);
        }
};
// };

bool BaseBag::insertFirst(BaseItem *item)
{
    if (nodeSize == 0)
    {
        head = new Node(item, nullptr);
        ++nodeSize;

        // this->head->nodeItem->setType( item->getType() );
        return true;
    }

    else if (nodeSize > 0 && nodeSize < maximumSize)
    {
        Node *newNode = new Node(item, head);

        newNode->next = head;
        newNode->nodeItem = item;
        head = newNode;
        ++nodeSize;

        // this->head->nodeItem->setType( item->getType() );
        return true;
    }

    else
        return false;

    // else if (nodeSize == maximumSize)
    // {

    // }

    
};

// BaseItem implementation

bool PhoenixDownI::canUse(BaseKnight *knight) 
{
    if (knight->getHP() <= 0)
        return true;

    else
        return false;
};

// Place setType into use function of each classes

 void PhoenixDownI::use(BaseKnight *knight) 
{
    // Restore knight's hp

    typeOfItem = ::PhoenixDownI;

    knight->setHP(knight->getMaxHp());

    //After done with using, delete the item


};

bool PhoenixDownII::canUse(BaseKnight *knight) 
{

    int dividedMaxHp = (knight->getMaxHp()) / 4;
    if (knight->getHP() < dividedMaxHp)
        return true;

    else
        return false;
};

 void PhoenixDownII::use(BaseKnight *knight) 
{
    // Restore knight's hp to maxHp

    typeOfItem = ::PhoenixDownII;

    knight->setHP(knight->getMaxHp());
};

bool PhoenixDownIII::canUse(BaseKnight *knight) 
{
    int dividedMaxHp = (knight->getMaxHp()) / 3;

    if (knight->getHP() < dividedMaxHp)
        return true;

    else
        return false;
};

 void PhoenixDownIII::use(BaseKnight *knight) 
{

    int dividedMaxHp = (knight->getMaxHp()) / 3;
    int increaseHp = (knight->getMaxHp()) / 4;

    typeOfItem = ::PhoenixDownIII;
    // Restore knight's hp
    if (knight->getHP() <= 0)
        knight->setHP(dividedMaxHp);

            else knight->setHP(knight->getHP() + increaseHp);
};

bool PhoenixDownIV::canUse(BaseKnight *knight) 
{
    int dividedMaxHp = (knight->getMaxHp()) / 2;

    if (knight->getHP() <= dividedMaxHp)
        return true;

    else
        return false;
};

 void PhoenixDownIV::use(BaseKnight *knight) 
{
    // Restore knight's hp

    int dividedMaxHp = (knight->getMaxHp()) / 2;
    int increaseHp = (knight->getMaxHp()) / 5;

    typeOfItem = ::PhoenixDownIV;

    if (knight->getHP() <= 0)
        knight->setHP(dividedMaxHp);

            else knight->setHP(knight->getHP() + increaseHp);
};

bool Antidote::canUse(BaseKnight *knight) 
{
    if (knight->getAntidote() >= 1)
        return true;
    else
        return false;
};

 void Antidote::use(BaseKnight *knight) 
{
    int newAntidote = knight->getAntidote() - 1;

    typeOfItem = ::Antidote;

    knight->setAntidote(newAntidote);
};

 BaseItem *BaseBag::get(ItemType itemType, BaseKnight *knight)
{
    // get method with checking availability of using (exclude delete node)

    Node *bagNode = head;

    while (bagNode != NULL)
    {
        //Need to handle case to find general type PHOENIX
        if (itemType != PHOENIX) 
        {
            if (bagNode->nodeItem->getType() == itemType && bagNode->nodeItem->canUse(knight))
            {
                // Create a temporary BaseItem pointer to store Node Item when swapping 2 nodes
                BaseItem *itemPtr = bagNode->nodeItem;


                bagNode->nodeItem = head->nodeItem;
                head->nodeItem = itemPtr;

                // Use item part; need to check again;
                // Move head to the next head

                // head = head->next;
                // --nodeSize;

                // delete head;
                // itemPtr->use(knight);

                return itemPtr;
            }
        }

        else if (itemType == PHOENIX)
        {
            if (bagNode->nodeItem->getGeneralType() == itemType && bagNode->nodeItem->canUse(knight))
            {
                //Change head with itemPtr;
                BaseItem *itemPtr = bagNode->nodeItem;
                bagNode->nodeItem = head->nodeItem;
                head->nodeItem = itemPtr;

                // head = head->next;
                // --nodeSize;

                // delete head;
                // itemPtr->use(knight);
                return itemPtr;
            }
        }

        bagNode = bagNode->next;
    }

    return nullptr;
};

 ItemType BaseItem::getType() const
{
    return this->typeOfItem;
};

ItemType BaseItem::getGeneralType() const
{
    return generalType;
};


 void BaseBag::delete3Items()
{
    int initialNodeSize = this->nodeSize;

    if(initialNodeSize >= 3)
        for (int counter = 0; counter < 3; ++counter)
        {
            Node *tempNode = head;
            delete tempNode;
            head = head->next;

            --nodeSize;
        }

    else 
    {
        for (int counter = 0; counter < initialNodeSize; ++counter)
        {
            Node *tempNode = head;
            delete tempNode;
            head = head->next;

            --nodeSize;
        }
    }
};

 string BaseBag::toString() const
{
    string outputString = "Bag[count=" + to_string(nodeSize) + ";";

    Node *newNode = head;

    string stringType[5] = {"Antidote", "PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV" };
    ItemType enumType;

    int mapIndex = 0;

    while (newNode != NULL)
    {
        enumType = newNode->nodeItem->getType();

        mapIndex = static_cast<int>(enumType);
        // if( enumType == PhoenixDownI)
        //     {
        //         stringType = "PhoenixDownI";
        //     }

        // else if ( enumType == PhoenixDownII )
        //     {
        //         stringType = "PhoenixDownII";
        //     }

        // else if ( enumType == PhoenixDownIII )
        //     {
        //         stringType = "PhoenixDownIII";
        //     }

        // else if ( enumType == PhoenixDownIV )
        //     {
        //         stringType = "PhoenixDownIV";
        //     }

        // else if ( enumType == Antidote )
        //     {
        //         stringType = "Antidote";
        //     };

        //Remove static cast, since to_string can convert enum to string itself
        outputString += stringType[mapIndex];

        if(newNode->next != NULL)
            outputString += ",";

        // Last item handle
        if (newNode->next == NULL)
        {
            // outputString += to_string(static_cast<int>(newNode->next->nodeItem->getType()));
            outputString += "]";
            break;
        }

        newNode = newNode->next;
    }
    
    //Handle case where first node is NULL

    if( newNode == NULL)
        {
            outputString += "]";
        }

    return outputString;
};

// Fight method for each type of knight

void BaseKnight::winMadBearToTroll(BaseOpponent *opponent)
{
    // Adding gill according to each opponent's id, with maximum gill for 999

    this->gil += opponent->getGil();

    // if (this->gil > 999)
    //     gil = 999;
};

void BaseKnight::loseMadBearToTroll(BaseOpponent *opponent, int eventIndex, Events *eventPtr)
{
    // HP = HP − baseDamage ∗ (levelO − level)
    // int getBaseDamage(int eventIndex, Events *eventPtr);
    // nt getLevel(int eventIndex, Events *eventPtr);

    this->hp -= ((opponent->getBaseDamage(eventIndex, eventPtr)) * (opponent->getLevel(eventIndex, eventPtr) - this->level));

                // Need to add function to handle when hp belows 0
                // This handle function includes 2 steps:
                // 1. find PhoenixDown in bag
                // 2. Gil consideration

                this->hpBelow0Handler();
};

void BaseKnight::winTornbery(BaseOpponent *opponent)
{
    this->level += 1;

    if (this->level > 10)
        this->level = 10;
};

void BaseKnight::loseTornbery(BaseOpponent *opponent, int eventIndex, Events *eventPtr)
{
    // Need to add function to handle when knight got poisoned

    if (this->knightType != DRAGON)
    {
        if (this->antidote >= 1)
        {
            BaseItem *antidotePtr = this->bag->get( Antidote, this);

            if (antidotePtr != NULL)
                {
                    antidotePtr->use(this);

                    this->getBag()->deleteAfterUsing();
                    //Don't need to add this line, since decrement antidote is already in antidotePtr->use(this)
                    // --(this->antidote);
                }

        }
        // Need to add function to handle dropping 3 last items
        else
        {
            this->bag->delete3Items();
            this->hp -= 10;

            if (this->hp <= 0)
                this->hpBelow0Handler();
        }
    }

    else
        return;
};

void BaseKnight::winQueenOfCards(BaseOpponent *opponent)
{
    this->gil *= 2;
    // Need to add superfluous gill handler
};

void BaseKnight::loseQueenOfCards(BaseOpponent *opponent)
{
    if (this->getType() != PALADIN)
        this->gil /= 2;
};

void BaseKnight::winOmegaWeapon(BaseOpponent *opponent)
{
    this->level = 10;
    this->gil = 999;
};

void BaseKnight::loseOmegaWeapon(BaseOpponent *opponent)
{
    this->hp = 0;
    this->hpBelow0Handler();
};

// Declare in armyKnight class
void BaseKnight::winHades(BaseOpponent *opponent)
{
    // any type of knight from level 10, or paladin lvl 8 could take down
    // Receive paladin Shield when winning
};

void BaseKnight::loseHades(BaseOpponent *opponent)
{
    this->hp = 0;
    this->hpBelow0Handler();
};

void BaseKnight::meetNina()
{
    if (this->gil < 50)
        return;

    else if (this->gil >= 50)
    {
        int oneThirdMax = this->maxhp / 3;
        int oneFifthMax = this->maxhp / 5;
        if (hp < oneThirdMax)
        {
            if (this->getType() != PALADIN)
                this->gil -= 50;

            this->hp += oneFifthMax;
        }
    }
};

void BaseKnight::lostInDurianGarden()
{
    this->hp = this->maxhp;
};

 void BaseKnight::hpBelow0Handler()
{
    // Step 1, find PHOENIXDOWN

    //Need to find base on general type 
    //Need to overload get function to make it find the nearest PHOENIX type

    BaseItem *itemPtr = bag->get(PHOENIX, this);



    if(itemPtr != NULL)
    {
        itemPtr->use(this);
        this->getBag()->deleteAfterUsing();
    }


    if (this->hp <= 0)
    {
        // Calling phoenix for secondLife

        if (this->gil >= 100)
        {
            this->gil -= 100;

            this->hp = maxhp / 2;
        }

        // Not include deleting knight yet
    };
};

 void BaseKnight::setGil(int gilToSet)
{
    this->gil = gilToSet;
};

void ArmyKnights::deleteKnight(int position)
{
    if (knight[position] != NULL)
    {
        delete knight[position];
        knight[position] = nullptr;

        --knightCounter;
    }

    else if (knight[position] == NULL) {
        --knightCounter;
    }

            if (knightCounter < 0 )
                knightCounter = 0;
};

void ArmyKnights::passGil()
{
    // If last Knight receive more than 999 gil, then the left over will be passed to the previous knight,...

    int counter = knightCounter - 1; // 99 -> 98

    int initialRemainderGil = this->lastKnight()->getGil() - 999;

    int remainderGil = initialRemainderGil;

    // counter - 1: lastKnight ex: counter = 99 -> 98
    // counter - 2: before lastKnight
    // counter - 3: before of before lastKnight

    while (remainderGil > 0 && counter >= 1)
    {
        // Prev knight (1)
        knight[counter - 1]->setGil(remainderGil);

        //Adjust lastKnight gil to maximum;

        knight[counter]->setGil(999);

            // Decrement counter to come to Prev knight (1)
            --counter;

        remainderGil = knight[counter]->getGil() - 999;
    }

    //Handling case where there's only 1 knight in the army, 

    if ( remainderGil > 0 && counter == 0)
    {
        this->lastKnight()->setGil(999);
    }
};  
