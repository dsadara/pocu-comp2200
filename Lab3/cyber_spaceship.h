#ifndef CYBER_SPACESHIP_H
#define CYBER_SPACESHIP_H

#define FALSE (0)
#define TRUE (1)

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length);

size_t cluster_overlap_count(const char* check_address, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count);

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count);

#endif /* CYBER_SPACESHIP */
