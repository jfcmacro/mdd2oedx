#include "../config.h"
#include "mdlexer.h"
#include "mdtokens.h"
#include <unistd.h>
#include <libgen.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <xercesc/util/PlatformUtils.hpp>
#include "oedx.h"

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

  try {
    xercesc::XMLPlatformUtils::Initialize();
  }
  catch(const xercesc::XMLException& toCatch) {
    return EXIT_FAILURE;
  }

  char *path = ::strdup(argv[0]);
  char *progname = ::basename(path);

  int c;
  while ((c = getopt(argc, argv, "hv")) != -1) {
    switch (c) {
    case 'v':
      version(progname);
      break;
    case 'h':
      usage(progname);
      break;
    }
  }

  for (int i = optind; i < argc; ++i) {
    FILE *fd = nullptr;

    if (::strcmp(argv[i], "-") != 0)
      fd = ::fopen(argv[i], "r");
    else
      fd = ::stdin;

    if (fd == nullptr) {
      std::cerr << "Could't open "
		<< argv[i] << std::endl;
    }
    else {
      yyrestart(fd);
      yyset_in(fd);
      extern TokenInfo *currTkn;
      TokenType token;
      while ((token = ((TokenType) yylex())) != TKEOF) {
	std::cout << currTkn->getText() << std::endl;
	delete currTkn;
      }
      fclose(fd);
    }
  }

  oedx::Course course("Scala_03", "EPAM Latam");

  std::cout << course.getXMLLine() << std::endl;

  oedx::Module m1;
  oedx::Module m2;

  std::cout << m1.getUrlName() << std::endl;
  std::cout << m2.getUrlName() << std::endl;

  xercesc::XMLPlatformUtils::Terminate();
  
  return EXIT_SUCCESS;
}
