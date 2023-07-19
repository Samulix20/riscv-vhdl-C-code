#include "print.h"

// -------------- Strings --------------

void print_str(char* str) {
    for (int i = 0; str[i] != 0; i++) {
        print_char(str[i]);
    }
}

// -------------- 32 bits --------------

void printmc_int32(int32 num, uint8 minchars) {
    if (num < 0) {
        num = -num;
        print_char('-');
    }
    printmc_uint32(num, minchars);
}

void printmc_uint32(uint32 num, uint8 minchars) {
    char res[5];
    int i = 0;

    while(num > 0) {
        uint8 val = num % 10;
        num /= 10;
        res[i] = '0' + val;
        i++;
    }

    int j = i;
    while (j < minchars || j == 0) {
        print_char('0');
        j++;
    }

    i--;
    while(i >= 0) {
        print_char(res[i]);
        i--;
    }
}

// -------------- 64 bits --------------

void printmc_int64(int64 num, uint8 minchars) {
    if (num < 0) {
        num = -num;
        print_char('-');
    }
    printmc_uint64(num, minchars);
}


void printmc_uint64(uint64 num, uint8 minchars) {
    char res[20];
    int i = 0;

    while(num > 0) {
        uint8 val = num % 10;
        num /= 10;
        res[i] = '0' + val;
        i++;
    }

    int j = i;
    while (j < minchars || j == 0) {
        print_char('0');
        j++;
    }

    i--;
    while(i >= 0) {
        print_char(res[i]);
        i--;
    }
}

// -------------- fixed16 --------------

void print_fixed16(fix16 num) {
    if (num < 0) {
        num = -num;
        print_char('-');
    }
    print_uint32(num >> 16);
    print_char('.');
    uint64 dpart = 10000000000000000;
    printmc_uint64((dpart / (1 << 16)) * (num & 0xFFFF), 16);
}

enum {NOPARSE, PARSE, LPARSED};
/*
    %i  -> int32_t
    %u  -> uint32_t
    %li -> int64_t
    %lu -> uint64_t
    %f  -> fix16_t
*/
void fprint(char* format, uint64* params) {
    uint8 state = NOPARSE;
    size_t j = 0;
    
    for(size_t i = 0; format[i] != 0; i++) {
        switch (state) {
        case NOPARSE:
            if(format[i] == '%') state = PARSE;
            else print_char(format[i]);
            break;

        case PARSE:
            switch (format[i]){
            case 'i':
                print_int32((int32) params[j]);
                j++;
                state = NOPARSE;
                break;
            case 'u':
                print_uint32((uint32) params[j]);
                j++;
                state = NOPARSE;
                break;
            case 'f':
                print_fixed16((fix16) params[j]);
                j++;
                state = NOPARSE;
                break;
            case 'l':
                state = LPARSED;
                break;
            default:
                print_char('%');
                i--;
                state = NOPARSE;
                break;
            }
            break;
        
        case LPARSED:
            if(format[i] == 'u') {
                print_uint64(params[j]);
                j++;
            }
            else if (format[i] == 'i') {
                print_int64(params[j]);
                j++;
            }
            else i--;
            state = NOPARSE;
            break;
        }
    }
}

// Common buffer for printing macros
uint64 print_buff[10];
