#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <list>
#include <forward_list>
#include <random>
#include <algorithm>
#include "timer/timer.cpp"

template <typename Conteiner>
auto time_measure_by_std_sort(Conteiner conteiner)
{
	Timer time {"start sort", std::cout};
	std::sort(conteiner.begin(), conteiner.end());
	time.stop();
	auto t = time.get_time();
	
	return t;
}

template <typename Conteiner>
auto time_measure_by_member(Conteiner conteiner)
{
	Timer time {"start sort", std::cout};
	conteiner.sort();
	time.stop();
	auto t = time.get_time();
	
	return t;	
}

template <typename Conteiner>
void fill_conteiner_by_random(Conteiner& conteiner, std::array<int, 100000> array)
{
	for (auto it = std::begin(array); it != std::end(array); ++it)
		conteiner.push_back(*it);
}

template <typename T>
void fill_conteiner_by_random(std::forward_list<T>& conteiner, std::array<int, 100000> array)
{	
	std::reverse(std::begin(array), std::end(array));
	for (auto it = std::begin(array); it != std::end(array); ++it)
		conteiner.push_front(*it);
}

auto test_result(std::vector< std::vector<double> > seria)
{
	std::vector<double> res;

	for (size_t j = 0; j < seria[0].size(); j++)
	{
		double sum = 0;
		for (size_t i = 0; i < seria.size(); i++)
		{
			sum += seria[i][j];
			std::cout << seria[i][j] << " ";
		}
		std::cout << std::endl << std::endl;
		res.push_back(sum / seria.size());
	}

	return res;
}

int main()
{
	std::uniform_int_distribution<int> distribution(0, 99);
	std::mt19937 engine; //  Mersenne twister MT19937

	std::array<int, 100000> array;
	for (auto& elem : array)
		elem = distribution(engine); //  Generate a uniform integral variate between 0 and 99.

	std::vector<int> vector;
	fill_conteiner_by_random< std::vector<int> > (vector, array);

	std::deque<int> deque;
	fill_conteiner_by_random< std::deque<int> > (deque, array);

	std::list<int> list;
	fill_conteiner_by_random< std::list<int> > (list, array);

	std::forward_list<int> forward_list;
	fill_conteiner_by_random<int> (forward_list, array);

	std::vector< std::vector<double> > seria(50);
	for (auto& current : seria)
	{
		// use std::sort

		current.push_back(time_measure_by_std_sort(array)); // #0

		current.push_back(time_measure_by_std_sort(vector)); // #1

		current.push_back(time_measure_by_std_sort(deque)); // #2

		// use member-function sort:

		current.push_back(time_measure_by_member(list)); // #3

		current.push_back(time_measure_by_member(forward_list)); // #4
	}

	auto result = test_result(seria);
	std::cout << std::endl << std::endl;
	for (auto& elem : result)
		std::cout << elem << " ";
}

/* 
Experiment results (100 measurements):
	1	0.029965	std::array
	2	0.052479	std::vector
	3	0.092292	std::deque
	4	0.103798	std::forward_list
	5	0.106558	std::list
   
More detailed:
	rating | conteiner 		  | average  | 50 measurements
	1 	   | std::array		  | 0.030260 | 0.024615 0.023260 0.025188 0.059442 0.023729 0.061627 0.023453 0.024722 0.029306 0.023782 0.027916 0.023992 0.027397 0.024445 0.024220 0.028451 0.024491 0.029661 0.023370 0.025368 0.024251 0.023831 0.060639 0.023266 0.025056 0.024061 0.024604 0.023334 0.050712 0.030485 0.024070 0.023816 0.046348 0.024506 0.026165 0.023046 0.129951 0.024991 0.023614 0.025393 0.023452 0.028126 0.028390 0.026059 0.024946 0.024825 0.023218 0.024124 0.024230 0.025051
	2	   | std::vector 	  | 0.056179 | 0.047953 0.045197 0.043428 0.047196 0.043544 0.043104 0.086278 0.043278 0.044161 0.043590 0.044041 0.046880 0.067750 0.044299 0.043618 0.047139 0.079569 0.070441 0.071992 0.044505 0.043417 0.043600 0.046653 0.076924 0.045661 0.073169 0.043938 0.044852 0.046067 0.077596 0.045396 0.044385 0.043982 0.044125 0.043668 0.049898 0.083725 0.043809 0.046598 0.047307 0.044614 0.080230 0.044855 0.045059 0.043141 0.045188 0.146186 0.047328 0.045232 0.184386
	3	   | std::deque		  | 0.088460 | 0.109051 0.078401 0.077504 0.076801 0.077637 0.078531 0.077908 0.100590 0.104135 0.077443 0.078692 0.076839 0.078015 0.102884 0.078156 0.077824 0.078484 0.076779 0.077472 0.097780 0.078304 0.078870 0.076864 0.078831 0.197069 0.080124 0.109659 0.078543 0.076725 0.077118 0.097968 0.079495 0.077660 0.081096 0.112710 0.111529 0.078294 0.109981 0.116324 0.083653 0.078335 0.077689 0.079490 0.106677 0.105915 0.077588 0.102762 0.077579 0.077435 0.077764
	4	   | std::forward_list| 0.091073 | 0.080535 0.083047 0.110747 0.103502 0.084793 0.100789 0.113118 0.083758 0.083442 0.105513 0.098956 0.110985 0.080155 0.084106 0.084511 0.112765 0.112437 0.178634 0.080853 0.084209 0.088384 0.119458 0.109428 0.085216 0.108828 0.080884 0.082178 0.082373 0.098991 0.080759 0.084307 0.080801 0.113864 0.082233 0.086433 0.082389 0.080577 0.084322 0.084393 0.084116 0.106656 0.105103 0.096667 0.082630 0.082892 0.107701 0.081177 0.136417 0.109164 0.081479
	5	   | std::list 		  | 0.095333 | 0.110179 0.075231 0.077913 0.208655 0.074713 0.081857 0.074709 0.101662 0.100356 0.077033 0.078883 0.077871 0.078545 0.096711 0.075265 0.078151 0.086973 0.077178 0.085544 0.103351 0.113049 0.080058 0.077746 0.081624 0.079622 0.077055 0.101602 0.074698 0.081337 0.079201 0.098983 0.075117 0.080190 0.079136 0.115229 0.116153 0.079336 0.137696 0.099937 0.101305 0.080682 0.077758 0.092639 0.102678 0.100760 0.078517 0.105754 0.080117 0.076182 0.108713
    
    
*/

