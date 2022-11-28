#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>
#include "Poly.h"

using namespace std;
//COSNTRUTORES:
    //CONSTRUTOR DEFAULT:
    Poly::Poly(): grau(0), a(nullptr){}

    //CONSTRUTOR ESPECIFICO:
    Poly::Poly(int Grau): grau(Grau), a(nullptr){
        if(grau>0){ //para parametro de apenas o maior grau 1.0
            a = new double[grau+1];
            for(int i=0;i<=grau;i++){
                if(i==grau) a[i] = 1.0;
                else a[i] = 0.0;
            }
        }
        if(grau==0){ //para parametro nulo
            a = new double[grau+1];
            a[0] = 0.0;
        }
        if(grau<0){Poly();} //grau negativo cria um default
    }
    //CONSTRUTOR POR CÓPIA:
    Poly::Poly(const Poly& copia): grau(copia.grau), a(nullptr){
        if(grau>0){
            a = new double[grau+1];
            for (int i=0;i<=grau;i++) a[i] = copia.a[i];
        }
    }
    //CONSTRUTOR POR MOVIMENTO:
    Poly::Poly(const Poly&& movimento): grau(movimento.grau), a(movimento.a){
        grau = 0;
        a = nullptr;
    }
//SOBRECARGAS:
    //OPERADOR =:
    Poly Poly::operator=(Poly& copia){
        delete[] a;
        grau = copia.grau;
        a = new double[grau+1];
        for(int i=0;i<=grau;i++){
            a[i] = copia.a[i];
        }
        return *this;
    }
    Poly Poly::operator=(Poly&& movimento){
        delete[] a;
        grau = movimento.grau;
        a = new double[grau+1];
        for(int i=0;i<=grau;i++){
            a[i] = movimento.a[i];
        }
        return *this;
    }
    //OPERADOR []:
    double Poly::operator[](int iesimo){
        return getCoef(iesimo);
    }
    //OPERADOR ():
    double Poly::operator()(int x){
        return getValor(x);
    }
    // OPERADOR <<: IMPRIMIR O POLINOMIO
    ostream &operator<<(ostream &cout, const Poly&P){
        if(P.grau<0){}
        else{
            for(int i=P.grau;i>=0;i--){
                if(P.a[i]==0.0){
                    if((i==0) & (P.grau==0)){
                        cout << P.a[i];
                    }
                }else{
                    if(P.a[i]<0.0){//IMPRIME O SINAL DO COEFICIENTE:
                        cout << "-";
                    }else if(i!=P.grau){
                        cout << "+";
                    }
                    if(fabs(P.a[i])!=1.0 or i==0){ //pega o módulo do coeficiente
                        cout << fabs(P.a[i]);
                    }
                    if(i!=0){//IMPRIME A POTENCIA DO X:
                        if(fabs(P.a[i])!=1.0){
                            cout << "*";
                        }cout << "x";
                        if(i>1){
                            cout <<"^" << i;
                        }
                    }
                }
            }
        }
        return cout;
    }
    //OPERADOR >>: RECEBER O POLINOMIO
    istream &operator>>(istream &cin, Poly &P){
        if(P.grau<0){
            cerr << "Erro, polinomio vazio.";
        }else{
            for(int i=(P.grau);i>=0;i--){
                cout << "x^" << i << ": ";
                cin >> P.a[i];
                if((P.grau!=0) & (i==P.grau)){
                    while(P.a[i]==0.0){
                        cout << "x^" << i << ": ";
                        cin >> P.a[i];
                    }
                }
            }
        }
        return cin;
    }
    Poly Poly::operator+(const Poly &P)const{
        Poly prov(max(getGrau(), P.getGrau()));
        if(empty()==true or isZero()==true){}
        else{
            for(int i=0;i<=prov.grau;i++){
                prov.a[i] = getCoef(i) + P.getCoef(i);
            }
        }
        return prov;
    }
    Poly Poly::operator-(const Poly &P)const{
        Poly prov(max(getGrau(), P.getGrau()));
        if(empty()==true or isZero()==true){}
        else{
            for(int i=0;i<=prov.grau;i++){
                prov.a[i] = getCoef(i) - P.getCoef(i);
            }
        }
        return prov;
    }
    Poly Poly::operator*(const Poly &P)const{
        Poly prov(getGrau()+P.getGrau());
        for(int k=0;k<=prov.grau;k++){
            prov.a[k] = 0.0;
        }
        for(int i=0;i<=grau;i++){
            for(int j=0;j<=P.grau;j++){
                prov.a[i+j] += a[i] * P.a[j];
            }
        }
        return prov;
    }
    Poly Poly::operator-()const{
        Poly prov(getGrau());
        if(empty()==true or isZero()==true){}
        else{
            for(int i=0;i<=prov.grau;i++){
                prov.a[i] = -getCoef(i);
            }
        }
        return prov;
    }

//MÉTODOS:
    //MÉTODO RECRIAR:
    void Poly::recriar(int Grau) {
        grau = Grau;
        delete[] a;
        a = new double[grau];
        Poly{grau};
    }
    //MÉTODO EMPTY:
    bool Poly::empty()const{
        if(grau<0) return true;
        else return false;
    }
    //MÉTODO ISZERO:
    bool Poly::isZero()const{
        if((grau==0) & (a[grau+1]==0.0)) return true;
        else return false;
    }
    //MÉTODO GETGRAU:
    int Poly::getGrau()const{
        return grau;
    }
    //MÉTODO GETCOEF:
    double Poly::getCoef(int iesimo)const{
        if(iesimo<0 or iesimo>grau){
            return 0.0;
        }else return a[iesimo];
    }
    //MÉTODO DE CONSULTA GETVALOR:
    double Poly::getValor(double x)const{
        double valor=0.0;
        if(!empty()){
            for(int i=0;i<=grau;i++){
                valor += getCoef(i)*(pow(x,i));
            }
        }else return 0.0;
        return valor;
    }
    //MÉTODO SETCOEF:
    void Poly::setCoef(int indice, double novoValor){
        if((indice<0 or indice>grau) or ((grau!=0) & (novoValor==0))){
            cerr << "Erro: Indice invalido";
        }else a[indice] = novoValor;
    }
    //MÉTODO DE SALVAR EM ARQUIVO:
    ofstream salvar_arq;
    bool Poly::salvar(string nomeArquivo){
        salvar_arq.open(nomeArquivo);
        salvar_arq << "POLY " << grau << "\n";
        if(grau<0){return true;}
        else{
            for(int i=0;i<=grau;i++){
                salvar_arq << a[i] << " ";
            }
        }
        salvar_arq.close();
        return true;
    }
    //MÉTODO LER DE UM ARQUIVO:
    ifstream ler_arq;
    bool Poly::ler(string nomeArquivo){
        string poly;
        Poly prov;
        delete[] prov.a;
        ler_arq.open(nomeArquivo);
        if(ler_arq.is_open()){
            ler_arq >> poly >> prov.grau;
            prov.a = new double[prov.grau+1];
            if(grau>=0){
                for(int i=0;i<=prov.grau;i++){
                    ler_arq >> prov.a[i];
                }
            }
        }
        ler_arq.close();
        *this = prov;
        return true;
    }
