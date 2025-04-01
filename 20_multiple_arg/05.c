#include <stdio.h>
#include <stdarg.h>

struct point_t {
    int x;
    int y;
};

int print_positive_integer(int value) {
    if (value == 0)
        return 0;
    int length = print_positive_integer(value / 10);
    putchar('0' + (value % 10));
    return length + 1;
}

int print_integer(int value) {
    if (value == 0) {
        putchar('0');
        return 1;
    }

    if (value < 0) {
        putchar('-');
        return 1 + print_integer(-value);
    }

    return print_positive_integer(value);
}

int print_fractional_recursive(double fractional, int depth) {
    if (depth == 5) {
        return 0;
    }

    fractional *= 10.0;
    int digit = (int)fractional;
    putchar('0' + digit);
    return 1 + print_fractional_recursive(fractional - digit, depth + 1);
}

int print_double(double value) {
    int length = 0;
    if (value < 0.0) {
        putchar('-');
        length++;
        value = -value;
    }

    int integer_part = (int)value;
    length += print_integer(integer_part);
    putchar('.');
    length++;
    length += print_fractional_recursive(value - integer_part, 0);
    return length;
}


int print_point(struct point_t point) {
    int length = 0;
    putchar('(');
    length += print_integer(point.x);
    putchar(' ');
    length += print_integer(point.y);
    putchar(')');
    return length + 3;
}

int print_string(char * c){
    if(!c)
        return 0;
    int length = 0;
    while(*c != '\0'){
        putchar(*c);
        c++;
        length++;
    }
    return length;
}

int my_printf(char *format, ...) {
    if(format == NULL)
        return 0;
    int count = 0;
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format != '%') {
            putchar(*format);
            count++;
            format++;
            continue;
        }

        format++;

        switch (*format) {
            case 's':
                count += print_string(va_arg(args, char *));
                break;
            case 'd':
                count += print_integer(va_arg(args, int));
                break;
            case 'f':
                count += print_double(va_arg(args, double));
                break;
            case 'p':
                count += print_point(va_arg(args, struct point_t));
                break;
        }
        format++;
    }

    va_end(args);
    return count;
}

int is_number(char c){
    return (c >= '0' && c <= '9') ? 1 : 0;
}
int scan_int(int * res){
    if(!res)return 0;
    int flag = 0;
    int m = 1;
    char c = getchar();
    *res = 0;
    while(1) {
        if(c == '\n' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            return 0;
        if (c != '-' && is_number(c) == 0)
            c = getchar();
        else if(c == '-') {
            m = -1;
            break;
        }
        else {
            flag = 1;
            *res += (int) c - '0';
            break;
        }
    }


    while(is_number(c = getchar()) != 0){
        if(*res == 0 && flag == 1)
            return 1;
        if(flag == 1)
            *res *= 10;
        *res += ((int)c - '0') * m;
        flag = 1;
    }
    return 1;
}

int scan_point_t(struct point_t * p){
    if(!p)return 0;

    int flag = 0;
    int m = 1;
    char c = getchar();
    while(c!='(') {
        if(c == '\n')
            return 0;
        if (c != '-' && is_number(c) == 0)
            c = getchar();
    }
    p->x = 0;
    c = getchar();
    if(c != '-' && is_number(c) == 0)
        return 0;
    else if(c == '-')
        m = -1;
    else {
        flag = 1;
        p->x += (int) c - '0';
    }

    while(is_number(c = getchar()) != 0){
        if(p->x == 0 && flag == 1)
            break;
        if(flag == 1)
            p->x *= 10;
        p->x += ((int)c - '0') * m;
        flag = 1;
    }
    if(c != ' ')
        return 0;

    p->y = 0;
    m = 1;
    flag = 0;
    c = (char)getchar();
    if(c != '-' && is_number(c) == 0)
        return 0;
    else if(c == '-')
        m = -1;
    else {
        flag = 1;
        p->y += (int) c - '0';
    }

    while(is_number(c = getchar()) != 0){
        if(p->y == 0 && flag == 1)
            return 0;
        if(flag == 1)
            p->y *= 10;
        p->y += ((int)c - '0') * m;
        flag = 1;
    }
    if(c != ')')
        return 0;

    return 2;
}

int scan_double(double * d){
    if(!d)return 0;
    int flag = 0;
    double m = 1;
    int int_part = 0;
    char c = getchar();
    *d = 0;

    while(1) {
        if(c == '\n' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            return 0;
        if (c != '-' && is_number(c) == 0)
            c = getchar();
        else if(c == '-') {
            m = -1;
            break;
        }
        else {
            flag = 1;
            int_part += (int) c - '0';
            break;
        }
    }

    while(is_number(c = getchar()) != 0){
        if(int_part == 0 && flag == 1)
            break;
        if(flag == 1)
            int_part *= 10;
        int_part += ((int)c - '0');
        flag = 1;
    }
    if(is_number(c) == 0 && c != '.') {
        *d = (double) int_part * m;
        return 1;
    }
    *d = 0;
    int counter = 0;
    while(is_number(c = getchar()) != 0){
        *d *= 10;
        *d += ((double )c - '0');
        counter++;
    }
    for(int i = 0; i < counter; ++i)
        *d /= 10;
    *d += int_part;
    *d *= m;
    if(c == '\n')
        return 2;
    return 1;
}

int my_scanf(char *format, ...) {
    if(format == NULL)
        return 0;
    va_list args;
    va_start(args, format);
    int a;
    int count = 0;
    int *d;
    double *f;
    struct point_t *p;

    while (*format) {
        if (*format != '%') {
            format++;
            continue;
        }
        format++;
        switch (*format) {
            case 'd':
                d = va_arg(args, int *);
                a = scan_int(d);
                if(a == 2)
                    count++;
                else
                    count += a;
                break;
            case 'f':
                f = va_arg(args, double *);
                a = scan_double(f);
                if(a == 2)
                    count++;
                else
                    count += a;
                break;
            case 'p':
                p = va_arg(args, struct point_t *);
                count += scan_point_t(p);
                format++;
                break;
        }
    }

    va_end(args);
    return count;
}

int main() {
    return 0;
}
