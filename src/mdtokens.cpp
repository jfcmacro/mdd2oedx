#include "mdtokens.h"

static TokenInfo* currTkn;

TokenContent::TokenContent() : text() { }

TokenContent::~TokenContent() { }

std::string
TokenContent::getText() {
  return text;
}

void
TokenContent::setText(char c) {
  text.push_back(c);
}

void
TokenContent::setText(const std::string& text) {
  this->text.append(text);
}

TokenContentText::TokenContentText() :
  TokenContent() { }

TokenContentText::~TokenContentText() { }

bool
TokenContentText::isText() const {
  return true;
}

TokenContentLink::TokenContentLink() :
  TokenContent() { }

TokenContentLink::~TokenContentLink() { }

bool
TokenContentLink::isText() const {
  return false;
}

TokenContentImage::TokenContentImage() :
  TokenContent() { }

TokenContentImage::~TokenContentImage() { }

bool
TokenContentImage::isText() const {
  return false;
}

TokenContentEmph::TokenContentEmph() :
  TokenContent() { }

TokenContentEmph::~TokenContentEmph() { }

bool
TokenContentEmph::isText() const {
  return false;
}

TokenContentStrong::TokenContentStrong() :
  TokenContent() { }

TokenContentStrong::~TokenContentStrong() { }

bool
TokenContentStrong::isText() const {
  return false;
}

TokenContentCode::TokenContentCode() :
  TokenContent() { }

TokenContentCode::~TokenContentCode() { }

bool
TokenContentCode::isText() const {
  return false;
}

TokenInfo::TokenInfo(TokenType tokenType,
		     int line) :
  tokenType(tokenType),
  tkncnt(),
  line(line) { }

TokenInfo* TokenInfo::getCurrTkn() {
  return currTkn;
}

TokenInfo* TokenInfo::getCleanCurrTkn() {
  TokenInfo* tmp = currTkn;
  currTkn = nullptr;
  return tmp;
}

void TokenInfo::createCurrTkn(TokenType tokenType,
			      int line) {
  if (currTkn == nullptr)
    currTkn = new TokenInfo(tokenType, line);
}

TokenInfo::~TokenInfo() { }

void
TokenInfo::addTknContent(TokenContent* tknCont) {
  tkncnt.push_back(tknCont);
}

int
TokenInfo::getLine() const {
  return line;
}

TokenType
TokenInfo::getTokenType() const {
  return tokenType;
}

std::vector<TokenContent*>*
TokenInfo::getContent() {
  return &tkncnt;
}

TokenContent*
TokenInfo::getLastContent() {
  if (tkncnt.empty()) return nullptr;
  TokenContent* tc = tkncnt.back();
  if (tc->isText()) return tc;
  return nullptr;
}
