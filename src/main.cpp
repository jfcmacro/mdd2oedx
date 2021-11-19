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

static void printElems(std::vector<oedx::Elem*>& elems) {
  std::for_each(elems.begin(),
		elems.end(),
		[](const oedx::Elem* elem) {
		  std::cout << elem->getText() << std::endl;
		});
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

  for (int i = optind; i < argc; ++i) {
    FILE *fd = nullptr;
    std::vector<TokenInfo*>* vec = nullptr;

    if (::strcmp(argv[i], "-") != 0)
      fd = ::fopen(argv[i], "r");
    else
      fd = ::stdin;

    if (fd == nullptr) {
      std::cerr << "Could't open "
		<< argv[i] << std::endl;
    }
    else {
      vec = processInput(fd);
      fclose(fd);

      course = processTokens(vec);
    }
  }

  std::cout << course->getXMLLine() << std::endl;

  std::vector<oedx::Module*> vMod = course->getModules();
  printElems(course->getElems());

  std::for_each(vMod.begin(),
		vMod.end(),
		[](oedx::Module* mod) {
		  printElems(mod->getElems());
		  std::cout << "Module: " << mod->getTitle()
			    << " " << mod->getUrlName()
			    << std::endl;
		  std::vector<oedx::Unit*> vUnit = mod->getUnits();
		  std::for_each(vUnit.begin(),
				vUnit.end(),
				[](oedx::Unit* unit) {
				  printElems(unit->getElems());
				  std::cout << "Unit: " << unit->getTitle()
					    << " " << unit->getUrlName()
					    << std::endl;
				  std::vector<oedx::Section*> vSection = unit->getSections();
				  std::for_each(vSection.begin(),
						vSection.end(),
						[](oedx::Section* sec) {
						  printElems(sec->getElems());
						  std::cout << "Section: " << sec->getTitle()
							    << " " << sec->getUrlName()
							    << std::endl;
						  std::vector<oedx::Chapter*> vChapter = sec->getChapters();
						  std::for_each(vChapter.begin(),
								vChapter.end(),
								[](oedx::Chapter* chap) {
								  printElems(chap->getElems());
								  std::cout << "Chapter: " << chap->getTitle()
									    << " " << chap->getUrlName()
									    << std::endl;
								  std::vector<oedx::SubChapter*> vSubChapter = chap->getSubChapters();
								  std::for_each(vSubChapter.begin(),
										vSubChapter.end(),
										[](oedx::SubChapter* subChap) {
										  printElems(subChap->getElems());
										  std::cout << "SubChapter: " << subChap->getTitle()
											    << " " << subChap->getUrlName()
											    << std::endl;
										});
								});
						});
				});
		});

  xercesc::XMLPlatformUtils::Terminate();

  return EXIT_SUCCESS;
}
