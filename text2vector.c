#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Convert Morse code to a vector suitable for CW generation in GNU Radio
// Williams WD5GNR -- Hackaday

// A-Z then 0-9 -- could add some prosigns
char *cw[] =
  {
    ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",".-.",".-..",
    "--","-.","---",".--.","--.-",".-.","...","-","..-","..._",".--","-..-","-.--","--..",
    "-----",".----","..---","...--","....-",".....","-....","--...","---..","----."
  };

char *dit="1,0";
char *dah="1,1,1,0";
char *cspace="0";
char *wspace="0,0";
    

void emit(int index)
{
  int i;
  int l;
  if (isspace(index))
    {
      printf(",%s",wspace);
      return;
    }
  index=toupper(index);
  if (isalpha(index)) index-='A';   // point to letter
  else if (isdigit(index)) index=index+26-'0';  // point to number
  else
    {
      fprintf(stderr,"Warning: Unknown character %c\n",index);
      return;  // skip unknown
    }
  l=strlen(cw[index]);
  for (i=0;i<l;i++)
    printf(",%s",cw[index][i]=='.'?dit:dah);
  printf(",%s",cspace);
  return;
}


int main(int argc, char *argv[])
{
  int c;
  printf("(0,");
  while ((c=getchar())!=EOF)
    {
      emit(c);
    }
  printf(")\n");
  return 0;
}
