#include <stdlib.h> //Standard library
#include <stdio.h> //Standard input / output
#include <string.h> 

int main() {
  unsigned char key[20];
  unsigned char phrase[20];
  unsigned char S[256];

  // Leyendo las entradas
  scanf("%[^\n]%*c", key);
  scanf("%[^\n]%*c", phrase);
  
  int phraselength = strlen(phrase);
  unsigned char K[phraselength];
  unsigned char output[phraselength];

  // KSA
  int keylength = strlen(key);
  int j = 0;
  for (int i = 0; i < 256; i++) {
    S[i] = i;
  }
  for (int i = 0; i < 256; i++) {
    j = (j + S[i] + key[i % keylength]) % 256;
    // swap values of S[i] and S[j]
    S[i]=S[i]^S[j];
    S[j]=S[i]^S[j];
    S[i]=S[j]^S[i];
  }

  // PRGA
  int i = 0;
  j = 0;
  int k;
  while (k < phraselength) {
    i = (i + 1) % 256;
    j = (j + S[i]) % 256;
    // swap values of S[i] and S[j]
    S[i]=S[i]^S[j];
    S[j]=S[i]^S[j];
    S[i]=S[j]^S[i];
    K[k] = S[(S[i] + S[j]) % 256];
    k++;
  }

  // Generando salida
  for (int i = 0; i < phraselength; i++) {
    unsigned char temp = phrase[i] ^ K[i];
    output[i] = temp;
  }
  
  for (int i = 0; i < phraselength; ++i) printf("%02hhX", output[i]);
  printf("\n");
  return 0;
}