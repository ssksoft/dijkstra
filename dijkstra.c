#include <stdio.h>
#include <stdbool.h>

#define INF 100000
#define N 7
#define START_POINT 1
#define DIST_POINT 3
#define INIT_ROUTE -1

int distance[N][N]={
    {0,2,8,4,-1,-1,-1},
    {2,0,-1,-1,3,-1,-1},
    {8,-1,0,-1,2,3,-1},
    {4,-1,-1,0,-1,8,-1},
    {-1,3,2,-1,0,-1,9},
    {-1,-1,3,8,-1,0,3},
    {-1,-1,-1,-1,9,3,0}
    };


void init(int *route, int *shortest_dist_from_start, bool *fixed_point){
    for(int i=0;i<N;i++){
        route[i] = INIT_ROUTE;
        shortest_dist_from_start[i] = INF;
        fixed_point[i] = false;
    }
}

bool is_unfixed_point(bool current_fixed_point){
    if(current_fixed_point==false){
        return true;
    }
    else{
        return false;    
    }
    
}

void get_unfixed_point(int *current_point, bool *fixed_point){
    while(*current_point<N){
        if(is_unfixed_point(fixed_point[*current_point])){
            break;
        }
        else{
            // donothing
        }
        *current_point +=1;
    }
}

bool all_point_fixed(int *current_point){
    if(*current_point==N){
        return true;
    }
    else{
        return false;    
    }
    
}

bool is_shorter(int *shortest_dist_from_start_j, int *shortest_dist_from_start_i){
    if(*shortest_dist_from_start_j < *shortest_dist_from_start_i){
        return true;
    }
    else{
        return false;
    }
}

bool new_dist_is_shorter(int new_dist, int *shortest_dist_from_start, int *destination){
    return new_dist < shortest_dist_from_start[*destination];
}

void search_shorter_point(int *current_point, bool *fixed_point, int *shortest_dist_from_start){
    for(int search_index=*current_point+1; search_index<N; search_index++){
        if(is_unfixed_point(*fixed_point) && is_shorter(&shortest_dist_from_start[search_index], &shortest_dist_from_start[*current_point])){
            *current_point = search_index;
        }
        else{
            // donothing
        }
    }
}

void fix_current_point(int *current_point, bool *fixed_point){
    fixed_point[*current_point] = true;
}

bool is_next_point(int *current_point, int destination){
    return distance[*current_point][destination] >0;
}



void update_distance(int new_dist, int *shortest_dist_from_start, int *destination, int *route, int *current_point){
    if(new_dist_is_shorter(new_dist, shortest_dist_from_start, destination)){
        shortest_dist_from_start[*destination] = new_dist;
        route[*destination] = *current_point;
    }
}

void update_shortest_dist(int *current_point, bool *fixed_point, int *route, int *shortest_dist_from_start){
    int new_dist = 0;
    for(int destination=0; destination< N; destination++){
        if(is_next_point(current_point, destination) && is_unfixed_point(&destination)){
            new_dist = *shortest_dist_from_start + distance[*current_point][destination];
            update_distance(new_dist, shortest_dist_from_start, &destination, route, current_point);
        
        }
    }
}

void dijkstra(int *route, int *shortest_dist_from_start, bool *fixed_point){
    while(true){
        int *current_point=0;
        get_unfixed_point(current_point,fixed_point);
        if(all_point_fixed(current_point)){
            break;
        }
        else{
            search_shorter_point(current_point, fixed_point, shortest_dist_from_start);
            }
        
        fix_current_point(current_point, fixed_point);

        update_shortest_dist(current_point, fixed_point, route, shortest_dist_from_start);
        
    }
}

int main(void){

    int route[N];
    int shortest_dist_from_start[N];
    bool fixed_point[N];
   
    init(route, shortest_dist_from_start, fixed_point);
    shortest_dist_from_start[START_POINT] = 0;
    dijkstra(route, shortest_dist_from_start, fixed_point);
    
    
}



