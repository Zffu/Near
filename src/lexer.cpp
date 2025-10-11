#include <near/lexer/lexer.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace near::lexer;

token_t Lexer::identifier() {
	size_t start = this->pos;
 	while (pos < source.size() && (isalnum(source[pos]) || source[pos] == '_' || source[pos] == '.')) pos++;

	token_t t;
	t.type = TokenType::IDENTIFIER;
	t.str_val = source.substr(start, pos - start);

	return t;
}

token_t Lexer::number() {
	size_t start = this->pos;
    while (pos < source.size() && isdigit(source[pos])) pos++;

	token_t t;
	t.type = TokenType::NUM;
	t.num_val = std::stoi(source.substr(start, pos - start));
}

token_t Lexer::string() {
    char quote = source[pos++];
    size_t start = pos;
    while (pos < source.size() && source[pos] != quote) pos++;
    std::string val = source.substr(start, pos - start);
    if (pos < source.size()) pos++; // skip closing quote

	token_t t;
	t.type = TokenType::STRING;
	t.str_val = val;

	return t;
}

void Lexer::skip_whitespaces() {
    while (pos < source.size()) {
        if (isspace(source[pos])) {
            pos++;
        } else if (source[pos] == '#' ) { // comment till end of line
            while (pos < source.size() && source[pos] != '\n') pos++;
        } else break;
    }
}

token_t Lexer::next_token() {
	this->skip_whitespaces();

	if(this->pos >= this->source.size()) {
		token_t t;
		t.type = TokenType::END_OF_FILE;

		return t;
	}

	char c = source[pos];

	if(std::isalpha(c) || c == '_' || c == '.') {
		return identifier();
	} 

	if(std::isdigit(c)) {
		return number();
	}

	if (c == '"' || c == '\'') {
		return string();
	}

	pos++;

	token_t t;
	t.type = TokenType::SYMBOL;
	t.str_val = std::string(1, c);

	return t;
}