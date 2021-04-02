#ifndef DATA_STORE_H
#define DATA_STORE_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>

user_t* get_user_by_id_or_null(user_t** users_or_null, size_t id);

user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username);

int update_email_release(user_t** users_or_null, size_t id, const char* email);

int update_password_release(user_t** users_or_null, size_t id, const char* password);

void hide_email_address(char* email_address_for_logging);

void hide_password(char* password);

#endif /* DATA_STORE_H */