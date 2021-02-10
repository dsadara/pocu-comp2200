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

    if (delims_count == 7) {
        printf("delims_count: %d\n", delims_count);
        version = 1;
    }

    if (delims_count == 18) {
        printf("delims_count: %d\n", delims_count);
        version = 2;
    }

    if (delims_count == 0) {
        deserialize_v3(stream, out_character);
        version = 3;
    }
    fclose(stream);

    return version;
}
/*
void deserialize_v1_to_v3(FILE* stream, character_v3_t* out_character)
{

}

void deserialize_v2_to_v3(FILE* stream, character_v3_t* out_character)
{

}
*/
void deserialize_v3(FILE* stream, character_v3_t* out_character)
{
    char buffer[4096];
    char tmp;
    int result;
    size_t minion_count;
    size_t i;
    size_t line_length;
    
    rewind(stream); /* 테스트중에 스트림 초기화가 안되서 사용중 */

    line_length = get_line_length(stream);
    fgets(buffer, line_length, stream);
    remove_column(buffer);
    sscanf(buffer, "%s%d%d%d%d%d%d%d%d%d%d%d%d%zd",
    out_character->name, &out_character->level, &out_character->health,
    &out_character->mana, &out_character->strength, &out_character->dexterity,
    &out_character->intelligence, &out_character->armour, &out_character->evasion,
    &out_character->elemental_resistance.fire, &out_character->elemental_resistance.cold, &out_character->elemental_resistance.lightning,
    &out_character->leadership, &out_character->minion_count);

    minion_count = out_character->minion_count;
    if (minion_count == 0) {
        return;
    }
    line_length = get_line_length(stream);
    for (i = 0; i < minion_count; i++) {
        fgets(buffer, line_length, stream);
        remove_column(buffer);
        sscanf(buffer, "%s%d%d%d", out_character->minions[i].name, &out_character->minions[i].health,
        &out_character->minions[i].strength, &out_character->minions[i].defence);
    }
}

void remove_column(char* buffer)
{
    char* character = buffer;

    while(*character++ != '\0') {
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
