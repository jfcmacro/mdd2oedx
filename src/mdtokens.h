#pragma once
#include <string>
#include <vector>

enum TokenType { TKEOF, H1, H2, H3, H4, H5, H6, TEXT, CODE, ITEM, ENUM, EMPH, DIV, BLOCK, BOLD, LABEL };

class TokenContent {
protected:
  std::string text;
public:
  TokenContent();
  virtual ~TokenContent() = 0;
  virtual bool isText() const = 0;
  std::string getText();
  void setText(char c);
  void setText(const std::string& text);

};

class TokenContentText : public TokenContent {
public:
  TokenContentText();
  virtual ~TokenContentText();
  virtual bool isText() const;
};

class TokenContentLink : public TokenContent {
public:
  TokenContentLink();
  virtual ~TokenContentLink();
  virtual bool isText() const;
};

class TokenContentImage : public TokenContent {
public:
  TokenContentImage();
  virtual ~TokenContentImage();
  virtual bool isText() const;
};

class TokenContentEmph : public TokenContent {
public:
  TokenContentEmph();
  virtual ~TokenContentEmph();
  virtual bool isText() const;
};

class TokenContentStrong : public TokenContent {
public:
  TokenContentStrong();
  virtual ~TokenContentStrong();
  virtual bool isText() const;
};

class TokenContentCode : public TokenContent {
public:
  TokenContentCode();
  virtual ~TokenContentCode();
  virtual bool isText() const;
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
  int getCol() const;
  TokenType getTokenType() const;
  std::vector<TokenContent*>* getContent();
  TokenContent* getLastContent();
};
