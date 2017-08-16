#include <bits/stdc++.h>
#include "course.h"
#include "person.h"

#define COURSE_FILE "course.dat"
#define TEACHER_FILE "teacher.dat"
#define STUDENT_FILE "student.dat"

person_list teacher, student;
course_list course;

int main_menu() {
    puts("Class Election System");
    puts("");
    puts("1: login as an administrator");
    puts("2: login as a teacher");
    puts("3: login as a student");
    puts("0: quit");
    puts("");
    printf("Please enter your choice: ");
    int x; cin >> x;
    return x;
}

int admin_menu() {
    puts("Administrator menu");
    puts("");
    puts("1: add a teacher");
    puts("2: add a student");
    puts("0: quit");
    puts("");
    printf("Please enter your choice: ");
    int x; cin >> x;
    return x;
}

int teacher_menu() {
    puts("Teacher menu");
    puts("");
    puts("1: add a course");
    puts("2: delete a course");
    puts("3: view a course");
    puts("0: quit");
    puts("");
    printf("Please enter your choice: ");
    int x; cin >> x;
    return x;
}

int student_menu() {
    puts("Student menu");
    puts("");
    puts("1: select a course");
    puts("2: unselect a course");
    puts("3: view status");
    puts("0: quit");
    puts("");
    printf("Please enter your choice: ");
    int x; cin >> x;
    return x;
}

int main() {
    course.read(COURSE_FILE);
    teacher.read(TEACHER_FILE);
    student.read(STUDENT_FILE);
    while (1) {
        int op = main_menu();
        switch (op) {
            case 1: {
                int flag = 1;
                while (flag) {
                    int opt = admin_menu();
                    switch (opt) {
                        case 1: {
                            int id;
                            string name;
                            printf("please enter teacher ID: "); cin >> id;
                            printf("please enter teacher name: "); cin >> name;
                            teacher.add(id, name);
                            teacher.write(TEACHER_FILE);
                            break;
                        }
                        case 2: {
                            int id;
                            string name;
                            printf("please enter student ID: "); cin >> id;
                            printf("please enter student name: "); cin >> name;
                            student.add(id, name);
                            student.write(STUDENT_FILE);
                            break;
                        }
                        case 0: {
                            flag = 0;
                            break;
                        }
                    }
                }
                break;
            }
            case 2: {
                int flag = 1;
                int tea_id = 0;

                printf("Please enter your teacher ID: ");
                cin >> tea_id;
                if (teacher.id2name(tea_id) == "") {
                    puts("No such ID. quit.");
                    break;
                }

                string tea_name = teacher.id2name(tea_id);
                while (flag) {
                    int opt = teacher_menu();
                    switch (opt) {
                        case 1: {
                            printf("Please enter course name: ");
                            string name;
                            cin >> name;
                            int ret = course.add(name, tea_id, tea_name);
                            cout << "ok! Your course ID is: " << ret << endl;
                            course.write(COURSE_FILE);
                            break;
                        }
                        case 2: {
                            cout << course.get_all_course(tea_id) << endl;
                            printf("Please enter course ID: ");
                            int id;
                            cin >> id;
                            int ret = course.del(id);
                            if (ret == 0) {
                                puts("Invalid course ID. quit. ");
                                break;
                            }
                            course.write(COURSE_FILE);
                            break;
                        }
                        case 3: {
                            cout << course.get_all_course(tea_id) << endl;
                            printf("Please enter course ID: ");
                            int id;
                            cin >> id;
                            cout << course.get_course_info(id) << endl;
                            break;
                        }
                        case 0: {
                            flag = 0;
                            break;
                        }
                    }
                }
                break;
            }
            case 3: {
                int flag = 1;
                int stu_id = 0;

                printf("Please enter your student ID: ");
                cin >> stu_id;
                if (student.id2name(stu_id) == "") {
                    puts("No such ID. quit.");
                    break;
                }

                string stu_name = student.id2name(stu_id);
                while (flag) {
                    int opt = student_menu();
                    switch (opt) {
                        case 1: {
                            cout << course.get_all_course(-1, stu_id) << endl;
                            printf("Please enter course ID (select): ");
                            int id;
                            cin >> id;
                            int ret = course.select(id, stu_id, stu_name);
                            if (ret == 0) {
                                puts("you have selected this course before.");
                                break;
                            }
                            puts("ok");
                            course.write(COURSE_FILE);
                            break;
                        }
                        case 2: {
                            cout << course.get_all_course(-1, stu_id) << endl;
                            printf("Please enter course ID (unselect): ");
                            int id;
                            cin >> id;
                            int ret = course.unselect(id, stu_id, stu_name);
                            if (ret == 0) {
                                puts("you haven't selected this course yet.");
                                break;
                            }
                            puts("ok");
                            course.write(COURSE_FILE);
                            break;
                        }
                        case 3: {
                            cout << course.get_all_course(-1, stu_id) << endl;
                            break;
                        }
                        case 0: {
                            flag = 0;
                            break;
                        }
                    }
                }
                break;
            }
            case 0: {
                return 0;
            }
        }
    }
    return 0;
}
