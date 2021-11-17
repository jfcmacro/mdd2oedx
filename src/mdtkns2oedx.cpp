#include "mdtkns2oedx.h"
#include <vector>
#include <string>
#include <istream>

std::vector<std::string>*
getText2TknContent(std::vector<TokenContent*>* vTknCnt) {
  std::vector<std::string>* strs = new std::vector<>();
  std::for_each(vTknCnt->begin(),
		vTknCnt->end(),
		[](const TokenContent* tknCnt) {
		  std::string tmp { tknCnt->getText() };
		  strs->push_back(tmp);
		});
  return strs;
}


Course* processTokens(const std::vector<TokenInfo*>* vec) {
  Course* pCourse = nullptr;
  std::for_each(vec->begin(), vec->end(),[](const TokenInfo* pTknInf) {
      switch(pTkInfo->getTokenType()) {
      case H1:
	{
	  std::vector<std::string>* vstrs = getText2TknContent(pTkInfo->getContent());
	  std::istream istr{ (*vstrs)[0] };
	  std::string name;
	  std::string ulr_name;
	  std::string org { "EPAM Latam S4N" };
	  std::readline(istr, name, '.');
	  std::readline(istr, url_name);
	  pCourse = new Course(name.trim(), url_name.trim(), org);
	  delete vstrs;
	}
	break;

      case H2:
	{
	  std::vector<std::string>* vstrs = getText2TknContent(pTkInfo->getContent());
	  std::string title { (*vtrs)[0] };
	  pCourse->addModule(new Module(title));
	}
	break;

      case H3:
	{
	  std::vector<std::string>* vstrs = getText2TknContent(pTkInfo->getContent());
	  std::string title { (*vtrs)[0] };
	  pCourse->getLastModule()->addUnit(new Unit(title));
	}
	break;

      case H4:
	{
	  std::vector<std::string>* vstrs = getText2TknContent(pTkInfo->getContent());
	  std::string title { (*vtrs)[0] };
	  pCourse->getLastModule()->getLastUnit()->addSection(new Section(title));
	}
	break;

      case TEXT:
	{
	}
	break;

      });

    }
