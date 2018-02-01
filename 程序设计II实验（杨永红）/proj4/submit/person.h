#ifndef _PERSON
#define _PERSON

#include <bits/stdc++.h>

using namespace std;

#define BUFFER_SIZE 1024
#define map_i map <int, string> :: iterator

class person_list {
public:
    void read(string filename) {
        person.clear();
        FILE *fin = fopen(filename.c_str(), "r");
        if (fin) {
            int id;
            static char name[BUFFER_SIZE];
            while (~fscanf(fin, "%d%s", &id, name))
                person[id] = name;
            fclose(fin);
        }
    }
    bool add(int id, string name) {
        if (person.find(id) != person.end()) return 0;
        person[id] = name;
    }
    string id2name(int id) {
        if (person.find(id) == person.end()) return string("");
        return person[id];
    }
    void write(string filename) {
        FILE *fout = fopen(filename.c_str(), "w");
        for (map_i it = person.begin(); it != person.end(); ++it)
            fprintf(fout, "%d %s\n", it->first, it->second.c_str());
        fflush(fout);
        fclose(fout);
    }
private:
    map <int, string> person;
};

#undef map_i

#endif
