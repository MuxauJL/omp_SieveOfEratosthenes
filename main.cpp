#include <vector>
#include <iostream>
#include <omp.h>

int main() {
	constexpr size_t n = 100000000;
	std::vector<bool> numbers(n, true);
	for (auto num_threads : { 1,2,3,4 }) {
		double start = omp_get_wtime();
#pragma omp parallel for num_threads(num_threads)
		for (int i = 2; i < numbers.size(); ++i) {
			if (!numbers[i])
				continue;
			for (int j = 2*i; j < n; j += i)
				numbers[j] = false;
		}
		double end = omp_get_wtime();
		std::cout << "Threads count: " << num_threads << " time: " << end - start << '\n';


		/*for (int i = 0; i < numbers.size(); ++i)
			if (numbers[i])
				std::cout << i << ' ';*/
	}
	system("pause");
	return 0;
}