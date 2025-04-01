//
// Created by jdobr on 09.08.2023.
//

#ifndef INC_05_CHAR_OPERATIONS_H
#define INC_05_CHAR_OPERATIONS_H

char lower_to_upper(char ch);
char upper_to_lower(char ch);
char space_to_dash(char ch);
char reverse_letter(char ch);

char * letter_modifier (const char * inputText, char (*func)(char));

#endif //INC_05_CHAR_OPERATIONS_H
