#include "mdtokens.h"
#include "mdlexer.h"

static TokenInfo* currTkn;

TokenContent::TokenContent() : text() { }

TokenContent::~TokenContent() { }

std::string
TokenContent::getText() const {
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

std::string
TokenContentText::getHtmlText() const {
  return getText();
}

TokenContentLink::TokenContentLink(std::string& text,
				   std::string& url) : TokenContent(),
						       url(url) {
  this->setText(text);
}

TokenContentLink::~TokenContentLink() { }

bool
TokenContentLink::isText() const {
  return false;
}

std::string
TokenContentLink::getHtmlText() const {
  std::string ret {"<a href=\"" + url + "\">" + text + "</a>"};
  return ret;
}

TokenContentImage::TokenContentImage() :
  TokenContent() { }

TokenContentImage::~TokenContentImage() { }

bool
TokenContentImage::isText() const {
  return false;
}

std::string
TokenContentImage::getHtmlText() const {
  return getText();
}

TokenContentEmph::TokenContentEmph() :
  TokenContent() { }

TokenContentEmph::~TokenContentEmph() { }

bool
TokenContentEmph::isText() const {
  return false;
}

std::string
TokenContentEmph::getHtmlText() const {
  std::string retVal { "<em>" + getText() + "</em>" };
  return retVal;
}

TokenContentStrong::TokenContentStrong() :
  TokenContent() { }

TokenContentStrong::~TokenContentStrong() { }

bool
TokenContentStrong::isText() const {
  return false;
}

std::string
TokenContentStrong::getHtmlText() const {
  std::string retVal { "<strong>" + getText() + "</strong>" };
  return retVal;
}

TokenContentDel::TokenContentDel() :
  TokenContent() { }

TokenContentDel::~TokenContentDel() { }

bool
TokenContentDel::isText() const {
  return false;
}

std::string
TokenContentDel::getHtmlText() const {
  std::string retVal { "<del>" + getText() + "</del>" };
  return retVal;
}

TokenContentCode::TokenContentCode() :
  TokenContent() { }

TokenContentCode::~TokenContentCode() { }

bool
TokenContentCode::isText() const {
  return false;
}

std::string
TokenContentCode::getHtmlText() const {
  std::string retVal { "<pre>" + getText() + "</pre>" };
  return retVal;
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

std::vector<TokenInfo*>*
processInput(FILE* fd) {
  yyrestart(fd);
  yyset_in(fd);
  TokenType token;
  std::vector<TokenInfo*>* vec = new std::vector<TokenInfo*>();

  while ((token = ((TokenType) yylex())) != TKEOF)
    vec->push_back(TokenInfo::getCleanCurrTkn());

  return vec;
}
