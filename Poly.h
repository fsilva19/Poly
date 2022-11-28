#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>

class Poly{
    private:
        int grau; //grau do polinomio
        double* a; //ponteiro dos coeficientes
    public:
    //CONSTRUTORES:
        Poly();                   // default
        Poly(int grau);           // especifico
        Poly(const Poly& copia);   // por copia
        Poly(const Poly&& movimento); // por movimento
    //MÉTODOS:
        void recriar(int grau);
        bool empty()const;
        bool isZero()const;
        int getGrau()const;
        double getCoef(int iesimo)const;
        double getValor(double x)const;
        void setCoef(int indice, double novoValor);
        bool salvar(std::string nomeArquivo);
        bool ler(std::string nomeArquivo);
    //SOBRECARGAS:
        Poly operator=(Poly& copia);
        Poly operator=(Poly&& movimento);
        double operator[](int iesimo);
        double operator()(int x);
        Poly operator+(const Poly &P)const;
        Poly operator-(const Poly &P)const;
        Poly operator*(const Poly &P)const;
        Poly operator-()const;
    //SOBRECARGA DE ENTRADA  E SAÍDA:
        friend std::ostream &operator<<(std::ostream &cout, const Poly &P);
        friend std::istream &operator>>(std::istream &cin, Poly &P);
    //DESTRUTORES:
};
