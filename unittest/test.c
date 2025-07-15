#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(){
	char buffer[50];
	snprintf(buffer, sizeof(buffer),"Task02,indx:%d\r\n",3);
	printf("%s",buffer);

	return 0;
}



