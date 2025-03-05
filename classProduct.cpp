#include <iostream>

class Product {
private:
    int price;
public:
    Product(int price) { this->price = price; }

    void setPrice(int my_price) {
        this->price = my_price;
    }

    int getPrice() const {
        return this->price;
    }
};

class IProductValidator {
public:
    virtual bool IsValid(int price) const = 0;
    virtual ~IProductValidator() {};
};

class ProductValidator : public IProductValidator {
public:
    bool IsValid(int price) const override {
        return price > 0;
    }
};

class CustomerServiceValidator : public IProductValidator {
public:
    bool IsValid(int price) const override {
        return price > 100000;
    }
};

bool ValidateProduct(const Product& product, const IProductValidator& validator) {
    return validator.IsValid(product.getPrice());
}

int main() {
    Product p1(50);
    Product p2(150000);

    ProductValidator defaultValidator;
    CustomerServiceValidator customerValidator;

    std::cout << "Product 1 (default validator): " 
              << ValidateProduct(p1, defaultValidator) << std::endl;
    std::cout << "Product 1 (customer validator): " 
              << ValidateProduct(p1, customerValidator) << std::endl;

    std::cout << "Product 2 (default validator): " 
              << ValidateProduct(p2, defaultValidator) << std::endl;
    std::cout << "Product 2 (customer validator): " 
              << ValidateProduct(p2, customerValidator) << std::endl;

    return 0;
}
