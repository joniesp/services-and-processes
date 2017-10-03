#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


#define N 30
#define DEBUG(...); if(verbose) \
  fprintf(stderr, __VA_ARGS__);

const char *program_name;
int verbose = 0;

void print_usage(FILE *out, int return_code){
  fprintf(out,"usage: %s\n"
      "This program converts from any base to any base.\n"
      "\n"
      "Examples\n"
      "conversion -b2 34 => 1000 10\n", program_name);
  exit(return_code);
}

int main(int argc, char *argv[]){

  int next_option;
  int output_base;
  int number;
  int convertido[N];
  int aux = 0;

  const char *short_options = "hb:vi:";
  const struct option long_options[] = {
    {"help", 0, NULL, 'h'},
    {"base", 1, NULL, 'b'},
    {"verbose", 0, NULL, 'v'},
    {"input", 1, NULL, 'i'}
  };

  program_name = argv[0];

  do{
    next_option = getopt_long(argc, argv, short_options, long_options, NULL);
      switch(next_option){
	case 'h':
	  print_usage(stdout, EXIT_SUCCESS);
	  break;
	case 'b':
	  output_base = atoi(optarg);
	  DEBUG("Estableciendo la salida de %i\n", output_base);
	  number = atoi(optarg + 2);
	  break;
	case 'v':
	  verbose = 1;
	  break;
	case 'i':
	  output_base = atoi(optarg);
	  DEBUG("Estableciendo la salida de %i\n", output_base);
	  number = atoi(optarg + 2);
	  break;
	case '?':
	  print_usage(stderr, EXIT_FAILURE);
	case -1:
	  break;
	default:
	  abort();
	  break;
      }
  }while(next_option != -1)


  DEBUG("Funcionando en modo prolijo.\n");

  if(verbose){
    while(number > 0){
      convertido[aux] = number % output_base;
      number /= output_base;
      aux++;
    }
    aux--;

    for(; aux >= 0; aux--)
      printf("%i", convertido[aux]);

    printf("\n");
  }
  return EXIT_SUCCESS;
}

