#include <iostream>
#include <cstdlib>
#include <chrono>
//#include <cstdint>
int* randArray(int rar[], int len) //pseudo-rand
{
    std::srand(time(0));
    for(auto i = 0; i < len; i++)
    {
        rar[i] = std::rand()%len;
    }
    return rar;
}
int* sortInc(int iar[], int len)
{
    if(len == 1) 
        return iar;
    int maxIndex = 0;
    for(int i = 1; i < len; i++) {
        if(iar[i] > iar[maxIndex])
            maxIndex = i;
    }
    int tmp = iar[len-1];
    iar[len-1] = iar[maxIndex];
    iar[maxIndex] = tmp;
    return(sortInc(iar, len-1));
}

int linearSearch(int iar[],int len, int key)
{
    for(int i = 0; i < len; i++)
    {
        if(iar[i] == key)
            return i;
    }
    return -1;
}

int binary_search(int iar[], int len, int key)
{
    int right = len-1, left = 0;
    while(left <= right)
    {
        int middle = left + (right-left)/2;
        if(iar[middle] == key)
            return middle;
        else if(iar[middle] < key)
            left = middle+1;
        else
            right = middle-1;   
    }
    return -1;
}

int main()
{
    //generating data:
    //Tstart
    auto start = std::chrono::high_resolution_clock::now(); 
    //
    int startArray[50000] = {0};
    int len = 50000;
    randArray(startArray, len);
    //sorting/prep:
    sortInc(startArray, len);
    int rand = std::rand()%len;
    int index1 = -1, index2 = -1;
    //Tstop
    auto stop = std::chrono::high_resolution_clock::now();
    auto T_U = std::chrono::duration_cast< std::chrono::nanoseconds>( 
        stop - start);
    //
    //linearsearch:
    //T_u_processingStart
    start = std::chrono::high_resolution_clock::now();
    //

    index1 = linearSearch(startArray, len, rand);
    //Tstop
    stop = std::chrono::high_resolution_clock::now();
    auto T_processing_unoptimized = std::chrono::duration_cast< std::chrono::nanoseconds>( 
        stop - start);
    auto T_unoptimized = T_U + T_processing_unoptimized;
    //
    //binary_search:
    //TStart
    start = std::chrono::high_resolution_clock::now();
    //
    index2 = binary_search(startArray, len, rand);
    //Tstop
    stop = std::chrono::high_resolution_clock::now();
    auto T_processing_optimized = std::chrono::duration_cast< std::chrono::nanoseconds>( 
        stop - start);
    auto T_optimized = T_U + T_processing_optimized;
    //
    std::cout << "(in nanoseconds)" << std::endl;
    std::cout << "\nT_processing_unop = " << T_processing_unoptimized.count() << ", T_unop = " << T_unoptimized.count() << std::endl;
    std::cout << "\nT_processing_opti = " << T_processing_optimized.count() << ", T_opti = " << T_optimized.count() << std::endl;
    std::cout << "\nlinear search index = " << index1 << 
        ", and bsearch index = " << index2 << std::endl;
    return(0);
}