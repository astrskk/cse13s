#include "path.h"

#include <assert.h>
#include <stdlib.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

Path *path_create(uint32_t capacity) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->total_weight = 0;
    p->vertices = stack_create(capacity);
    return p;
}

void path_free(Path **pp) {
    stack_free(&(*pp)->vertices);
    free(*pp);
    *pp = NULL;
}

uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_distance(const Path *p) {
    return p->total_weight;
}

void path_add(Path *p, uint32_t val, const Graph *g) {
    if (path_vertices(p) < 1) {
        stack_push(p->vertices, val);
        return;
    }
    uint32_t last_vertex;
    stack_peek(p->vertices, &last_vertex);
    stack_push(p->vertices, val);
    uint32_t curr_vertex;
    stack_peek(p->vertices, &curr_vertex);
    uint32_t curr_weight = graph_get_weight(g, last_vertex, curr_vertex);
    p->total_weight += curr_weight;
}

uint32_t path_remove(Path *p, const Graph *g) {
    uint32_t removed_vertex;
    stack_pop(p->vertices, &removed_vertex);
    if (path_vertices(p) <= 1) {
        p->total_weight = 0;
    } else {
        uint32_t new_last_vertex;
        stack_peek(p->vertices, &new_last_vertex);
        uint32_t curr_weight = graph_get_weight(g, new_last_vertex, removed_vertex);
        p->total_weight -= curr_weight;
    }
    return stack_size(p->vertices);
}

void path_copy(Path *dst, const Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->total_weight = src->total_weight;
}

void path_print(const Path *p, FILE *outfile, const Graph *g) {
    fprintf(outfile, "Alissa starts at:\n");
    Stack *temp = stack_create(stack_size(p->vertices));
    uint32_t *x = 0;
    for (uint32_t i = (stack_size(p->vertices) - 1); i >= 0; i--) {
        stack_pop(temp, x);
        fprintf(outfile, "%s\n", graph_get_vertex_name(g, *x));
    }
    fprintf(outfile, "Total distance: %" PRIu32 "\n", p->total_weight);
    stack_free(&temp);
}
