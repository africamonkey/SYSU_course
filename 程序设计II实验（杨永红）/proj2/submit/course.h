#ifndef _COURSE
#define _COURSE

#include <bits/stdc++.h>
#include "student.h"
#include "teacher.h"
#include "prompt.h"

struct course {
    int course_id;
    std::string name;
    int tea_id;
    std::vector<int> stu_id;
};

struct course_list {
public:
    static void init() {
        c.clear();
        FILE *fin = fopen("course.dat", "r");
        if (fin) {
            int id;
            static char name[1000];
            int tea_id;
            int sz;
            course _c;
            while (~fscanf(fin, "%d%s%d%d", &id, name, &tea_id, &sz)) {
                _c.course_id = id;
                _c.name = name;
                _c.tea_id = tea_id;
                _c.stu_id.clear();
                for (int i = 0; i < sz; ++i) {
                    int x;
                    fscanf(fin, "%d", &x);
                    _c.stu_id.push_back(x);
                }
                c.push_back(_c);
            }
            fclose(fin);
        }
    }
    static int add(std::string name, int tea_id) {
        course _c;
        _c.course_id = c.size();
        _c.name = name;
        _c.tea_id = tea_id;
        _c.stu_id.clear();
        c.push_back(_c);
        prompt_message("success\n");
        return _c.course_id;
    }
    static int is_select(int course_fake_id, int stu_id) {
        for (int i = 0; i < (int)c[course_fake_id].stu_id.size(); ++i)
            if (c[course_fake_id].stu_id[i] == stu_id)
                return 1;
        return 0;
    }
    static void select(int course_id, int stu_id) {
        for (int i = 0; i < (int)c.size(); ++i)
            if (c[i].course_id == course_id) {
                if (!is_select(i, stu_id)) {
                    c[i].stu_id.push_back(stu_id);
                    prompt_message("success\n");
                    return;
                }
            }
        prompt_message("error: you have already selected\n");
    }
    static void unselect(int course_id, int stu_id) {
        for (int i = 0; i < (int)c.size(); ++i)
            if (c[i].course_id == course_id) {
                if (is_select(i, stu_id)) {
                    for (int j = 0; j < (int)c.size(); ++j)
                        if (c[i].stu_id[j] == stu_id)
                            c[i].stu_id.erase(c[i].stu_id.begin() + j);
                    prompt_message("success\n");
                    return;
                }
            }
        prompt_message("error: you have already unselected\n");
    }
    static void write() {
        FILE *fout = fopen("course.dat", "w");
        for (int i = 0; i < (int)c.size(); ++i) {
            fprintf(fout, "%d %s %d %d", c[i].course_id, c[i].name.c_str(), c[i].tea_id, (int)c[i].stu_id.size());
            for (int j = 0; j < (int)c[i].stu_id.size(); ++j)
                fprintf(fout, " %d", c[i].stu_id[j]);
            fprintf(fout, "\n");
        }
        fflush(fout);
        fclose(fout);
    }
    static std::string get_all_course(int tea_id = -1, int stu_id = -1) {
        if (c.size() == 0) return std::string("No course exists.\n");
        if (tea_id != -1) {
            int cnt = 0;
            for (int i = 0; i < (int)c.size(); ++i)
                if (c[i].tea_id == tea_id)
                    ++cnt;
            if (cnt == 0) return std::string("No course exists.\n");
        }
        std::string ret = "";
        char st[10000];
        sprintf(st, "%-12s %-20s %-20s %s\n", "Course ID", "Course Name", "Teacher Name", stu_id == -1 ? "" : "status");
        ret += std::string(st);
        for (int i = 0; i < (int)c.size(); ++i)
            if (c[i].tea_id == tea_id || tea_id == -1) {
                sprintf(st, "%-12d %-20s %-20s %s\n", c[i].course_id, c[i].name.c_str(), teacher_list::id2name(c[i].tea_id).c_str(), stu_id == -1 ? "" : (is_select(i, stu_id) ? "selected" : "  -  "));
                ret += std::string(st);
            }
        return ret;
    }
    static std::string get_course_info(int course_id) {
        int id = -1;
        for (int i = 0; i < (int)c.size(); ++i) {
            if (c[i].course_id == course_id) id = course_id;
        }
        if (id == -1) {
            return std::string("course not exists\n");
        }
        char st[10000];
        sprintf(st, "course ID: %d\ncourse name: %s\nStudents:\n%-12s %s\n", c[id].course_id, c[id].name.c_str(), "student ID", "student Name");
        std::string ret = "";
        ret += std::string(st);
        for (int i = 0; i < (int)c[id].stu_id.size(); ++i) {
            sprintf(st, "%-12d %s\n", c[id].stu_id[i], student_list::id2name(c[id].stu_id[i]).c_str());
            ret += std::string(st);
        }
        return ret;
    }
private:
    static std::vector<course> c;
};

std::vector <course> course_list::c;

#endif
