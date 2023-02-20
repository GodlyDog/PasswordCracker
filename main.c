#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "main.h"

//
// Created by Damon Burdell on 2/16/23.
//

unsigned long min_password_length = 1;
unsigned long max_password_length = 6;

int common_pass(char* password, char* filename) {
    FILE *file;
    char str[60];
    file = fopen(filename , "r");
    if (file == NULL) {
        return -1;
    }
    while (fgets(str, 60, file) != NULL) {
        str[strlen(str)-1] = '\0';
        if (strcmp(password, str) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int brute(char* password, char* base, unsigned long len, char characters[]) {
    unsigned long length = strlen(base);
    if (length > len) {
        return -1;
    }
    for (unsigned long i = 0; i < strlen(characters); i++) {
        char copy[2];
        copy[1] = '\0';
        copy[0] = characters[i];
        char* compare = strcat(base, copy);
        if (strcmp(password, compare) == 0) {
            return 1;
        }
        base[strlen(base)-1] = '\0';
    }
    for (unsigned long i = 0; i < strlen(characters); i++) {
        char copy[2];
        copy[1] = '\0';
        copy[0] = characters[i];
        char* compare = strcat(base, copy);
        char passing[max_password_length + 1];
        strcpy(passing, compare);
        base[strlen(base)-1] = '\0';
        int status = brute(password, passing, len, characters);
        if (status > 0) {
            return 1;
        }
    }
    return -1;
}

int brute_master(char* password, char* base) {
    char passing[max_password_length+1];
    strcpy(passing, base);
    //char all_symbols[] =
    //        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890~`!@#$%^&*()_-+={[}]|\\:;\"'<,>.?/";
    char alphanumeric[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    char lowercase[] = "abcdefghijklmnopqrstuvwxyz";
    for (unsigned long round = 1; round < max_password_length; round++) {
        int status = brute(password, passing, round, lowercase);
        if (status > 0) {
            return 1;
        }
    }
    printf("Password contains capitalized letters, numbers, or symbols\n");
    for (unsigned long round = 1; round < max_password_length; round++) {
        int status = brute(password, passing, round, alphanumeric);
        if (status > 0) {
            return 1;
        }
    }
    return -1;
}

int main() {
    printf("Enter a password: ");
    char password[50];
    scanf("%s", password);
    clock_t time;
    time = clock();

    int common = common_pass(password, "common_passwords.txt");
    if (common < 0) {
        perror("common_passwords.txt file not found\n");
    }
    if (common > 0) {
        time = clock() - time;
        double time_taken = ((double) time) / CLOCKS_PER_SEC;
        printf("%s%f%s", "Found password in list of common passwords in ", time_taken, " seconds\n");
        return 1;
    }
    printf("Password not in 1000 most used passwords, checking leaks\n");
    int leaked = common_pass(password, "leaked.txt");
    if (leaked < 0) {
        perror("leaked.txt file not found\n");
    }
    if (leaked > 0) {
        time = clock() - time;
        double time_taken = ((double) time) / CLOCKS_PER_SEC;
        printf("%s%f%s", "Found password in list of leaked passwords in ", time_taken, " seconds\n");
        return 1;
    }
    printf("Password not in leaked passwords, brute forcing\n");
    int brutish = brute_master(password, "");
    if (brutish > 0) {
        time = clock() - time;
        double time_taken = ((double) time) / CLOCKS_PER_SEC;
        printf("%s%f%s", "Found password by brute force in ", time_taken, " seconds\n");
        return 1;
    }
    printf("Password not cracked\n");
    return -1;
}
