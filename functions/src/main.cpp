#include "functions.h"
#include <iostream>

using TFunctionPtr = std::shared_ptr<TFunction>;

int main() {
	auto a = funcFactory::Create(FunctionType::polynomial,{5,1});
	auto b = funcFactory::Create(FunctionType::polynomial,{-2,1});
	//auto c = funcFactory::Create(FunctionType::polynomial,{-1,1});
	auto f = a * b;
	std::cout<< f -> ToString() <<std::endl;
	std::cout<< gradientDescent(f, 1000, -3)<< std::endl;
	std::cout<< gradientDescent(f, 1000, 0)<< std::endl;
	std::cout<< f -> Derivative(10)<< std::endl;
	std::cout<<f->Value(3)<<std::endl;
	/*auto f = funcFactory::Create(FunctionType::power, 2); // PowerFunc x^2
	auto g = funcFactory::Create(FunctionType::polynomial, {7, 0, 3, 15}); // TPolynomial 7 + 3*x^2 + 15*x^3
	std::cout << f->ToString() << " for x = 10 is " << f->Value(10) << std::endl;
	std::cout << g->ToString() << " for x = 10 is " << g->Value(10) << std::endl;
	auto p = f + g;
	std::cout<< p->ToString() << " Derivative for x = 1 is "<< p->Derivative(1)<< std::endl; // 53
	std::cout<< f->ToString() << " Derivative for x = 3 is "<< f->Derivative(3)<< std::endl; // 6
	*/
    	return 0;
}
