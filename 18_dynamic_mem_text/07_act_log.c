//
// Created by jdobr on 28.08.2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "act_log.h"

struct user_t *create_user(const char *login, const char *password, int *err_code){
    if(!login || !password){
        ERROR(1);
        return NULL;
    }

    struct user_t * u = calloc(1, sizeof(struct user_t));
    if(!u){
        ERROR(2);
        return NULL;
    }
    u->login = calloc(strlen(login) + 1, sizeof(char));
    if(!(u->login)){
        free(u);
        ERROR(2);
        return NULL;
    }
    strcpy(u->login, login);

    u->password = calloc(strlen(password) + 1, sizeof(char));
    if(!(u->password)){
        free(u->login);
        free(u);
        ERROR(2);
        return NULL;
    }
    strcpy(u->password, password);
    u->logon = 0;
    ERROR(0);
    return u;
}

void free_user(struct user_t *user){
    if(!user || !user->login || !user->password) return;
    free(user->login);
    free(user->password);
    free(user);
}

struct users_t *create_users(int N, int *err_code){
    if(N < 1){
        ERROR(1);
        return NULL;
    }

    struct users_t * u = calloc(1, sizeof(struct users_t));
    if(!u){
        ERROR(2);
        return NULL;
    }
    u->size = 0;
    u->capacity = N;
    u->users = calloc(N, sizeof(struct user_t *));
    if(!(u->users)){
        free(u);
        ERROR(2);
        return NULL;
    }
    ERROR(0);
    return u;
}

void free_users(struct users_t *users){
    if(!users || !users->users || users->capacity < 1 || users->size < 0 || users->size > users->capacity) return;

    if(users->users){
        for(int i = 0; i < users->size; ++i)
            free_user(*(users->users + i));
        free(users->users);
    }
    free(users);
}

struct user_t* find_user(const struct users_t *users, char *login, int *err_code){
    if(!users || !login || !(users->users) || users->size < 0 || users->capacity < 1){ ERROR(1); return NULL;}
    for(int i = 0; i < users->size; ++i)
        if(strcmp((*(users->users + i))->login, login) == 0) { ERROR(0); return *(users->users + i); }

    ERROR(2);
    return NULL;
}


int add_user(struct users_t *users, struct user_t *user){
    if(!users || !user || !users->users || users->size < 0 || users->capacity < 1 || !(user->login) || !(user->password)) return 1;

    int error = 0;
    find_user(users, user->login, &error);

    if(error == 0)
        return 2;

    if(users->size == users->capacity){
        struct user_t ** temp = (struct user_t **)realloc(users->users, users->capacity * 2 * sizeof(struct user_t *));
        if(!temp) return 3;
        users->users = temp;
        users->capacity *= 2;
    }

    (*(users->users + users->size)) = user;
    users->size++;
    return 0;
}

