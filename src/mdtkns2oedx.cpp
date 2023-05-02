#include "mdtkns2oedx.h"
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
// To remove
#include <iostream>

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

void
addOEdxNode(TokenInfo *pTknInfo,
	    oedx::Node** curNode,
	    int upLevel,
	    std::string ref = "") {

  oedx::Node* parent = (*curNode)->up(upLevel);
  oedx::Node* node = nullptr;

  if (ref.size() != 0) {
    std::string str { "Scala_02" };
    node = new oedx::Node(str,
			  pTknInfo,
			  parent);
  }
  else
    node = new oedx::Node(pTknInfo,
			  parent);
  *curNode = node;
}

oedx::Node*
processTokens(std::string& courseName,
	      const std::vector<TokenInfo*>* vec) {
  oedx::Node* topNode = new oedx::Node();
  oedx::Node* curNode = topNode;

  for (auto  it = vec->begin();
       it != vec->end();
       ++it) {


    oedx::OEdxNode curTknType = curNode->getOEdxType();
    TokenType tknType = (*it)->getTokenType();

    switch(curTknType) {
    case oedx::OETop:
      {
	switch(tknType) {
	case H1:
	  addOEdxNode((*it), &curNode, 0, courseName);
         break;
	case H2:
	case H3:
	case H4:
	case H5:
	case H6:
	  std::cerr << "Error process tokens: You only add H1 token to OETop"
		    << " "
		    << (*it)->getLine()
		    << std::endl;
	  return nullptr;
	  break;
	default:
	  curNode->addTokenInfo((*it));
	  break;
	}
      }
      break;

    case oedx::OECourse:
      {
	switch(tknType) {
	case H1:
	  std::cerr << "Error process tokens: You cannot add another course"
		    << " "
		    << (*it)->getLine()
		    << std::endl;
	  return nullptr;
	  break;
	case H2:
	  addOEdxNode((*it), &curNode, 0);
	  break;
	case H3:
	case H4:
	case H5:
	case H6:
	  std::cerr << "Error process tokens: You are not added a Module"
		    << " "
		    << (*it)->getLine()
		    << std::endl;
	  return nullptr;
	  break;
	default:
	  curNode->addTokenInfo((*it));
	  break;
	}
      }
      break;

    case oedx::OEModule:
      {
	switch(tknType) {
	case H1:
	  std::cerr << "Error process tokens: You cannot add another course"
		    << " "
		    << (*it)->getLine()
		    << std::endl;
	  return nullptr;
	  break;
	case H2:
	  addOEdxNode((*it), &curNode, 1);
	  break;
	case H3:
	  addOEdxNode((*it), &curNode, 0);
	  break;
	case H4:
	case H5:
	case H6:
	  std::cerr << "Error process tokens: You are not added a Sequence"
		    << " "
		    << (*it)->getLine()
		    << std::endl;
	  return nullptr;
	  break;
	default:
	  curNode->addTokenInfo((*it));
	  break;
	}
      }
      break;

    case oedx::OESequential:
      {
	switch(tknType) {
	case H1:
	  {
	    std::cerr << "Error process tokens: You cannot add another course"
		      << " "
		      << (*it)->getLine()
		      << std::endl;
	    return nullptr;
	  }
	  break;
	case H2:
	  addOEdxNode((*it), &curNode, 2);
	  break;
	case H3:
	  addOEdxNode((*it), &curNode, 1);
	  break;
	case H4:
	  addOEdxNode((*it), &curNode, 0);
	  break;
	case H5:
	case H6:
	  std::cerr << "Error process tokens: You are not added a Module Sequence"
		    << " "
		    << (*it)->getLine()
		    << std::endl;
	  return nullptr;
	  break;
	default:
	  curNode->addTokenInfo((*it));
	  break;
	}
      }
      break;

    case oedx::OEVertical:
      {
	switch(tknType) {
	case H1:
	  std::cerr << "Error process tokens: You cannot add another course"
		    << " "
		    << (*it)->getLine()
		    << std::endl;
	  return nullptr;
	  break;
	case H2:
	  addOEdxNode((*it), &curNode, 3);
	  break;
	case H3:
	  addOEdxNode((*it), &curNode, 2);
	  break;
	case H4:
	  addOEdxNode((*it), &curNode, 1);
	  break;
	case H5:
	  addOEdxNode((*it), &curNode, 0);
	  break;
	case H6:
	  std::cerr << "Error process tokens: You are not added a up level before"
		    << " "
		    << (*it)->getLine()
		    << std::endl;
	  return nullptr;
	  break;
	default:
	  curNode->addTokenInfo((*it));
	  break;
	}
      }
      break;

    case oedx::OEH3:
      {
	switch(tknType) {
	case H1:
	  std::cerr << "Error process tokens: You cannot add another course"
		    << " "
		    << (*it)->getLine()
		    << std::endl;
	  return nullptr;
	  break;
	case H2:
	  addOEdxNode((*it), &curNode, 4);
	  break;
	case H3:
	  addOEdxNode((*it), &curNode, 3);
	  break;
	case H4:
	  addOEdxNode((*it), &curNode, 2);
	  break;
	case H5:
	  addOEdxNode((*it), &curNode, 1);
	  break;
	case H6:
	  addOEdxNode((*it), &curNode, 0);
	  break;
	default:
	  curNode->addTokenInfo((*it));
	  break;
	}
      }
      break;

    case oedx::OEH4:
      {
	switch(tknType) {
	case H1:
	  std::cerr << "Error process tokens: You cannot add another course"
		    << " "
		    << (*it)->getLine()
		    << std::endl;
	  return nullptr;
	  break;
	case H2:
	  addOEdxNode((*it), &curNode, 5);
	  break;
	case H3:
	  addOEdxNode((*it), &curNode, 4);
	  break;
	case H4:
	  addOEdxNode((*it), &curNode, 3);
	  break;
	case H5:
	  addOEdxNode((*it), &curNode, 2);
	  break;
	case H6:
	  addOEdxNode((*it), &curNode, 1);
	  break;
	default:
	  curNode->addTokenInfo((*it));
	  break;
	}
      }
      break;

    }
  }
  return topNode;
}
