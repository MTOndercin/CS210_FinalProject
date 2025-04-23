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
            if(cache[i].code == c && cache[i].name == n)
            {
                print(cache[i]);
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
                    cache.add(city);
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