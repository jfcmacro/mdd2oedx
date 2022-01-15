#pragma once
#include <string>
#include <vector>
#include <map>
#include "mdtokens.h"

namespace oedx {

  enum OEdxNode { OETop, OECourse, OEModule, OESequential, OEVertical, OEH3, OEH4, OEUnknown };

  OEdxNode fromTokenType2OEdexNode(TokenType &tknType);

  class Node {
    Node* parent;
    std::vector<Node*> children;
    std::vector<TokenInfo*> tkncnt;
  protected:
    std::string urlName;
  public:
    Node(std::string& urlName, TokenInfo* pTknInfo, Node* parent = nullptr);
    Node(TokenInfo* pTknInfo, Node* parent = nullptr);
    Node(Node* parent = nullptr);
    ~Node();
    std::string getUrlName() const;
    void addTokenInfo(TokenInfo *tknInfo);
    void addChild(Node* child);
    std::vector<TokenInfo*> getTokenInfo();
    std::vector<Node*> getChildren();
    OEdxNode getOEdxType() const;
    Node* up(const int level);
    Node* getParent() const;
  };
}
