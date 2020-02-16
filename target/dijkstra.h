#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H_

#define INF 100000
#define N 7
#define START_POINT 1
#define DEST_POINT 3
#define INIT_ROUTE -1

unsigned int init(
    int *route, 
    int *shortest_dist_from_start, 
    bool *fixed_point, 
    int *shortest_dist_start2dest, 
    int *number_point_in_route);

bool is_unfixed_point(bool *current_fixed_point);

unsigned int get_unfixed_point(
    int *current_point, 
    bool fixed_point[],
    int *unfixed_point);

bool all_point_fixed(int *current_point);

bool is_shorter(
    int shortest_dist_from_start_j, 
    int shortest_dist_from_start_i);

bool new_dist_is_shorter(
    int new_dist, 
    int shortest_dist_from_start[], 
    int destination);

unsigned int search_shorter_point(
    int current_point, 
    bool fixed_point[], 
    int shortest_dist_from_start[],
    int *shorter_point
    );

unsigned int fix_current_point(
    int current_point, 
    bool fixed_point_in[],
    bool fixed_point_out[]);

bool is_next_point(
    int current_point, 
    int destination);

unsigned int update_distance(
    int new_dist, 
    int shorter_point, 
    int shortest_dist_from_start_in[],
    int route_in[], 
    int current_point,
    int shortest_dist_from_start_out[],
    int route_out[]);

unsigned int update_shortest_dist(
    int current_point, 
    bool fixed_point[], 
    int route[], 
    int shortest_dist_from_start[],
    int route_out[],
    int shortest_dist_drom_start_out[]);

void get_shortest_dist_start2dest(
    int *shortest_dist_from_start, 
    int *shortest_dist_start2dest);

void get_route_from_dest(
    int *route, 
    int *route_from_dest, 
    int *number_point_in_route);

void print_result(
    int number_point_in_route, 
    int shortest_dist_start2dest, 
    int *route_from_dest);

void dijkstra(
    int *route, 
    int *shortest_dist_from_start,
    bool *fixed_point, 
    int *shortest_dist_start2dest,
    int *route_from_dest, 
    int *number_point_in_route);



#endif