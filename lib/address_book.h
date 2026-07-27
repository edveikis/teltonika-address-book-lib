#ifndef ADDRESS_BOOK
#define ADDRESS_BOOK

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "exit_codes.h"

struct AddressBook {
    char name[20];
    char surname[20];
    char email[50];
    char phoneNum[20];
    struct AddressBook *next;
};

void print(struct AddressBook *book);
int add(struct AddressBook src, struct AddressBook **dst) ;
int add_to_pos(struct AddressBook src, struct AddressBook **dst, int pos);
int delete(struct AddressBook **book, int pos);
void delete_all(struct AddressBook **book);
struct AddressBook get(struct AddressBook *book, int pos);
struct AddressBook* find_by(char *keyword, struct AddressBook **book);

#endif