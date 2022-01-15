#include "oedx.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <uuid++.hh>

namespace oedx {

  OEdxNode
  fromTokenType2OEdexNode(TokenType &tknType) {
    OEdxNode retVal = OEUnknown;
    switch(tknType) {
    case H1:
      retVal = OECourse;
      break;
    case H2:
      retVal = OEModule;
      break;
    case H3:
      retVal = OESequential;
      break;
    case H4:
      retVal = OEVertical;
      break;
    case H5:
      retVal = OEH3;
      break;
    case H6:
      retVal = OEH4;
      break;
    default:
      retVal = OEUnknown;
    }
    return retVal;
  }

  Node::Node(std::string& urlName,
	     TokenInfo* pTknInfo,
	     Node* parent) :
    urlName(urlName),
    parent(parent),
    children(),
    tkncnt() {

    tkncnt.push_back(pTknInfo);
  }

  Node::Node(TokenInfo* pTknInfo,
	     Node* parent) :
    parent(parent),
    children(),
    tkncnt() {
    uuid id;

    id.make(UUID_MAKE_V1);
    urlName = id.string();

    tkncnt.push_back(pTknInfo);
  }

  Node::Node(Node* parent) :
    parent(parent),
    children(),
    tkncnt() {
    uuid id;

    id.make(UUID_MAKE_V1);
    urlName = id.string();
  }

  Node::~Node() {
  }

  std::string
  Node::getUrlName() const {
    return urlName;
  }

  void
  Node::addTokenInfo(TokenInfo *tknInfo) {
    tkncnt.push_back(tknInfo);
  }

  void
  Node::addChild(Node* child) {
    children.push_back(child);
  }

  OEdxNode
  Node::getOEdxType() const {
    OEdxNode ret = OETop;

    if (parent == nullptr) return ret;

    switch (tkncnt[0]->getTokenType()) {
    case H1: ret = OECourse; break;
    case H2: ret = OEModule; break;
    case H3: ret = OESequential; break;
    case H4: ret = OEVertical; break;
    case H5: ret = OEH3; break;
    case H6: ret = OEH4; break;
    }
    return ret;
  }

  Node*
  Node::up(const int level) {
    Node* retVal { this };

    for (int i = 0; i == level; i++)
      retVal = retVal->getParent();

    return retVal;
  }

  Node*
  Node::getParent() const {
    return parent;
  }
}
