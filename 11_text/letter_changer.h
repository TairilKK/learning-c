#ifndef EMPTY_PROJECT_LETTER_CHANGER_H

enum letter_changer_t {  TO_LOWER=0, TO_UPPER=1 };

char to_lower(char a);
char to_upper(char a);
char* change_letter_size(char *txt, enum letter_changer_t c);

#define  EMPTY_PROJECT_LETTER_CHANGER_H

#endif //EMPTY_PROJECT_LETTER_CHANGER_H
