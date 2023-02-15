#include <iostream>
#include <iomanip>
#include <vector>

void explore_vector(size_t size, std::vector<int>& v)
{
	auto cap = v.capacity();

	std::cout << "Initial size: " << v.size() << ", capacity: " << cap << std::endl;

    std::cout << "When there is not enough memory in the vector capacity changes:" << std::endl
    	<< "Size:       Capacity:   Ratio:" << std::endl << std::left;
    while (v.size() < size)
    {
    	v.push_back(0);
    	if (v.capacity() > cap)
    	{
    		std::cout << std::setw(12) << v.size()
                      << std::setw(12) << v.capacity()
                      << std::setw(12) << v.capacity() / static_cast < double > (cap) << std::endl;
            cap = v.capacity();
    	}
    }
    std::cout << std::endl << "Final size: " << v.size() << ", capacity: " << v.capacity() << std::endl << std::endl;
}

int main()
{
	size_t size = 1000;
    std::vector<int> v;
    explore_vector(size, v);

    v.clear();
    v.shrink_to_fit();
    v.reserve(50);
    explore_vector(size, v);

    v.clear();
    v.shrink_to_fit();
    //v.reserve(1e+6);
    size_t size_big = 1e+10;
    explore_vector(size_big, v);
}

/*
I've got the results:

	Initial size: 0, capacity: 0
	When there is not enough memory in the vector capacity changes:
	Size:       Capacity:   Ratio:
	1           1           inf
	2           2           2
	3           4           2
	5           8           2
	9           16          2
	17          32          2
	33          64          2
	65          128         2
	129         256         2
	257         512         2
	513         1024        2

	Final size: 1000, capacity: 1024

	Initial size: 0, capacity: 50
	When there is not enough memory in the vector capacity changes:
	Size:       Capacity:   Ratio:
	51          100         2
	101         200         2
	201         400         2
	401         800         2
	801         1600        2

	Final size: 1000, capacity: 1600

Additional exploration. The first time:

	Initial size: 0, capacity: 1000000
	When there is not enough memory in the vector capacity changes:
	Size:       Capacity:   Ratio:
	1000001     2000000     2
	2000001     4000000     2
	4000001     8000000     2
	8000001     16000000    2
	16000001    32000000    2
	32000001    64000000    2
	64000001    128000000   2
	128000001   256000000   2
	256000001   512000000   2
	512000001   1024000000  2
	terminate called after throwing an instance of 'std::bad_alloc'
	  what():  std::bad_alloc

The second time:

	Initial size: 0, capacity: 0
	When there is not enough memory in the vector capacity changes:
	Size:       Capacity:   Ratio:
	1           1           inf
	2           2           2
	3           4           2
	5           8           2
	9           16          2
	17          32          2
	33          64          2
	65          128         2
	129         256         2
	257         512         2
	513         1024        2
	1025        2048        2
	2049        4096        2
	4097        8192        2
	8193        16384       2
	16385       32768       2
	32769       65536       2
	65537       131072      2
	131073      262144      2
	262145      524288      2
	524289      1048576     2
	1048577     2097152     2
	2097153     4194304     2
	4194305     8388608     2
	8388609     16777216    2
	16777217    33554432    2
	33554433    67108864    2
	67108865    134217728   2
	134217729   268435456   2
	268435457   536870912   2
	536870913   1073741824  2
	terminate called after throwing an instance of 'std::bad_alloc'
	  what():  std::bad_alloc
*/