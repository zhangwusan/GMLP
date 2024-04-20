#include <iostream>
#include <chrono>
#include <vector>


#include "Gnumerical.hpp"
#include "gnarray.hpp"

using namespace std;
using namespace MLP;



int main() {
    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();


    GNumerical <double, 2, 3, 4> cal(2);
    cout<< cal.ndim() <<endl;
    cout<< cal.size() <<endl;
    

    
    // Stop measuring time
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    auto duration_seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    cout << "Time taken: " << duration.count() << " nanoseconds" << endl;
    cout << "Tiem taken: " << duration_seconds.count() << " seconds" << endl;
    return 0;
}







