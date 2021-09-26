#include "../config.h"
#include <unistd.h>
#include <iostream>
#include <cstdlib>

static void usage(const char* progname) {
  std::cout << "Usage: " << progname
	    << " -h" << std::endl;
  std::cout << "\t" << "Print this message"
	    << std::endl;
  std::cout << "       " << progname
	    << " -v" << std::endl;
  std::cout << "\t" << "Print the version"
	    << std::endl;
  exit(EXIT_SUCCESS);
}

int
main(int argc, char **argv) {

  int c; 
  while ((c = getopt(argc, argv, "hv")) != -1) {
    switch (c) {
    case 'v':
      std::cout << argv[0]
		<< " version "
		<< VERSION 
		<< std::endl;
      break;
    case 'h':
      usage(argv[0]);
      break;
    }
  }
  
  return EXIT_SUCCESS;
}
