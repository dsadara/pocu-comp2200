#include "character_deserializer.h"

int get_character(const char* filename, character_v3_t* out_character)
{
    FILE* stream;
    char character;
    char delims_count = 0;
    int version = -1;

    stream = fopen(filename, "r");

    while ((character = fgetc(stream)) != EOF) {
        if (character == ',') {
            delims_count++;
        }
    }
    rewind(stream);

    if (delims_count == 7) {
        deserialize_v1_to_v3(stream, out_character);
        version = 1;
    }

    if (delims_count == 18) {
        deserialize_v2_to_v3(stream, out_character);
        version = 2;
    }

    if (delims_count == 0) {
        deserialize_v3(stream, out_character);
        version = 3;
    }
    fclose(stream);

    return version;
}

void deserialize_v1_to_v3(FILE* stream, character_v3_t* out_character)
{
    char buffer[256];
    char* token;
    size_t i;

    fgets(buffer, 256, stream);

    token = strtok(buffer, ",:");
    match_key(token, out_character);
    for (i = 0; i < 7; i++) {
        token = strtok(NULL, ",:");
        match_key(token, out_character);
    }
    out_character->minion_count = 0;
}

void deserialize_v2_to_v3(FILE* stream, character_v3_t* out_character)
{
    size_t line_length;
    char buffer[256];
    unsigned int magic_resistance;

    line_length = get_line_length(stream);
    
    fgets(buffer, line_length, stream);
    remove_comma(buffer);

    sscanf(buffer, "%s%d%d%d%d%d%d%d%d%d", out_character->name, &out_character->level, &out_character->strength, &out_character->dexterity, &out_character->intelligence, &out_character->armour, &out_character->evasion, &magic_resistance, &out_character->health, &out_character->mana);
    out_character->name[50] = '\0';
    out_character->leadership = out_character->level / 10;
    out_character->minion_count = 0;
    out_character->elemental_resistance.fire = magic_resistance / 3;
    out_character->elemental_resistance.cold = magic_resistance / 3;
    out_character->elemental_resistance.lightning = magic_resistance / 3;
    
}

void deserialize_v3(FILE* stream, character_v3_t* out_character)
{
    char buffer[512];
    size_t minion_count;
    size_t i;
    size_t line_length;

    line_length = get_line_length(stream);
    fgets(buffer, line_length, stream);
    remove_column(buffer);
    sscanf(buffer, "%s%d%d%d%d%d%d%d%d%d%d%d%d%zd", out_character->name, &out_character->level, &out_character->health, &out_character->mana, &out_character->strength, &out_character->dexterity, &out_character->intelligence, &out_character->armour, &out_character->evasion, &out_character->elemental_resistance.fire, &out_character->elemental_resistance.cold, &out_character->elemental_resistance.lightning, &out_character->leadership, &out_character->minion_count);
    out_character->name[50] = '\0';

    minion_count = out_character->minion_count;
    if (minion_count == 0) {
        return;
    }
    line_length = get_line_length(stream);
    for (i = 0; i < minion_count; i++) {
        fgets(buffer, line_length, stream);
        remove_column(buffer);
        sscanf(buffer, "%s%d%d%d", out_character->minions[i].name, &out_character->minions[i].health, &out_character->minions[i].strength, &out_character->minions[i].defence);
        out_character->minions[i].name[50] = '\0';
    }
}

void remove_column(char* buffer)
{
    char* character = buffer;

    while (*character++ != '\0') {
        if (*character == '|') {
            *character = ' ';
        }
    }
}

size_t get_line_length(FILE* stream)
{
    size_t length_count = 0;

    while (fgetc(stream) != '\n') {
        length_count++;
    }

    return length_count;
}

void remove_comma(char* buffer)
{
    char* character = buffer;

    while (*character++ != '\0') {
        if (*character == ',') {
            *character = ' ';
        }
    }
}

void match_key(char* token, character_v3_t* out_character)
{
    unsigned int id;
    unsigned int dex;
    unsigned int armour;
    unsigned int magic_resistance;
    unsigned int level;

    if (strcmp(token, "lvl") == 0) {
        token = strtok(NULL, ",:");
        sscanf(token, "%d", &level);
        out_character->level = level;
        out_character->leadership = level / 10;
        return;
    }

    if (strcmp(token, "intel") == 0) {
        token = strtok(NULL, ",:");
        sscanf(token, "%d", &out_character->intelligence);
        return;
    }

    if (strcmp(token, "str") == 0) {
        token = strtok(NULL, ",:");
        sscanf(token, "%d", &out_character->strength);
        return;
    }

    if (strcmp(token, "dex") == 0) {
        token = strtok(NULL, ",:");
        sscanf(token, "%d", &dex);
        out_character->dexterity = dex;
        out_character->evasion = dex / 2;
        return;
    }

    if (strcmp(token, "def") == 0) {
        token = strtok(NULL, ",:");
        sscanf(token, "%d", &armour);
        out_character->armour = armour;
        magic_resistance = armour / 4;
        out_character->elemental_resistance.fire = magic_resistance / 3;
        out_character->elemental_resistance.cold = magic_resistance / 3;
        out_character->elemental_resistance.lightning = magic_resistance / 3;
        return;
    }

    if (strcmp(token, "id") == 0) {
        token = strtok(NULL, ",:");
        sscanf(token, "%d", &id);
        sprintf(out_character->name, "player_%d", id);
        return;
    }

    if (strcmp(token, "hp") == 0) {
        token = strtok(NULL, ",:");
        sscanf(token, "%d", &out_character->health);
        return;
    }

    if (strcmp(token, "mp") == 0) {
        token = strtok(NULL, ",:");
        sscanf(token, "%d", &out_character->mana);
        return;
    }
}
