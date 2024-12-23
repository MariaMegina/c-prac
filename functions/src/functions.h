#include <memory>
#include <stdexcept>
#include <vector>
#include <cmath>

enum class FunctionType {
	identical,
	constant,
	power,
	exponential,
	polynomial
};

enum class Operation {
	add,
	sub,
	mul, 
	div
};

class TFunction {
public:
	virtual double Value(double arg) const = 0;
	virtual double Derivative(double arg) const = 0;
	virtual std::string ToString() const = 0;
	
	friend std::shared_ptr<TFunction> operator+(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b);
	friend std::shared_ptr<TFunction> operator-(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b);
	friend std::shared_ptr<TFunction> operator*(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b);
	friend std::shared_ptr<TFunction> operator/(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b);

	template <class T>
	friend std::shared_ptr<TFunction> operator+(std::shared_ptr<TFunction> a, T b) {
        	throw std::logic_error("invalid argument");
    	}
    	template <class T>
    	friend std::shared_ptr<TFunction> operator-(std::shared_ptr<TFunction> a, T b) {
        	throw std::logic_error("invalid argument");
    	}
    	template <class T>
    	friend std::shared_ptr<TFunction> operator*(std::shared_ptr<TFunction> a, T b) {
        	throw std::logic_error("invalid argument");
    	}
    	template <class T>
    	friend std::shared_ptr<TFunction> operator/(std::shared_ptr<TFunction> a, T b) {
        	throw std::logic_error("invalid argument");
    	}
};

class IdenticalFunction : public TFunction {
public:
    	IdenticalFunction() {}
    	double Value(double arg) const override {
        	return arg;
    	}
    	double Derivative(double arg) const override {
        	return 1;
    	}
    	std::string ToString() const override {
        	return "x";
    	}
};

class ConstantFunction : public TFunction {
public:
    	ConstantFunction(double constant) : constant_(constant) {};
    	double Value(double arg) const override {
        	return constant_;
    	}
    	double Derivative(double arg) const override {
        	return 0;
    	}
    	std::string ToString() const override {
        	return std::to_string(constant_);
    	}
private:
    	double constant_;
};

class PowerFunction : public TFunction {
public:
    	PowerFunction(double power) : power_(power) {};
    	double Value(double arg) const override {
        	return pow(arg, power_);
    	}
    	double Derivative(double arg) const override {
        	return power_ * pow(arg, power_ - 1);
    	}
    	std::string ToString() const override {
        	return "x^" + std::to_string(power_);
    	}
private:
    	double power_;
};

class ExponentialFunction : public TFunction {
public:
    	double Value(double arg) const override {
        	return std::exp(arg);
    	}
    	double Derivative(double arg) const override {
        	return std::exp(arg);
    	}
    	std::string ToString() const override {
        	return "e^x";
    	}
};

class PolynomialFunction : public TFunction {
public:
    	PolynomialFunction(const std::vector<double>& coef) : coef_(coef) {};
    	double Value(double arg) const override {
        	double res = 0;
        	for (int i = 0; i < coef_.size(); ++i) {
        		res += pow(arg, i) * coef_[i];
        	}
        	return res;
    	}
    	double Derivative(double arg) const override {
        	double res = 0;
        	for (int i = 1; i < coef_.size(); ++i) {
        	    	res += i * pow(arg, i - 1) * coef_[i];
        	}
        	return res;
    	}
    	std::string ToString() const override {
        	std::string res = std::to_string(coef_[0]);
        	for (int i = 1; i < coef_.size(); ++i) {
        		if(std::to_string(coef_[i]) != "0.000000"){	
            			res += " + " + std::to_string(coef_[i]) + "*x^" + std::to_string(i);
            		}
        	}
        	return res;
    	}
private:
    	std::vector<double> coef_;
};

class OperationOnFunctions : public TFunction {
public:
    	OperationOnFunctions(std::shared_ptr<TFunction> first,
        	std::shared_ptr<TFunction> second, Operation oper) :
        	first_(first), second_(second), oper_(oper) {}
    	double Value(double arg) const override;
    	double Derivative(double arg) const override;
    	std::string ToString() const override;
private:
    	std::shared_ptr<TFunction> first_;
    	std::shared_ptr<TFunction> second_;
    	Operation oper_;
};

class funcFactory {
	public:
		static std::shared_ptr<TFunction> Create(FunctionType function_type);
		static std::shared_ptr<TFunction> Create(FunctionType function_type, double arg);
        	static std::shared_ptr<TFunction> Create(FunctionType function_type, std::vector<double> args);
};

double gradientDescent(std::shared_ptr<TFunction> func, unsigned iters, double x);
