#pragma once

#include <string>
#include <vector>

namespace ast {
    class expr_ast {
    public:
        virtual ~expr_ast() = default;
    };

    class num_expr_ast : public expr_ast {
    private:
        double val;
    public:
        num_expr_ast(double val) : val(val) {}
    };

    class var_expr_ast : public expr_ast {
    private:
        std::string name;
    public:
        var_expr_ast(const std::string &name) : name(name) {}
    };

    class binary_expr_ast : public expr_ast {
    private:
        char op;
        std::unique_ptr<expr_ast> LHS, RHS;
    public:
    binary_expr_ast(char Op, std::unique_ptr<expr_ast> LHS,
                    std::unique_ptr<expr_ast> RHS)
        : op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
    };

    class call_expr_ast : public expr_ast {
    std::string callee;
    std::vector<std::unique_ptr<expr_ast>> args;

    public:
    call_expr_ast(const std::string &Callee,
                std::vector<std::unique_ptr<expr_ast>> args)
        : callee(Callee), args(std::move(args)) {}
    };

    class prototype_ast {
    private:
        std::string name;
        std::vector<std::string> args;
    public:
        prototype_ast(const std::string &name, std::vector<std::string> args)
            : name(name), args(std::move(args)) {}
        
        const std::string &get_name() const { return name; }
    };

    class function_ast {
    private:
        std::unique_ptr<prototype_ast> proto;
        std::unique_ptr<expr_ast> body;
    public:
        function_ast(std::unique_ptr<prototype_ast> proto, 
            std::unique_ptr<expr_ast> body) :
            proto(std::move(proto)), body(std::move(body)) {}
    };
}