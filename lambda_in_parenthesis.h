#pragma once

#include <clang-tidy/ClangTidyCheck.h>

#include <clang/ASTMatchers/ASTMatchFinder.h>

namespace parenthesis_check {
class LambdaInParents : public clang::tidy::ClangTidyCheck {
public:
    using clang::tidy::ClangTidyCheck::ClangTidyCheck;

public:
    void registerMatchers(clang::ast_matchers::MatchFinder* finder) override;

    void check(
        const clang::ast_matchers::MatchFinder::MatchResult& result) override;
};
}  // namespace parenthesis_check