#include <assert.h>
#include "cyber_spaceship.h"

#define CAB_LENGTH (50)

void test_multi_cluster_overlap(void);

int main(void)
{
    test_multi_cluster_overlap();
	return 0;
}

void test_multi_cluster_overlap(void) {
    const char cyber_asteroid_belt[30];
    size_t cab_length;
    const char* cluster_start_address[13];
    size_t cluster_lengths[13];
    
    size_t out_longest_safe_area_length = 0;
		size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
		const char* longest_safe_cluster_start_address;
    
    
    /*
    cab_length = 30;
    cluster_start_address[0] = &cyber_asteroid_belt[0];
    cluster_start_address[1] = &cyber_asteroid_belt[0];
    cluster_start_address[2] = &cyber_asteroid_belt[0];
    cluster_start_address[3] = &cyber_asteroid_belt[0];
    cluster_start_address[4] = &cyber_asteroid_belt[0];
    cluster_start_address[5] = &cyber_asteroid_belt[0];
    cluster_start_address[6] = &cyber_asteroid_belt[29];
    cluster_start_address[7] = &cyber_asteroid_belt[24];
    cluster_start_address[8] = &cyber_asteroid_belt[22];
    cluster_start_address[9] = &cyber_asteroid_belt[10];
    cluster_start_address[10] = &cyber_asteroid_belt[6];
    cluster_start_address[11] = &cyber_asteroid_belt[1];
    cluster_start_address[12] = &cyber_asteroid_belt[1];
    cluster_lengths[0] = 30;
    cluster_lengths[1] = 26;
    cluster_lengths[2] = 22;
    cluster_lengths[3] = 10;
    cluster_lengths[4] = 6;
    cluster_lengths[5] = 1;
    cluster_lengths[6] = 1;
    cluster_lengths[7] = 6;
    cluster_lengths[8] = 4;
    cluster_lengths[9] = 14;
    cluster_lengths[10] = 17;
    cluster_lengths[11] = 14;
    cluster_lengths[12] = 29;
    
    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cyber_asteroid_belt, cab_length, cluster_start_address, cluster_lengths, 13, out_longest_safe_area_length_p);
    assert(longest_safe_cluster_start_address == &cyber_asteroid_belt[15]);
    assert(out_longest_safe_area_length == 8);
    */
    cab_length = 30;
    cluster_start_address[0] = &cyber_asteroid_belt[2];
    cluster_start_address[1] = &cyber_asteroid_belt[3];
    cluster_start_address[2] = &cyber_asteroid_belt[10];
    cluster_start_address[3] = &cyber_asteroid_belt[19];
    cluster_start_address[4] = &cyber_asteroid_belt[23];
    cluster_start_address[5] = &cyber_asteroid_belt[24];
    cluster_start_address[6] = &cyber_asteroid_belt[0];
    cluster_start_address[7] = &cyber_asteroid_belt[0];
    cluster_start_address[8] = &cyber_asteroid_belt[25];
    cluster_lengths[0] = 10;
    cluster_lengths[1] = 12;
    cluster_lengths[2] = 7;
    cluster_lengths[3] = 11;
    cluster_lengths[4] = 1;
    cluster_lengths[5] = 1;
    cluster_lengths[6] = 30;
    cluster_lengths[7] = 30;
    cluster_lengths[8] = 5;
    
    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cyber_asteroid_belt, cab_length, cluster_start_address, cluster_lengths, 9, out_longest_safe_area_length_p);
    printf("%p, %p - %p = %p\n", (void*)&cyber_asteroid_belt[30], (void*)&cyber_asteroid_belt[23], (void*)longest_safe_cluster_start_address, (void*)(&cyber_asteroid_belt[23] - longest_safe_cluster_start_address));
    printf("%zd\n", out_longest_safe_area_length);
    assert(longest_safe_cluster_start_address == &cyber_asteroid_belt[23]);
    assert(out_longest_safe_area_length == 7);
    /*
    cab_length = 30;
    cluster_start_address[0] = &cyber_asteroid_belt[2];
    cluster_start_address[1] = &cyber_asteroid_belt[3];
    cluster_start_address[2] = &cyber_asteroid_belt[10];
    cluster_start_address[3] = &cyber_asteroid_belt[19];
    cluster_start_address[4] = &cyber_asteroid_belt[22];
    cluster_start_address[5] = &cyber_asteroid_belt[24];
    cluster_start_address[6] = &cyber_asteroid_belt[0];
    cluster_start_address[7] = &cyber_asteroid_belt[0];
    cluster_start_address[8] = &cyber_asteroid_belt[25];
    cluster_start_address[9] = &cyber_asteroid_belt[19];
    cluster_start_address[10] = &cyber_asteroid_belt[21];
    cluster_lengths[0] = 10;
    cluster_lengths[1] = 12;
    cluster_lengths[2] = 9;
    cluster_lengths[3] = 11;
    cluster_lengths[4] = 2;
    cluster_lengths[5] = 1;
    cluster_lengths[6] = 30;
    cluster_lengths[7] = 30;
    cluster_lengths[8] = 4;
    cluster_lengths[9] = 2;
    cluster_lengths[10] = 1;
    
    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cyber_asteroid_belt, cab_length, cluster_start_address, cluster_lengths, 11, out_longest_safe_area_length_p);
    
    assert(longest_safe_cluster_start_address == &cyber_asteroid_belt[19]);
    assert(out_longest_safe_area_length == 10);
    */
    printf("test_multi_cluster_overlap clear\n\n");
}
