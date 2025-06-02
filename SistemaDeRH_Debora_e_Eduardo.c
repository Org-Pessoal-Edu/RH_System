#include <stdio.h>
#include <string.h> //função strcmp() para comparar strings
#include <ctype.h> //função tolower() para deixar letras minúsculas
#include <stdlib.h> //função system() para execução de comandos no terminal

//Criação da estrutura de uma árvore binária
typedef struct T_no T_no;
struct T_no {
 int CPF;
 char Nome[50];
 T_no *esq, *dir;
};
T_no *arvoreCPF; //Criando um ponteiro para a raíz da árvore (inicia como NULL)

//Função para inserir um funcionário
void inserir(char *vetor, int cpf){
    T_no *novo = (T_no*)malloc(sizeof(T_no));
    if (!novo) {
        printf("Erro de alocação de memória.\n");
        return;
    }

    novo->CPF = cpf;
    strcpy(novo->Nome, vetor);
    novo->esq = novo->dir = NULL;

    if (arvoreCPF == NULL) {
        arvoreCPF = novo;
        return;
    }

    T_no *atual = arvoreCPF, *pai = NULL;
    while (atual != NULL) {
        pai = atual;
        if (cpf == atual->CPF) {
            printf("CPF já cadastrado!\n");
            free(novo);
            return;
        } else if (cpf < atual->CPF) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    if (cpf < pai->CPF) pai->esq = novo;
    else pai->dir = novo;
}

//Função para remover um funcionário através do CPF
T_no* removerRec(T_no *raiz, int cpf){
    if (raiz == NULL) {
        printf("Funcionário com CPF %d não encontrado.\n", cpf);
        return NULL;
    }

    if (cpf < raiz->CPF) {
        raiz->esq = removerRec(raiz->esq, cpf);
    } else if (cpf > raiz->CPF) {
        raiz->dir = removerRec(raiz->dir, cpf);
    } else {
        // Encontrado
        if (raiz->esq == NULL) {
            T_no *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            T_no *temp = raiz->esq;
            free(raiz);
            return temp;
        } else {
            // Dois filhos: encontrar o menor da subárvore direita
            T_no *temp = raiz->dir;
            while (temp->esq != NULL) temp = temp->esq;
            raiz->CPF = temp->CPF;
            strcpy(raiz->Nome, temp->Nome);
            raiz->dir = removerRec(raiz->dir, temp->CPF);
        }
    }
    return raiz;
}

void remover(int cpf){
    arvoreCPF = removerRec(arvoreCPF, cpf);
}

//Função para buscar um funcionário através do CPF
void buscar(int cpf){
    T_no *atual = arvoreCPF;
    while (atual != NULL) {
        if (cpf == atual->CPF) {
            printf("Funcionário encontrado:\nNome: %s\nCPF: %d\n", atual->Nome, atual->CPF);
            return;
        } else if (cpf < atual->CPF) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }
    printf("Funcionário com CPF %d não encontrado.\n", cpf);
}

//Função para listar funcionários em ordem crescente de CPF
void listarRec(T_no *raiz) {
    if (raiz == NULL) return;
    listarRec(raiz->esq);
    printf("Nome: %s | CPF: %d\n", raiz->Nome, raiz->CPF);
    listarRec(raiz->dir);
}

void listar(){
    listarRec(arvoreCPF);
}

void limparTela(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

//Função para ler strings e frases (Além de remover o enter do usuário da memória)
void sget( char* vetor, int tam){
    fflush(stdin); //Limpar teclas antigas
    if (fgets(vetor, tam, stdin)){
        int i;
        for( i=0; vetor[i] != '\n' && vetor[i]; ++i);
        vetor[i] = '\0';
    }
}

//Função para padronizar todas as letras de input do usuário minúsculas (facilitando comparações)
//Utiliza a biblioteca <ctype.h>
void padronizarLetras( char *vetor){
    for( int i = 0; vetor[i] != '\0' && vetor[i]; ++i){
        vetor[i] = tolower(vetor[i]); //tolower deixa o caractere minúsculo
    }
}

//Função do menu principal
int menu(){
    int tamOpcao = 20;
    int tamNome = 50;
    char opcao[tamOpcao];
    char nome[tamNome];
    int cpf;

    //Chamada da função que limpa a tela
    limparTela();

    //Menu e escolha de opções
    printf("\nBem vindo ao RH System! Gerenciamento de ponta para o seu negocio!\n");
    printf("\n======================================\n");
    printf("Menu de funcionalidades:\n- Inserir\n- Remover\n- Buscar\n- Listar\n- Sair");
    printf("\n======================================\n");
    printf("Digite uma das opcoes: ");
    sget( opcao, tamOpcao);

    //Chamada da função que diminui todas as letras
    padronizarLetras(opcao); 

    //Comparações da opção digitada pelo usuário
    //Verifica se é a função inserir (strcmp retornará 0 se sim)
    if(strcmp(opcao, "inserir") == 0){
        printf("\nInsira o nome do funcionario: ");
        sget(nome, tamNome);
        printf("\nInsira o CPF do funcionario: ");
        scanf("%d", &cpf);
        fflush(stdin);
        inserir(nome, cpf);
    }
    //Verifica se é a função remover (strcmp retornará 0 se sim)
    else if(strcmp(opcao, "remover") == 0){
        printf("\nInsira o CPF do funcionario: ");
        scanf("%d", &cpf);
        fflush(stdin);
        //remover(cpf);
    }
    //Verifica se é a função buscar (strcmp retornará 0 se sim)
    else if(strcmp(opcao, "buscar") == 0){
        printf("\nInsira o CPF do funcionario: ");
        scanf("%d", &cpf);
        fflush(stdin);
        //buscar(cpf);
    }
    //Verifica se é a função listar (strcmp retornará 0 se sim)
    else if(strcmp(opcao, "listar") == 0){
        printf("\nClientes em ordem de CPF:\n");
        //listar();
    }
    //Verifica se quer sair (strcmp retornará 0 se sim)
    else if(strcmp(opcao, "sair") == 0){
        return 0;
    }

    else{ //Caso digite algo diferente
        printf("Opcao Invalida! Digite apenas umas das opcoes..."); 
    }

    printf("\nPressione Enter para continuar..."); //Já que a tela será limpa, deixei uma confirmação antes
    getchar(); //Espera um input da tecla Enter do usuário;
    return 1; //Retorna 1 para o while continuar rodando até o usuário digitar sair
}
//Função main, apenas responsável por executar o Menu
//Criei uma função para o menu para modularizar o código e abrir espaço para futuras melhorias
int main(void){
    while(menu() != 0); //O próprio while chama o menu(), então não precisa criar o corpo da função {}
    return 0;
}
