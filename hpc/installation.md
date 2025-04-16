OpenMP is a library for executing C, C++ and Fortran code on multiple processors at the same time. This makes your code much faster if it uses a lot of loops, and utilizes the full power of your CPU. In case you just want to see the code, the link is here.

Setting up OpenMP on Ubuntu / Linux
I am not entirely sure how this works on other platforms. It is near-impossible on Mac, there are some weird setup instructions for Windows, but on Linux and Ubuntu it is really easy.

Run sudo apt-get install libomp-dev in your Terminal.
Create a C++ Project , and title it HelloOpenMP .
Select your project, and go to the Properties dialog.
Go to C/C++ Build -> Settings .
Select GCC C++ Compiler / Miscellaneous .
In the Other flags input, add on -fopenmp .
Select GCC C++ Linker / Libraries .
In the Libraries (-l) field, click the add button and type in gomp.
Afterwards, your properties should look something like this:

Left: compiler flags, Right: linker libraries
That’s it!

Using OpenMP
Say you have a awesome program that prints out a list of 10 numbers:

#include <stdio.h>
int main(){
for(int i=0;i<10;i++){
printf("%i\n",i);
}
return 0;
}
This outputs something like:

0
1
2
3
4
5
6
7
8
9
Now, lets OpenMPinize it!

#include <stdio.h>
int main(){
#pragma omp parallel for
for(int i=0;i<10;i++){
printf("%i\n",i);
}
return 0;
}
This outputs something like:

4
7
6
9
0
1
8
2
3
5
The numbers are out of order because each iteration in the loop is executed at a slightly different time, in parallel.

Wait, what? “How could it be that easy?” I hear you say. It actually is this easy, if your compiler supports OpenMP. In general, GCC with a recent version should be fine. And if your compiler doesn’t support it — the pragmas are ignored! And your code falls back to single-core sluggishness. So OpenMP is completely compatible with any machine.

The source code can be found here
