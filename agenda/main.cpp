#include"pessoa.h"
int main (void)
{
    pessoa Seus_Dados("e","n",0);
    char endere [50],no [50];
    int idad;
    printf("digite o seu nome\n\n");
    gets(no);
    printf("digite seu endereco\n\n");
    gets(endere);
    printf("digite a sua idade\n\n");
    fflush(stdin);
    scanf("%d",&idad);
    Seus_Dados.setIdade(idad);
    Seus_Dados.setNome(no);
    Seus_Dados.setEndereco(endere);
    system("pause");
    system("cls");
    printf("SEUS DADOS SAO:\n\nNome:%s\n\nIdade:%d\n\nEndereco:%s",Seus_Dados.getNome(),Seus_Dados.getIdade(),Seus_Dados.getEndereco());

    getch();
    return 0;

}
