#include <stdio.h>
#include <stdbool.h>
#include "dijkstra.h"

int main(void){

    int route[N];
    int shortest_dist_from_start[N];
    bool fixed_point[N];
    int shortest_dist_start2dest;
    int route_from_dest[N];
    int number_point_in_route;
   
    init(route, shortest_dist_from_start, fixed_point, &shortest_dist_start2dest,&number_point_in_route);
    
    dijkstra(route, shortest_dist_from_start, \
    fixed_point,&shortest_dist_start2dest, \
    route_from_dest, &number_point_in_route);

    print_result(number_point_in_route, shortest_dist_start2dest, route_from_dest);
    
}