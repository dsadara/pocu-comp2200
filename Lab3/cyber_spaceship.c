#include <stddef.h>
#include "cyber_spaceship.h"

/*
const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
{
    size_t i;
    size_t is_start_point = TRUE;
    size_t temp_longest_safe_area_length = 0;
    const char* temp_longest_safe_cluster_start_address;
    const char* longest_safe_cluster_start_address; 

    if (cab_length == 0) {
        *out_longest_safe_area_length = 0;
        return NULL;
    }

    for (i = 0; i < cab_length; i++) {
        if (cluster_overlap_count(cab_start_location + i, cluster_start_locations, cluster_lengths, cluster_count) % 2 == 0) {
            if (is_start_point) {
                temp_longest_safe_cluster_start_address = cab_start_location + i;
                is_start_point = FALSE;
            }
            temp_longest_safe_area_length++;
        } else {
            if (is_start_point == FALSE && temp_longest_safe_area_length > *out_longest_safe_area_length) {
                *out_longest_safe_area_length = temp_longest_safe_area_length;
                longest_safe_cluster_start_address = temp_longest_safe_cluster_start_address;
                is_start_point = TRUE;
            }
            temp_longest_safe_area_length = 0;
        }
        
    }
    return longest_safe_cluster_start_address;
}
*/
const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
{
    size_t i;
    size_t is_start_point = TRUE;
    size_t temp_longest_safe_area_length = 0;
    size_t final_longest_safe_area_length = 0;
    const char* temp_longest_safe_cluster_start_address;
    const char* final_longest_safe_cluster_start_address; 

    if (cab_length == 0) {
        *out_longest_safe_area_length = 0;
        return NULL;
    }

    for (i = 0; i < cab_length; i++) {
        if (cluster_overlap_count(cab_start_location + i, cluster_start_locations, cluster_lengths, cluster_count) % 2 == 0) { 
            temp_longest_safe_area_length++;
            if (is_start_point) {
                temp_longest_safe_cluster_start_address = cab_start_location + i;
                is_start_point = FALSE;
            }
        } else {
            if (temp_longest_safe_area_length > final_longest_safe_area_length) {
                final_longest_safe_cluster_start_address = temp_longest_safe_cluster_start_address;
                final_longest_safe_area_length = temp_longest_safe_area_length;
                temp_longest_safe_area_length = 0;
            }
            is_start_point = TRUE;
        }
    }

    if (final_longest_safe_area_length == 0) {
        final_longest_safe_cluster_start_address = temp_longest_safe_cluster_start_address;
        final_longest_safe_area_length = temp_longest_safe_area_length;
    }

    *out_longest_safe_area_length = final_longest_safe_area_length;
    return final_longest_safe_cluster_start_address;
}

size_t cluster_overlap_count(const char* check_address, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{
    size_t i;
    size_t overlap_count = 0;

    for (i = 0; i < cluster_count; i++) {
        if (cluster_start_locations[i] <= check_address && check_address < cluster_start_locations[i] + cluster_lengths[i]) {
            overlap_count++;
        }
    }

    return overlap_count;
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{
    size_t i;
    double travel_time_floating_point;
    size_t safe_zone_length_temp = 0;
    size_t danger_zone_length_temp = 0;

    for (i = 0; i < cab_length; i++) {
        if (cluster_overlap_count(cab_start_location + i, cluster_start_locations, cluster_lengths, cluster_count) % 2 == 0) {
            safe_zone_length_temp++;
        } else {
            danger_zone_length_temp++;
        }
    }
    
    travel_time_floating_point = safe_zone_length_temp / 10.0 + danger_zone_length_temp / 5.0;
    return (int)(travel_time_floating_point + 0.5);
}
