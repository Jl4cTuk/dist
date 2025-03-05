#include <iostream>
#include <typeinfo>

class AbstractEntity {
public:
    virtual void Print() { 
        std::cout << "call AbstractEntity" << std::endl; 
    }
    virtual ~AbstractEntity() = default;
};

class AccountEntity : public AbstractEntity {   
public:
    void Print() override { 
        std::cout << "call AccountEntity" << std::endl;
    }
};

class RoleEntity : public AbstractEntity {  
public:
    void Print() override { 
        std::cout << "call RoleEntity" << std::endl;
    }
};

class IRepository { 
public:
    virtual void Save(AbstractEntity* entity) = 0;
    virtual ~IRepository() = default;
};

class AccountRepository : public IRepository {
public:
    void Save(AbstractEntity* entity) override {
        if (typeid(*entity) != typeid(AccountEntity)) {
            std::cout << "type error" << std::endl;
            return;
        }
        std::cout << "save AccountEntity" << std::endl;
    }
};

class RoleRepository : public IRepository {
public:
    void Save(AbstractEntity* entity) override {
        if (typeid(*entity) != typeid(RoleEntity)) {
            std::cout << "type error" << std::endl;
            return;
        }
        std::cout << "save RoleEntity" << std::endl;
    }
};

int main() {
    AccountEntity account;
    RoleEntity role;

    account.Print();
    role.Print();
    std::cout << std::endl;

    AccountRepository accountRepo;
    RoleRepository roleRepo;

    accountRepo.Save(&account);
    roleRepo.Save(&role);
    
    std::cout << std::endl;
    accountRepo.Save(&role);
    roleRepo.Save(&account);
    
    return 0;
}