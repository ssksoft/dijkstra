#include <stdio.h>
#include <stdbool.h>
#include <testRunner.h>
#include "dijkstra.h"

static unsigned int test_init(void);
static unsigned int test_is_unfixed_point(void);
static unsigned int test_get_unfixed_point(void);
static unsigned int test_all_point_fixed(void);
static unsigned int test_is_shorter(void);
static unsigned int test_new_dist_is_shorter(void);
static unsigned int test_search_shorter_point(void);
static unsigned int test_fix_current_point(void);
static unsigned int test_is_next_point(void);
static unsigned int test_update_distance(void);
static unsigned int test_update_shortest_dist(void);


int main(void){
	testRunner(test_init);
	testRunner(test_is_unfixed_point);
	testRunner(test_get_unfixed_point);
	testRunner(test_all_point_fixed);
	testRunner(test_is_shorter);
	testRunner(test_new_dist_is_shorter);
	testRunner(test_search_shorter_point);
	testRunner(test_fix_current_point);
	testRunner(test_is_next_point);
	testRunner(test_update_distance);
	testRunner(test_update_shortest_dist);
	return 0;
}

static unsigned int test_init(void)
{
	unsigned int err;
	int expect;

	int route[N];
	int shortest_dist_from_start[N];
	bool fixed_point[N];
	int shortest_dist_start2dest;
	int number_point_in_route;

	// Test case 1_route
	expect = INIT_ROUTE;
	err = init(route, shortest_dist_from_start, fixed_point, &shortest_dist_start2dest,&number_point_in_route);
	
	for(int i=0;i<N;i++){
		TEST_ASSERT_EQUALS(route[i], expect);
	}
	TEST_ASSERT_EQUALS(err,0);
	

	// Test case 2_shortest_dist_from_start
	
	err = init(route, shortest_dist_from_start, fixed_point, &shortest_dist_start2dest,&number_point_in_route); 
	
	for(int i=0;i<N;i++){
		if(i == START_POINT){
			expect = 0;
		}
		else{
			expect = INF;
		}
		TEST_ASSERT_EQUALS(shortest_dist_from_start[i],expect);
		// STERT_POINTのみ期待値0
	}
	TEST_ASSERT_EQUALS(err,0);

	// Test case 3_fixed_point
	err = init(route, shortest_dist_from_start, fixed_point, &shortest_dist_start2dest,&number_point_in_route); 
	
	for(int i=0;i<N;i++){
		bool expect_bool = false;
		TEST_ASSERT_EQUALS(fixed_point[i],expect_bool);
	}
	TEST_ASSERT_EQUALS(err,0);

	// Test case 4 shortest_dist_start2dest
	err = init(route, shortest_dist_from_start, fixed_point, &shortest_dist_start2dest,&number_point_in_route);
	expect = INF;
	TEST_ASSERT_EQUALS(shortest_dist_start2dest,expect);
	TEST_ASSERT_EQUALS(err,0);

	// Test case 5 number_point_in_route
	err = init(route, shortest_dist_from_start, fixed_point, &shortest_dist_start2dest,&number_point_in_route);
	expect = 0;
	TEST_ASSERT_EQUALS(number_point_in_route,expect);
	TEST_ASSERT_EQUALS(err,0);

	return 0;
}

static unsigned int test_is_unfixed_point(void)
{
	//
	bool return_val;
	bool expect;
	bool current_fixed_point;

	// test 1
	current_fixed_point = false;
	return_val = is_unfixed_point(&current_fixed_point);
	expect = true;
	TEST_ASSERT_EQUALS(return_val,expect);
	
	// test 2
	current_fixed_point = true;
	return_val = is_unfixed_point(&current_fixed_point);
	expect = false;
	TEST_ASSERT_EQUALS(return_val,expect);

	return 0;
}

static unsigned int test_get_unfixed_point(void)
{
	unsigned int err;
	int expect;
	int current_point;
	bool fixed_point[N];
	int unfixed_point;

	current_point = 0;
	for(int i=0;i<N;i++){
		fixed_point[i] = false;
	}

	// test 1
	fixed_point[0] = true;
	fixed_point[2] = true;
	err = get_unfixed_point(&current_point, fixed_point, &unfixed_point);
	expect = 1;
	// printf("expect=%d, ans=%d\n", expect,unfixed_point);
	TEST_ASSERT_EQUALS(unfixed_point,expect);
	TEST_ASSERT_EQUALS(err,0);

	return 0;
}

static unsigned int test_all_point_fixed(void)
{
	int current_point;
	bool return_val;	
	bool expect;
	// test1
	current_point = 0;
	expect = false;
	return_val = all_point_fixed(&current_point);
	// printf("act=%d, exp=%d\n", return_val, expect);
	TEST_ASSERT_EQUALS(return_val, expect);

	// test2
	current_point = N;
	expect = true;
	return_val = all_point_fixed(&current_point);
	// printf("act=%d, exp=%d\n", return_val, expect);
	TEST_ASSERT_EQUALS(return_val, expect);
	return 0;
}

static unsigned int test_is_shorter(void)
{
	int shortest_dist_from_start_search;
	int shortest_dist_from_start_current;
	bool return_val;
	bool expect;

	// test1
	shortest_dist_from_start_search = 9;
	shortest_dist_from_start_current = 10;
	expect = true;
	return_val = is_shorter(shortest_dist_from_start_search, shortest_dist_from_start_current);
	TEST_ASSERT_EQUALS(return_val, expect)

	// test2
	shortest_dist_from_start_search = 10;
	shortest_dist_from_start_current = 10;
	expect = false;
	return_val = is_shorter(shortest_dist_from_start_search, shortest_dist_from_start_current);
	TEST_ASSERT_EQUALS(return_val, expect)

	// test3
	shortest_dist_from_start_search = 11;
	shortest_dist_from_start_current = 10;
	expect = false;
	return_val = is_shorter(shortest_dist_from_start_search, shortest_dist_from_start_current);
	TEST_ASSERT_EQUALS(return_val, expect)

	return 0;
}

static unsigned int test_new_dist_is_shorter(void){
	int new_dist;
	int shortest_dist_from_start[N];
	int destination;
	bool return_val;
	bool expect;

	for(int i=0;i<N;i++){
		shortest_dist_from_start[i] = 0;
	}

	// test1
	new_dist = 1;
	destination = 3;
	shortest_dist_from_start[destination]=2;
	
	expect = true;
	return_val = new_dist_is_shorter(new_dist, shortest_dist_from_start, destination);
	TEST_ASSERT_EQUALS(return_val, expect);
	
	// test2
	new_dist = 2;
	destination = 3;
	shortest_dist_from_start[destination]=2;
	expect = false;
	return_val = new_dist_is_shorter(new_dist, shortest_dist_from_start, destination);
	TEST_ASSERT_EQUALS(return_val, expect);

	// test3
	new_dist = 3;
	destination = 3;
	shortest_dist_from_start[destination]=2;
	expect = false;
	return_val = new_dist_is_shorter(new_dist, shortest_dist_from_start, destination);
	TEST_ASSERT_EQUALS(return_val, expect);	
	return 0;
}

static unsigned int test_search_shorter_point(void){
	int current_point;
	bool fixed_point[N];
	int shortest_dist_from_start[N];
	int shorter_point = 0;
	int expect = 0;
	unsigned int err = 0;

	for(int i=0;i<N;i++){
		fixed_point[i] = false;
		shortest_dist_from_start[i] = INF;
	}
	
	// test1
	current_point = 1;
	fixed_point[3] = true;
	shortest_dist_from_start[2] = 1;
	expect = 2;
	err = search_shorter_point(current_point, fixed_point,shortest_dist_from_start,&shorter_point);

	TEST_ASSERT_EQUALS(shorter_point,expect);
	TEST_ASSERT_EQUALS(err,0);

	return 0;
}

static unsigned int test_fix_current_point(void){
	int current_point;
	bool fixed_point_in[N];
	bool fixed_point_out[N];
	unsigned int err=0;
	bool expect;

	for(int i=0;i<N;i++){
		fixed_point_in[i] = false;
	}

	// test
	current_point = 1;
	err = fix_current_point(current_point, fixed_point_in, fixed_point_out);
	for(int i=0;i<N;i++){
		if(i==current_point){
			expect = true;
		}
		else{
			expect = false;
		}
		// printf("act=%d, exp=%d\n",fixed_point_out[i],expect);
		TEST_ASSERT_EQUALS(fixed_point_out[i], expect);
		TEST_ASSERT_EQUALS(err,0);
	}
	
	return 0;
}

static unsigned int test_is_next_point(void){
	int current_point = 0;
	int destination = 0;
	bool return_val = false;
	bool expect = false;

	// test1
	expect = false;
	current_point = 0;
	destination = 4;
	return_val = is_next_point(current_point,destination);
	TEST_ASSERT_EQUALS(return_val,expect);

	// test2
	expect = false;
	current_point = 1;
	destination = 1;
	return_val = is_next_point(current_point,destination);
	TEST_ASSERT_EQUALS(return_val,expect);

	// test3
	expect = true;
	current_point = 1;
	destination = 0;
	return_val = is_next_point(current_point,destination);
	TEST_ASSERT_EQUALS(return_val,expect);
	return 0;
}

static unsigned int test_update_distance(void){
	int new_dist;
	int shorter_point;
	int shortest_dist_from_start_in[N];
	int route_in[N];
	int current_point;
	int shortest_dist_from_start_out[N];
	int route_out[N];
	unsigned int err;
	int expect1;
	int expect2;

	for(int i=0;i<N;i++){
		shortest_dist_from_start_in[i] = 0;
		route_in[i] = INIT_ROUTE;
	}

	// test1
	new_dist = 1;
	shorter_point = 3;
	shortest_dist_from_start_in[shorter_point] = 4;
	current_point = 2;
	expect1 = new_dist;
	expect2 = current_point;
	err = update_distance(
		new_dist, shorter_point,
		shortest_dist_from_start_in, 
		route_in, current_point,
		shortest_dist_from_start_out, route_out);
	for(int i=0;i<N;i++){
		if(i==shorter_point){
			TEST_ASSERT_EQUALS(shortest_dist_from_start_out[i], expect1);
			TEST_ASSERT_EQUALS(route_out[i],expect2);
		}
		else{
			TEST_ASSERT_EQUALS(shortest_dist_from_start_out[i], shortest_dist_from_start_in[i]);
			TEST_ASSERT_EQUALS(route_out[i],route_in[i]);
		}
		
	}
	TEST_ASSERT_EQUALS(err,0);
	return 0;
}

static unsigned int test_update_shortest_dist(void){
	int current_point;
	bool fixed_point[N];
	int route[N];
	int shortest_dist_from_start[N];
	int route_out[N];
	int shortest_dist_from_start_out[N];
	
	int route_out_expect[N];
	int shortest_dist_from_start_out_expect[N];
	unsigned int err = 0;
	for(int i=0;i<N;i++){
		fixed_point[i] = false;
		route[i] = INIT_ROUTE;
		shortest_dist_from_start[i] = INF;
	}

	// test1
	current_point = 1;
	fixed_point[1] = true;
	shortest_dist_from_start[0] = 1;
	err = update_shortest_dist(current_point, fixed_point, route, shortest_dist_from_start, route_out,shortest_dist_from_start_out);
	route_out_expect[0] = 1;
	shortest_dist_from_start_out_expect[0] = 1;
	for(int i=0;i<N;i++){
		printf("route_out[%d]=%d\n",i,route_out[i]);
		printf("route_out_expect[%d]=%d\n",i,route_out_expect[i]);
		TEST_ASSERT_EQUALS(route_out[i],route_out_expect[i]);
		printf("shortest[%d]=%d\n",i,shortest_dist_from_start_out[i]);
		TEST_ASSERT_EQUALS(shortest_dist_from_start_out[i],shortest_dist_from_start_out_expect[i]);
	}
	TEST_ASSERT_EQUALS(err,0);
	
	return 0;
	
}