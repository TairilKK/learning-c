//
// Created by jdobr on 31.08.2023.
//

#ifndef INC_05_FUNCTIONS_H
#define INC_05_FUNCTIONS_H

char ** text_modifier(const char *text, int n, ...);
void free_texts(char ** t);

char* lower_to_upper(const char *in);
char* upper_to_lower(const char *in);
char* space_to_dash(const char *in);
char* reverse_letter(const char *in);

#endif //INC_05_FUNCTIONS_H
