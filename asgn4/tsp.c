#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "i:o:dh"

uint32_t min_weight = -1;
Path *g_best_path = NULL;

void dfshelper(uint32_t vertex, Graph *g, Path *p) {
    if (graph_vertices(g) == path_vertices(p)) {
        if (graph_get_weight(g, vertex, 0) != 0) {
            path_add(p, 0, g);
            if (min_weight < 0 || path_distance(p) < min_weight) {
                min_weight = path_distance(p);
                if (g_best_path == NULL) {
                    g_best_path = path_create(graph_vertices(g) + 1);
                }
                path_copy(g_best_path, p);
            }
            path_remove(p, g);
        }
    }
}

void dfs(uint32_t vertex, Graph *g, Path *p, uint32_t iter) {
    printf("got to iter: %u\n", iter);
    dfshelper(vertex, g, p);
    graph_visit_vertex(g, vertex);
    for (uint32_t i = 0; i < graph_vertices(g); i++) {
        if (graph_get_weight(g, vertex, i) != 0) {
            if (!graph_visited(g, i)) {
                path_add(p, i, g);
                dfs(i, g, p, iter + 1);
                path_remove(p, g);
            }
        }
    }
    graph_unvisit_vertex(g, vertex);
    printf("leaving on iter: %u\n", iter);
}

int main(int argc, char **argv) {

    int opt = 0;
    bool help = false;
    int arguments = 0;
    bool directed = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            infile = fopen(optarg, "r");
            //printf("got infile %s\n", optarg);
            if (infile == NULL) {
                printf("infile broke");
            }
            assert(infile != NULL);
            arguments = 1;
            //printf("arguments is %u\n", arguments);
            break;
        case 'o':
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                printf("outfile broke");
            }
            assert(outfile != NULL);
            arguments = 1;
            break;
        case 'd':
            directed = true;
            arguments = 1;
            break;
        case 'h':
            help = true;
            //printf("help is true\noptarg is %s\n", optarg);
            arguments = 1;
            break;
        }
    }

    if (arguments == 0) {
        fprintf(stderr, "After running ./tsp you can include any of these flags\n-i <inputfile> :  Sets the "
               "file to read from (input file). Requires a filename as an argument. The default "
               "file to read from is stdin\n-o <outputfile> : Sets the file to write to (output "
               "file). Requires a filename as an argument. The default file to write to is "
               "stdout\n-d : Treats all graphs as directed. The default is undirected graphs.\n-h "
               ": Prints this help 	message.");
        return 0;
    }
    if (help == true) {
        printf("After running ./tsp you can include any of these flags\n-i <inputfile> :  Sets the "
               "file to read from (input file). Requires a filename as an argument. The default "
               "file to read from is stdin\n-o <outputfile> : Sets the file to write to (output "
               "file). Requires a filename as an argument. The default file to write to is "
               "stdout\n-d : Treats all graphs as directed. The default is undirected graphs.\n-h "
               ": Prints this help 	message.");
        return 0;
    }

    uint32_t num_vertices = 0;
    //printf("num vertices is %u\n", num_vertices);
    if (fscanf(infile, "%u\n", &num_vertices) != 1) {
        fprintf(stderr, "tsp: error reading number of vertices\n");
        exit(1);
    }
    //printf("num vertices is %u\n", num_vertices);

    Graph *g = graph_create(num_vertices, directed);
    char vertex[100];
    for (uint32_t i = 0; i < num_vertices; i++) {
        //got fgets from discord help (ben)
        if (fgets(vertex, sizeof(vertex), infile) == NULL) {
            fprintf(stderr, "tsp: error reading in vertex name\n");
            exit(1);
        } else {
            vertex[strcspn(vertex, "\n")] = '\0';
            graph_add_vertex(g, vertex, i);
        }
    }
    uint32_t num_edges = 0;
    if (fscanf(infile, "%u\n", &num_edges) != 1) {
        fprintf(stderr, "tsp: error reading in num edges");
        exit(1);
    }
    uint32_t start = 0;
    uint32_t end = 0;
    uint32_t weight = 0;
    for (uint32_t i = 0; i < num_edges; i++) {        
        if (fscanf(infile, "%u %u %u", &start, &end, &weight) != 3) {
            fprintf(stderr, "tsp: error reading adjacency list");
            exit(1);
        }
        graph_add_edge(g, start, end, weight);
    }
    //graph_print(g);
    
    

    Path *best_path = path_create(graph_vertices(g) + 1);
    path_add(best_path, 0, g);
    //run dfs
    dfs(0, g, best_path, 0);
    //path_print(g_best_path, outfile, g);
    
    if (g_best_path == NULL || path_vertices(g_best_path) == graph_vertices(g) + 1) {
        fprintf(outfile, "No path found! Alissa is lost!\n");
    } else {
        path_print(g_best_path, outfile, g);
    }
    
    if (infile != stdin) {
        fclose(infile);
    }

    if (outfile != stdout) {
        fclose(outfile);
    }
    graph_free(&g);
    path_free(&g_best_path);
    path_free(&best_path);
    
    return 0;
}
