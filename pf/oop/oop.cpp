#include "oop.h"

int main()
{
    Animal* pA[] = {new Insect(1000), 
                    new Ant(8, 1000), 
                    new Human("John", 0), 
                    new Antman("Scott", 30, 999)};

    for (int i = 0; i < 4; ++i)
    {
        pA[i]->eat();
        pA[i]->play();
    }

    for (int i = 0; i < 4; ++i)
    {
        //delete pA[i]; 
        // what will happen? -> error because using the pointer of object to destroy it, not the data itself
    
        delete pA[i];
    }

    // early & late binding?
}