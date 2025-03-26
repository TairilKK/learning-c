//
// Created by jdobr on 19.08.2023.
//

#ifndef INC_20_MESSAGE_T_H
#define INC_20_MESSAGE_T_H

struct message_t
{
    char a;
    double b;
    int c;
};

int load_data(struct message_t *cp, int size, const char *filename);
int decode_message(const struct message_t *cp, int size, char *msg, int text_size);

#endif //INC_20_MESSAGE_T_H
