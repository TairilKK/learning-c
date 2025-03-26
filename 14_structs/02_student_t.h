//
// Created by jdobr on 18.08.2023.
//

#ifndef INC_02_STUDENT_T_H
#define INC_02_STUDENT_T_H

#define ERROR(error_code) do{ if(err_code != NULL) *err_code = error_code; }while(0)

struct student_t {
    char name[20];
    char surname[40];
    int index;
};

struct student_t* read(struct student_t* p, int *err_code);
void show(const struct student_t* p);

#endif //INC_02_STUDENT_T_H
