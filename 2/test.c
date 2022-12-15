#include <stdio.h>
#include <stdbool.h>

#define N_DOTS 3
#define N_OCTETS 4
#define NUM_SIZE 4

bool is_valid_ip(const char * addr);

int main() {
    if (is_valid_ip("12.255.56.1"))
        puts("\n12.255.56.1 is a valid IP");
    else
        puts("\n12.255.56.1 is not a valid IP");

    return 0;
}

bool is_valid_ip(const char * addr)
{
    unsigned short int i, numbers[N_OCTETS];
    int total_read;
    char format[NUM_SIZE];
  
    for (i = 0; *addr != '\0'; addr++) {
        if (*addr == '.')
            ++i;
    }
  
    if (i != N_DOTS)
        return false;
  
    if ((total_read = sscanf(addr, "%hu.%hu.%hu.%hu", &numbers[0], &numbers[1], &numbers[2], &numbers[3])) != 4) {
        printf("Total read: %d\n", total_read);
        return false;
    }
  
    for (i = 0; i < N_OCTETS; ++i)
    {
        printf("%hu ", numbers[i]);
        if (numbers[i] < 0 || numbers[i] > 255)
            return false;
      
        sprintf(format, "%hu", numbers[i]);
      
        if (format[0] == '0')
            return false;
    }
  
    return true;
}