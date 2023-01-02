// \begin{code}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// \end{code}
// \begin{code}
void swap(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}   
// \end{code}
// \begin{code}
void bubble_sort(int *xs, int xs_size)
{
   for (int i = xs_size - 1; i > 1; --i) {
       for (int j = 0; j < i; ++j) {
           if (xs[j] > xs[j + 1]) {
               swap(&xs[j], &xs[j + 1]);
           }
       }
   }
}
// \end{code}
// \begin{code}
#define MAX_X_SIZE 100

void generate_n_numbers(int *xs, int n)
{
    for (int i = 0; i < n; ++i) {
        xs[i] = rand() % MAX_X_SIZE;
    }
}
// \end{code}
// \begin{code}
// 1 2 3 5 4 6
// ^ ^ ascending
// 1 2 3 5 4 6
//   ^ ^ ascending
// 1 2 3 5 4 6
//     ^ ^ ascending
// 1 2 3 5 4 6
//       ^ ^ DESCENDNIG!!!
bool is_sorted(int *xs, int n)
{
    for (int i = 0; i < n - 1; ++i) {
        if (xs[i] > xs[i + 1]) {
            return false;
        }
    }
    return true;
}
int main(){}
// \end{code}
