#include <iostream>
#include <string>

using namespace std;

struct SCP {
    int id;
    int objClass;
    string speConProcedures;
    string description;
    string* addendums;
    int numAddendums;
};

int compareObjectClass(const SCP &objA, const SCP &objB)
{
    return (objA.objClass > objB.objClass);
}

SCP** sortDatabase(SCP** arr, int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (arr[i]->id > arr[j]->id) swap(arr[i], arr[j]);
        }
    }
}

int main()
{

}