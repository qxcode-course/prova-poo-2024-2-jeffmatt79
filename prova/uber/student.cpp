#include <iostream>
#include "fn.hpp"
#include <iostream>
#include <memory>
#include <optional>

class pessoa {
private:
    std::string nome;
    int money;

public:
    pessoa(std::string nome = "", int money = 0) : nome(nome), money(money) {}

    void salario(int money) {
        this->money = money;
    }

    int saldo() {
        return money;
    }

    void mudarNome(std::string nome) {
        this->nome = nome;
    }

    std::string Getnome() {
        return this->nome;
    }

    void show() {
        if (this->nome == "") {
            std::cout << "none\n";
        } else {
            std::cout << this->nome << ":" << this->money << "\n";
        }
    }
};

class moto {
private:
    int custo;
    std::shared_ptr<pessoa> motorista;
    std::shared_ptr<pessoa> passageiro;

public:
    moto() : custo(0), motorista(nullptr), passageiro(nullptr) {}

    void setdriver(std::shared_ptr<pessoa> m) {
        motorista = m;
    }

    void setpass(std::shared_ptr<pessoa> p) {
        passageiro = p;
    }

    void drive(int km) {
        if (!motorista) {
            std::cout << "não tem motorista\n";
            return;
        }
        this->custo += km;
    }

    void leave() {
        if (!passageiro) {
            std::cout << "não tem passageiro\n";
            return;
        }

        if (passageiro->saldo() < this->custo) {
            std::cout << "pobre\n";
            passageiro->salario(0);
            motorista->salario(motorista->saldo() + custo);
            custo = 0;
            passageiro = std::make_shared<pessoa>();
             passageiro = std::make_shared<pessoa>();
        } else {
            passageiro->salario(motorista->saldo() - this->custo);
            motorista->salario(motorista->saldo() + custo);
            custo = 0;
            passageiro = std::make_shared<pessoa>();
        }
    }

    void show() {
        std::cout << "const:" << this->custo << ", driver:";
        if (motorista) {
            motorista->show();
        } else {
            std::cout << "none\n";
        }
        std::cout << ", pass:";
        if (passageiro) {
            passageiro->show();
        } else {
            std::cout << "none\n";
        }
        std::cout << "\n";
    }
};

int main() {
    std::shared_ptr<pessoa> lucas = std::make_shared<pessoa>("lucas", 10000);
    std::shared_ptr<pessoa> Marcos = std::make_shared<pessoa>("Marcos", 500);

    moto motoca;

    motoca.show();
    
    motoca.setdriver(lucas);
    motoca.setpass(Marcos);
    
    motoca.show();
    
    motoca.drive(550);
    motoca.show();
    
    motoca.leave();
    motoca.show();
}

class Adapter {
public:
    void setDriver(std::string name, int money) {
        (void) name;
        (void) money;
    }
    void setPass(std::string name, int money) {
        (void) name;
        (void) money;
    }
    void drive(int distance) {
        (void) distance;
    }
    void leavePass() {
    }
    void show() {
    }
};

int main() {
    Adapter adp;
    while (true) {
        fn::write("$", "");
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write(line);

        if      (args[0] == "end")       { break;                                  }
        else if (args[0] == "setDriver") { adp.setDriver(args[1], +args[2]);       }
        else if (args[0] == "setPass")   { adp.setPass(args[1], +args[2]);         }
        else if (args[0] == "drive")     { adp.drive(+args[1]);                    }
        else if (args[0] == "leavePass") { adp.leavePass();                        }
        else if (args[0] == "show")      { adp.show();                             }
        else                             { fn::write("fail: command not found\n"); }
    }
}
