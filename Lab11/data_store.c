#include "data_store.h"

static void hide_email_address(char* email_address_for_logging)
{
    size_t i;
    size_t at_location = 0;

    for (i = 0; i < 51; i++) {
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

static void hide_password(char* password)
{
    size_t i;
    size_t password_length = strlen(password);

    if (password_length == 1) {
        password[0] = '*';
    } else if (password_length == 2) {
        password[1] = '*';
    } else if (password_length != 0) {
        for (i = 1; i < password_length - 1; i++) {
            password[i] = '*';
        }
    }
}

user_t* get_user_by_id_or_null(user_t** users_or_null, size_t id)
{
    if (users_or_null == NULL) {
        return NULL;
    }
    size_t i = 0;

    while (users_or_null[i] != NULL) {
        if (users_or_null[i]->id == id) {
            return users_or_null[i];
        }
        i++;
    }

    return NULL;
}

user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username)
{
    if (users_or_null == NULL || username == NULL) {
        return NULL;
    }
    size_t i = 0;

    while (users_or_null[i] != NULL) {
        if (strcmp(users_or_null[i]->username, username) == 0) {
            return users_or_null[i];
        }
        i++;
    }
    return NULL;
}

bool update_email(user_t** users_or_null, size_t id, const char* email)
{
    if (users_or_null == NULL) {
        return false;
    }
    size_t i = 0;
    char later_email_address_for_release[51];
    char prior_email_address_for_release[51];

    strncpy(later_email_address_for_release, email, 51);
    later_email_address_for_release[50] = '\0';
    hide_email_address(later_email_address_for_release);

    FILE* stream = fopen("log.txt", "a");
    while (users_or_null[i] != NULL) {
        if (users_or_null[i]->id == id) {
            strncpy(prior_email_address_for_release, users_or_null[i]->email, 51);
            prior_email_address_for_release[50] = '\0';
#if defined (RELEASE)
            hide_email_address(prior_email_address_for_release);
            fprintf(stream, "TRACE: User %zd updated email from \"%s\" to \"%s\"\n", users_or_null[i]->id, prior_email_address_for_release, later_email_address_for_release);
#else
            fprintf(stream, "TRACE: User %zd updated email from \"%s\" to \"%s\"\n", users_or_null[i]->id, users_or_null[i]->email, email);
#endif
            strncpy(users_or_null[i]->email, email, 51);
            users_or_null[i]->email[50] = '\0';
            fclose(stream);
            return true;
        }
        i++;
    }
    fclose(stream);
    return false;
}

bool update_password(user_t** users_or_null, size_t id, const char* password)
{
    if (users_or_null == NULL || password == NULL) {
        return false;
    }
    size_t length = strlen(password);
    if (length > 50) {
        return false;
    }
    size_t i = 0;
    char prior_password_for_release[51];
    char later_password_for_release[51];

    strncpy(later_password_for_release, password, 51);
    later_password_for_release[50] = '\0';
    hide_password(later_password_for_release);

    FILE* stream = fopen("log.txt", "a");

    while (users_or_null[i] != NULL) {
        if (users_or_null[i]->id == id) {
            strncpy(prior_password_for_release, users_or_null[i]->password, 51);
            prior_password_for_release[50] = '\0';
#if defined (RELEASE)
            hide_password(prior_password_for_release);
            fprintf(stream, "TRACE: User %zd updated password from \"%s\" to \"%s\"\n", users_or_null[i]->id, prior_password_for_release, later_password_for_release);
#else
            fprintf(stream, "TRACE: User %zd updated password from \"%s\" to \"%s\"\n", users_or_null[i]->id, users_or_null[i]->password, password);
#endif
            strncpy(users_or_null[i]->password, password, 51);
            users_or_null[i]->password[50] = '\0';
            fclose(stream);
            return true;
        }
        i++;
    }

    fclose(stream);
    return false;
}
