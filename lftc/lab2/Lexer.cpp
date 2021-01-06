#include <iostream>
#include "Lexer.h"
#include "StreamUtils.h"

void Lexer::insertSimpleToken(const std::shared_ptr<Token>& token) {
    tokens.push_back(std::make_shared<Token>(*token));
}

void Lexer::insertIndexedToken(const std::shared_ptr<Token>& token) {
    IndexedTokenValue value(token->buffer);

    Node<IndexedTokenValue> *node;
    if (token->id == TK_ID) {
        node = identifiers.insertNode(value, true);
    } else {
        node = constants.insertNode(value, true);
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
    LexerStatus status;

    while (in) {
        bool skipSuccess = StreamUtils::skipWhitespace(in);
        if (!skipSuccess) {
            break;
        }

        auto initialPosition = in.tellg();
        for (const auto& token : tokenDefinitions) {
            in.seekg(initialPosition, std::istream::beg);

            status = token->tryFind(in);
            if (status != FIND_TOKEN_SUCCESS) {
                continue;
            }

            insertToken(token);
            break;
        }

        if (status != FIND_TOKEN_SUCCESS) {
            return FIND_TOKEN_FAILED;
        }
    }

    return PARSE_SUCCESS;
}

std::vector<Token> Lexer::getTokens() {
    std::vector<Token> result;

    for (const auto& token : tokens) {
        result.push_back(*token);
    }

    return result;
}

void Lexer::describeTokens(std::ostream& out) {
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
    describeTokens(out);
    out << std::endl;

    out << "Identifiers" << std::endl;
    describeIndexedTokenValues(identifiers.linear(), out);
    out << std::endl;

    out << "Constants" << std::endl;
    describeIndexedTokenValues(constants.linear(), out);
    out << std::endl;
}

LexerStatus Token::tryFind(std::istream &in) {
    buffer.clear();
    return FIND_TOKEN_SUCCESS;
}

LexerStatus ExactTextToken::tryFind(std::istream &in) {
    Token::tryFind(in);

    bool readSuccess = StreamUtils::read(in, buffer, textMatch.size());
    if (!readSuccess || buffer != textMatch) {
        return FIND_TOKEN_FAILED;
    }

    return FIND_TOKEN_SUCCESS;
}

LexerStatus ExactKeywordToken::tryFind(std::istream &in) {
    Token::tryFind(in);

    auto result = keywordCatchAllFsm.parse(in);
    if (result.matched.empty() || result.matched != textMatch) {
        return FIND_TOKEN_FAILED;
    }

    buffer = result.matched;

    return FIND_TOKEN_SUCCESS;
}

LexerStatus DelimitedTextToken::tryFind(std::istream &in) {
    Token::tryFind(in);

    while (in) {
        unsigned char c = in.get();
        if (in.fail()) {
            return FIND_TOKEN_FAILED;
        }

        buffer.push_back(c);

        if (buffer.size() == start.size()) {
            if (!buffer.starts_with(start)) {
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

LexerStatus IntToken::tryFind(std::istream &in) {
    Token::tryFind(in);

    FiniteStateMachine::Result result;
    std::string matchedBuffer;
    std::string extraBuffer;

    result = integerFsm.parse(in);
    matchedBuffer = result.matched;
    if (matchedBuffer.empty()) {
        return FIND_TOKEN_FAILED;
    }

    auto positionBefore = in.tellg();
    result = keywordCatchAllFsm.parse(in);
    extraBuffer = result.matched;
    if (!extraBuffer.empty()) {
        in.seekg(positionBefore);
        return FIND_TOKEN_FAILED;
    }

    buffer = matchedBuffer;

    return FIND_TOKEN_SUCCESS;
}

LexerStatus DoubleToken::tryFind(std::istream &in) {
    Token::tryFind(in);

    FiniteStateMachine::Result result;
    std::string matchedBuffer;
    std::string extraBuffer;

    result = realFsm.parse(in);
    matchedBuffer = result.matched;
    if (matchedBuffer.empty()) {
        return FIND_TOKEN_FAILED;
    }

    auto positionBefore = in.tellg();
    result = keywordCatchAllFsm.parse(in);
    extraBuffer = result.matched;
    if (!extraBuffer.empty()) {
        in.seekg(positionBefore);
        return FIND_TOKEN_FAILED;
    }

    buffer = matchedBuffer;

    return FIND_TOKEN_SUCCESS;
}

LexerStatus IdToken::tryFind(std::istream &in) {
    Token::tryFind(in);

    FiniteStateMachine::Result result;
    std::string matchedBuffer;
    std::string extraBuffer;

    result = idFsm.parse(in);
    matchedBuffer = result.matched;
    if (matchedBuffer.empty()) {
        return FIND_TOKEN_FAILED;
    }

    auto positionBefore = in.tellg();
    result = keywordCatchAllFsm.parse(in);
    extraBuffer = result.matched;
    if (!extraBuffer.empty()) {
        in.seekg(positionBefore);
        return FIND_TOKEN_FAILED;
    }

    buffer = matchedBuffer;

    return FIND_TOKEN_SUCCESS;
}
