#include <iostream>
#include <sstream>
#include <string>

using namespace std;

float add(float a, float b) {return a + b;}
float sub(float a, float b) {return a - b;}
float mul(float a, float b) {return a * b;}

typedef float(*myOp)(float, float);

int main(int narg, char** argv)
{
    float a, b;
    char ch;

    //float(*op)(float, float); 
    //op is a function pointer that points to a function receiving two arguments of float number to return a float result
    
    myOp opList[] = {add, sub, mul};
    char opIdx[256];
    opIdx['+'] = 0;
    opIdx['-'] = 1;
    opIdx['*'] = 2;


    stringstream ss(argv[1]);
    ss >> a >> ch >> b;

    cout << opList[opIdx[ch]](a, b);
}