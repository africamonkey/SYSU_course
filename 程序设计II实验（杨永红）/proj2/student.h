#ifndef _STUDENT
#define _STUDENT

#include <bits/stdc++.h>
#include "prompt.h"

struct student {
    int stu_id;
    std::string name;
    student(int stu_id = 0, std::string name="") : stu_id(stu_id), name(name) {}
};

class student_list {
public:
    static void init() {
        stu.clear();
        FILE *fin = fopen("student.dat", "r");
        if (fin) {
            int id;
            static char name[1000];
            while (~fscanf(fin, "%d%s", &id, name))
                stu.push_back(student(id, std::string(name)));
            fclose(fin);
        }
    }
    static void add() {
        int id = prompt_read_int("Please input student ID: ");
        std::string name = prompt_read_name("Please input student name: ");
        for (int i = 0; i < (int)stu.size(); ++i)
            if (stu[i].stu_id == id) {
                prompt_message("error: student ID exists.\n");
                return;
            }
        stu.push_back(student(id, name));
        prompt_message("success\n");
    }
    static std::string id2name(int id) {
        for (int i = 0; i < (int)stu.size(); ++i)
            if (stu[i].stu_id == id) {
                return stu[i].name;
            }
        return "";
    }
    static void write() {
        FILE *fout = fopen("student.dat", "w");
        for (int i = 0; i < (int)stu.size(); ++i)
            fprintf(fout, "%d %s\n", stu[i].stu_id, stu[i].name.c_str());
        fflush(fout);
        fclose(fout);
    }
private:
    static std::vector <student> stu;
};

std::vector <student> student_list::stu;

#endif
