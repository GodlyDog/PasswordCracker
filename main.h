//
// Created by Damon Burdell on 2/19/23.
//

#ifndef PASSWORDCRACKER_MAIN_H
#define PASSWORDCRACKER_MAIN_H
int common_pass(char* password, char* filename);
int brute(char* password, char* base, unsigned long len, char* characters);
int brute_master(char* password, char* base);
int main();

#endif //PASSWORDCRACKER_MAIN_H
