#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



/* Compile from src directory:                    */
/* gcc print_each_char.c -o ../print_each_char    */



print_help(char* my_name) {
   printf("Usage %s [ -l <max_chars> ]\n", my_name);
}



print_each_char(FILE *ifp, int limit_c, int max_c) {

   int c, c_count=0, CHAR_STRING_BUF_SIZE = 7;
   char char_string[CHAR_STRING_BUF_SIZE];
   const char *ascii_strings[33];

   ascii_strings[0]="NUL";
   ascii_strings[1]="SOH";
   ascii_strings[2]="STX";
   ascii_strings[3]="ETX";
   ascii_strings[4]="EOT";
   ascii_strings[5]="ENQ";
   ascii_strings[6]="ACK";
   ascii_strings[7]="BEL";
   ascii_strings[8]="BS";
   ascii_strings[9]="TAB";
   ascii_strings[10]="LF";
   ascii_strings[11]="VT";
   ascii_strings[12]="FF";
   ascii_strings[13]="CR";
   ascii_strings[14]="SO";
   ascii_strings[15]="SI";
   ascii_strings[16]="DLE";
   ascii_strings[17]="DC1";
   ascii_strings[18]="DC2";
   ascii_strings[19]="DC3";
   ascii_strings[20]="DC4";
   ascii_strings[21]="NAK";
   ascii_strings[22]="SYN";
   ascii_strings[23]="ETB";
   ascii_strings[24]="CAN";
   ascii_strings[25]="EM";
   ascii_strings[26]="SUB";
   ascii_strings[27]="ESC";
   ascii_strings[28]="FS";
   ascii_strings[29]="GS";
   ascii_strings[30]="RS";
   ascii_strings[31]="US";
   ascii_strings[32]="SPACE";


   printf("\n\n\nChar\tDec\tOct\tHex\t#Count\n\n");

   while ((c = fgetc(ifp)) != EOF ) {

      c_count++;

      if ((limit_c > 0) && (c_count > max_c)){
         return 0;
      }

      if ( c <= 32 ) {
         strcpy(char_string,ascii_strings[c]);
      }
      else if ( c == 127 ) {
         strcpy(char_string,"DEL");
      }
      else if ( c > 127 ) {
         sprintf(char_string,"Ex%d",c);
      }
      else {
         sprintf(char_string,"%c",c);
      }



      printf("\'%s\'\t%d\t\\%03o\t0x%0.2X\t#%d\n",char_string,c,c,c,c_count);

   }

   return 0;

}



int main(int argc, char* argv[]) {

   FILE *input_file_pointer;
   int index;
   int c;
   int arg_limit_chars = 0;
   int arg_max_chars = 0;

   opterr = 0;

   while ((c = getopt (argc, argv, "hl:")) != -1)
      switch (c)
      {
         case 'h':
            print_help(argv[0]);
            return 0;
         case 'l':
            arg_limit_chars = 1;
            arg_max_chars = atoi(optarg);
            break;
         case '?':
            if (optopt == 'l')
               fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
               fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
               fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
            return 1;
         default:
            abort ();
      }

   if ( optind < argc ) {
      if ( (input_file_pointer = fopen(argv[optind], "r") ) == NULL ) {
         fprintf(stderr, "Cannot open file %s for reading.\n", argv[optind]);
         exit(1);
      }
   }
   else {
      input_file_pointer = stdin;
   }

   print_each_char(input_file_pointer, arg_limit_chars, arg_max_chars);

   if (input_file_pointer != NULL) {
      fclose(input_file_pointer);
   }

   return 0;
}
