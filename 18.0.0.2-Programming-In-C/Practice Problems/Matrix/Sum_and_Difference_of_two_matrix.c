#include <stdio.h>
#include <conio.h>

int main(){
	int row,column,i,j;
	printf("Enter the row: ");
	scanf("%d", &row);
	printf("Enter the column: ");
	scanf("%d", &column);
	
	int matrix1[row][column];
	int matrix2[row][column];
	int sum[row][column];
	int difference[row][column];
	
	// matrix 1 ka inputwa
	printf("Entering the Matrix 1 : \n");
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			scanf("%d", &matrix1[i][j]);
		}
	}
	
	// matrix 2 ka inputwa
	printf("Entering the Matrix 2 : \n");
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			scanf("%d", &matrix2[i][j]);
		}
	}
	
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			sum[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	}
	
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			difference[i][j] = matrix1[i][j] - matrix2[i][j];
		}
	}
	
	printf("Entering the Sum : \n");
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			printf("%d ", sum[i][j]);
		}
		printf("\n");
	}
	
	printf("Entering the Difference : \n");
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			printf("%d ", difference[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}