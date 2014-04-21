#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char** argv)
{
   const char* optstr = "abc:";
   int   c;

   while((c = getopt(argc, argv, optstr)) != -1)
   {
      switch(c)
      {
      case 'a':
         printf("opt a set\n");
         break;
      case 'b':
         printf("opt b set\n");
         break;
      case 'c':
         // missing c argument is checked by getopt
         printf("opt c set\n");
         printf("opt c argument: %s\n", optarg);
         break;
      defautl:
         printf("unknown option %c\n", c);
         exit(-1);
      }
   }
   return 0;
}
