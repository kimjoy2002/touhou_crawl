#pragma once


#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <random>
#include "common.h"
void test_rand(const char* tt);


template <class T>
void rand_shuffle(T first, T last)
{
	//test_rand("rand_shuffle start");


	if(first  ==  last)
		return; 
	for(auto  it=first+1;  it != last; ++it) 
		iter_swap ( it ,  first  +  randA(it-first)); 
	//shuffle(que_.begin(),que_.end());


	
	//test_rand("rand_shuffle end");
}