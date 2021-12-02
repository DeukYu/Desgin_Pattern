/*
    Single Responsibility Principle Practice Program
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Journal
{
public:
    string title;
    vector<string>  entries;

    explicit Journal(const string& title) :
        title{ title }
    {
    }
    void Add(const string& entry);
    void Save(const string& filename); // Save : 단일 책임 원칙에 벗어난다.
};

void Journal::Add(const string& entry)
{
    static int count = 1;
    entries.emplace_back(to_string(count++) + ": " + entry);
}

void Journal::Save(const string& filename)
{
    ofstream ofs(filename);
    for (auto& s : entries)
        ofs << s << endl;
}

class PersistenceManager
{
public:
    static void Save(const Journal& j, const string& filename)
    {
        ofstream ofs(filename);
        for (auto& s : j.entries)
            ofs << s << endl;
    }
};

void main()
{
    Journal journal{ "Dear Diary" };
    journal.Add("I ate a bug");
    journal.Add("I cried today");

    //journal.save("diary.txt");

    PersistenceManager pm;
    pm.Save(journal, "diary.txt");
}