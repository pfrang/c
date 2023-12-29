#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>

int compare(char *s1, char *s2){
	int flag = 0;
	while(*s1 != '\0' || *s2 == '\0'){
		if(*s1 == *s2){
			s1++;
			s2++;
		}
		
		else if(
		(*s1 == '\0' && *s2 != '\0') 
		|| (*s1 != '\0' && *s2 == '\0') 
		|| (*s1 != *s2))
		{
			flag = 1;
			break;
		}
	}
	return flag;
}

int main(){
	char c[100];
	int i;
	
	// taking input from user
	//printf("Enter the string: ");
	//fgets(c, sizeof(c), stdin);
	//printf("Output: %s",c);
	
	// -------------------------------------------------------------------
	
	// How to find the length of the string
	int length = 0;
	while(c[length] != '\0'){
		length++;
	}
	int length_2 = strlen(c);
	//printf("Length: %d", length);
	
	// -------------------------------------------------------------------
	
	// How to reverse an string
	/*
	for(i = length; i>=0 ; i--){
		printf("%c ", c[i]);
	}
	printf("\n");
	*/
	
	// -------------------------------------------------------------------
	
	// How to compare the strings in the C [without built-in function]
	
	char s1[100],s2[100];
	// s1 = Rishav => 43
	// s2 = Rishav
	/*
	printf("Enter the string1: ");
	fgets(s1, sizeof(s1), stdin);
	printf("Enter the string2: ");
	fgets(s2, sizeof(s2), stdin);
	*/
	/*
	ans = compare(s1,s2); // 1
	if(ans == 0){
		printf("Strings are equal");
	}
	else{
		printf("Not equal");
	}
	*/
	int ans = 0;
	
	//ans = strcmp(s1,s2);
	//printf("%d", ans);
	/*
	if(ans == 0){
		printf("Strings are equal");
	}
	else{
		printf("Not equal");
	}
	*/
	
	// --------------------------------------------------------
	 // How to  Concatenate two strings
	 
	 strcat(s1,s2);
	 //puts(s1);
	 //puts(s2);
	 //printf("%s", s1);
	 
	 // --------------------------------------------------------
	 printf("Enter the string1: ");
	//fgets(s1, sizeof(s1), stdin);
	scanf("%c", &s1);
	
	int LowerCase, UpperCase;
	
	LowerCase = (s1 == 'a' || s1 == 'e' || s1 == 'i' || s1 == 'o' || s1 == 'u');
	UpperCase = (s1 == 'A' || s1 == 'E' || s1 == 'I' || s1 == 'O' || s1 == 'U');
	
	/*
	if(LowerCase || UpperCase){
		printf("VOWEL HOON MAI");
	}
	
	else{
		printf("CONSONANT HOON MAI");
	}
	*/
	 
	// ---------------------------------------------------------------------
	
	
	return 0;
}
