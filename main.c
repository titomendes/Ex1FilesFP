#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


const char *formatOut="%s,%d,%s,%d,%d\n"; //formato para ser escrito no ficheiro

typedef struct{
    int num;
    char nome[80];
    char curso[80];
    int nota1;
    int nota2;

}Alunos;

void menu(Alunos *aluno);
bool findNumber(int number);
void inserirAlunos();
void mudaNota();
void sairJanela();
void menuClose();

int main()
{
 Alunos *aluno=(Alunos*)malloc(sizeof(aluno));
 menu(aluno);

    return 0;
}

void menu(Alunos *aluno)
{
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
   int numAluno;
   p= fopen("Alunos.dat","r+");//r+ leitura e escrita
   if(p==NULL)
      {
        perror("Erro, arquivo nao aberto");
      }
   printf("Numero do aluno a mudar detalhes: ");
   scanf("%d",&numAluno);
   //começar aqui usar strtok para chegar a linha onde esta o nome e fazer break.imprimir a linha para ver se esta na linha correcta
}

bool findNumber(int number)
{
    FILE *p;
    char temp[50];
    char d[]=",";
    bool flag=false;

    p= fopen("Alunos.dat","r");
     if(p==NULL)
      {
        perror("Erro, arquivo nao aberto");
      }
     while(!(feof(p)))
     {
        fgets(temp,50,p);
        char *portion= strtok(temp,d);
        while(portion!=NULL)
        {
           if(atoi(portion)==number)
           {
              flag=true;
              break;
           }
          portion=strtok(NULL,d);
        }
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
        scanf("%s",aluno->nome);
        for(int i=0;i<strlen(aluno->nome);i++){
            if((aluno->nome[i])=='.')
            {
                aluno->nome[i]=' ';
            }
        }
        printf("Nota1 do aluno: ");
        scanf("%d",&aluno->nota1);
        printf("Nota2 do aluno: ");
        scanf("%d",&aluno->nota2);
        getchar();
        printf("Curso do aluno: ");
        scanf("%s",aluno->curso);
        for(int i=0;i<strlen(aluno->curso);i++){
            if((aluno->curso[i])=='.')
            {
                aluno->curso[i]=' ';
            }
        }
        fflush(stdin);
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
