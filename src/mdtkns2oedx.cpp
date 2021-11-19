#include "mdtkns2oedx.h"
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <vector>
#include <string>
#include <sstream>
#include <stack>

// TODO Improve this section
// This is added from Stack Overflow
// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

std::vector<std::string>*
getText2TknContent(std::vector<TokenContent*>* vTknCnt) {
  std::vector<std::string>* strs = new std::vector<std::string>();
  std::for_each(vTknCnt->begin(),
		vTknCnt->end(),
		[strs](const TokenContent* tknCnt) {
		  std::string tmp { tknCnt->getText() };
		  strs->push_back(tmp);
		});
  return strs;
}
//


oedx::Course*
processTokens(const std::vector<TokenInfo*>* vec) {
  oedx::Course* pCourse = nullptr;
  std::stack<oedx::Elems*> sElems;

  std::for_each(vec->begin(), vec->end(),[&pCourse,&sElems](TokenInfo* pTknInf) {
      switch(pTknInf->getTokenType()) {
      case H1:
	{
	  std::vector<std::string>* vstrs = getText2TknContent(pTknInf->getContent());
	  std::istringstream sstr((*vstrs)[0]);
	  std::string name;
	  std::string url_name;
	  std::string org { "S4N" };
	  std::getline(sstr, name, '.');
	  std::getline(sstr, url_name);
	  pCourse = new oedx::Course(trim(name), trim(url_name), org);
	  if (sElems.empty())
	    sElems.push(pCourse);
	  else
	    ;
	  delete vstrs;
	}
	break;

      case H2:
	{
	  std::vector<std::string>* vstrs = getText2TknContent(pTknInf->getContent());
	  std::string title { (*vstrs)[0] };
	  oedx::Module *pModule = new oedx::Module(title);
	  pCourse
	    ->addModule(pModule);

	  for (int i = sElems.size(); i >= H2 - H1; i--) sElems.pop();

	  sElems.push(pModule);
	}
	break;

      case H3:
	{
	  std::vector<std::string>* vstrs = getText2TknContent(pTknInf->getContent());
	  std::string title { (*vstrs)[0] };
	  oedx::Unit *pUnit = new oedx::Unit(title);
	  pCourse
	    ->getLastModule()
	    ->addUnit(pUnit);

	  for (int i = sElems.size(); i >= H3 - H1; i--) sElems.pop();

	  sElems.push(pUnit);
	}
	break;

      case H4:
	{
	  std::vector<std::string>* vstrs = getText2TknContent(pTknInf->getContent());
	  std::string title { (*vstrs)[0] };
	  oedx::Section *pSection = new oedx::Section(title);
	  pCourse
	    ->getLastModule()
	    ->getLastUnit()
	    ->addSection(pSection);

	  for (int i = sElems.size(); i >= H4 - H1; i--) sElems.pop();

	  sElems.push(pSection);
	}
	break;

      case H5:
	{
	  std::vector<std::string>* vstrs = getText2TknContent(pTknInf->getContent());
	  std::string title { (*vstrs)[0] };
	  oedx::Chapter *pChapter = new oedx::Chapter(title);
	  pCourse
	    ->getLastModule()
	    ->getLastUnit()
	    ->getLastSection()
	    ->addChapter(pChapter);

	  for (int i = sElems.size(); i >= H5 - H1; i--) sElems.pop();

	  sElems.push(pChapter);
	}
	break;

      case H6:
	{
	  std::vector<std::string>* vstrs = getText2TknContent(pTknInf->getContent());
	  std::string title { (*vstrs)[0] };
	  oedx::SubChapter *pSubChapter = new oedx::SubChapter(title);
	  pCourse->getLastModule()
	    ->getLastUnit()
	    ->getLastSection()
	    ->getLastChapter()
	    ->addSubChapter(pSubChapter);

	  for (int i = sElems.size(); i >= H5 - H1; i--) sElems.pop();

	  sElems.push(pSubChapter);
	}
	break;

      case TEXT:
	{
	  std::string body {"<p>"};
	  std::for_each(pTknInf->getContent()->begin(),
			pTknInf->getContent()->end(),
			[&body](const TokenContent* tkncnt) {
			  body += tkncnt->getHtmlText();
			});
	  body += "</p><br/>";

	  oedx::Html *pHtml = new oedx::Html(body);
	  sElems.top()->addElem(pHtml);
	}
	break;
      }
    });

  return pCourse;
}
