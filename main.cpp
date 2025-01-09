#include <iostream>
#include <vector>
#include <thread>
#include <cmath>

using namespace std;

int main() {
    vector<int> primes;
}

class FindPrimes {
public:
    bool isPrime(int num) {
        if (num == 2) return true;
        if (num % 2 == 0) return false;
        if (num == 1) return false;
        for (int i = 3; i < sqrt(num); i+=2) {
            if (num % i == 0) return false;
        }
        return true;
    }

    void findPrimesInRangeWithThreads(int start, int end, int numThreads) {

    }
};
