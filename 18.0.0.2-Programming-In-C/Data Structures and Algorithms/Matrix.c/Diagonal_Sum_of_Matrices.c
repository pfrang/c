#include <stdio.h>
#include <conio.h>

int main(){
	int row,column,i,j;
	
	printf("Enter the row: ");
	scanf("%d", &row);
	printf("Enter the column: ");
	scanf("%d", &column);
	
	int matrix[row][column];
	
	int sum_of_diagonal = 0;
	
	if(row == column){
		//input le rha
		for(i=0;i<row;i++){
			for(j=0;j<column;j++){
				scanf("%d", &matrix[i][j]);
			}
		}
		
		// output de rha
		for(i=0;i<row;i++){
			for(j=0;j<column;j++){
				printf("%d ", matrix[i][j]);
			}
			printf("\n");
		}
		
		// sum nikaal rha
		for(i = 0 ; i<row; i++){
			sum_of_diagonal = sum_of_diagonal+matrix[i][i];
		}
		
		printf("Diagonal SUM: %d", sum_of_diagonal);
	}
	else{
		printf("CHALA JAA BSDK");
	}
	return 0;	
}
