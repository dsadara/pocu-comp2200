#ifndef DATA_STORE_H
#define DATA_STORE_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "user.h"

user_t* get_user_by_id_or_null(user_t** users_or_null, size_t id);

user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username);

int update_email(user_t** users_or_null, size_t id, const char* email);

int update_password(user_t** users_or_null, size_t id, const char* password);

static void hide_email_address(char* email_address_for_logging);

static void hide_password(char* password);

#endif /* DATA_STORE_H */
