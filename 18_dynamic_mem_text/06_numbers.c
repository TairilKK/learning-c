//
// Created by jdobr on 30.08.2023.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "06_numbers.h"

char *my_strcat(char **dest, const char * src){
    if(!dest || !src) return NULL;

    int src_size = (int) strlen(src);
    int dest_size = 0;
    if((*dest))
        dest_size = (int) strlen(*dest);

    char * temp;
    temp = realloc(*dest, (src_size + dest_size + 1) * sizeof(char));

    if(!temp) return NULL;
    strcpy(temp + dest_size, src);
    *dest = temp;
    return *dest;
}

char *ltoa(unsigned long long number){
    int size = 0;
    if(number == 0)
        size = 1;

    unsigned long long c_number = number;
    while(c_number != 0){
        c_number/=10;
        size++;
    }

    char * res = calloc(size + 1, sizeof(char));
    if(!res) return NULL;

    for(int i = 0; i < size; ++i) {
        *(res + size - i - 1) = (number % 10) + '0';
        number/=10;
    }
    return res;
}

unsigned long long power(unsigned long long  x, int a){
    if(a <= 0)
        return 1;
    unsigned long long  c_x = x;
    for(int i = 1; i < a; ++i)
        x *= c_x;
    return x;
}

int number_2_words(char **text, unsigned long long number){
    if(!text) return 1;
    *text = NULL;
    char * temp = NULL;
    if(number == 0) {
        temp = my_strcat(text, "Zero");
        if(!temp)
            return 2;
        return 0;
    }

    unsigned long long cpy_num = number;
    int size = 0;
    while(cpy_num != 0){
        size++;
        cpy_num/=10;
    }

    unsigned long long h = 0, c_h = 0;
    unsigned long long digit = 0;
    unsigned long long sum_of_3digits = 0;
    int i = 0;
    while(i < size){
        unsigned long long a = power(10ULL, size - i - 1);
        digit = (number / (a)) % 10;
        h = digit * power(10ULL, size - i - 1);
        c_h += h;
        cpy_num = number - c_h;
        temp = NULL;
        if((size - i) % 3 == 0)
            sum_of_3digits = 0;
        sum_of_3digits += digit;
        switch(digit){
            case 1:
                if((size - i - 1) % 3 != 1) {
                    temp = my_strcat(text, "One");
                }
                else{
                    i++;
                    a = power(10ULL, size - i - 1);
                    digit = (number / (a)) % 10;
                    h = digit * power(10ULL, size - i - 1);
                    c_h += h;
                    cpy_num = number - c_h;
                    temp = NULL;
                    if((size - i) % 3 == 0)
                        sum_of_3digits = 0;
                    sum_of_3digits += digit;
                    switch(digit){
                        case 1:
                            temp = my_strcat(text, "Eleven");
                            if(!temp){
                                if(*text)free(*text);
                                *text = NULL;
                                return 2;
                            }
                            break;
                        case 2:
                            temp = my_strcat(text, "Twelve");
                            if(!temp){
                                if(*text)free(*text);
                                *text = NULL;
                                return 2;
                            }
                            break;
                        case 3:
                            temp = my_strcat(text, "Thirteen");
                            if(!temp){
                                if(*text)free(*text);
                                *text = NULL;
                                return 2;
                            }
                            break;
                        case 4:
                            temp = my_strcat(text, "Fourteen");
                            if(!temp){
                                if(*text)free(*text);
                                *text = NULL;
                                return 2;
                            }
                            break;
                        case 5:
                            temp = my_strcat(text, "Fifteen");
                            if(!temp){
                                if(*text)free(*text);
                                *text = NULL;
                                return 2;
                            }
                            break;
                        case 6:
                            temp = my_strcat(text, "Sixteen");
                            if(!temp){
                                if(*text)free(*text);
                                *text = NULL;
                                return 2;
                            }
                            break;
                        case 7:
                            temp = my_strcat(text, "Seventeen");
                            if(!temp){
                                if(*text)free(*text);
                                *text = NULL;
                                return 2;
                            }
                            break;
                        case 8:
                            temp = my_strcat(text, "Eighteen");
                            if(!temp){
                                if(*text)free(*text);
                                *text = NULL;
                                return 2;
                            }
                            break;
                        case 9:
                            temp = my_strcat(text, "Nineteen");
                            if(!temp){
                                if(*text)free(*text);
                                *text = NULL;
                                return 2;
                            }
                            break;
                        default:
                            temp = my_strcat(text, "Ten");
                            if(!temp){
                                if(*text)free(*text);
                                *text = NULL;
                                return 2;
                            }
                            break;
                    }
                }

                if(!temp){
                    if(*text)free(*text);
                    *text = NULL;
                    return 2;
                }
                break;
            case 2:
                if((size - i - 1) % 3 != 1)
                    temp = my_strcat(text, "Two");
                else
                    temp = my_strcat(text, "Twenty");
                if(!temp){
                    if(*text)free(*text);
                    *text = NULL;
                    return 2;
                }
                break;
            case 3:
                if((size - i - 1) % 3 != 1)
                    temp = my_strcat(text, "Three");
                else
                    temp = my_strcat(text, "Thirty");
                if(!temp){
                    if(*text)free(*text);
                    *text = NULL;
                    return 2;
                }
                break;
            case 4:
                if((size - i - 1) % 3 != 1)
                    temp = my_strcat(text, "Four");
                else
                    temp = my_strcat(text, "Forty");
                if(!temp){
                    if(*text)free(*text);
                    *text = NULL;
                    return 2;
                }
                break;
            case 5:
                if((size - i - 1) % 3 != 1)
                    temp = my_strcat(text, "Five");
                else
                    temp = my_strcat(text, "Fifty");
                if(!temp){
                    if(*text)free(*text);
                    *text = NULL;
                    return 2;
                }
                break;
            case 6:
                if((size - i - 1) % 3 != 1)
                    temp = my_strcat(text, "Six");
                else
                    temp = my_strcat(text, "Sixty");
                if(!temp){
                    if(*text)free(*text);
                    *text = NULL;
                    return 2;
                }
                break;
            case 7:
                if((size - i - 1) % 3 != 1)
                    temp = my_strcat(text, "Seven");
                else
                    temp = my_strcat(text, "Seventy");
                if(!temp){
                    if(*text)free(*text);
                    *text = NULL;
                    return 2;
                }
                break;
            case 8:
                if((size - i - 1) % 3 != 1)
                    temp = my_strcat(text, "Eight");
                else
                    temp = my_strcat(text, "Eighty");
                if(!temp){
                    if(*text)free(*text);
                    *text = NULL;
                    return 2;
                }
                break;
            case 9:
                if((size - i - 1) % 3 != 1)
                    temp = my_strcat(text, "Nine");
                else
                    temp = my_strcat(text, "Ninety");
                if(!temp){
                    if(*text)free(*text);
                    *text = NULL;
                    return 2;
                }
                break;
            /* digit == 0 */
            default:
                break;
        }
        if(digit != 0)
        /* Setki */
        if((size - i - 1) % 3 == 2 && temp && sum_of_3digits != 0){
            if(*((*text) + strlen(*text) - 1) != ' ') {
                temp = my_strcat(text, " ");
                if(!temp){
                    if(*text)free(*text);
                    *text = NULL;
                    return 2;
                }
                temp = NULL;
            }
            temp = my_strcat(text, "Hundred");
            if(!temp){
                if(*text)free(*text);
                *text = NULL;
                return 2;
            }
        }

        if(sum_of_3digits != 0){
            switch (size - i - 1) {
                case 3:
                    if (*((*text) + strlen(*text) - 1) != ' ' && sum_of_3digits != 0) {
                        temp = my_strcat(text, " ");
                        if (!temp) {
                            if (*text)free(*text);
                            *text = NULL;
                            return 2;
                        }
                        temp = NULL;
                    }
                    temp = my_strcat(text, "Thousand");
                    if (!temp) {
                        if (*text)free(*text);
                        *text = NULL;
                        return 2;
                    }
                    break;
                case 6:
                    if (*((*text) + strlen(*text) - 1) != ' ' && sum_of_3digits != 0) {
                        temp = my_strcat(text, " ");
                        if (!temp) {
                            if (*text)free(*text);
                            *text = NULL;
                            return 2;
                        }
                        temp = NULL;
                    }
                    temp = my_strcat(text, "Million");
                    if (!temp) {
                        if (*text)free(*text);
                        *text = NULL;
                        return 2;
                    }
                    break;
                case 9:
                    if (*((*text) + strlen(*text) - 1) != ' ' && sum_of_3digits != 0) {
                        temp = my_strcat(text, " ");
                        if (!temp) {
                            if (*text)free(*text);
                            *text = NULL;
                            return 2;
                        }
                        temp = NULL;
                    }
                    temp = my_strcat(text, "Billion");
                    if (!temp) {
                        if (*text)free(*text);
                        *text = NULL;
                        return 2;
                    }
                    break;
                case 12:
                    if (*((*text) + strlen(*text) - 1) != ' ' && sum_of_3digits != 0) {
                        temp = my_strcat(text, " ");
                        if (!temp) {
                            if (*text)free(*text);
                            *text = NULL;
                            return 2;
                        }
                        temp = NULL;
                    }
                    temp = my_strcat(text, "Trillion");
                    if (!temp) {
                        if (*text)free(*text);
                        *text = NULL;
                        return 2;
                    }
                    break;
                case 15:
                    if (*((*text) + strlen(*text) - 1) != ' ' && sum_of_3digits != 0) {
                        temp = my_strcat(text, " ");
                        if (!temp) {
                            if (*text)free(*text);
                            *text = NULL;
                            return 2;
                        }
                        temp = NULL;
                    }
                    temp = my_strcat(text, "Quadrillion");
                    if (!temp) {
                        if (*text)free(*text);
                        *text = NULL;
                        return 2;
                    }
                    break;
                case 18:
                    if (*((*text) + strlen(*text) - 1) != ' ' && sum_of_3digits != 0) {
                        temp = my_strcat(text, " ");
                        if (!temp) {
                            if (*text)free(*text);
                            *text = NULL;
                            return 2;
                        }
                        temp = NULL;
                    }

                    temp = my_strcat(text, "Quintillion");
                    if (!temp) {
                        if (*text)free(*text);
                        *text = NULL;
                        return 2;
                    }
                    break;
                case 21:
                    if (*((*text) + strlen(*text) - 1) != ' ' && sum_of_3digits != 0) {
                        temp = my_strcat(text, " ");
                        if (!temp) {
                            if (*text)free(*text);
                            *text = NULL;
                            return 2;
                        }
                        temp = NULL;
                    }
                    temp = my_strcat(text, "Sextillion");
                    if (!temp) {
                        if (*text)free(*text);
                        *text = NULL;
                        return 2;
                    }
                    break;
                case 24:
                    if (*((*text) + strlen(*text) - 1) != ' ' && sum_of_3digits != 0) {
                        temp = my_strcat(text, " ");
                        if (!temp) {
                            if (*text)free(*text);
                            *text = NULL;
                            return 2;
                        }
                        temp = NULL;
                    }
                    temp = my_strcat(text, "Septillion");
                    if (!temp) {
                        if (*text)free(*text);
                        *text = NULL;
                        return 2;
                    }
                    break;
                case 27:
                    if (*((*text) + strlen(*text) - 1) != ' ' && sum_of_3digits != 0) {
                        temp = my_strcat(text, " ");
                        if (!temp) {
                            if (*text)free(*text);
                            *text = NULL;
                            return 2;
                        }
                        temp = NULL;
                    }
                    temp = my_strcat(text, "Octillion");
                    if (!temp) {
                        if (*text)free(*text);
                        *text = NULL;
                        return 2;
                    }
                    break;
                case 30:
                    if (*((*text) + strlen(*text) - 1) != ' ' && sum_of_3digits != 0) {
                        temp = my_strcat(text, " ");
                        if (!temp) {
                            if (*text)free(*text);
                            *text = NULL;
                            return 2;
                        }
                        temp = NULL;
                    }
                    temp = my_strcat(text, "Nonillion");
                    if (!temp) {
                        if (*text)free(*text);
                        *text = NULL;
                        return 2;
                    }
                    break;
                default:
                    break;
            }
        }
        if(cpy_num != 0 && size - i > 1 && *((*text) + strlen(*text) - 1) != ' '){
            temp = my_strcat(text, " ");
            if(!temp){
                if(*text)free(*text);
                *text = NULL;
                return 2;
            }
        }

        ++i;
    }
    return 0;
}
