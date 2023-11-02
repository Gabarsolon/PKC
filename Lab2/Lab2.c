#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//For Lab-3: problem no.1

char* encrypt(char text[], int* key, int m) {
    int textLength = strlen(text);
    int extendedTextLength = textLength;

    //if the length of the text isn't a multiple of m, then we should extended in order to be
    if (extendedTextLength % m != 0)
        extendedTextLength += m - textLength % m;

    char* encryptedText = (char*)malloc(sizeof(char) * (extendedTextLength + 1));
    char* extendedText = (char*)malloc(sizeof(char) * (extendedTextLength + 1));

    strcpy(extendedText, text);

    //fill the black spaces with underscore
    for (int i = textLength; i < extendedTextLength; i++) {
        extendedText[i] = '_';
    }
    //add the string terminal character at the end
    extendedText[extendedTextLength] = '\0';

    //in order to encrypt each part of the text, we need an offset for each iteration
    int textOffset = 0;
    
    while (textOffset < extendedTextLength) {
        //iterate the key...
        for (int keyIndex = 0; keyIndex < m; keyIndex++)\
            //...and add to the encrypted text at the current position + offset
            //the character from the original text + 
            encryptedText[textOffset + keyIndex] = extendedText[textOffset + key[keyIndex]];
        //the offset moves to the next segment of the message corresponding to the key length
        textOffset += m;
    }
    //add the string terminal character at the end
    encryptedText[extendedTextLength] = '\0';

    //deallocate memory
    free(extendedText);

    return encryptedText;
}

int main() {
    //                   0  1  2  3  4
    int key[] =         {1, 3, 4, 2, 0};
    //                   0  1  2  3  4
    int reversedKey[] = {4, 0, 3, 1, 2};

    //the length of the key
    int m = 5;

    char text[100];

    printf("Input a text to encrypt: ");
    scanf("%[^\n]", text);

    char* encryptedText = encrypt(text, key, m);
    printf("The encryptext text is: %s\n", encryptedText);

    char* decryptedText = encrypt(encryptedText, reversedKey, m);
    printf("The decrypted text is:  %s", encrypt(encryptedText, reversedKey, m));

    free(encryptedText);
    free(decryptedText);

    return 0;
}