#include <stdio.h>
#include <string.h>


int pointers()
{
  int f = 2;

  int *ptr = &f; //Declares a new var pointer named ptr pointing to address(&) of f;

  printf("%i\n", *ptr);

  printf("%p\n", ptr);

  int arr[10] = { 1,2,3,4,5,6,7,8,9,10};

  int *ptr2 = &arr[0];

  for (int i = 0; i < 10; i++) {
    printf("%i\n", *ptr2);
    ptr2++;
  }
}


 int main() {
  double weight;
  int x;
  int *n;
  char s = 3;
  x = 3;
  n = &x;
  int arr[] = { 3,45,5,4,2 };

  int matrix[][3] = {{3, 4, 56}, {3, 5, 56}, {4, 3, 5}};

  char stringArr[5] = "Hed";

  printf("%s\n", stringArr);

  int arr2[3];

  char name[1];

  strcpy(stringArr, name); //this will cause overflow as char stringArr gets defined a length when first declared

  int matrixSize = strlen(stringArr);
  int actualStrLength = sizeof(matrixSize);
  printf("Matrix size %d\n", actualStrLength);
  int sizeofDef = sizeof(matrix); //sizeof declares how much memory it occupies
  printf("%i\n", sizeofDef);

  printf("-------------------------\n");
  for(int i = 0; i < sizeof(matrix) / sizeof(matrix[0]); i++) {
    for ( int j = 0; j < sizeof(matrix[0]) / sizeof(int); j ++) {
      printf("%d\n", matrix[i][j]);
    }
  }


  int h = sizeof(arr);

  int len = sizeof(arr) / sizeof(int);

  printf("Size is %d bytes\n", h);
  printf("Len is %d bytes\n", len);

  // switch(x) {
  //   case 1:
  //     printf("Your weight is blal %d\n", x);
  //     break;
  //   default:
  //     printf("Woot planet");
  // }

  pointers();
}
