#define _OPEN_SYS_ITOA_EXT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


const char *formatOut="%d,%s,%s,%d,%d\n"; //formato para ser escrito no ficheiro
const char *formatIn="%d,%[^,],%[^,],%d,%d\n";
typedef struct{
    int num;
    char nome[80];
    char curso[80];
    int nota1;
    int nota2;

}Alunos;

void apagarAluno(Alunos *aluno);
void menu(Alunos *aluno);
bool findNumber(int number);
void inserirAlunos(Alunos *aluno);
void mudaNota(Alunos *aluno);
void sairJanela(Alunos *aluno);
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
    printf("\nMudar detalhes: opcao 2");
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

        case 3:
            apagarAluno(aluno);
            break;
    }
}

void mudaNota(Alunos *aluno)
{
   FILE *p;
   int numAluno;
  char d[]=",";
  char temp[50];
  int cont=0;
  bool flag=false;
   p= fopen("Alunos.dat","r+");//r+ leitura e escrita
   if(p==NULL)
      {
        perror("Erro, arquivo nao aberto");
      }
      //encontrar linha do aluno atraves do numero e de um contador
   printf("Numero do aluno a mudar detalhes: ");
   scanf("%d",&numAluno);
     while(!feof(p))
     {
        cont++;
        fgets(temp,50,p);
        char *portion= strtok(temp,d);
        while(portion!=NULL)
        {
           if(atoi(portion)==numAluno)
           {
              flag=true;
           }
          portion=strtok(NULL,d);
        }
        if(flag)
            break;
    }

    rewind(p);
    int cont2=cont;
    int pos=cont2; //posicao para depois gravar na linha certa do ficheiro temporario
    while(cont>1)
    {
        fgets(temp,50,p);
        cont--;
    }
    fscanf(p,formatIn,&aluno->num,aluno->nome,aluno->curso,&aluno->nota1,&aluno->nota2);
    int esc;
    char mud;
    do
    {
        printf("curso(0), nota1(1), nota2(2): ");
        scanf("%d",&esc);
        getchar();

        switch(esc)
        {
            case 2:
                printf("Nova nota: ");
                scanf("%d",&aluno->nota2);
                getchar();
                printf("Mais alguma mudanca?Sim(s),nao(n): ");
                scanf("%c",&mud);
                break;

            case 1:
                printf("Nova nota: ");
                scanf("%d",&aluno->nota1);
                getchar();
                printf("Mais alguma mudanca?Sim(s),nao(n): ");
                scanf("%c",&mud);
                break;

            case 0:
                printf("Novo curso: ");
                fgets(aluno->curso,sizeof(aluno->curso),stdin);
                for(int i=0;i<strlen(aluno->curso);i++)
                {
                    if(aluno->curso[i]=='\n')
                        aluno->curso[i]='\0';
                }
                printf("Mais alguma mudanca?Sim(s),nao(n): ");
                scanf("%c",&mud);
                break;
        }
    }
    while(mud=='s');

    // gravar em ficheiro temporário
     FILE *tempo;
     tempo= fopen("temp_Alunos.dat","w");
     if(tempo==NULL)
      {
        perror("Erro, arquivo nao aberto");
      }

      rewind(p);
      int linha=1;
      int contaLinhas=0;
      while(!feof(p))
      {
          fgets(temp,sizeof(temp),p);
          if(linha==pos)
            fprintf(tempo,formatOut,aluno->num,aluno->nome,aluno->curso,aluno->nota1,aluno->nota2);

          else{
            fputs(temp,tempo);
            }
            contaLinhas++;
            linha++;
          if(contaLinhas==6){
            break;
          }
      }

    fclose(tempo);
    fclose(p);
    free(aluno);
    sairJanela(aluno);
    remove("Alunos.dat");
    rename("temp_Alunos.dat","Alunos.dat");
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
     while(!feof(p))
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
        for(int i=0;i<strlen(aluno->nome);i++){
            if(aluno->nome[i]=='\n')
            {
                aluno->nome[i]='\0';
            }
        }
        printf("Nota1 do aluno: ");
        scanf("%d",&aluno->nota1);
        printf("Nota2 do aluno: ");
        scanf("%d",&aluno->nota2);
        getchar();
        printf("Curso do aluno: ");
        fgets(aluno->curso,sizeof(aluno->curso),stdin);
        for(int i=0;i<strlen(aluno->curso);i++){
            if(aluno->curso[i]=='\n')
            {
                aluno->curso[i]='\0';
            }
        }
        fprintf(p,formatOut,aluno->num,aluno->nome,aluno->curso,aluno->nota1,aluno->nota2);
        fclose(p);
        free(aluno);
        sairJanela(aluno);
}

void apagarAluno(Alunos *aluno){
    FILE *p;
    FILE *tempo;
    int numAluno;
    char d[]=",";
    char temp[50];
    int cont=0;
  bool flag=false;
   p= fopen("Alunos.dat","r+");//r+ leitura e escrita
   tempo= fopen("temp_Alunos.dat","w");
     if(tempo==NULL)
      {
        perror("Erro, arquivo nao aberto");
      }
   if(p==NULL)
      {
        perror("Erro, arquivo nao aberto");
      }
      //encontrar linha do aluno atraves do numero e de um contador
   printf("Numero do aluno a apagar: ");
   scanf("%d",&numAluno);
     while(!feof(p))
     {
        cont++;
        fgets(temp,50,p);
        char *portion= strtok(temp,d);
        while(portion!=NULL)
        {
           if(atoi(portion)==numAluno)
           {
              flag=true;
           }
          portion=strtok(NULL,d);
        }
        if(flag)
            break;
    }
    rewind(p);
    int pos=6;
    while(!feof(p)){
        fgets(temp,sizeof(temp),p);
        cont--;
        pos--;
        if(cont==0)
            continue;
        fputs(temp,tempo);
        if(pos==0)
            break;
    }
    fclose(p);
    fclose(tempo);
    remove("Alunos.dat");
    rename("temp_Alunos.dat","Alunos.dat");

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
