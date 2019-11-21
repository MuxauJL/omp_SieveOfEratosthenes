#include <vector>
#include <iostream>
#include <omp.h>

int main() {
	constexpr size_t n = 1000000000;
	bool* prime_numbers = new bool[n];
	size_t max_idx = sqrt(n);
	for (size_t i = 0; i < n; ++i)
		prime_numbers[i] = true;
	for (auto num_threads : { 1,2,3,4 }) {
		double start = omp_get_wtime();
#pragma omp parallel for num_threads(num_threads) schedule(dynamic)
		for (int i = 2; i <= max_idx; ++i) {
			if (!prime_numbers[i])
				continue;
			for (int j = i * i; j < n; j += i)
				prime_numbers[j] = false;
		}
		double end = omp_get_wtime();
		std::cout << "Threads count: " << num_threads << " time: " << end - start << '\n';
	}
	delete[] prime_numbers;
	system("pause");
	return 0;
}