#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

enum ExitCodes {
    APP_SUCCESS,
    APP_FAILURE,
};

enum Options {
    PRINT_DATA = 1,
    ADD_CONTACT,
    ADD_CONTACT_TO_I,
    DEL_CONTACT_AT_I,
    DEL_CONTACTS,
    FIND_CONTACT_AT_I,
    FIND_CONTACT,
    QUIT
};

struct AddressBook {
    char name[20];
    char surname[20];
    char email[50];
    char phoneNum[20];
    struct AddressBook *next;
};

struct AddressBook *dst;
int is_running = 1;

/*

Address book

*/
void print(struct AddressBook *book);
int add(struct AddressBook src, struct AddressBook **dst) ;
int add_to_pos(struct AddressBook src, struct AddressBook **dst, int pos);
int delete(struct AddressBook **book, int pos);
void delete_all(struct AddressBook **book);
struct AddressBook get(struct AddressBook *book, int pos);
struct AddressBook* find_by(char *keyword, struct AddressBook **book);

/*

CSV Reader

*/
struct AddressBook *read_data(const char *filename);
int write_line(const char *filename, struct AddressBook node);
int write_all(const char *filename, struct AddressBook *head);

void print_menu(void);
static void sig_handler(int signum);
static void cleanup(void);
static void read_field(const char *prompt, char *dest, size_t size);
int read_int(const char *prompt);
int get_addresses_path(char *dest, size_t size, char* file);

int main(void) {
    signal(SIGINT,sig_handler);
    signal(SIGTERM,sig_handler);
    signal(SIGHUP,sig_handler);
    signal(SIGQUIT,sig_handler);

    char path[512];
    if (get_addresses_path(path, sizeof(path), "addresses.csv") == APP_FAILURE) {
        // If we dont have $HOME we dont know where to store the file...
        return APP_FAILURE;
    }

    dst = read_data(path);

    while (is_running) {
        print_menu();

        int option = read_int("Command no.: ");

        if (option > 0) {
            if (option == PRINT_DATA) {
                print(dst);
            }
            else if (option == ADD_CONTACT) {
                struct AddressBook new_contact = {0};

                char name[20];
                read_field("Name: ", name, sizeof(name));
                strncpy(new_contact.name, name, 19);

                char surname[20];
                read_field("Surname: ", surname, sizeof(surname));
                strncpy(new_contact.surname, surname, 19);

                char email[50];
                read_field("Email: ", email, sizeof(email));
                strncpy(new_contact.email, email, 49);

                char phone_num[20];
                read_field("Phone number: ", phone_num, sizeof(phone_num));
                strncpy(new_contact.phoneNum, phone_num, 19);
                
                write_line(path, new_contact);
                add(new_contact, &dst);
            }
            else if (option == ADD_CONTACT_TO_I) {
                struct AddressBook new_contact = {0};

                char name[20];
                read_field("Name: ", name, sizeof(name));
                strncpy(new_contact.name, name, 19);

                char surname[20];
                read_field("Surname: ", surname, sizeof(surname));
                strncpy(new_contact.surname, surname, 19);

                char email[50];
                read_field("Email: ", email, sizeof(email));
                strncpy(new_contact.email, email, 49);

                char phone_num[20];
                read_field("Phone number: ", phone_num, sizeof(phone_num));
                strncpy(new_contact.phoneNum, phone_num, 19);

                int i = read_int("Index: ");
                
                if (i >= 0) {
                    add_to_pos(new_contact, &dst, i);
                    write_all(path, dst);
                }
            }
            else if (option == DEL_CONTACT_AT_I) {
                int i = read_int("Index of contact to be deleted: ");

                if (i >= 0) { 
                    delete(&dst, i);
                    write_all(path, dst);
                }
            }
            else if (option == DEL_CONTACTS) {
                delete_all(&dst);
                write_all(path, dst);
            }
            else if (option == FIND_CONTACT_AT_I) {
                int i = read_int("Index of contact to be found: ");

                struct AddressBook selected = get(dst, i);
                print(&selected);
            }
            else if (option == FIND_CONTACT) {

                char keyword[50];
                read_field("Search keyword: ", keyword, sizeof(keyword));

                struct AddressBook *selected = find_by(keyword, &dst);
                if (selected != NULL) {
                    print(selected);
                    delete_all(&selected);
                }
            }
            else if (option == QUIT)
            {
                raise(SIGINT);
            }
        }
    }

    cleanup();

    return APP_SUCCESS;
}

void print_menu(void) {
    printf("Options:\n");
    printf("1. Display all records in address book\n");
    printf("2. Add new address to the book\n");
    printf("3. Add new addess at specific location\n");
    printf("4. Delete address at specific index\n");
    printf("5. Delete entire address book\n");
    printf("6. Find address by index\n");
    printf("7. Find address by name, surname, email or phone number\n");
    printf("8. Quit\n");
    printf("\n");
    printf("\n");
    printf("\n");
}

static void sig_handler(int signum) {
    is_running = 0;
}

static void cleanup(void) {
    delete_all(&dst);
    free(dst);
}

void clear (void)
{
    while ( getchar() != '\n' );
}

static void read_field(const char *prompt, char *dest, size_t size) {
    
    printf("%s", prompt);
    
    if (fgets(dest, size, stdin) == NULL) {
        dest[0] = '\0';
        return;
    }
    
    // Buffer cleanup
    int ch;
    size_t len = strlen(dest);

    if (len > 0 && dest[len - 1] == '\n') {
        dest[len - 1] = '\0';
    } 
    else {
        while ((ch = getchar()) != '\n' && ch != EOF) ;
    }
}

int read_int(const char *prompt) {
    int option;
    int c;

    // Continue till input is valid
    while (1) {
        printf("%s", prompt);

        if (scanf("%d", &option) == 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            
            return option;
        }

        // invalid input, clear buffer
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

int get_addresses_path(char *dest, size_t size, char* file) {
    const char *home = getenv("HOME");

    if (home == NULL) {
        return APP_FAILURE;
    }

    snprintf(dest, size, "%s/%s", home, file);

    return APP_SUCCESS;
}