<h1 align="center">CPUtest - my first C++ program</h1>
<p align="center"><i>Simple C++ CPU tester to measure your processor speed in arithmetic operations per second.</i></p>
<p align="center"><i>Developed as a laboratory project for <a href="http://www.univ.kiev.ua/en">Taras Shevchenko National University of Kyiv</a></i></p>
<br>

# Problem

General conditions were given <a href="https://sites.google.com/site/byvkyiv1/arhiteom_stac/arhiteom_lab_01">here</a>.

Productivity of our computer systems directly depends on the processor. Processors are usually comparing by their speed which is measured in GHz (millions of operations per second). By operation, we mean simple logical and arithmetical operations. 

Of course, practical speed of our processors may differ depending on number of currently available threads of the processor, operating system settings, the task it performs, etc. So one of the way to measure actual processor speed is to test it, for example, on the nuber of particular arithmetic operations. But in this case we need to be careful to avoid compiler simplification because our computer system can just slip through some task that we've built for processor to test it.

# Solution

To compare our operating system I've developed a simple C++ terminal program that does different arithmetic operations (addition, subtracting, multiplication and division) on different data types (int, long, float, double, char). By default, the program 
perform `30000` simple operations and does this `10` times to get the fastest attempt.

To avoid simplification, the program works with three variables which is constantly changing their values depending on each other. Here how it works for addition:

```cpp
for (int i=0; i<iterations; i++)  
    {
        a = b + c;
        b = c + a;
        c = a + b;
    }
```

For the division I used a little modified method to avoid the `Floating point exception` which occurs when some number is divided by a rounded to zero integer.


```cpp
for (int i=3; i<=iterations+3;i++)  
    {
        a = i / b;
        c = i / a;
        b = i / c;
    }
```


# Usage

Compile the file and run it. Then you should get this message with results in your terminal:

```
+    int       363M      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX         99%     
-    int       363M      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX         99%     
*    int       282M      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                    77%     
/    int       94M       XXXXXXXXXXXXX                                             26%     
+    long      363M      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX        100%    
-    long      362M      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX         99%     
*    long      282M      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                    77%     
/    long      58M       XXXXXXXX                                                  16%     
+    float     282M      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                    77%     
-    float     282M      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                    77%     
*    float     231M      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                           63%     
/    float     133M      XXXXXXXXXXXXXXXXXX                                        36%     
+    double    282M      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                    77%     
-    double    282M      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                    77%     
*    double    231M      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                           63%     
/    double    97M       XXXXXXXXXXXXX                                             26%     
+    char      362M      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX         99%     
-    char      361M      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX         99%     
*    char      282M      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                    77%     
/    char      90M       XXXXXXXXXXXX                                              24%   
```
In the third column you can see the processor speed (in Millions of operations per second - simmilar to GHz).


# In addition

There was a recommendation to increase the number of operations in each cycle (like it's shown below). In this case other loop operations (like `i++` which I don't measure) would take a smaller portion of time than the execution of the loop body. After some tests I've found out that, indeed, average arithmetic operation speed in the previous compact version was less on 5-10%, which leads us to the fact that each set of additional (outer of the body) operations may cost us approximately a half of time of the tested arithmetic operation. However, the changes on some compilers were not visible.

```cpp
for (int i=0; i<iterations; i++)  
    {
        a = b + c;
        b = c + a;
        c = a + b;
        
        a = b + c;
        b = c + a;
        c = a + b;
        
        a = b + c;
        b = c + a;
        c = a + b;
    }
```
