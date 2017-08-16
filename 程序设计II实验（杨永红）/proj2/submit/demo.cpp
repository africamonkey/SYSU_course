#include <bits/stdc++.h>
#include "student.h"
#include "teacher.h"
#include "course.h"
#include "prompt.h"

using namespace std;

void menu_admin() {
    while (1) {
        int op = prompt_read_int("1: add a teacher\n2: add a student\n3: quit\n\nPlease choose an operation: ");
        if (op == 1) {
            teacher_list::add();
            teacher_list::write();
        } else
        if (op == 2) {
            student_list::add();
            student_list::write();
        } else {
            break;
        }
    }
}

void menu_teacher() {
    int tea_id = prompt_read_int("Please input your teacher ID: ");
    while (1) {
        int op = prompt_read_int("1: add a course\n2: view a course\n3: quit\n\nPlease choose an operation: ");
        if (op == 1) {
            std::string name = prompt_read_name("Please input a course name: ");
            course_list::add(name, tea_id);
            course_list::write();
        } else
        if (op == 2) {
            prompt_message(course_list::get_all_course(tea_id).c_str());
            int x = prompt_read_int("Please input a course_id: ");
            prompt_message(course_list::get_course_info(x).c_str());
        } else {
            break;
        }
    }
}

void menu_student() {
    int stu_id = prompt_read_int("Please input your student ID: ");
    while (1) {
        int op = prompt_read_int("1: select a course\n2: unselect a course\n3: view status\n4: quit\n\nPlease choose an operation: ");
        if (op == 1) {
            prompt_message(course_list::get_all_course(-1, stu_id).c_str());
            int x = prompt_read_int("Please input a course_id: ");
            course_list::select(x, stu_id);
            course_list::write();
        } else
        if (op == 2) {
            prompt_message(course_list::get_all_course(-1, stu_id).c_str());
            int x = prompt_read_int("Please input a course_id: ");
            course_list::unselect(x, stu_id);
            course_list::write();
        } else
        if (op == 3) {
            prompt_message(course_list::get_all_course(-1, stu_id).c_str());
        } else {
            break;
        }
    }
}

void menu() {
    while (1) {
        int op = prompt_read_int("Class Election System (demo)\n\n1: administrator\n2: teacher\n3: student\n4: quit\n\nPlease choose your role: ");
        if (op == 1) {
            menu_admin();
        } else
        if (op == 2) {
            menu_teacher();
        } else
        if (op == 3) {
            menu_student();
        } else {
            break;
        }
    }
}

int main() {
    student_list::init();
    teacher_list::init();
    course_list::init();
    menu();
}
