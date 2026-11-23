#include <ctype.h>
#include <string.h>

int stricmp(const char* left, const char* right) {
    signed char left_character;
    signed char right_character;

    for (;;) {
        left_character = (signed char)tolower(*left++);
        right_character = (signed char)tolower(*right++);

        if (left_character < right_character)
            return -1;

        if (left_character > right_character)
            return 1;

        if (left_character == '\0')
            return 0;
    }
}

// FE10: itoa is linked too (wrapper 0x80291CEC, __msl_itoa 0x8028E13C); standard MSL implementation
char* __msl_strrev(char* str) {
    int SmallIndex = 0;
    int BigIndex = strlen(str) - 1;

    while (SmallIndex < BigIndex) {
        char Temp = str[SmallIndex];

        str[SmallIndex] = str[BigIndex];
        str[BigIndex] = Temp;

        SmallIndex++;
        BigIndex--;
    }

    return str;
}

char* __msl_itoa(int val, char* str, int radix) {
    char IsNegative = 0;
    unsigned int theNum = val;
    int StrIndex = 0;

    if (val < 0) {
        theNum = -val;
        IsNegative = 1;
    }

    do {
        int CurDigit = theNum % radix;
        if (CurDigit > 9) {
            str[StrIndex++] = CurDigit + 'A' - 10;
        } else {
            str[StrIndex++] = CurDigit + '0';
        }
        theNum /= radix;
    } while (theNum);

    if (IsNegative) {
        str[StrIndex++] = '-';
    }

    str[StrIndex++] = 0;
    __msl_strrev(str);
    return str;
}

char* itoa(int val, char* str, int radix) {
    return __msl_itoa(val, str, radix);
}
