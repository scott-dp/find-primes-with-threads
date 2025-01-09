#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
#include <algorithm>
#include <mutex>

using namespace std;

class FindPrimes {
public:
    static vector<int> primes;
    static mutex primeMutex;

    static bool isPrime(int num) {
        if (num == 2) return true;
        if (num % 2 == 0) return false;
        if (num == 1) return false;
        for (int i = 3; i < sqrt(num); i+=2) {
            if (num % i == 0) return false;
        }
        return true;
    }

    static vector<int> getPrimesInRangeWithThreads(int start, int end, int numThreads) {
        vector<thread> threads;
        int delta = (end - start) / (numThreads);

        int threadNum = 0;
        for (int i = start; i <= end; i += delta) {
            threadNum++;
            int currentEnd = i+delta-1;
            if (threadNum == numThreads) {
                currentEnd = end;
                threads.emplace_back(findPrimeInRangeAndAppendToPrimeVector, i, currentEnd);
                break;
            }
            threads.emplace_back(findPrimeInRangeAndAppendToPrimeVector, i, currentEnd);
        }

        for(thread &thread : threads) {
            thread.join();
        }

        sortPrimes();

        return primes;
    }

    static void findPrimeInRangeAndAppendToPrimeVector(int start, int end) {
        for (int i = start; i <= end; i ++) {
            if (isPrime(i)) {
                lock_guard<mutex> lock(primeMutex);
                primes.push_back(i);
            }
        }
    }

    static void sortPrimes() {
        sort(primes.begin(), primes.end());
    }
};

vector<int> FindPrimes::primes;
mutex FindPrimes::primeMutex;

int main() {
    vector<int> primes;
    primes = FindPrimes::getPrimesInRangeWithThreads(1, 100, 6);

    for (int num : primes) {
        cout << num << endl;
    }
}
