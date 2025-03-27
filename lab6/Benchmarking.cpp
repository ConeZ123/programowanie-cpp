#include <string>
#include <chrono>
#include <iostream>
#include <vector>
#include <list>

class TimeMeasurement
{
	std::string name;
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	
public:
	TimeMeasurement(std::string _name) : name(_name) {
		start = std::chrono::high_resolution_clock::now();
	}
	
	~TimeMeasurement() {
		std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;
		std::cout << name << ": " << duration.count() << " sec" << std::endl;
	}
};

int main() {
    const int N = 100000;

    // Dodawanie na początek
	{
        TimeMeasurement t("Dodawanie na początek vector");
        std::vector<int> vec;
        for (int i = 0; i < N; i++) {
            vec.insert(vec.begin(), 123456);
        }
    }

    {
        TimeMeasurement t("Dodawanie na początek list");
        std::list<int> lst;
        for (int i = 0; i < N; i++) {
            lst.insert(lst.begin(), 123456);
        }
    }

    // Cache friendliness

    {
        TimeMeasurement t("Sumowanie elementów vector");
        std::vector<int> vec;
        vec.reserve(N);

        for (int i =0; i < N; i++) {
            vec.push_back(i);
        }

        long long sum = 0;
        for (int val : vec) {
            sum += val;
        }
        std::cout << "Suma vector: " << sum << std::endl;
    }

    {
        TimeMeasurement t("Sumowanie elementów list");
        std::list<int> lst;
        for (int i = 0; i < N; i++) {
            lst.push_back(i);
        }

        long long sum = 0;
        for (int val : lst) {
            sum +=val;
        }
        std::cout << "Suma list: " << sum << std::endl;
    }

    return 0;
}