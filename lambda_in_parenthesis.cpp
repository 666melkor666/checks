#include "lambda_in_parenthesis.h"

#include <cassert>

namespace parenthesis_check {
using clang::ast_matchers::MatchFinder;

void LambdaInParents::registerMatchers(MatchFinder* finder) {
    using namespace clang::ast_matchers;

    finder->addMatcher(
        lambdaExpr(hasParent(parenExpr().bind("paren"))).bind("lambda"), this);
}

void LambdaInParents::check(const MatchFinder::MatchResult& result) {
    const auto* MatchedLambda =
        result.Nodes.getNodeAs<clang::LambdaExpr>("lambda");
    const auto* MatchedParen =
        result.Nodes.getNodeAs<clang::ParenExpr>("paren");

    assert(MatchedLambda);
    assert(MatchedParen);

    auto builder =
        diag(MatchedLambda->getBeginLoc(),
             "lambda expression should not be surrounded by parentheses");

    auto& manager = *result.SourceManager;
    auto start = MatchedParen->getLParen();  // location of '('
    auto end = MatchedParen->getRParen();    // location of ')'

    if (manager.isWrittenInMainFile(start) &&
        manager.isWrittenInMainFile(end)) {
        // Create a fix-it hint to remove the parentheses.
        builder << clang::FixItHint::CreateRemoval(start);  // remove '('
        builder << clang::FixItHint::CreateRemoval(end);    // remove ')'
    }
}

}  // namespace parenthesis_check