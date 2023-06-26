#include "lambda_in_parenthesis.h"
#include "return_statement_in_parenthesis.h"

#include <clang-tidy/ClangTidyModule.h>
#include <clang-tidy/ClangTidyModuleRegistry.h>

#include <clang/Tooling/Tooling.h>

namespace parenthesis_check {
class Module : public clang::tidy::ClangTidyModule {
public:
    void addCheckFactories(
        clang::tidy::ClangTidyCheckFactories& factories) override {
        factories.registerCheck<LambdaInParents>("lambda-in-parenthesis");
        factories.registerCheck<ReturnStatement>("return-stmt-in-parenthesis");
    }
};

static clang::tidy::ClangTidyModuleRegistry::Add<Module> _(
    "Parenthesis checks",
    "Various checks regarding parenthesis usage");
}  // namespace parenthesis_check