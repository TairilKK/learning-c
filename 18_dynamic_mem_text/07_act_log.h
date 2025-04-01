//
// Created by jdobr on 28.08.2023.
//

#ifndef INC_15_ACT_LOG_H
#define INC_15_ACT_LOG_H

struct user_t
{
    char *login;
    char *password;
    unsigned char logon;
};

struct users_t
{
    int size;
    int capacity;
    struct user_t **users;
};

struct user_t *create_user(const char *login, const char *password, int *err_code);
struct users_t *create_users(int N, int *err_code);

int add_user(struct users_t *users, struct user_t *user);

struct user_t* find_user(const struct users_t *users, char *login, int *err_code);

void free_user(struct user_t *user);
void free_users(struct users_t *users);

#define ERROR(error_code) do{ if(err_code) *err_code = error_code; }while(0)

#endif //INC_15_ACT_LOG_H