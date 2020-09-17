/******************************************************************************
Roman Ts., K-23, https://github.com/zork0/CPUtest/
*******************************************************************************/
#include <chrono> 
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <typeinfo>
#include <typeindex>
#include <deque>
using namespace std; 
using namespace std::chrono;

int testing_times = 10; // number of tests to find the fastest attempt
int iterations = 10000; // inner loop for 3 simple opeations for each iteration 
long max_speed;
std::deque<long> results;

template <typename T>
void addition(T a, T b, T c)
{
    for (int i=0; i<iterations; i++)  
    {
        a = b + c;
        b = c + a;
        c = a + b;
    }
}

template <typename T>
void substracting(T a, T b, T c)
{
    for (int i=0; i<iterations; i++)  
    {
        a = b - c;
        b = c - a;
        c = a - b;
    }
}

template <typename T>
void multiplication(T a, T b, T c)
{
    for (int i=0; i<iterations;i++)  
    {
        a = b * c;
        b = c * a;
        c = a * b;
    }
}

template <typename T>
void division(T a, T b, T c)
{
    for (int i=1; i<=iterations;i++)  
    {
        a = i / b;
        c = i / a;
        b = i / c;
    }
}

template <typename T>
double operation_test(int f, T a, T b, T c)
{
    /* f - number of particular function from (*functptr). 
    Make sure that there is a function and a sign - array signs[] from type_testing() - for each number f */
    
    void (*functptr[])(T, T, T) = {addition, substracting, multiplication, division};
    
    double list[testing_times];
    for (int i=0; i<testing_times; i++)  
    {
        auto start = high_resolution_clock::now();
        
        (*functptr[f])(a, b, c);
        
        auto stop = high_resolution_clock::now(); 
        auto dur = stop - start;
        auto f_secs = std::chrono::duration_cast<std::chrono::duration<double>>(dur);
        list[i] = f_secs.count();
    }
    return *std::min_element(list, list+testing_times);
}

template <typename T>
void type_testing(T a, T b, T c, string t_name, bool print=false)
{
    string signs[4] = {"+", "-", "*", "/"};
    
    for(int f = 0; f < 4; ++f) 
        {
            if (print) { 
                /* show results */
                long first = results.front();
                results.pop_front();
                string first_result = std::to_string(first/1000000) + "M";
                int proc = 100*first/::max_speed;
                std::string s(proc/2, 'X');
                cout << left << setw(5) << signs[f] << setw(10) << t_name << setw(10) 
                << first_result << std::scientific << setw(58) << s << setw(8) << std::to_string(proc) + "%" << endl;
            } else {
                /* testing and storing data in global deque "results" */
                double t = operation_test(f, a, b, c);
                long speed = 1/t * iterations * 3;
                results.push_back(speed);
                if (speed > max_speed) {
                    ::max_speed = speed;
                }
            }
        }
}

void general_testing(bool print=false) 
{
    /* Variables for each type */
    int a = 1; long l_a = 1; float f_a = 1; double d_a = 1; char c_a = 1;
    int b = 1; long l_b = 1; float f_b = 1; double d_b = 1; char c_b = 1;
    int c = 1; long l_c = 1; float f_c = 1; double d_c = 1; char c_c = 1;
    
    type_testing(a, b, c, "int", print);
    type_testing(l_a, l_b, l_c, "long", print);
    type_testing(f_a, f_b, f_c, "float", print);
    type_testing(d_a, d_b, d_c, "double", print);
    type_testing(c_a, c_b, c_c, "char", print);
    if (not print) {
        general_testing(true); // recursion to show results from global deque
    }
}

int main()
{
    general_testing();
    return 0; 
}
