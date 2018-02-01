#ifndef _TEACHER
#define _TEACHER

#include <bits/stdc++.h>
#include "prompt.h"

struct teacher {
    int tea_id;
    std::string name;
    teacher(int tea_id = 0, std::string name="") : tea_id(tea_id), name(name) {}
};

class teacher_list {
public:
    static void init() {
        tea.clear();
        FILE *fin = fopen("teacher.dat", "r");
        if (fin) {
            int id;
            static char name[1000];
            while (~fscanf(fin, "%d%s", &id, name))
                tea.push_back(teacher(id, std::string(name)));
            fclose(fin);
        }
    }
    static void add() {
        int id = prompt_read_int("Please input teacher ID: ");
        std::string name = prompt_read_name("Please input teacher name: ");
        for (int i = 0; i < (int)tea.size(); ++i)
            if (tea[i].tea_id == id) {
                prompt_message("error: teacher ID exists.\n");
                return;
            }
        tea.push_back(teacher(id, name));
        prompt_message("success\n");
    }
    static std::string id2name(int id) {
        for (int i = 0; i < (int)tea.size(); ++i)
            if (tea[i].tea_id == id) {
                return tea[i].name;
            }
        return "";
    }
    static void write() {
        FILE *fout = fopen("teacher.dat", "w");
        for (int i = 0; i < (int)tea.size(); ++i)
            fprintf(fout, "%d %s\n", tea[i].tea_id, tea[i].name.c_str());
        fflush(fout);
        fclose(fout);
    }
private:
    static std::vector <teacher> tea;
};

std::vector <teacher> teacher_list::tea;

#endif
