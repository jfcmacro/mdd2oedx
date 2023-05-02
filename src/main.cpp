#include "../config.h"
#include "mdtokens.h"
#include "mdtkns2oedx.h"
#include <unistd.h>
#include <libgen.h>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <filesystem>
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

  oedx::Node* root;

  if (!(argc == optind + 1)) {
    std::cerr << "Only process one course at time" << std::endl;
    return EXIT_FAILURE;
  }

  // for (int i = optind; i < argc; ++i) {
  FILE *fd = nullptr;
  std::vector<TokenInfo*>* vec = nullptr;

  fd = ::fopen(argv[optind], "r");
  std::filesystem::path filePath { argv[optind] };
  std::filesystem::path projectDir { filePath.parent_path() };
  std::filesystem::path fileName { filePath.stem() };
  std::string strFileName { fileName.string() };

  std::cout << "Project directory: " << projectDir << std::endl;
  std::cout << "Filename: " << fileName << std::endl;


  if (fd == nullptr) {
    std::cerr << "Could't open "
	      << argv[optind] << std::endl;
    return EXIT_FAILURE;
  }


  vec = processInput(fd);
  fclose(fd);

  root = processTokens(strFileName, vec);

  std::filesystem::path originDir { std::filesystem::current_path() };

  std::filesystem::current_path(projectDir);

  std::string wd { oedx::createPopulateWorkDir() };

  std::cout << "New Directory: "
	    << wd
	    << std::endl;

  std::filesystem::current_path(originDir);

  xercesc::XMLPlatformUtils::Terminate();

  return EXIT_SUCCESS;
}

