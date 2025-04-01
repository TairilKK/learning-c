//
// Created by jdobr on 29.08.2023.
//

#ifndef INC_16_CROSS_H
#define INC_16_CROSS_H

int create_leading_word_cross(const char *first, const char *second, char ***result);
int create_double_leading_word_cross(
        const char *first, const char *second, const char *third, const char *fourth,
        char ***result, char ***first_cross, char ***second_cross);

void destroy(char **words);
void display(char ** w);

int validation(char * w);
int firstLetterCross(const char *first, const char *second, int * w, int * h);

#endif //INC_16_CROSS_H