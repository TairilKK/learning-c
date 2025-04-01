#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "07_act_log.h"

#define CAPACITY 10
#define FILENAME_CAPACITY 40

int main() {

    /* Tworzenie struktury */
    int err = 0;
    struct users_t * users = create_users(CAPACITY, &err);
    if(err == 2){
        printf("Failed to allocate memory");
        return 8;
    }

    /* Otwieranie pliku logs.txt*/
    FILE *logFile = fopen("logs.txt", "w");
    if(!logFile){
        printf("Couldn't create file");
        free_users(users);
        return 5;
    }

    /* Alokacja pamięci na filename */
    char * filename = calloc(FILENAME_CAPACITY, sizeof(char));
    if(!filename){
        printf("Failed to allocate memory");
        free_users(users);
        fclose(logFile);
        return 8;
    }

    /* Pobieranie nazwy pliku */
    int it = 0;
    char c = 0;
    printf("Podaj nazwe pliku: ");
    while((c = getchar()) != '\n' && it < FILENAME_CAPACITY) {
        *(filename + it) = c;
        it++;
    }
    if(c!='\n')
        while(getchar() != '\n');

    /* Otwieranie pliku wejściowego */
    FILE *f = fopen(filename, "rb");
    if(!f){
        printf("Couldn't open file");
        free_users(users);
        free(filename);
        fclose(logFile);
        return 4;
    }

    /* Odczytywanie z pliku wejściowego */
    int size = 0;
    char * message = NULL;
    char * operation = NULL;
    char * login = NULL;
    char * pass = NULL;
    struct user_t * user = NULL;

    while(fread(&size, sizeof(int), 1, f) == 1){
        if(size < 0){
            printf("Failed to allocate memory");
            free(filename);
            free_users(users);
            fclose(logFile);
            fclose(f);
            return 8;
        }
        message = calloc(size + 1, sizeof(char));
        if(!message){
            printf("Failed to allocate memory");
            free(filename);
            free_users(users);
            fclose(logFile);
            fclose(f);
            return 8;
        }
        fread(message, sizeof(char), size, f);

        /* OPERACJA */
        operation = strtok(message, " ");

        /* LOGIN */
        login = strtok(NULL, " ");

        /* PASSWORD */
        pass = strtok(NULL, " ");

        if(strcmp(operation, "register") == 0){
            user = create_user(login, pass, &err);
            if(err == 2){
                printf("Failed to allocate memory");
                free(filename);
                free(message);
                free_users(users);
                fclose(logFile);
                fclose(f);
                return 8;
            }
            err = add_user(users, user);
            if(err == 0)
                fprintf(logFile, "success: new user added\n");
            else {
                fprintf(logFile, "fail: user already exists\n");
                free_user(user);
            }
        }
        else if(strcmp(operation, "login") == 0){
            user = find_user(users, login, NULL);
            if(!user)
                fprintf(logFile, "fail: no such user\n");
            else if(strcmp(user->password, pass) != 0)
                fprintf(logFile, "fail: incorrect password\n");
            else if(user->logon == 1)
                fprintf(logFile, "fail: already logged in\n");
            else{
                fprintf(logFile, "success: user logged in\n");
                user->logon = 1;
            }
        }
        else if(strcmp(operation, "logout") == 0){
            user = find_user(users, login, NULL);
            if(!user)
                fprintf(logFile, "fail: no such user\n");
            else if(user->logon == 0)
                fprintf(logFile, "fail: already logged out\n");
            else{
                fprintf(logFile, "success: user logged out\n");
                user->logon = 0;
            }
        }
        else
            fprintf(logFile, "fail: incorrect command\n");

        free(message);
    }
    printf("File saved\n");
    if(users->size == 0)
        printf("Nothing to show");
    else
        for(int i = 0; i < users->size; printf("%s %s %d\n", (*(users->users + i))->login, (*(users->users + i))->password, (*(users->users + i))->logon), ++i);

    free_users(users);
    free(filename);
    fclose(logFile);
    fclose(f);
    return 0;
}
