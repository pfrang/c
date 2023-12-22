#include <stdio.h>

//prototype func
struct Test thisIsAFunctionReturningTheTestStruct(struct Test, struct Test*);
void pointerStructure(void);
struct Table
{
  int length;
  int width;
  int height;
  char color[20];
};

int main()
{
  int table1Length = 24;
  int table1Width = 24;
  int table1Height = 20;
  char table1Color[20] = "Dark Brown";

  int table2Length = 42;
  int table2Width = 18;
  int table2Height = 32;
  char table2Color[20] = "Matte Black";

  // Write your code below
  struct Table table1 = {
      .length = table1Length,
      .height = table1Height,
      .width = table1Width,
  };

  table1.length = 2;
  pointerStructure();
};

struct Person
{
  char name[40];
  int age;
};

struct Test
{
  int age;
};

void pointerStructure()
{
  struct Person person1 = {"Martin", 57};
  struct Person person2 = {"Michelle", 27};
  // Write your code below
  struct Person* person1Pointer = &person1;
  struct Person* person2Pointer = &person2;

  (*person1Pointer).age = (*person1Pointer).age + 1;
  person2Pointer->age = person2Pointer->age + 10; //To ways of achieving the same, dereferencing the pointer
  printf("Hello my name is %s and I am %d years old.\n", person1.name, person1.age);
  printf("Hello my name is %s and I am %d years old.\n", person2.name, person2.age);
  struct Test test1 = {30}; //setting age to be 30 here
  struct Test test2 = thisIsAFunctionReturningTheTestStruct(test1, &test1); //assigned to new struct test2
  printf("Age is changed to + 10 globally here %i\n", test1.age);
}



//Modifying a struct within function only changes local but passing the adress and assigning a pointer modifies original struct
struct Test thisIsAFunctionReturningTheTestStruct(struct Test input, struct Test* inputPointer)
{
  input.age = 25;
  inputPointer->age = inputPointer->age + 10; //here updates test1
  printf("Age is changed to 25 locally here %i\n", input.age);
  return input;
}
