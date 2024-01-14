#include <cmath>
#include<iostream>

float map(float value, float fromMin, float fromMax, float toMin, float toMax)
{
    return ((value - fromMin) * (toMax - toMin)) / (fromMax - fromMin) + toMin;
}

void normalTo24bitNormalMap(char exercise, float x, float y, float z)
{
    std::cout << exercise << ".) [" 
              << std::round(map(x, -1.0f, 1.0f, 0.0f, 255.0f)) << ", "
              << std::round(map(y, -1.0f, 1.0f, 0.0f, 255.0f)) << ", "
              << std::round(map(z, -1.0f, 1.0f, 0.0f, 255.0f)) << "]" << std::endl;
}

int main()
{
    // a.) [0, 128, 128]
    normalTo24bitNormalMap('a', -1.0f, 0.0f, 0.0f);
    
    // b.) [162, 59, 230]
    normalTo24bitNormalMap('b', 0.267f, -0.535f, 0.805f);
    
    // c.) [128, 128, 255]
    normalTo24bitNormalMap('c', 0.0f, 0.0f, 1.0f);
    
    // d.) [128, 237, 193]
    normalTo24bitNormalMap('d', 0.0f, 0.857f, 0.514f);
    
    return 0;
}
