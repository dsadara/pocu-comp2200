#include "user.h"
#include "data_store.h"

user_t* get_user_by_id_or_null(user_t** users_or_null, size_t id)
{
    size_t user_num = _msize(users_or_null) / sizeof(user_t*);
    size_t i;
    for (i = 0; i < user_num; i++) {
        if (users_or_null[i]->id == id) {
            return users_or_null[i];
        }
    }
    return 0;
}

user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username)
{
    size_t user_num = _msize(users_or_null) / sizeof(user_t*);
    size_t i;
    for (i = 0; i < user_num; i++) {
        if (strcmp(users_or_null[i]->username, username) == 0) {
            return users_or_null[i];
        }
    }
    return 0;
}

int update_email(user_t** users_or_null, size_t id, const char* email)
{
    int return_value = 0;
    size_t user_num = _msize(users_or_null) / sizeof(user_t*);
    size_t i;
    char later_email_address_for_logging[50];
    char prior_email_address_for_logging[50];

    strcpy(later_email_address_for_logging, email);

    FILE* stream = fopen("log.txt", "a");
    for (i = 0; i < user_num; i++) {
        if (users_or_null[i] == 0) {
            break;
        }
        
        if (users_or_null[i]->id == id) {
            strcpy(prior_email_address_for_logging, users_or_null[i]->email);
#if defined (RELEASE)
            hide_email_address(prior_email_address_for_logging);
            hide_email_address(later_email_address_for_logging);
#endif
            fprintf(stream, "TRACE: User %zd updated email from \"%s\" to \"%s\"\n", users_or_null[i]->id, prior_email_address_for_logging, later_email_address_for_logging);
            strcpy(users_or_null[i]->email, email);
            return_value = 1;
            break;
        }
    }
    
    fclose(stream);
    return return_value;
}

int update_password(user_t** users_or_null, size_t id, const char* password)
{
    int return_value = 0;
    size_t user_num = _msize(users_or_null) / sizeof(user_t*);
    size_t i;
    char prior_password_for_logging[50];
    char later_password_for_logging[50];

    strcpy(later_password_for_logging, password);

    FILE* stream = fopen("log.txt", "a");

    for (i = 0; i < user_num; i++) {
        if (users_or_null[i] == 0) {
            break;
        }

        if (users_or_null[i]->id == id) {
            strcpy(prior_password_for_logging, users_or_null[i]->password);
#if defined (RELEASE)
            hide_password(prior_password_for_logging);
            hide_password(later_password_for_logging);
#endif
            fprintf(stream, "TRACE: User %zd updated password from \"%s\" to \"%s\"\n", users_or_null[i]->id, prior_password_for_logging, later_password_for_logging);
            strcpy(users_or_null[i]->password, password);
            return_value = 1;
            break;
        }
    }

    fclose(stream);
    return return_value;
}

void hide_email_address(char* email_address_for_logging)
{
    size_t i;
    size_t at_location = 0;

    for (i = 0; i < 50; i++) {
        if (email_address_for_logging[i] == '@') {
            at_location = i;
            break;
        }
    }

    if (at_location == 1) {
        email_address_for_logging[0] = '*';
    } else if (at_location == 2) {
        email_address_for_logging[1] = '*';
    } else if (at_location != 0) {
        for (i = 1; i < at_location - 1; i++) {
            email_address_for_logging[i] = '*';
        }
    }
}

void hide_password(char* password)
{
    size_t i;
    size_t password_length = strlen(password);

    if (password_length == 1) {
        password[0] = '*';
    } else if (password_length == 2) {
        password[1] = '*';
    } else {
        for (i = 1; i < password_length - 1; i++) {
            password[i] = '*';
        }
    }
}
