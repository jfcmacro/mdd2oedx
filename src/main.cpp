#include "../config.h"
#include "mdlexer.h"
#include "mdtokens.h"
#include <unistd.h>
#include <libgen.h>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
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

oedx::Course*
createCourse(TokenInfo *currTkn) {
  std::vector<TokenContent*> *vec_cont = currTkn->getContent();
  std::istringstream ist((*vec_cont)[0]->getText());
  std::string url_name, name, org;

  char del { '.' };

  getline(ist, url_name, del);
  getline(ist, name, del);
  getline(ist, org);

  name = name.substr(1);
  org = org.substr(1);
  
  return new oedx::Course(url_name, name, org);
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

  oedx::Course *course = nullptr;
  oedx::Module *currMod = nullptr;
  oedx::Unit   *currUnit = nullptr;

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
      TokenType token;
      while ((token = ((TokenType) yylex())) != TKEOF) {
	TokenInfo *tknInfo = TokenInfo::getCleanCurrTkn();
	switch (token) {
	case H1:
	  course = createCourse(tknInfo);
	  break;
	case H2:
	  {
	    std::vector<TokenContent*>* vector = tknInfo->getContent();
	    std::string title((*vector)[0]->getText());
	    oedx::Module *mod = new oedx::Module(title);
	    course->addModule(mod);
	    currMod = mod;
	  }
	  break;
	case H3:
	  { std::vector<TokenContent*>* vector = tknInfo->getContent();
	    std::string title((*vector)[0]->getText());
	    oedx::Unit *unit = new oedx::Unit(title);
	    currMod->addUnit(unit);
	  }
	  break;
	}
      }
      fclose(fd);
    }
  }


  std::cout << course->getXMLLine() << std::endl;

  xercesc::XMLPlatformUtils::Terminate();

  return EXIT_SUCCESS;
}
