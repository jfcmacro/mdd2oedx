#pragma once
#include <string>
#include <vector>
#include <cstdio>

enum TokenType { TKEOF,
  H1, H2, H3, H4, H5, H6,
  TEXT, CODE, ITEM, ENUM, DIV, BLOCK, LABEL,
  EMPH, BOLD, DEL,
  ONE_CHOICE, SELECTED_ONE_CHOICE, MULT_CHOICE, SELECTED_MULT_CHOICE,
  BLANK_LINE};

class TokenContent {
protected:
  std::string text;
public:
  TokenContent();
  virtual ~TokenContent() = 0;
  virtual bool isText() const = 0;
  virtual std::string getHtmlText() const = 0;
  virtual std::string getText() const;
  void setText(char c);
  void setText(const std::string& text);

};

class TokenContentText : public TokenContent {
public:
  TokenContentText();
  virtual ~TokenContentText();
  virtual bool isText() const;
  virtual std::string getHtmlText() const;
};

class TokenContentLink : public TokenContent {
  std::string url;
public:
  TokenContentLink(std::string& text, std::string& url);
  virtual ~TokenContentLink();
  virtual bool isText() const;
  virtual std::string getHtmlText() const;
};

class TokenContentImage : public TokenContent {
public:
  TokenContentImage();
  virtual ~TokenContentImage();
  virtual bool isText() const;
  virtual std::string getHtmlText() const;
};

class TokenContentEmph : public TokenContent {
public:
  TokenContentEmph();
  virtual ~TokenContentEmph();
  virtual bool isText() const;
  virtual std::string getHtmlText() const;
};

class TokenContentStrong : public TokenContent {
public:
  TokenContentStrong();
  virtual ~TokenContentStrong();
  virtual bool isText() const;
  virtual std::string getHtmlText() const;
};

class TokenContentDel : public TokenContent {
public:
  TokenContentDel();
  virtual ~TokenContentDel();
  virtual bool isText() const;
  virtual std::string getHtmlText() const;
};

class TokenContentCode : public TokenContent {
public:
  TokenContentCode();
  virtual ~TokenContentCode();
  virtual bool isText() const;
  virtual std::string getHtmlText() const;
};

class TokenInfo {
  TokenType tokenType;
  std::vector<TokenContent*> tkncnt;
  int line;
  TokenInfo(TokenType tokenType, int line);
public:
  static TokenInfo* getCurrTkn();
  static TokenInfo* getCleanCurrTkn();
  static void createCurrTkn(TokenType tokenType, int line);
  ~TokenInfo();
  void addTknContent(TokenContent* tknCont);
  int getLine() const;
  TokenType getTokenType() const;
  std::vector<TokenContent*>* getContent();
  TokenContent* getLastContent();
};

std::vector<TokenInfo*>* processInput(FILE* fd);
