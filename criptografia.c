#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 10000
#define SHIFT 3  

char texto[MAX_SIZE]; 
int texto_carregado = 0;


void lerArquivo() {
    char nomeArquivo[100];
    FILE *arquivo;

    printf("Digite o caminho do arquivo para ler: ");
    scanf("%s", nomeArquivo);

    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }


    size_t lidos = fread(texto, sizeof(char), MAX_SIZE - 1, arquivo);
    texto[lidos] = '\0'; 

    fclose(arquivo);
    texto_carregado = 1;
    printf("Arquivo lido com sucesso!\n");
}


void criptografar() {
    if (!texto_carregado) {
        printf("Nenhum texto carregado.\n");
        return;
    }

    for (int i = 0; texto[i] != '\0'; i++) {
        if (isalpha(texto[i])) {
            char base = isupper(texto[i]) ? 'A' : 'a';
            texto[i] = (texto[i] - base + SHIFT) % 26 + base;
        }
    }

    printf("Texto criptografado com sucesso!\n");
    printf("Texto criptografado:\n%s\n", texto);
}


void descriptografar() {
    if (!texto_carregado) {
        printf("Nenhum texto carregado.\n");
        return;
    }

    for (int i = 0; texto[i] != '\0'; i++) {
        if (isalpha(texto[i])) {
            char base = isupper(texto[i]) ? 'A' : 'a';
            texto[i] = (texto[i] - base - SHIFT + 26) % 26 + base;
        }
    }

    printf("Texto descriptografado com sucesso!\n");
    printf("Texto descriptografado:\n%s\n", texto);
}


void salvarArquivo() {
    if (!texto_carregado) {
        printf("Nenhum texto carregado.\n");
        return;
    }

    char nomeArquivo[100];
    FILE *arquivo;

    printf("Digite o caminho do arquivo para salvar: ");
    scanf("%s", nomeArquivo);

    arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao salvar o arquivo.\n");
        return;
    }

    fwrite(texto, sizeof(char), strlen(texto), arquivo);
    fclose(arquivo);

    printf("Arquivo salvo com sucesso!\n");
}


int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1 - Ler arquivo texto\n");
        printf("2 - Criptografar\n");
        printf("3 - Descriptografar\n");
        printf("4 - Salvar arquivo\n");
        printf("5 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();  

        switch (opcao) {
            case 1:
                lerArquivo();
                break;
            case 2:
                criptografar();
                break;
            case 3:
                descriptografar();
                break;
            case 4:
                salvarArquivo();
                break;
            case 5:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 5);

    return 0;
}
