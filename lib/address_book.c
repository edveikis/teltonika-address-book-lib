#include "address_book.h"

void print(struct AddressBook *book)
{
    int i = 1;
    struct AddressBook *curr = book;
    while (curr != NULL) {

        printf("[ %d ] %s %s %s %s\n", i, 
            curr->name, curr->surname, curr->email, curr->phoneNum);

        curr = curr->next;
        ++i;
    }

    printf("\n");
    printf("\n");
    printf("\n");
}

int copy_struct(struct AddressBook src, struct AddressBook **dst)
{
    *dst = malloc(sizeof(struct AddressBook));

    if (*dst == NULL) {
        return APP_FAILURE;
    }
    
    strncpy((*dst)->name, src.name, 19);
    (*dst)->name[19] = '\0';
 
    strncpy((*dst)->surname, src.surname, 19);
    (*dst)->surname[19] = '\0';
 
    strncpy((*dst)->email, src.email, 49);
    (*dst)->email[49] = '\0';
 
    strncpy((*dst)->phoneNum, src.phoneNum, 19);
    (*dst)->phoneNum[19] = '\0';
 
    (*dst)->next = NULL;

    return APP_SUCCESS;
}

int add(struct AddressBook src, struct AddressBook **dst) 
{
    if (*dst == NULL) {
        if (copy_struct(src, dst) == APP_FAILURE) {
            return APP_FAILURE;
        }
    }
    else {
        struct AddressBook *book = (*dst);
        while (book->next != NULL) {
            book = book->next;
        }

        if (copy_struct(src, &book->next) == APP_FAILURE) {
            return APP_FAILURE;
        }
    }

    return APP_SUCCESS;
}

int add_to_pos(struct AddressBook src, struct AddressBook **dst, int pos)
{
    if (pos < 0) {
        return APP_FAILURE;
    } 

    if (pos == 0) {
        struct AddressBook *head = *dst;
        struct AddressBook *newHead = NULL;

        if (copy_struct(src, &newHead) == APP_FAILURE) {
            return APP_FAILURE;
        }

        newHead->next = head;
        *dst = newHead;
    }
    else {
        struct AddressBook *node = *dst;
        
        for (int i = 0; i < pos - 1; ++i) {
            if (node == NULL) {
                return APP_FAILURE;
            }

            node = node->next;
        }     

        // Node can be null if for fails
        if (node == NULL) {
            return APP_FAILURE;
        }

        struct AddressBook *newNode = NULL;
        if (copy_struct(src, &newNode) == APP_FAILURE) {
            return APP_FAILURE;
        }
        
        newNode->next = node->next;
        node->next = newNode;
    }

    return APP_SUCCESS;
}

int delete(struct AddressBook **book, int pos)
{
    if (pos < 0) {
        return APP_FAILURE;
    }

    if (pos == 0) {
        if (*book == NULL) {
            return APP_FAILURE;
        }

        struct AddressBook *tmp = (*book)->next;
        free(*book);
        *book = tmp;
    } 
    else {
        struct AddressBook *node = *book;
        
        for (int i = 0; i < pos - 1; ++i) {
            if (node == NULL) {
                return APP_FAILURE;
            }

            node = node->next;
        }  
        
        // Node can be null if for fails
        if (node == NULL || node->next == NULL) {
            return APP_FAILURE;
        }

        struct AddressBook *toDel = node->next;
        node->next = node->next->next;
        free(toDel);
    }

    return APP_SUCCESS;
}

void delete_all(struct AddressBook **book)
{
    struct AddressBook *node = *book;
    while (node != NULL) {
        struct AddressBook *tmp = node->next;
        free(node);
        node = tmp;
    }
    *book = NULL;
}

struct AddressBook get(struct AddressBook *book, int pos)
{
    struct AddressBook result = { 0 };
    struct AddressBook *node = book;

    if (pos < 0) {
        return result;
    }

    for (int i = 0; i < pos; ++i) {
        if (node == NULL) {
            return result;
        }
        node = node->next;
    }

    if (node == NULL) {
        return result;
    }

    strncpy(result.name, node->name, 19);
    result.name[19] = '\0';
 
    strncpy(result.surname, node->surname, 19);
    result.surname[19] = '\0';
 
    strncpy(result.email, node->email, 49);
    result.email[49] = '\0';
 
    strncpy(result.phoneNum, node->phoneNum, 19);
    result.phoneNum[19] = '\0';
 
    result.next = NULL;
    
    return result;
}

char *strlwr(char *s) {
    for (char *p = s; *p; ++p) {
        *p = tolower((unsigned char)*p);
    }
    return s;
}

struct AddressBook* find_by(char *keyword, struct AddressBook **book)
{
    struct AddressBook *node = *book;
    struct AddressBook *result = NULL;

    while (node != NULL)
    {
        // keyword has to not be null and not a termnator
        if (keyword != NULL && keyword[0] != '\0' && // and one of the following has to return true
            (strcmp(node->name,     keyword) == 0 ||
             strcmp(node->surname,  keyword) == 0 ||
             strcmp(node->email,    keyword) == 0 ||
             strcmp(node->phoneNum, keyword) == 0
            )) {
            struct AddressBook tmp = { 0 };
            
            strncpy(tmp.name, node->name, 19);
            tmp.name[19] = '\0';

            strncpy(tmp.surname, node->surname, 19);
            tmp.surname[19] = '\0';

            strncpy(tmp.email, node->email, 49);
            tmp.email[49] = '\0';

            strncpy(tmp.phoneNum, node->phoneNum, 19);
            tmp.phoneNum[19] = '\0';
            if (add(tmp, &result) == APP_FAILURE) {
                delete_all(&result);
                return NULL;
            }
        }

        node = node->next;
    }

    return result;
}