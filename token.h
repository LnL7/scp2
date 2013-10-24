#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
  ErrorToken = 0,
  VersionToken,
  IdentifierToken,
  StepsToken,
  TextToken,
  ChoiceToken
} TokenType;

#endif
