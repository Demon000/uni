#include <iostream>
#include <sstream>
#include "Lexer.h"
#include "utils.h"

#define DEBUG 0

enum LexerStatus Lexer::skipWhitespace(std::istream &in) {
    char c;

    while (true) {
        if (in.eof()) {
            return REACHED_EOF;
        }

        in.get(c);
        if (!isspace(c)) {
            in.putback(c);
            break;
        }
    }

    return SKIP_WHITESPACE_SUCCESS;
}

void Lexer::tokenize(std::istream& in) {
    while (!in.eof()) {
        status = skipWhitespace(in);
        if (status != SKIP_WHITESPACE_SUCCESS) {
            break;
        }

        for (const auto& token : tokenDefinitions) {
            auto initialPosition = in.tellg();
            if (DEBUG) std::cout << "Trying: " << token->label << std::endl;
            status = token->tryFind(in);
            if (status == FIND_TOKEN_SUCCESS) {
                if (DEBUG) std::cout << "Found: " << token->label << " " << token->id << " " << token->buffer << std::endl;
                tokens.push_back(std::make_shared<Token>(*token));
                break;
            } else {
                auto finalPosition = in.tellg();
                if (initialPosition != finalPosition) {
                    std::stringstream ss;
                    ss << "Stream position changed from " << initialPosition << " to " << finalPosition << " for token "
                            << token->label << " fail case" << std::endl;
                    throw std::runtime_error(ss.str());
                }
            }
        }

        if (status != FIND_TOKEN_SUCCESS) {
            throw std::runtime_error("Failed to find token");
        }
    }
}

void Lexer::describe(std::ostream& out) {
    out << "Token id\tMatched text\tToken label" << std::endl;
    for (const auto& token : tokens) {
        out << token->id << "\t\t" << token->buffer << "\t\t" << token->label << std::endl;
    }
}

void Token::putLastBack(std::istream& in) {
    in.putback(buffer.back());
    buffer.pop_back();
}

void Token::putBufferBack(std::istream &in) {
    while (!buffer.empty()) {
        putLastBack(in);
    }
}

enum LexerStatus Token::readOfSize(std::istream &in, size_t size) {
    char c;

    while (true) {
        if (in.eof()) {
            return REACHED_EOF;
        }

        in.get(c);
        buffer.push_back(c);

        if (buffer.size() == size) {
            return READ_SUCCESS;
        }
    }
}

enum LexerStatus Token::readValidChar(std::istream &in, const std::string &validChars) {
    char c;

    if (in.eof()) {
        return REACHED_EOF;
    }

    in.get(c);

    if (validChars.find(c) == std::string::npos) {
        in.putback(c);
        return READ_INVALID;
    }

    buffer.push_back(c);

    return READ_SUCCESS;
}

enum LexerStatus Token::readValidWord(std::istream &in, const std::string &validChars) {
    enum LexerStatus status;

    while (true) {
        status = readValidChar(in, validChars);
        if (status != READ_SUCCESS) {
            break;
        }
    }

    if (buffer.empty()) {
        return READ_INVALID;
    }

    return READ_SUCCESS;
}


enum LexerStatus Token::tryFind(std::istream &in) {
    buffer.resize(0);
    return FIND_TOKEN_SUCCESS;
}

enum LexerStatus ExactTextToken::tryFind(std::istream &in) {
    Token::tryFind(in);

    auto status = readOfSize(in, textMatch.size());
    if (status != READ_SUCCESS || buffer != textMatch) {
        putBufferBack(in);
        return FIND_TOKEN_FAILED;
    }

    return FIND_TOKEN_SUCCESS;
}

enum LexerStatus ExactKeywordToken::tryFind(std::istream &in) {
    Token::tryFind(in);

    auto status = readValidWord(in, VALID_CATCH_ALL_CHARS);
    if (status != READ_SUCCESS || textMatch != buffer) {
        putBufferBack(in);
        return FIND_TOKEN_FAILED;
    }

    return FIND_TOKEN_SUCCESS;
}

enum LexerStatus DelimitedTextToken::tryFind(std::istream &in) {
    Token::tryFind(in);

    char c;
    while (true) {
        if (in.eof()) {
            return FIND_TOKEN_FAILED;
        }

        in.get(c);
        buffer.push_back(c);

        if (buffer.size() == start.size()) {
            if (!buffer.starts_with(start)) {
                putBufferBack(in);
                return FIND_TOKEN_FAILED;
            }
        }

        if (buffer.size() >= start.size() + end.size()) {
            if (buffer.ends_with(end)) {
                break;
            }
        }
    }

    return FIND_TOKEN_SUCCESS;
}

enum LexerStatus IntToken::tryFind(std::istream &in) {
    Token::tryFind(in);

    auto status = readValidWord(in, VALID_CATCH_ALL_CHARS);
    if (status != READ_SUCCESS) {
        goto fail_find;
    }

    if (!isValidIntConstant(buffer)) {
        goto fail_find;
    }

    return FIND_TOKEN_SUCCESS;

fail_find:
    putBufferBack(in);
    return FIND_TOKEN_FAILED;
}

enum LexerStatus DoubleToken::tryFind(std::istream &in) {
    Token::tryFind(in);

    enum LexerStatus status;
    size_t pos;

    status = readValidWord(in, VALID_CATCH_ALL_CHARS);
    if (status != READ_SUCCESS) {
        goto fail_find;
    }

    if (!isValidIntConstant(buffer)) {
        goto fail_find;
    }

    status = readValidChar(in, ".");
    if (status != READ_SUCCESS) {
        goto fail_find;
    }

    pos = buffer.size();
    status = readValidWord(in, VALID_CATCH_ALL_CHARS);
    if (status != READ_SUCCESS) {
        goto fail_find;
    }

    if (!isValidIntConstant(buffer, pos, false)) {
        goto fail_find;
    }

    return FIND_TOKEN_SUCCESS;

fail_find:
    putBufferBack(in);
    return FIND_TOKEN_FAILED;
}

enum LexerStatus IdToken::tryFind(std::istream &in) {
    Token::tryFind(in);

    auto status = readValidWord(in, VALID_CATCH_ALL_CHARS);
    if (status != READ_SUCCESS) {
        goto fail_find;
    }

    if (isValidDigit(buffer[0])) {
        goto fail_find;
    }

    return FIND_TOKEN_SUCCESS;

    fail_find:
    putBufferBack(in);
    return FIND_TOKEN_FAILED;
}
