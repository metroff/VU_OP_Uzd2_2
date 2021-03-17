#include "math.hpp"

// Skaičiuojamas vidurkis
double findMean(vector<int> &vec) {
    if (vec.empty())
        return 0;
    return std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
}

// Skaičiuojama mediana
double findMedian(vector<int> &vec) {
    if (vec.empty())
        return 0;
    sort(vec.begin(), vec.end());
    int index = vec.size() / 2;
    return (vec.size()%2==0) ? (double)(vec[index-1]+vec[index])/2.0 : (double)vec[index];
}