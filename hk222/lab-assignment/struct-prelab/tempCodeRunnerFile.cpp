void addAddendum(SCP &obj, string addendum)
{
    string* tmp = new string[obj.numAddendums + 1];
    for (int i = 0; i < obj.numAddendums; ++i) tmp[i] = obj.addendums[i];
    tmp[obj.numAddendums + 1] = addendum;

    obj.addendums = tmp;
    obj.numAddendums += 1;
}