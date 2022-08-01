#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Funções.h"

const char *formatOut="%s%d\n%s%d\n%d\n\n"; //formato para ser escrito no ficheiro

typedef struct{
    int num;
    char nome[50];
    char curso[20];
    int nota1;
    int nota2;

}Alunos;

void menu(Alunos *aluno);
bool findNumber(int number);
void inserirAlunos();
void mudaNota();
void sairJanela();
void menuClose();

int main(){

 Alunos *aluno=(Alunos*)malloc(sizeof(aluno));
 menu(aluno);

    return 0;
}

void menu(Alunos *aluno){
    printf("Inserir aluno: opcao 1");
    printf("\nMudar de nota: opcao 2");
    printf("\nApagar contas: opcao 3\n");

    int opcao;
    scanf("%d",&opcao);

    switch(opcao){
        case 1:
            inserirAlunos(aluno);

            break;
        case 2:
            mudaNota(aluno);
            break;

        /*case 3:
            apagar(contas);
            break;*/
    }
}

void mudaNota(Alunos *aluno)
{
   FILE *p;
   char nomes[30];
   char temp[30];
   char atributos[5][20];
  // const char *formatIn="%s\n%d\n%s%\n%d\n%d";
   p= fopen("Alunos.dat","r+");//r+ leitura e escrita
   if(p==NULL)
      {
        perror("Erro, arquivo nao aberto");
      }
   printf("Nome completo do aluno a mudar notas: ");
   getchar();
   fgets(nomes,sizeof(nomes),stdin);
   while(!(feof(p)))
   {
       fgets(temp,sizeof(temp),p);
       if(strcmp(temp,nomes)==0)
       {
             strcpy(aluno->nome,temp);
            break;
       }
    }
     fgets(temp,sizeof(temp),p);
     aluno->num=atoi(temp);
    fgets(temp,sizeof(temp),p);
    strcpy(aluno->curso,temp);
    fgets(temp,sizeof(temp),p);
    aluno->nota1=atoi(temp);
    fgets(temp,sizeof(temp),p);
    aluno->nota2=atoi(temp);

    char escolha[30];
    char nota1="nota 1";
    printf("O que deseja mudar?");
    fgets(escolha,30,stdin);
    /*if(strcmp(escolha,nota1)==0)
    {
        printf("Insira a nota: ");
        scanf("%d",&aluno->nota1);
    }*/
    printf("%d",aluno->nota1);


}

bool findNumber(int number)
{
    FILE *p;
    p= fopen("Alunos.dat","r");
     if(p==NULL)
      {
        perror("Erro, arquivo nao aberto");
      }
    bool flag=false;
    char temp[20];
    int value;
    while(!(feof(p)))
    {
        fgets(temp,sizeof(temp),p);
        value=atoi(temp);
        if(value==number){
           flag=true;
            break;
         }
         else
        flag=false;
    }
    fclose(p);
    return flag;

}

void inserirAlunos(Alunos *aluno)
{
    FILE *p;
    p= fopen("Alunos.dat","a+");//a+ anexar novos dados e podes escrever e ler
      if(p==NULL)
      {
        perror("Erro, arquivo nao aberto");
      }
        getchar();
        printf("Numero do aluno: ");
        scanf("%d",&aluno->num);
        while(findNumber(aluno->num)==true)
        {
            printf("Numero ja existe,insira outro: ");
            scanf("%d",&aluno->num);
        }
        getchar();
        printf("Nome do aluno:");
        fgets(aluno->nome,sizeof(aluno->nome),stdin);
        printf("Nota1 do aluno: ");
        scanf("%d",&aluno->nota1);
        printf("Nota2 do aluno: ");
        scanf("%d",&aluno->nota2);
        getchar();
        printf("Curso do aluno: ");
        fgets(aluno->curso,sizeof(aluno->curso),stdin);
        fprintf(p,formatOut,aluno->nome,aluno->num,aluno->curso,aluno->nota1,aluno->nota2);
        fclose(p);
        free(aluno);
        sairJanela();
}

void sairJanela(Alunos *aluno){

    int opcao;
    printf("Deseja sair(0) ou voltar ao menu principal(1)");
    scanf("%d",&opcao);
    if(opcao==1)
        menu(aluno);
    else
        menuClose();
}

void menuClose(){

    printf("Acabou");

}
