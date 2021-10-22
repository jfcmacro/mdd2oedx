#include "mdtokens.h"

TokenInfo::TokenInfo(TokenType tokenType, int line, int col) :
  tokenType(tokenType),
  text(),
  line(line),
  col(col) { }

TokenInfo::~TokenInfo() { }

void
TokenInfo::addText(char c) {
  text.push_back(c);
}

int
TokenInfo::getLine() const {
  return line;
}

int
TokenInfo::getCol() const {
  return col;
}

TokenType
TokenInfo::getTokenType() const {
  return tokenType;
}

std::string
TokenInfo::getText() const {
  return text;
}
