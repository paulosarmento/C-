#include<conio.h>
#include<stdio.h>
#include<windows.h>

class pessoa
{
    private:
    char * endereco;
    int idade;
    char * nome;

    public:
    void setNome(char*no);
    void setIdade(int ida);
    void setEndereco(char*endere);
    int getIdade();
    char * getEndereco();
    char * getNome();
    pessoa(char * enderec,char * nom,int idad);
};
