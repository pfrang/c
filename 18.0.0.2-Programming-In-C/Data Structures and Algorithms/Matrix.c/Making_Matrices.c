#include <stdio.h>
#include <conio.h>

int main(){
	int row,column,i,j;
	printf("Enter the row: ");
	scanf("%d", &row);
	printf("Enter the column: ");
	scanf("%d", &column);
	int matrix[row][column];
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			scanf("%d", &matrix[i][j]);
		}
	}
	printf("Printing the matrix: \n");
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	return 0;
}
