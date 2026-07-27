#include "csv_reader.h"

struct AddressBook *read_data(const char *filename)
{
    struct AddressBook * result = NULL;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    char line[1024];

    // fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        struct AddressBook tmp = { 0 };
        char *token;

        // Remove newline if present
        line[strcspn(line, "\n")] = '\0';

        token = strtok(line, ",");
        if (token) {
            strcpy(tmp.name, token);
        } 

        token = strtok(NULL, ",");
        if (token) {
            strcpy(tmp.surname, token);
        } 

        token = strtok(NULL, ",");
        if (token) {
            strcpy(tmp.email, token);
        }

        token = strtok(NULL, ",");
        if (token) {
            strcpy(tmp.phoneNum, token);
        }

        if (add(tmp, &result) == APP_FAILURE) {
            fclose(file);
            delete_all(&result);
            return NULL;
        }
    }

    fclose(file);

    return result;
}

int write_line(const char *filename, struct AddressBook node)
{
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        return APP_FAILURE;
    }

    fprintf(file, "%s,%s,%s,%s\n",
            node.name,
            node.surname,
            node.email,
            node.phoneNum);

    fclose(file);

    return APP_SUCCESS;
}

int write_all(const char *filename, struct AddressBook *head)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return APP_FAILURE;
    }

    struct AddressBook *current = head;

    while (current != NULL) {
        fprintf(file, "%s,%s,%s,%s\n",
                current->name,
                current->surname,
                current->email,
                current->phoneNum);

        current = current->next;
    }

    fclose(file);

    return APP_SUCCESS;
}