#include <stdio.h>

size_t mystrlen(char *str) {
	int len = 0;
	while (*str != '\0') {
		str++;
		len++;
	}
	return len;
}

char *mystrcpy(char *dest, char *src) {
	while (*src != '\0') {
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return 0;
}

int mystrcmp(char *str1, char *str2) {
	while (*str1 != '\0' && *str2 != '\0') {
		if (*str1 != *str2) {
			if (*str1 > *str2){
				return 1;
			}else{
				return -1;
			}
		}
		str1++;
		str2++;
	}

	return 0;
}

char *mystrcat(char *dest, char *src) {
	while (*dest != '\0'){
		dest++;
	}
	*dest = 1; //random da ne bude terminator

	mystrcpy(dest, src);

	return 0;
}

char *mystrstr(char *haystack, char *needle) {
	int needleLen = mystrlen(needle);
	int haystackLen = mystrlen(haystack);

	int i = 0;

	while (*haystack != '0' && haystackLen >= needleLen) {
		for (i = 0; i < needleLen; i++) {
			if (!(haystack[i] == needle[i])) {
				break;
			}
		}
		if (i == needleLen) {
			return haystack;
		}

		haystackLen--;
		haystack++;
	}

	return 0;
}

void reverse(char *dest, char *src) {
	for (int i = mystrlen(src)-1, j = 0; i >= 0; i--, j++) {
		dest[j] = src[i];
	}
}

int main() {
	char joso1[50] = "Test 1";
	char joso2[50] = "Test 22";
	char joso3[50] = "New test";
	char joso4[50] = "New test";
	char joso5[50] = "est";

	printf("%d\n", mystrlen(joso1));
	
	mystrcpy(joso2, joso1);
	puts(joso2);

	printf("%d, %d\n", mystrcmp(joso1, joso2), mystrcmp(joso1, joso3));

	mystrcat(joso3, joso1);
	puts(joso3);

	puts(mystrstr(joso1, joso5));
	puts(mystrstr(joso4, joso5));

	reverse(joso4, joso1);
	puts(joso4);
}