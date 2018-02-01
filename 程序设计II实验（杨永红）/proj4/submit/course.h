#ifndef _COURSE
#define _COURSE

#include <bits/stdc++.h>

using namespace std;

#define BUFFER_SIZE 1024
#define pis pair <int, string>
#define set_int_i set <int> :: iterator
#define set_pis_i set <pis> :: iterator
#define map_i map < int, course_b > :: iterator

struct course_b {
    int course_id;
    string name;
    int tea_id;
    string tea_name;
    set < int > stu_id;
    set < pis > stu;
};

class course_list {
public:
    void read(string filename) {
        c.clear();
        FILE *fin = fopen(filename.c_str(), "r");
        if (fin) {
            int id;
            static char name[BUFFER_SIZE];
            static char tea_name[BUFFER_SIZE];
            int tea_id;
            int sz;
            course_b _c;
            while (~fscanf(fin, "%d%s%d%s%d", &id, name, &tea_id, tea_name, &sz)) {
                _c.course_id = id;
                _c.name = name;
                _c.tea_id = tea_id;
                _c.tea_name = tea_name;
                _c.stu.clear();
                _c.stu_id.clear();
                for (int i = 0; i < sz; ++i) {
                    int stu_id;
                    static char stu_name[BUFFER_SIZE];
                    fscanf(fin, "%d", &stu_id);
                    fscanf(fin, "%s", stu_name);
                    _c.stu.insert(make_pair(stu_id, stu_name));
                    _c.stu_id.insert(stu_id);
                }
                c[id] = _c;
            }
            fclose(fin);
        }
    }
    int add(string name, int tea_id, string tea_name) {
        course_b _c;
        int num = 1;
        while (c.find(num) != c.end()) ++num;
        _c.course_id = num;
        _c.name = name;
        _c.tea_id = tea_id;
        _c.tea_name = tea_name;
        _c.stu.clear();
        c[num] = _c;
        return _c.course_id;
    }
    int del(int course_id) {
        map_i it = c.find(course_id);
        if (it == c.end()) return 0;
        c.erase(it);
        return 1;
    }
    bool is_select(int course_id, int stu_id) {
        return c[course_id].stu_id.find(stu_id) != c[course_id].stu_id.end();
    }
    bool select(int course_id, int stu_id, string stu_name) {
        if (is_select(course_id, stu_id)) return 0;
        c[course_id].stu_id.insert(stu_id);
        c[course_id].stu.insert(make_pair(stu_id, stu_name));
        return 1;
    }
    bool unselect(int course_id, int stu_id, string stu_name) {
        if (!is_select(course_id, stu_id)) return 0;
        c[course_id].stu_id.erase(stu_id);
        c[course_id].stu.erase(make_pair(stu_id, stu_name));
        return 1;
    }
    void write(string filename) {
        FILE *fout = fopen(filename.c_str(), "w");
        for (map_i it = c.begin(); it != c.end(); ++it) {
            fprintf(fout, "%d %s %d %s %d", it->second.course_id, it->second.name.c_str(), it->second.tea_id, it->second.tea_name.c_str(), (int)it->second.stu_id.size());
            for (set_pis_i s_it = it->second.stu.begin(); s_it != it->second.stu.end(); ++s_it)
                fprintf(fout, " %d %s", s_it->first, s_it->second.c_str());
            fprintf(fout, "\n");
        }
        fflush(fout);
        fclose(fout);
    }
    string get_all_course(int tea_id = -1, int stu_id = -1) {
        if (c.size() == 0) return string("No course exists.\n");
        if (tea_id != -1) {
            int cnt = 0;
            for (map_i it = c.begin(); it != c.end(); ++it)
                if (it->second.tea_id == tea_id)
                    ++cnt;
            if (cnt == 0) return string("No course exists.\n");
        }
        string ret = "";
        char st[10000];
        sprintf(st, "%-12s %-20s %-20s %s\n", "Course ID", "Course Name", "Teacher Name", stu_id == -1 ? "" : "status");
        ret += string(st);
        for (map_i it = c.begin(); it != c.end(); ++it)
            if (it->second.tea_id == tea_id || tea_id == -1) {
                sprintf(st, "%-12d %-20s %-20s %s\n", it->second.course_id, it->second.name.c_str(), it->second.tea_name.c_str(), stu_id == -1 ? "" : (is_select(it->second.course_id, stu_id) ? "selected" : "  -  "));
                ret += string(st);
            }
        return ret;
    }
    string get_course_info(int course_id) {
        if (c.find(course_id) == c.end()) return string("course not exists\n");
        static char st[10000];
        sprintf(st, "course ID: %d\ncourse name: %s\nStudents:\n%-12s %s\n", c[course_id].course_id, c[course_id].name.c_str(), "student ID", "student Name");
        string ret = "";
        ret += string(st);
        for (set_pis_i s_it = c[course_id].stu.begin(); s_it != c[course_id].stu.end(); ++s_it) {
            sprintf(st, "%-12d %s\n", s_it->first, s_it->second.c_str());
            ret += string(st);
        }
        return ret;
    }
private:
    map< int, course_b > c;
};

#undef map_i

#endif
