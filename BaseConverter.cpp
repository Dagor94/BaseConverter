// BaseConverter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int convertToDecimal(const char* input, int inputBase) {
    int decimalValue = 0;
    int length = strlen(input);
    int basePower = 1;

    // Converts the input to decimal, based on the length and goes character by character - from the back.
    for (int i = length - 1; i >= 0; i--) {
        char digit = toupper(input[i]);
        int numericValue;

        if (digit >= '0' && digit <= '9') {
            numericValue = digit - '0';
        }
        else if (digit >= 'A' && digit <= 'F') {
            numericValue = digit - 'A' + 10;
        }
        else {
            printf("Invalid character '%c' in input.\n", digit);
            return -1;
        }

        if (numericValue >= inputBase) {
            printf("Invalid digit '%c' for base %d.\n", digit, inputBase);
            return -1;
        }

        decimalValue += numericValue * basePower;
        basePower *= inputBase;
    }

    return decimalValue;
}

// 
void convertFromDecimal(int decimalValue, int outputBase, char* output) {
    char digits[] = "0123456789ABCDEF";
    int index = 0;

    if (decimalValue == 0) {
        output[index++] = '0';
    }
    else {
        while (decimalValue > 0) {
            int remainder = decimalValue % outputBase;
            output[index++] = digits[remainder];
            decimalValue /= outputBase;
        }
    }

    output[index] = '\0';

    for (int i = 0; i < index / 2; i++) {
        char temp = output[i];
        output[i] = output[index - 1 - i];
        output[index - 1 - i] = temp;
    }
}

// Generisk funktion til konvertering mellem talsystemer
void convertBase(const char* input, int inputBase) {
    // Konverter input til decimal
    int decimalValue = convertToDecimal(input, inputBase);
    if (decimalValue == -1) {
        return;
    }

    char binaryOutput[64], octalOutput[64], decimalOutput[64], hexadecimalOutput[64];

    convertFromDecimal(decimalValue, 2, binaryOutput);
    convertFromDecimal(decimalValue, 8, octalOutput);
    convertFromDecimal(decimalValue, 10, decimalOutput);
    convertFromDecimal(decimalValue, 16, hexadecimalOutput);

    printf("----------\n");
    printf("Input: %s (Base %d)\n\n", input, inputBase);
    printf("Binary: %s (Base 2)\n", binaryOutput);
    printf("Octal: %s (Base 8)\n", octalOutput);
    printf("Decimal: %s (Base 10)\n", decimalOutput);
    printf("Hexadecimal: %s (Base 16)\n", hexadecimalOutput);
}

// Henter basen ud fra prefix - 0b, 0o, od, ox
int getBaseFromPrefix(const char* prefix) {
    if (strcmp(prefix, "0b") == 0) {
        return 2;
    }
    else if (strcmp(prefix, "0o") == 0) {
        return 8;
    }
    else if (strcmp(prefix, "0d") == 0) {
        return 10;
    }
    else if (strcmp(prefix, "0x") == 0) {
        return 16;
    }
    else {
        return -1;
    }
}

int main() {
    char input[64], inputPrefix[3];
    int inputBase;
    char continueProgram = 'y';

    printf("Welcome to the Base Converter!\n");

    while (tolower(continueProgram) == 'y') {
        printf("\nEnter the input number with its base prefix (0b, 0o, 0d, 0x): ");
        scanf_s("%2s%63s", inputPrefix, (unsigned int)sizeof(inputPrefix), input, (unsigned int)sizeof(input));

        inputBase = getBaseFromPrefix(inputPrefix);
        if (inputBase == -1) {
            printf("Invalid input prefix. Please use 0b, 0o, 0d, or 0x.\n");
            continue;
        }

        convertBase(input, inputBase);

        printf("\nWould you like to convert another number? (y/n): ");
        scanf_s(" %c", &continueProgram, 1);
        system("cls");
    }

    printf("Thank you for using the Base Converter. Goodbye!\n");
    return 0;
}

