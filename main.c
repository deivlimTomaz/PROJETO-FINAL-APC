#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_ALUNOS 100
#define NOME_MAX 50
#define SENHA_MAX 20

typedef struct {
    int matricula;
    char nome[NOME_MAX];
    char senha[SENHA_MAX];
    int materiasMatriculadas[10];
    int qtdMatriculas;
    int totalCreditos;
} Aluno;

typedef struct {
    int codMateria;
    char nome[50];
    int creditos;
    int tipo; // 1 = Obrigatória; 2 = Específica; 3 = Optativa
} Disciplina;

Disciplina gradeCurricular[10] = {
    {1, "Cálculo 1", 4, 1},
    {2, "Algoritmos e Programação", 4, 1},
    {3, "Engenharia & Ambiente", 4, 1},
    {4, "Introdução à Engenharia", 4, 1},
    {5, "Desenho Industrial Assistido à Computador", 4, 1},
    {6, "Desenvolvimento de Software", 2, 3},
    {7, "Orientação a Objetos", 2, 2},
    {8, "Física 1", 4, 1},
    {9, "Introdução à Álgebra Linear", 4, 1},
    {10, "Estrutura de Dados 1", 2, 3},
};

Aluno listaAlunos[MAX_ALUNOS];
int totalAlunos = 0;
int alunoLogalIndex = -1; // Não logado

void menuPrincipal();
void cadastro();
void login();
void menuAluno(int detalhesAluno);
void fazerMatricula(int detalhesAluno);
void trancarMatricula(int detalhesAluno);
void mostrarMaterias(int detalhesAluno);
void limparBuffer();

int main(){
    setlocale(LC_ALL, "portuguese");
    int opcao = 0;

    do {
        menuPrincipal();
        scanf("%d", &opcao);
        system("cls");
        limparBuffer();

        switch (opcao){
            case 1:
                login();
                break;
            case 2:
                cadastro();
                break;
            case 3:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nDigite uma opção válida!\n");
                break;
        }

        if (opcao != 3){
            printf("Pressione ENTER para continuar...");
            getchar();
            system("cls");

        }
    } while (opcao != 3);
}

void limparBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void menuPrincipal(){
    printf("\n=======================================\n");
    printf("\n\tPORTAL SIGAA - UnB\n");
    printf("\n=======================================\n");

    printf("1) - Login\n");
    printf("2) - Cadastro\n");
    printf("3) - Sair do portal\n");
    printf("-> ");
}

void cadastro(){
    if (totalAlunos >= MAX_ALUNOS){
        printf("Erro: Limite de alunos atingidos!\n");
        return;
    }

    printf("\n\t>>FICHA DE CADASTRO<<\n");

    puts("Digite seu nome completo:");
    fgets(listaAlunos[totalAlunos].nome, NOME_MAX, stdin);
    listaAlunos[totalAlunos].nome[strcspn(listaAlunos[totalAlunos].nome, "\n")] = 0;
    printf("\n");

    puts("Crie a sua senha: ");
    scanf("%s", listaAlunos[totalAlunos].senha);
    printf("\n");
    limparBuffer();
    system("cls");

    int novaMatricula = 2025000 + totalAlunos;
    listaAlunos[totalAlunos].matricula = novaMatricula;

    printf("Seu cadastro foi realizado com sucesso!\n\n");
    printf("Anote sua matrícula para o login: %d\n\n", novaMatricula);

    totalAlunos++;
}

void login(){
    int matDigitada;
    char senhaDigitada[SENHA_MAX];
    int encontrarLogin = 0; // flag

    printf("\n\t>> LOGIN <<\n");

    puts("Matrícula:");
    scanf("%d", &matDigitada);
    limparBuffer();

    puts("Senha:");
    scanf("%s", senhaDigitada);
    limparBuffer();

    for (int i = 0; i < totalAlunos; i++){
        if ((matDigitada == listaAlunos[i].matricula) && (strcmp(listaAlunos[i].senha, senhaDigitada) == 0)){
            menuAluno(i);
            encontrarLogin = 1;
            break;
        }
    }

    if (encontrarLogin == 0){
        printf("A matrícula ou a senha estão errados, tente novamente!\n");
    }
}

void menuAluno(int detalhesAluno){
    int opcaoMenuAluno = 0;

    do {
        system("cls");

        printf("\nOlá, %s, bem-vindo(a) ao SIGAA - UnB.\n\n", listaAlunos[detalhesAluno].nome);

        puts("Qual procedimento você deseja fazer?\n");

        puts("1) - Realizar matrícula");
        puts("2) - Trancar matrícula");
        puts("3) - Matrículas em andamento");
        puts("4) - Logout (sair)");
        printf("-> ");
        scanf("%d", &opcaoMenuAluno);
        limparBuffer();
        system("cls");

        switch (opcaoMenuAluno){
            case 1:
                fazerMatricula(detalhesAluno);
                break;
            case 2:
                trancarMatricula(detalhesAluno);
                break;
            case 3:
                mostrarMaterias(detalhesAluno);
                break;
            case 4:
                printf("Fazendo logout...\n");
                break;
            default:
                printf("Escolha uma opção válida!\n");
                break;
        }

        if (opcaoMenuAluno != 4){
            printf("\nPressione ENTER para voltar ao menu do aluno...");
            getchar();
        }
    } while (opcaoMenuAluno != 4);
}

void fazerMatricula(int detalhesAluno){
    int codDigitado;
    int materiaEncontrada = -1;

    if (listaAlunos[detalhesAluno].qtdMatriculas >= 7){
        printf("\n Erro: Você atingiu o limite máximo de matérias!\n");
        return;
    }

    printf("\n\t>> MATÉRIAS DISPONÍVEIS <<\n\n");

    for (int i = 0; i < 10; i++){
        printf("Código: %d | Nome: %s | Créditos: %d | Tipo: %s\n",
        gradeCurricular[i].codMateria,
        gradeCurricular[i].nome,
        gradeCurricular[i].creditos,
        (gradeCurricular[i].tipo == 1) ? "Obrigatória" : (gradeCurricular[i].tipo == 2) ? "Específica" : "Optativa");
    }

    puts("\nDigite o código da matéria que deseja cursar:");
    printf("-> ");
    scanf("%d", &codDigitado);
    limparBuffer();
    system("cls");

    for (int i = 0; i < 10; i++){
        if (gradeCurricular[i].codMateria == codDigitado){
            materiaEncontrada = i;
            break;
        }
    }

    if (materiaEncontrada == -1){
        printf("\nErro: Código da matéria inválido!\n");
        return;
    }

    for (int i = 0; i < listaAlunos[detalhesAluno].qtdMatriculas; i++){
        if (listaAlunos[detalhesAluno].materiasMatriculadas[i] == codDigitado){
            printf("Você já está matriculado nessa matéria!\n");
            return;
        }
    }

    int posicaoVazia = listaAlunos[detalhesAluno].qtdMatriculas;
    listaAlunos[detalhesAluno].materiasMatriculadas[posicaoVazia] = codDigitado;
    listaAlunos[detalhesAluno].totalCreditos += gradeCurricular[materiaEncontrada].creditos;
    listaAlunos[detalhesAluno].qtdMatriculas++;

    printf("Você foi matriculado em %s\n", gradeCurricular[materiaEncontrada].nome);
}

void trancarMatricula(int detalhesAluno){
    int codDigitado;
    int iAluno = -1;
    int removerCredito = 0;

    printf("\n\t TRANCAMENTO DE MATRÍCULAS \n");
    printf("\n");
    puts("Digite o código da matrícula: ");
    scanf("%d", &codDigitado);
    limparBuffer();

    for (int i = 0; i < listaAlunos[detalhesAluno].qtdMatriculas; i++){
        if (codDigitado == listaAlunos[detalhesAluno].materiasMatriculadas[i]){
            iAluno = i;
            break;
        }
    }

    if (iAluno == -1){
        printf("Você não está cursando essa matéria!\n");
        return;
    }

    for (int i = 0; i < 10; i++){
        if (codDigitado == gradeCurricular[i].codMateria){
            removerCredito = gradeCurricular[i].creditos;
            break;
        }
    }

    for (int i = iAluno; i < listaAlunos[detalhesAluno].qtdMatriculas - 1; i++){
        listaAlunos[detalhesAluno].materiasMatriculadas[i] = listaAlunos[detalhesAluno].materiasMatriculadas[i + 1];
    }

    listaAlunos[detalhesAluno].totalCreditos -= removerCredito;
    listaAlunos[detalhesAluno].qtdMatriculas--;

    printf("Matrícula trancada com sucesso!\n");
}

void mostrarMaterias(int detalhesAluno){
    int totalCreditos = 0;
    int totalHoras = 0;
    int horas = 0;
    int codAtual;

    if (listaAlunos[detalhesAluno].qtdMatriculas == 0){
        printf("No momento, você não está matriculado em nenhuma matéria!\n");
        return;
    }

    printf("\n\t MINHAS MATRÍCULAS \n\n");

    printf("%-35s | %-10s | %-10s\n", "Disciplina", "Créditos", "Horas (est.)");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < listaAlunos[detalhesAluno].qtdMatriculas; i++){
        codAtual = listaAlunos[detalhesAluno].materiasMatriculadas[i];

        for (int j = 0; j < 10; j++){
            if (gradeCurricular[j].codMateria == codAtual){
                horas = gradeCurricular[j].creditos * 15;

                printf("%-35s | %-10d | %-10d\n", gradeCurricular[j].nome, gradeCurricular[j].creditos, horas);

                totalCreditos = totalCreditos += gradeCurricular[j].creditos;

                totalHoras += horas;

                break;
            }
        }
    }

    printf("---------------------------------------------------------------\n");
    printf("%-35s | %-10d | %-10d\n", "TOTAL ACUMULADO: ", totalCreditos, totalHoras);
}