#include "return_statement_in_parenthesis.h"

namespace parenthesis_check {

using clang::ast_matchers::MatchFinder;

void ReturnStatement::registerMatchers(MatchFinder* finder) {
    using namespace clang::ast_matchers;

    finder->addMatcher(returnStmt(has(parenExpr().bind("parenthesis"))), this);
}
void ReturnStatement::check(const MatchFinder::MatchResult& result) {
    auto* parenthesis = result.Nodes.getNodeAs<clang::ParenExpr>("parenthesis");

    assert(parenthesis);

    auto builder = diag(parenthesis->getBeginLoc(), "Useless parenthesis");

    auto& manager = *result.SourceManager;
    auto start = parenthesis->getLParen();
    auto end = parenthesis->getRParen();

    if (manager.isWrittenInMainFile(start) &&
        manager.isWrittenInMainFile(end)) {
        builder << clang::FixItHint::CreateRemoval(start);
        builder << clang::FixItHint::CreateRemoval(end);
    }
}
}  // namespace parenthesis_check