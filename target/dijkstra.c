// https://qiita.com/KUKDfhia/items/f1c6cc4cacd311787b95

#include <stdio.h>
#include <stdbool.h>
#include "dijkstra.h"

int distance[N][N]={
    {0,2,8,4,-1,-1,-1},
    {2,0,-1,-1,3,-1,-1},
    {8,-1,0,-1,2,3,-1},
    {4,-1,-1,0,-1,8,-1},
    {-1,3,2,-1,0,-1,9},
    {-1,-1,3,8,-1,0,3},
    {-1,-1,-1,-1,9,3,0}
    };

unsigned int init(
    int *route, 
    int *shortest_dist_from_start, 
    bool *fixed_point, 
    int *shortest_dist_start2dest, 
    int *number_point_in_route)
    {
    *shortest_dist_start2dest = INF;
    *number_point_in_route = 0;
    for(int i=0;i<N;i++){
        route[i] = INIT_ROUTE;
        shortest_dist_from_start[i] = INF;
        fixed_point[i] = false;
    }
    shortest_dist_from_start[START_POINT] = 0;
    return 0;
}

bool is_unfixed_point(bool *current_fixed_point)
{
    if(*current_fixed_point==false){
        return true;
    }
    else{
        return false;    
    }
    
}

unsigned int get_unfixed_point(
    int *current_point, 
    bool fixed_point[],
    int *unfixed_point
    )
    {
        *unfixed_point = *current_point;
        while(*unfixed_point<N){
            if(is_unfixed_point(&fixed_point[*unfixed_point])){
                break;
            }
            else{
                // donothing
            }
            *unfixed_point = *unfixed_point+1;
        }
        return 0;
    }


bool all_point_fixed(int *current_point)
{
    if(*current_point==N){
        return true;
    }
    else{
        return false;    
    }
    
}

bool is_shorter(
    int shortest_dist_from_start_search, 
    int shortest_dist_from_start_current)
    {
        if(shortest_dist_from_start_search < shortest_dist_from_start_current){
            return true;
        }
        else{
            return false;
        }
    }

bool new_dist_is_shorter(
    int new_dist, 
    int shortest_dist_from_start[], 
    int destination)
    {
    return new_dist < shortest_dist_from_start[destination];
}

unsigned int search_shorter_point(
    int current_point, 
    bool fixed_point[], 
    int shortest_dist_from_start[],
    int *shorter_point
    )
    {
    for(int search_index=current_point+1; search_index<N; search_index++){
        if(is_unfixed_point(&fixed_point[search_index]) && is_shorter(shortest_dist_from_start[search_index], shortest_dist_from_start[current_point])){
            *shorter_point = search_index;
        }
        else{
            // donothing
        }
    }

    return 0;
}

unsigned int fix_current_point(
    int current_point, 
    bool fixed_point_in[],
    bool fixed_point_out[])
{
    for(int i=0;i<N;i++){
        fixed_point_out[i] = fixed_point_in[i];
    }
    
    fixed_point_out[current_point] = true;
    return 0;
}

bool is_next_point(
    int current_point, 
    int destination)
    {
    return distance[current_point][destination] >0;
}



unsigned int update_distance(
    int new_dist, 
    int shorter_point, 
    int shortest_dist_from_start_in[], 
    int route_in[], 
    int current_point,
    int shortest_dist_from_start_out[], 
    int route_out[]
    )
{
        for(int i=0;i<N;i++){
            shortest_dist_from_start_out[i] = shortest_dist_from_start_in[i];
            route_out[i] = route_in[i];
        }
        
        if(new_dist_is_shorter(new_dist, shortest_dist_from_start_in, shorter_point)){
            shortest_dist_from_start_out[shorter_point] = new_dist;
            route_out[shorter_point] = current_point;
        }
    return 0;
}

unsigned int update_shortest_dist(
    int current_point, 
    bool fixed_point[], 
    int route[], 
    int shortest_dist_from_start[],
    int route_out[],
    int shortest_dist_from_start_out[]
    ){
    int new_dist = 0;
    for(int shorter_point=0; shorter_point< N; shorter_point++){
        if(is_next_point(current_point, shorter_point) && is_unfixed_point(&fixed_point[shorter_point])){
            new_dist = shortest_dist_from_start[shorter_point] + distance[current_point][shorter_point];
            int shortest_dist_from_start_out[N];
            int route_out[N];
            update_distance(new_dist, shorter_point, shortest_dist_from_start, route, current_point, route_out, shortest_dist_from_start_out);
        
        }
    }
    return 0;
}

void get_shortest_dist_start2dest(
    int *shortest_dist_from_start, 
    int *shortest_dist_start2dest)
    {
    *shortest_dist_start2dest = shortest_dist_from_start[DEST_POINT];
}

void get_route_from_dest(
    int *route, 
    int *route_from_dest, 
    int *number_point_in_route)
    {
    int current_point = 0;
    int current_element = 0;
    current_point = DEST_POINT;
    while(current_point != START_POINT){
        route[current_element] = current_point;
        current_point = route[current_point];
        current_element++;
    }
    route_from_dest[current_element] = START_POINT;
    *number_point_in_route = current_element;
}

void print_result(
    int number_point_in_route, 
    int shortest_dist_start2dest, 
    int *route_from_dest)
    {
    printf("出発地から目的地までの最短経路\n");
    for(int i = number_point_in_route; i>=0; i--){
        printf("%d,", route_from_dest[i]);
    }
    printf("\n出発地から目的地までの最短距離=%d", shortest_dist_start2dest);
}

void dijkstra(
    int *route, 
    int *shortest_dist_from_start,
    bool *fixed_point, 
    int *shortest_dist_start2dest,
    int *route_from_dest, 
    int *number_point_in_route)
    {
        int shorter_point=0;
        while(true){
            int current_point=0;
            int unfixed_point;
    
            get_unfixed_point(&current_point,fixed_point, &unfixed_point);
            printf("fixed_point=\n");
            for(int i=0;i<N;i++){
                printf("%d\n",fixed_point[i]);
            }
            if(all_point_fixed(&current_point)){
                break;
            }
            else{
                search_shorter_point(current_point, fixed_point, shortest_dist_from_start,&shorter_point);
                }
            
            bool fixed_point_out[N];
            for(int i=0;i<N;i++){
                fixed_point_out[i] = fixed_point[i];
            }
             
            fix_current_point(current_point, fixed_point, fixed_point_out);
            int shortest_dist_from_start_out[N];
            int route_out[N];
            update_shortest_dist(current_point, fixed_point_out, route, shortest_dist_from_start,shortest_dist_from_start_out,route_out);
            
        }
    get_shortest_dist_start2dest(shortest_dist_from_start,shortest_dist_start2dest);
    get_route_from_dest(route, route_from_dest, number_point_in_route);
}

