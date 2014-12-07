/* Hello World program */

#include<stdio.h>
#include<stdlib.h>

unsigned int ip_to_int (const char * ip)
{
    /* The return value. */
    unsigned v = 0;
    /* The count of the number of bytes processed. */
    int i;
    /* A pointer to the next digit to process. */
    const char * start;

    start = ip;
    for (i = 0; i < 4; i++) {
        /* The digit being processed. */
        char c;
        /* The value of this byte. */
        int n = 0;
        while (1) {
            c = * start;
            start++;
            if (c >= '0' && c <= '9') {
                n *= 10;
                n += c - '0';
            }
            /* We insist on stopping at "." if we are still parsing
               the first, second, or third numbers. If we have reached
               the end of the numbers, we will allow any character. */
            else if ((i < 3 && c == '.') || i == 3) {
                break;
            }
            else {
                return 1;
            }
        }
        if (n >= 256) {
            return 1;
        }
        v *= 256;
        v += n;
    }
    return v;
}

void ConvertIntToIp(int ip)
{
    unsigned char bytes[4];
	char * ipAdress;
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;	
    //printf("%d.%d.%d.%d\n", bytes[3], bytes[2], bytes[1], bytes[0]);  
	ipAdress=(char *)malloc(16);
	sprintf(ipAdress, "%d.%d.%d.%d", bytes[3], bytes[2], bytes[1], bytes[0]);
	printf("%s\n", ipAdress);
}

main()
{
	int ipConverted=0;
	printf("we going to test if we can convert ip to int and upside down\n");
	ipConverted = ip_to_int("192.168.0.100");
	printf("Int of 192.168.0.100: %d\n", ipConverted);
	ConvertIntToIp(ipConverted);
	ipConverted = ip_to_int("0.0.0.0");
	ConvertIntToIp(ipConverted);
	ipConverted = ip_to_int("111.111.111.111");
	ConvertIntToIp(ipConverted);
	ipConverted = ip_to_int("255.255.255.255");
	ConvertIntToIp(ipConverted);
    


}