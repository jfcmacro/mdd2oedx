#pragma once
#include "oedx.h"
#include "mdtokens.h"

oedx::Node* processTokens(std::string& courseName, const std::vector<TokenInfo*>* vec);
