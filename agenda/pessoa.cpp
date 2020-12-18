#include"pessoa.h"
pessoa::pessoa(char * enderec,char * nom,int idad)
{
    enderec=endereco;
    idad=idade;
    nom=nome;
}
void pessoa::setEndereco(char * endere)
{
    endere=endereco;
};
void pessoa::setNome(char * no)
{
    no = nome;
};
void pessoa::setIdade(int ida)
{
    idade=ida;
};
char * pessoa::getEndereco()
{
    return (endereco);
};
int pessoa::getIdade()
{
    return (idade);
};
char * pessoa::getNome()
{
    return(nome);
};
