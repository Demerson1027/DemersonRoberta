#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
FILE *arq;
typedef struct {
    int id;
    char nome[50];
    int idade;
    float nota1, nota2, media;
} Aluno;

Aluno alunos[MAX];
int total = 0;
int proximoID = 1;
// ====================== ARQUIVO BINÁRIO ======================


void salvarArquivo() {
    FILE *arq = fopen("alunos.dat", "wb");
    if (arq == NULL) {
        printf("Erro ao salvar arquivo!\n");
        return;
    }

    fwrite(&total, sizeof(int), 1, arq);
    fwrite(&proximoID, sizeof(int), 1, arq);
    fwrite(alunos, sizeof(Aluno), total, arq);
    fclose(arq);
}


    void carregarArquivo() {
    FILE *arq = fopen("alunos.dat", "rb");
    if (!arq) {
        total = 0;
        proximoID = 1;
        return;
    }
    fread(&total, sizeof(int), 1, arq);
    fread(&proximoID, sizeof(int), 1, arq);
    fread(alunos, sizeof(Aluno), total, arq);
    fclose(arq);
}

void mostrarArquivo() {
    FILE *arq = fopen("alunos.dat", "rb");
    if (arq == NULL) {
        printf("Nenhum arquivo encontrado!\n");
        return;
    }

    int totalArquivo;
    int proxIDArquivo;
    Aluno temp[MAX];

    // Lê os valores do arquivo
    fread(&totalArquivo, sizeof(int), 1, arq);
    fread(&proxIDArquivo, sizeof(int), 1, arq);
    fread(temp, sizeof(Aluno), totalArquivo, arq);

    fclose(arq);

    printf("\n=== DADOS SALVOS NO ARQUIVO ===\n");
    printf("Total de alunos: %d\n", totalArquivo);
    printf("Proximo ID gravado: %d\n\n", proxIDArquivo);

    for (int i = 0; i < totalArquivo; i++) {
        printf("ID: %d\n", temp[i].id);
        printf("Nome: %s\n", temp[i].nome);
        printf("Idade: %d\n", temp[i].idade);
        printf("Media: %.2f\n", temp[i].media);
        printf("-----------------------------\n");
    }
}

    



// =============================================================

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void CadastrarAlunos() {
    arq = fopen("alunos.dat" , "wb");
    if (total >= MAX) {
        printf("Limite atingido!\n");
        return;
    }

    limparBuffer();  
    alunos[total].id = proximoID;
    proximoID++;

    printf("\nCadastro do aluno (ID: %d)\n", alunos[total].id);
    printf("Digite o Nome Completo: ");
    fgets(alunos[total].nome, 50, stdin);
    alunos[total].nome[ strcspn(alunos[total].nome, "\n") ] = '\0';

    printf("Digite a idade: ");
    scanf("%d", &alunos[total].idade);

    printf("\nAluno %s cadastrado com sucesso!\n", alunos[total].nome);
    total++;
    salvarArquivo();
    fclose(arq);
}

void consultarPorID() {
    int id;
    printf("\nDigite o ID para consulta: ");
    scanf("%d", &id);

    for (int i = 0; i < total; i++) {
        if (alunos[i].id == id) {
            printf("\n--- Aluno Encontrado ---\n");
            printf("ID: %d\n", alunos[i].id);
            printf("Nome: %s\n", alunos[i].nome);
            printf("Idade: %d\n", alunos[i].idade);
            return;
        }
    }

    printf("Aluno não encontrado!\n");
}

void consultarporNome() {

    char nomebusca[50];
    int encontrou = 0;

    limparBuffer();
    printf("\nDigite o nome para consulta: ");
    fgets(nomebusca, 50, stdin);
    nomebusca[ strcspn(nomebusca, "\n") ] = '\0';

    for (int i = 0; i < total; i++) {
        if (strstr(alunos[i].nome, nomebusca) != NULL) {
            printf("\n--- Aluno Encontrado ---\n");
            printf("ID: %d\n", alunos[i].id);
            printf("Nome: %s\n", alunos[i].nome);
            printf("Idade: %d\n", alunos[i].idade);
            encontrou = 1;
            return;
        }
    }

    if (!encontrou)
        printf("Aluno nao encontrado!\n");

}

void listaTodososalunos() {
    printf("\n--- Lista de Todos os Alunos (%d) ---\n", total);

    if (total == 0) {
        printf("Nenhum aluno cadastrado!\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("ID: %d\n", alunos[i].id);
        printf("Nome: %s\n", alunos[i].nome);
        printf("Idade: %d\n", alunos[i].idade);
        printf("---------------------------\n");
    }
}


void deletarAluno() {
    int id;
    int encontrou = 0;

    printf("\nDigite o ID do aluno que deseja deletar: ");
    scanf("%d", &id);

    for (int i = 0; i < total; i++) {
        if (alunos[i].id == id) {

            // Move todos os alunos depois dele uma posição para trás
            for (int j = i; j < total - 1; j++) {
                alunos[j] = alunos[j + 1];
            }

            total--;
            salvarArquivo();

            printf("Aluno removido com sucesso!\n");

            encontrou = 1;
            break;
        }
    }

    if (!encontrou) {
        printf("Aluno com ID %2não encontrado!\n", id);
    }
    salvarArquivo();
}


void AlunoparaNota(){
    float Notas;
    float Soma = 0;
    int id;
    int provas;
    int encontrado = 0;
    printf("\nDigite o ID do aluno que deseja colocar a nota: ");
    scanf("%d", &id);

    for (int i = 0; i < total; i++) {
        if (alunos[i].id == id) {

        encontrado = 1;
            printf("\n--- Aluno Encontrado ---\n");
            printf("Nome: %s\n", alunos[i].nome);

    printf("\nQuantas provas voce quer calcular a media: ");
    scanf("%d",&provas);
    for (int p = 0; p < provas; p++)
    {
        printf("Nota %d: ",p + 1);
        scanf("%f",&Notas);
        Soma = Soma + Notas;


    }
    alunos[i].media = Soma / provas;
    
    printf("A media do aluno %s e %.2f",alunos[i].nome,alunos[i].media);  
    salvarArquivo();
    return;
    }
  }

printf("\naluno nao encontrado ");


}





int main() {
    carregarArquivo();

    int opcao;
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Cadastrar Alunos\n");
        printf("2 - Consultar Alunos\n");
        printf("3 - Deletar Aluno\n");
        printf("4 - Notas\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: CadastrarAlunos(); break;
            case 2: menuConsulta(); break;
            case 3: deletarAluno();break;
            case 4: notasTela();break;
            case 5: mostrarArquivo();break;
            
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}





void MediaAlunosCadastrados() {
    carregarArquivo();

    if (total == 0) {
        printf("\n====================================\n");
        printf("    Nenhum aluno cadastrado!\n");
        printf("====================================\n");
        return;
    }

    printf("\n====================================\n");
    printf("      MEDIA DE TODOS OS ALUNOS    \n");
    printf("====================================\n");

    for (int i = 0; i < total; i++) {
        printf(" Nome: %s\n", alunos[i].nome);
        printf(" Media: %.2f\n", alunos[i].media);
        printf("-------------------------------\n");
    }

    printf("\n====================================\n");
    printf("         Fim da listagem\n");
    printf("====================================\n");
}


void notasTela(){
    int versao;
    do {
        printf("\n=== Notas ===\n");
        printf("1 - Atribuir Nota\n");
        printf("2 - Exibir a Nota dos alunos\n");
        printf("3 - alterar Notas\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &versao);

        switch (versao) {
        case 1: AlunoparaNota();break;
        case 2: MediaAlunosCadastrados();break;
        case 3: alterarNota();break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }

    } while (versao != 0);

    return;
}



void menuConsulta() {
    int opcao;

    do {
        printf("\n=== CONSULTAR ALUNOS ===\n");
        printf("1 - Consultar por ID\n");
        printf("2 - Consultar por nome\n");
        printf("3 - Listar todos os alunos\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1: consultarPorID(); break;
        case 2: consultarporNome(); break;
        case 3: listaTodososalunos(); break;
        case 4: deletarAluno(); break;

        case 0: return;
        default: printf("Opção inválida!\n");
        }

    } while (opcao != 0);
}



void alterarNota() {
    int id;
    printf("Digite o ID que deseja alterar a nota: ");
    scanf("%d", &id);

    for (int i = 0; i < total; i++) {
        if (alunos[i].id == id) {

        }
    }

    printf("Aluno não encontrado!\n");
}
