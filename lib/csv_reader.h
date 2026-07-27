#ifndef CSV_READER
#define CSV_READER

#include <stdio.h>

#include "address_book.h"
#include "exit_codes.h"

struct AddressBook *read_data(const char *filename);
int write_line(const char *filename, struct AddressBook node);
int write_all(const char *filename, struct AddressBook *head);

#endif