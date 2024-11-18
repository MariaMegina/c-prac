#include "functions.h"
#include <memory>
#include <stdexcept>

std::shared_ptr<TFunction> funcFactory::Create(FunctionType function_type) {
    if (function_type == FunctionType::identical) {
        return std::make_shared<IdenticalFunction>();
    } else if (function_type == FunctionType::exponential) {
        return std::make_shared<ExponentialFunction>();
    } else {
        throw std::logic_error("wrong function type");
    }
}

std::shared_ptr<TFunction> funcFactory::Create(FunctionType function_type, double arg) {
    if (function_type == FunctionType::constant) {
        return std::make_shared<ConstantFunction>(arg);
    } else if (function_type == FunctionType::power) {
        return std::make_shared<PowerFunction>(arg);
    } else {
        throw std::logic_error("wrong function type");
    }
}

std::shared_ptr<TFunction> funcFactory::Create(FunctionType function_type, std::vector<double> args) {
    if (function_type == FunctionType::polynomial) {
        return std::make_shared<PolynomialFunction>(args);
    } else {
        throw std::logic_error("wrong function type");
    }
}

std::shared_ptr<TFunction> operator+(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b) {
    return std::make_shared<OperationOnFunctions>(a, b, Operation::add);
}
std::shared_ptr<TFunction> operator-(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b) {
    return std::make_shared<OperationOnFunctions>(a, b, Operation::sub);
}
std::shared_ptr<TFunction> operator*(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b) {
    return std::make_shared<OperationOnFunctions>(a, b, Operation::mul);
}
std::shared_ptr<TFunction> operator/(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b) {
    return std::make_shared<OperationOnFunctions>(a, b, Operation::div);
}

double OperationOnFunctions::Value(double arg) const {
    if (oper_ == Operation::add) {
        return first_->Value(arg) + second_->Value(arg);
    } else if (oper_ == Operation::sub) {
        return first_->Value(arg) - second_->Value(arg);
    } else if (oper_ == Operation::mul) {
        return first_->Value(arg) * second_->Value(arg);
    } else if (oper_ == Operation::div) {
        return first_->Value(arg) / second_->Value(arg);
    } else {
        throw std::logic_error("unknown operation");
    }
}

double OperationOnFunctions::Derivative(double arg) const {
    if (oper_ == Operation::add) {
        return first_->Derivative(arg) + second_->Derivative(arg);
    } else if (oper_ == Operation::sub) {
        return first_->Derivative(arg) - second_->Derivative(arg);
    } else if (oper_ == Operation::mul) {
        return second_->Value(arg) * first_->Derivative(arg) + first_->Value(arg) * second_->Derivative(arg);
    } else if (oper_ == Operation::div) {
        return (second_->Value(arg) * first_->Derivative(arg) - first_->Value(arg) * second_->Derivative(arg))
            / pow(second_->Value(arg), 2);
    } else {
        throw std::logic_error("unknown operation");
    }
}

std::string OperationOnFunctions::ToString() const {
    if (oper_ == Operation::add) {
        return first_->ToString() + " + " + second_->ToString();
    } else if (oper_ == Operation::sub) {
        return first_->ToString() + " - " + second_->ToString();
    } else if (oper_ == Operation::mul) {
        return first_->ToString() + " * " + second_->ToString();
    } else if (oper_ == Operation::div) {
        return first_->ToString() + " / " + second_->ToString();
    } else {
        throw std::logic_error("unknown operation");
    }
}

double gradientDescent(std::shared_ptr<TFunction> func, unsigned iters) {
    double step = 0.01;
    double current_x = 0;
    for (unsigned i = 0; i < iters; ++i) {
        current_x = current_x - step * func->Value(current_x) * func->Derivative(current_x);
    }
    return current_x;
}
