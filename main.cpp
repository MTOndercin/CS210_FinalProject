//Michal Ondercin
//Final Project
//4/22/25

#include <iostream>

using namespace std;

class City
{
public:
    string code;
    string name;
    double pop;

    City(string c, string n, double p)
    {
        code = c;
        name = n;
        pop = p;
    }
    void print()
    {
        cout << name << ", " << code << " - " << pop << endl;
    }
};

class Cache
{
public:
    City cache[10];
    int next;

    Cache(): cache{}
    {
        next = 0;
    }

    //add to cache
    void add(City c)
    {
        if(next == 10)
        {
            next = 1;
            cache[0] = c;
        }
        else
        {
            cache[next] = c;
            next++;
        }
    }

    //search cache
    bool search(string c, string n)
    {
        for(int i = 0; i < 10; i++)
        {
            if(cache[i].code == c)
            {
                if(n == cache[i].name)
                {
                    cache[i].print();
                    return true;
                }
            }
        }
        return false;
    }
};

int main()
{
    //variables
    Cache cache();



    return 0;
}