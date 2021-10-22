#pragma once
#include <string>

enum TokenType { TKEOF, H1, H2, H3, H4, H5, H6, TEXT, CODE, ITEM, ENUM, EMPH, DIV, BLOCK, BOLD };

class TokenInfo {
  TokenType tokenType;
  std::string text;
  int line;
  int col;
 public:
  TokenInfo(TokenType tokenType, int line, int col);
  ~TokenInfo();
  void addText(char c);
  int getLine() const;
  int getCol() const;
  TokenType getTokenType() const;
  std::string getText() const;
};
