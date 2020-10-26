#include <iostream>
#include <sstream>
#include "Lexer.h"
#include "utils.h"

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

void Lexer::insertSimpleToken(const std::shared_ptr<Token>& token) {
    tokens_.push_back(std::make_shared<Token>(*token));
}

void Lexer::insertIndexedToken(const std::shared_ptr<Token>& token) {
    IndexedTokenValue value(token->buffer);

    Node<IndexedTokenValue> *node;
    if (token->id == TK_ID) {
        node = identifiers_.insertNode(value, true);
    } else {
        node = constants_.insertNode(value, true);
    }
    token->index = node->data.index = node->index;

    insertSimpleToken(token);
}

void Lexer::insertToken(const std::shared_ptr<Token>& token) {
    if (token->isIndexed()) {
        insertIndexedToken(token);
    } else {
        insertSimpleToken(token);
    }
}

LexerStatus Lexer::tokenize(std::istream& in) {
    while (!in.eof()) {
        status = skipWhitespace(in);
        if (status != SKIP_WHITESPACE_SUCCESS) {
            break;
        }

        for (const auto& token : tokenDefinitions) {
            auto initialPosition = in.tellg();
            status = token->tryFind(in);
            if (status == FIND_TOKEN_SUCCESS) {
                insertToken(token);
                break;
            }

            auto finalPosition = in.tellg();
            if (initialPosition != finalPosition) {
                std::stringstream ss;
                ss << "Stream position changed from " << initialPosition << " to " << finalPosition << " for token "
                   << token->label << " fail case" << std::endl;
                throw std::runtime_error(ss.str());
            }
        }

        if (status != FIND_TOKEN_SUCCESS) {
            return FIND_TOKEN_FAILED;
        }
    }

    return PARSE_SUCCESS;
}

void Lexer::describeTokens(const std::vector<std::shared_ptr<Token>>& tokens,
                           std::ostream& out) {
    out << "Id\tBuffer\tLabel\tValue index" << std::endl;
    for (const auto& token : tokens) {
        if (token->isIndexed()) {
            out << token->id << "\t" << token->buffer << "\t" << token->label << "\t" << token->index << std::endl;
        } else {
            out << token->id << "\t" << token->buffer << "\t" << token->label  << "\t" << "-" << std::endl;
        }
    }
}

void Lexer::describeIndexedTokenValues(const std::vector<IndexedTokenValue>& values,
                                       std::ostream& out) {
    out << "Id\tValue" << std::endl;
    for (const auto& value : values) {
        out << value.index << "\t" << value.buffer << std::endl;
    }
}

void Lexer::describe(std::ostream& out) {
    out << "Tokens" << std::endl;
    describeTokens(tokens_, out);
    out << std::endl;

    out << "Identifiers" << std::endl;
    describeIndexedTokenValues(identifiers_.linear(), out);
    out << std::endl;

    out << "Constants" << std::endl;
    describeIndexedTokenValues(constants_.linear(), out);
    out << std::endl;
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
        goto fail_find;
    }

    return FIND_TOKEN_SUCCESS;

fail_find:
    putBufferBack(in);
    return FIND_TOKEN_FAILED;
}

enum LexerStatus ExactKeywordToken::tryFind(std::istream &in) {
    Token::tryFind(in);

    auto status = readValidWord(in, VALID_CATCH_ALL_CHARS);
    if (status != READ_SUCCESS || textMatch != buffer) {
        goto fail_find;
    }

    return FIND_TOKEN_SUCCESS;

fail_find:
    putBufferBack(in);
    return FIND_TOKEN_FAILED;
}

enum LexerStatus DelimitedTextToken::tryFind(std::istream &in) {
    Token::tryFind(in);

    char c;
    while (true) {
        if (in.eof()) {
            goto fail_find;
        }

        in.get(c);
        buffer.push_back(c);

        if (buffer.size() == start.size()) {
            if (!buffer.starts_with(start)) {
                goto fail_find;
            }
        }

        if (buffer.size() >= start.size() + end.size()) {
            if (buffer.ends_with(end)) {
                break;
            }
        }
    }

    return FIND_TOKEN_SUCCESS;

fail_find:
    putBufferBack(in);
    return FIND_TOKEN_FAILED;
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

    if (buffer.length() > ID_TOKEN_MAX_LENGTH) {
        goto fail_find;
    }

    return FIND_TOKEN_SUCCESS;

fail_find:
    putBufferBack(in);
    return FIND_TOKEN_FAILED;
}
