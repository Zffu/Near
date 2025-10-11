#include <stdint.h>

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

namespace near::lexer {

enum class TokenType {
	IDENTIFIER,
	NUM,
	STRING,
	SYMBOL,
	END_OF_FILE
};

struct token_t {
	TokenType type;
	std::string str_val;
	int num_val;
};

class Lexer {
private:
	std::string source;
	size_t pos;

	void skip_whitespaces();

	token_t identifier();
	token_t number();
	token_t string();

public:
	Lexer(const std::string& src): source(src), pos(0) {}

	token_t next_token();
};



}