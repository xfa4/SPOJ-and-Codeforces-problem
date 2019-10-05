#include <bits/stdc++.h> 
#include <iostream>
#include <stdio.h>
using namespace std;

int main () {
  int a, d, A[11], D[11]; //Atacantes, defensores y sus respectivos arrays
  while (true){
    scanf ("%d %d", &a, &d);
    if (a == 0 && d == 0) // The last line
      break;
    for (int i = 0; i < a; i++){
      scanf ("%d", &A[i]); // Save the positions in the arrays
    }
    for (int i = 0; i < d; i++){
      scanf ("%d", &D[i]); // Save the positions in the arrays
    }
    int n = sizeof(A)/sizeof(A[0]);
    sort(A,A+a);
    sort(D,D+d);
    if (A[0] >= D[1]){
      cout << "N\n";
    }
    else{
      cout << "Y\n";
    }
  }
}