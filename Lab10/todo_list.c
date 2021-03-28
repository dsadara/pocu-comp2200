#include "todo_list.h"

todo_list_t init_todo_list(size_t max_size)
{
    todo_list_t todo_list;
    todo_list.nodes = malloc(sizeof(todo_list_node_t) * max_size + sizeof(size_t));

    size_t* count = (size_t*)todo_list.nodes;
    *count = 0;
    return todo_list;
}

void finalize_todo_list(todo_list_t* todo_list)
{
    free(todo_list->nodes);
    todo_list->nodes = NULL;
}

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    if (priority < 0) {
        return false;
    }

    size_t current_index = get_count(todo_list);
    todo_list_node_t* todo_list_node_start = (todo_list_node_t*)((size_t*)todo_list->nodes + 1);

    todo_list_node_start[current_index].priority = priority;
    strncpy(todo_list_node_start[current_index].task, task, 512);
    
    (*(size_t*)todo_list->nodes)++;
    return true;
}

bool complete_todo(todo_list_t* todo_list)
{
    if (get_count(todo_list) == 0) {
        return false;
    }
    todo_list_node_t* todo_list_node_start = (todo_list_node_t*)((size_t*)todo_list->nodes + 1);
    int32_t high_priority_index;
    size_t task_count = get_count(todo_list);
    size_t i;

    high_priority_index = 0;
    for (i = 1; i < task_count; i++) {
        if (todo_list_node_start[high_priority_index].priority < todo_list_node_start[i].priority) {
            high_priority_index = i;
        }
    }

    for (i = high_priority_index; i < task_count - 1; i++) {
        todo_list_node_start[i].priority = todo_list_node_start[i + 1].priority;
        strncpy(todo_list_node_start[i].task, todo_list_node_start[i + 1].task, 512);
    }

    (*(size_t*)todo_list->nodes)--;
    return true;
}

const char* peek_or_null(const todo_list_t* todo_list)
{
    todo_list_node_t* todo_list_node_start = (todo_list_node_t*)((size_t*)todo_list->nodes + 1);
    int32_t high_priority_index;
    size_t task_count = get_count(todo_list);
    size_t i;

    high_priority_index = 0;
    for (i = 1; i < task_count; i++) {
        if (todo_list_node_start[high_priority_index].priority < todo_list_node_start[i].priority) {
            high_priority_index = i;
        }
    }

    return todo_list_node_start[high_priority_index].task;
}

size_t get_count(const todo_list_t* todo_list)
{
    return *(size_t*)todo_list->nodes;
}

bool is_empty(const todo_list_t* todo_list)
{
    if (*(size_t*)todo_list->nodes == 0) {
        return true;
    }
    return false;
}

void print_list(const todo_list_t* todo_list)
{
    todo_list_node_t* todo_list_node_start = (todo_list_node_t*)((size_t*)todo_list->nodes + 1);
    size_t i;
    size_t count = get_count(todo_list);
    printf("**print start**\n");
    for (i = 0; i < count; i++) {
        printf("priority: %d, task : %s\n", todo_list_node_start[i].priority, todo_list_node_start[i].task);
    }
    printf("**print end**\n");
}
