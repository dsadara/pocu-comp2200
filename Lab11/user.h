#ifndef USER_H
#define USER_H

typedef struct {
    size_t id;
    char username[50];
    char email[50];
    char password[50];
} user_t;

#endif /* USER_H */
