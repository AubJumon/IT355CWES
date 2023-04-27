

#include <stdio.h>
#include <string.h> // Include the string.h header for strlen()
#include <stdlib.h>

typedef struct{
    int value;
} Arithmetic;

Arithmetic* create_arithmetic(int val) // CWE-676: Use of potentially dangerous function 
{
    Arithmetic* a = malloc(sizeof(Arithmetic));
    a->value = val;
    return a;
}

int getValue(Arithmetic* a) // CWE-495: Private Data structure returned from Public Method
{
    return a->value;
}

int square(Arithmetic* a)
{
    return (a->value * a->value);
}

int cube(Arithmetic *a)
{
    return (a->value * a->value * a->value);
}

void delete(Arithmetic *a)
{
    free(a);
}

void functionWith1Argument(char a){
    printf("You have selected task %c", a);
}
int promptValue();
int power(int digit, int exponent);

int main() {
    char *input = (char*) malloc(sizeof(char) * 10);
    //char input[10]; //If you are going to 
    // Declare a character array with a size limit of 10 characters to prevent buffer overflow
    // CWE-457: Use of Uninitialized Variables 
    printf("Enter a character to determine which task to perform [a, b, c]: "); // CWE-134: Use of Externally-Controlled Format String 
    if (fgets(input, sizeof(input), stdin) == NULL) {
        /*
        In this section of code, the sizeof operator is being used on an array (input) 
        rather than a pointer type, so it is being used correctly. fgets() requires 
        the size of the buffer it is reading into as its second argument, and sizeof(input) 
        provides the size of the input array in bytes, which is the correct size to pass to fgets().

        CWE-467 applies when sizeof() is used on a pointer type, as the size returned by sizeof() 
        in that case is the size of the pointer, not the size of the pointed-to object. This can 
        lead to buffer overflows or other memory-related errors. However, in the above code, sizeof()
        is being used on an array, not a pointer type, so this CWE does not apply.
        */
        printf("Error reading input\n"); // CWE-134: Use of Externally-Controlled Format String 
        return 1;
    }
    input[strcspn(input, "\n")] = '\0'; //Use strcspn() to find the length of the 
    //input string and ensure that it is less than the size of the input buffer.
    //This will prevent switch() from accessing elements of the input array that are beyond the end of the string.()
    //CWE-125 (Out-of-bounds read) and CWE-787 (Out-of-bounds write) 
    /*
    This helps prevent CWE-126 (Buffer Over-read) and CWE-131 (Incorrect Calculation of 
    Buffer Size) by placing a terminator and by dynamically checking size with size of.
    This helps prevent CWE-170 (Improper Null Termination) by ensuring that the 
    input is properly null-terminated.
    NULL termination also helps with 
    */
    if (strlen(input) != 1) { // Check if the input is more than one character long
    /*
     If it's more than one character long, an error message is displayed and the program returns with an error code of 1. 
     This helps prevent CWE-127 (Buffer Under-read) by ensuring that only one character is read from the input.
    */
        printf("Invalid input\n"); // CWE-134: Use of Externally-Controlled Format String 
        return 1;
    }

    char task = input[0];
    /*
    This avoids direct manipulation of the input buffer and prevents CWE-468 by ensuring that 
    pointer arithmetic is not used to reduce the size of the input buffer.

    Note that strncpy() could also be used instead of char task = input[0]; to copy the 
    first character of input to task with a buffer size limit of 1, but since we only need 
    to copy one character, using char task = input[0]; is simpler and less error-prone.

    by specifying input[0] CWE-197: Numeric Truncation Error can be avoided.
    */

    functionWith1Argument(task);
    /*
        input is reduced to task to insure CWE-685: "Function call with incorrect number of arguments"
        is avoided for the above function. CWE-688: "Function Call With Incorrect Variable or Reference
        as Argument" is also avoided through the input validation.
    */

    switch (task) { // Check the first character of the input array
        case 'a':
            printf("Performing Task A\n");
                //divide 2 numbers
                int a = 3;
                int b = 7;
                printf("%d / %d = %f\n", a, b, (double)a/b ); // CWE-134: Use of Externally-Controlled Format String 
                /*
                    CWE-480: Use of Incorrect Operator
                    CWE-704: Incorrect Type Conversion or Cast 
                    Be careful to ensure that the actual conversion/cast
                    you are trying to do is possible given the relationship 
                    conditions. This will generally cause a syntax error in the development
                    environment but when working outside of development you should always be 
                    cautious. A cast may sometimes be possible without a syntax error but on 
                    object creation an exception will occur.  
                */
                
            break;// CWE-484: Omitted Break Statement in Switch 
        case 'b':
            printf("\nPerforming Task B\n"); // CWE-134: Use of Externally-Controlled Format String 
            // Code to perform Task B goes here
            int value = promptValue();
            Arithmetic* arithmetic1 = create_arithmetic(value);
            int sq = square(arithmetic1);
            int num1 = getValue(arithmetic1);
            printf("%d^2 = %d\n", num1, sq); // CWE-134: Use of Externally-Controlled Format String 
            delete(arithmetic1);
            break;// CWE-484: Omitted Break Statement in Switch 
        case 'c':
            printf("\nPerforming Task C\n"); // CWE-134: Use of Externally-Controlled Format String 
            // Code to perform Task C goes here
            int digit = promptValue();
            Arithmetic* arithmetic2 = create_arithmetic(digit);
            int cubed = cube(arithmetic2);
            int num2 = getValue(arithmetic2);
            printf("%d^3 = %d\n", num2, cubed); // CWE-134: Use of Externally-Controlled Format String 
            delete(arithmetic2);

            break;// CWE-484: Omitted Break Statement in Switch 
        default:
            printf("Invalid input\n");
            return 1;
    }

    //You don't have to free [] arrays
    free(input);//
    
    /*
    by placing free after all uses the below CWEs can be prevented
    */
    // CWE-401: Missing Release of Memory after Effective Lifetime 
    // CWE-415: Double Free 
    // CWE-416: Use After Free 

    return 0;
}

int promptValue()
{
    printf("Enter a number between 1 - 10: ");
    int size = 200;
    char* valueStr = (char*) malloc(sizeof(char) * size); 
    if (fgets(valueStr, size, stdin) == NULL) // CWE-123: Write-what-where Condition 
    {
        fprintf(stderr, "Value could not be read.\n"); // CWE-134: Use of Externally-Controlled Format String 
        exit(0);
    }
    valueStr[strcspn(valueStr, "\n")] = '\0'; // CWE-466: Return of Pointer Value Outside of Expected Range 
    int value = atoi(valueStr);
    if (value < 1 || value > 10)
    {
        fprintf(stderr, "Invalid value input\n"); // CWE-134: Use of Externally-Controlled Format String 
        exit(0);
    }
    free(valueStr);
    return value;
}
