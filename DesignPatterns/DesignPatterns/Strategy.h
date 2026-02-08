#pragma once
#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <random>

using Comparator = std::function<bool(int a, int b)>;
using Strategy  = std::function<void(std::vector<int>& input, Comparator comp)>;


class NumberContainer
{
public:
	NumberContainer(int amount)
	{
		numbers.reserve(amount);

		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(1, amount);

		numbers.begin();
		for (int i = 0; i < amount; i++)
			numbers.push_back(dist(rng));
	}


	void setStrategy(Strategy str, Comparator comp) {
		strategy   = str;
		comparator = comp;
	}

	void PrintSorted() {
		strategy(numbers, comparator);

		std::ranges::copy(numbers, std::ostream_iterator<int>(std::cout, " "));
	}

private:

	std::vector<int> numbers;

	Strategy strategy;
	Comparator comparator;
};





void PerformStrategy()
{
	NumberContainer container(9'999);

	Strategy STDsort =
		[](std::vector<int>& input, Comparator comp)
	{
		std::sort(input.begin(), input.end(), comp);
	};

	Strategy STABLEsort =
		[](std::vector<int>& input, Comparator comp)
	{
		std::stable_sort(input.begin(), input.end(), comp);
	};


	Comparator GT = [](int a, int b) { return a > b; };
	Comparator LT = [](int a, int b) { return a < b; };


	container.setStrategy(STDsort, GT);
	container.PrintSorted();

	system("PAUSE");
	container.setStrategy(STABLEsort, LT);
	container.PrintSorted();
}
