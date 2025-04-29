//Michal Ondercin
//Final Project
//4/22/25

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct City
{
    string code;
    string name;
    double pop;
    int use;
};

void print(City c)
{
    cout <<  c.name << ", " << c.code << " - " << c.pop << endl;
}

class Cache
{
public:
    City cache[10];
    int next = 0;

    Cache(): cache{} {};

    //add to cache
    void add(City c, int m)
    {
        switch (m)
        {
            case 1:
                //least frequently used
                if (next < 10)
                {
                    cache[next] = c;
                    next++;
                }
                else
                {
                    int lowest = cache[0].use, target = 0;
                    for (int i = 0; i < 10; i++)
                    {
                        if (cache[i].use < lowest)
                        {
                            lowest = cache[i].use;
                            target = i;
                        }
                    }
                    cache[target] = c;
                }
                break;
            case 2:
                //first in, first out
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
                break;
            case 3:
                //Random replacement
                if (next < 10)
                {
                    cache[next] = c;
                    next++;
                    //cout << "add to cache" << endl;
                }
                else
                {
                    srand(time(0));
                    cache[rand()%10] = c;
                    //cout << "Replaced" << endl;
                }
                break;
        }
    }

    //search cache
    bool search(string c, string n)
    {
        for(int i = 0; i < 10; i++)
        {
            if(cache[i].code == c && cache[i].name == n)
            {
                print(cache[i]);
                cache[i].use++;
                return true;
            }
        }
        return false;
    }
};

int main()
{
    //variables
    Cache cache;
    string name = "", code = "", line = "", word = "";
    int cType = 0;

    //choose cache type
    cout << "Please select a cache style\n" <<
            "(1): Least frequently used\n" <<
            "(2): First in, first out\n" <<
            "(3): Random replacement\n" << endl;
    cout << "Enter the number of your choice: ";
    cin >> cType;
    cin.ignore();

    //run loop
    while (true)
    {
        //get input
        cout << "Enter the name of the city (\"exit\" to exit): ";
        getline(cin, name);
        if (name == "exit")
            break;
        cout << "Enter the country code: ";
        cin >> code;
        cin.ignore();

        //search function
        bool found = false;
        if (!cache.search(code, name))
        {
            //open/reopen file each time
            ifstream file("world_cities.csv");
            if (!file.is_open())
            {
                std::cerr << "Error opening file" << std::endl;
                return 1;
            }

            //search through file
            while (getline(file, line) && found == false)
            {
                stringstream ss(line);
                vector<string> row;
                while (getline(ss, word, ','))
                {
                    row.push_back(word);
                }

                //if found, add to cache and print
                if (row[0] == code && row[1] == name)
                {
                    City city;
                    city.code = row[0];
                    city.name = row[1];
                    city.pop = stod(row[2]);
                    city.use = 0;
                    cache.add(city, cType);
                    print(city);
                    found = true;
                }
            }
        }
        else
        {
            cout << "(Found in cache)" << endl;
            found = true;
        }
        if (found == false)
            cout << "City not found" << endl;
    }
    return 0;
}