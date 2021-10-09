#include "../config.h"
#include <unistd.h>
#include <libgen.h>
#include <iostream>
#include <cstdlib>
#include <cstring>

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

static void version(const char* progname) {
  std::cout << progname
	    << " version "
	    << VERSION 
	    << std::endl;
  exit(EXIT_SUCCESS);
}

int
main(int argc, char **argv) {

  char *path = strdup(argv[0]);
  char *progname = basename(path);
  
  int c; 
  while ((c = getopt(argc, argv, "hv")) != -1) {
    switch (c) {
    case 'v':
      break;
    case 'h':
      usage(progname);
      break;
    }
  }

  std::cout << progname
	    << " not yet implemented"
	    << std::endl;
  
  return EXIT_SUCCESS;
}
