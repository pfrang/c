#include <stdio.h>
#include <conio.h>

int main(){
	const int PI = 3.14;
	double radius, length, width;
	scanf("%lf %lf %lf", &radius, &length, &width);
	
	// area and perimeter of the circle
	double perimeter_circle = 2*(PI)*radius;
	double area_circle = PI*radius*radius; // 3.14
	
	// area and perimeter of the rectangle
	double perimeter_quad = 2*(length+width);
	double area_quad = (length * width); // 1
	
	if(area_quad > area_circle){
		printf("Area of Rectangle is big");	
	}
	else{
		printf("Gola bada hai");
	}
	
	return 0;
}