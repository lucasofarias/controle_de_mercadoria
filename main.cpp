#include <iostream>
#include <iomanip>
#include <locale>

using namespace std;

struct informacoes {

    char produto[20];
    char fornecedor[20];
    int quantidade;
    float preco;
};

void menu() {

        cout << endl << "\t/===============================================================================\\" << endl;
        cout << "\t|                                                                               |" << endl;
        cout << "\t|                               BEM VINDO AO MENU                               |" << endl;
        cout << "\t|                                                                               |" << endl;
        cout << "\t|   1  - Entra dados do produto.                                                |" << endl;
        cout << "\t|   2  - Lista todos os produtos na tela.                                       |" << endl;
        cout << "\t|   3  - Pesquisar um produto pelo nome completo.                               |" << endl;
        cout << "\t|   4  - Pesquisar por fornecedor completo.                                     |" << endl;
        cout << "\t|   5  - Pesquisa produtos por faixa de preço.                                  |" << endl;
        cout << "\t|   6  - Altera quantidade em estoque (entrada e saída) pesquisado pelo nome.   |" << endl;
        cout << "\t|   7  - Altera o preço de um produto pesquisado pelo nome completo.            |" << endl;
        cout << "\t|   8  - Altera produto pesquisado pelo nome completo.                          |" << endl;
        cout << "\t|   9  - Exclui produto pesquisado pelo nome completo.                          |" << endl;
        cout << "\t|   10 - Fim.                                                                   |" << endl;
        cout << "\t|                                                                               |" << endl;
        cout << "\t\\===============================================================================/" << endl << endl;
}

void cadastrarDados(struct informacoes *ponteiroInformacoes, int tamanho) {

    cout << "Digite o nome do fornecedor: ";
    cin >> ponteiroInformacoes->fornecedor;

    cout << "Digite o nome do produto: ";
    cin >> ponteiroInformacoes->produto;

    cout << "Digite o preço do produto: ";
    cin >> ponteiroInformacoes->preco;

    cout << "Digite a quantidade disponível: ";
    cin >> ponteiroInformacoes->quantidade;

    FILE *ponteiroArquivo;
    ponteiroArquivo = fopen("dados.txt", "a");

    fwrite(ponteiroInformacoes, tamanho, 1, ponteiroArquivo);
    fclose(ponteiroArquivo);
}

void lerDados(struct informacoes *ponteiroInformacoes, int tamanho) {

    FILE *ponteiroArquivo;
    ponteiroArquivo = fopen("dados.txt", "r");

    if(ponteiroArquivo == NULL) {
        cout << "Erro: o arquivo 'dados.txt' não foi encontrado." << endl;
        exit(0);
    }

    for( ; ; ) {
        int a = fread(ponteiroInformacoes, tamanho, 1, ponteiroArquivo);

        if(a == 0) {
            break;
        }

        else if(ponteiroInformacoes->produto[0] != '*') {

            cout << "\t***********************" << endl;
            cout << "\tFornecedor: " << ponteiroInformacoes->fornecedor << endl;
            cout << "\tProduto: " << ponteiroInformacoes->produto << endl;
            cout << "\tPreço: " << ponteiroInformacoes->preco << endl;
            cout << "\tQuantidade: " << ponteiroInformacoes->quantidade << endl;
            cout << "\t***********************" << endl << endl;
        }
    }

    fclose(ponteiroArquivo);
}

void pesquisarProduto(struct informacoes *ponteiroInformacoes, int tamanho) {

    FILE *ponteiroArquivo;
    ponteiroArquivo = fopen("dados.txt", "r");

    if(ponteiroArquivo == NULL) {
        cout << "Erro: o arquivo 'dados.txt' não foi encontrado." << endl;
        exit(0);
    }

    int i;
    int achouProduto = 0;
    char nomeProduto[20];

    cout << "Digite o nome completo do produto: ";
    cin >> nomeProduto;

    for( ; ; ) {

        int a = fread(ponteiroInformacoes, tamanho, 1, ponteiroArquivo);

        if(a == 0) {
            break;
        }

        for(i = 0; nomeProduto[i] != '\0'; i++) {
            if(nomeProduto[i] != ponteiroInformacoes->produto[i]) {
                break;
            }
        }

        if(nomeProduto[i] == '\0' && ponteiroInformacoes->produto[i] == '\0') {
            cout << "Fornecedor: " << ponteiroInformacoes->fornecedor << endl;
            cout << "Produto: " << ponteiroInformacoes->produto << endl;
            cout << "Preço: " << ponteiroInformacoes->preco << endl;
            cout << "Quantidade: " << ponteiroInformacoes->quantidade << endl << endl;

            achouProduto++;
        }
    }

    if(achouProduto == 0) {
        cout << endl << "Nenhum produto com o nome '" << nomeProduto << "' foi encontrado." << endl;
    }

    fclose(ponteiroArquivo);
}

void pesquisarFornecedor(struct informacoes *ponteiroInformacoes, int tamanho) {

    FILE *ponteiroArquivo;
    ponteiroArquivo = fopen("dados.txt", "r");

    if(ponteiroArquivo == NULL) {
        cout << "Erro: o arquivo 'dados.txt' não foi encontrado." << endl;
        exit(0);
    }

    int i;
    int achouFornecedor = 0;
    char nomeFornecedor[20];

    cout << "Digite o nome completo do produto: ";
    cin >> nomeFornecedor;

    for( ; ; ) {

        int a = fread(ponteiroInformacoes, tamanho, 1, ponteiroArquivo);

        if(a == 0) {
            break;
        }

        for(i = 0; nomeFornecedor[i] != '\0'; i++) {

            if(nomeFornecedor[i] != ponteiroInformacoes->fornecedor[i]) {
                break;
            }
        }

        if(ponteiroInformacoes->produto[0] != '*') {

            if(nomeFornecedor[i] == '\0' && ponteiroInformacoes->fornecedor[i] == '\0') {

                cout << "Fornecedor: " << ponteiroInformacoes->fornecedor << endl;
                cout << "Produto: " << ponteiroInformacoes->produto << endl;
                cout << "Preço: " << ponteiroInformacoes->preco << endl;
                cout << "Quantidade: " << ponteiroInformacoes->quantidade << endl << endl;

                achouFornecedor++;
            }
        }
    }

    if(achouFornecedor == 0) {
        cout << "Nenhum fornecedor com o nome '" << nomeFornecedor << "' foi encontrado." << endl;
    }
}

void faixaDePreco(struct informacoes *ponteiroInformacoes, int tamanho) {

    FILE *ponteiroArquivo;
    ponteiroArquivo = fopen("dados.txt", "r");

    if(ponteiroArquivo == NULL) {
        cout << "Erro: o arquivo 'dados.txt' não foi encontrado." << endl;
        exit(0);
    }

    int achouProduto = 0;

    float valorMin;
    float valorMax;

    cout << "Digite um valor mínimo: ";
    cin >> valorMin;

    cout << "Agora digite um valor máximo: ";
    cin >> valorMax;

    for( ; ; ) {

        int a = fread(ponteiroInformacoes, tamanho, 1, ponteiroArquivo);

        if(a == 0) {
            break;
        }

        if(ponteiroInformacoes->preco >= valorMin && ponteiroInformacoes->preco <= valorMax) {

            if(!(ponteiroInformacoes->produto[0] == '*')) {

                cout << endl << "\t***********************" << endl;
                cout << "\tFornecedor: " << ponteiroInformacoes->fornecedor << endl;
                cout << "\tProduto: " << ponteiroInformacoes->produto << endl;
                cout << "\tPreço: " << ponteiroInformacoes->preco << endl;
                cout << "\tQuantidade: " << ponteiroInformacoes->quantidade << endl;
                cout << "\t***********************" << endl << endl;

                achouProduto++;
            }
        }
    }

    if(achouProduto == 0) {
        cout << "Nenhum produto na faixa R$" << valorMin << " - R$" << valorMax << " foi encontrado." << endl;
    }
}

void alterarEstoque(struct informacoes *ponteiroInformacoes, int tamanho) {

    FILE *ponteiroArquivo;
    ponteiroArquivo = fopen("dados.txt", "r");

    if(ponteiroArquivo == NULL) {
        cout << "Erro: o arquivo 'dados.txt' não foi encontrado." << endl;
        exit(0);
    }

    int i;
    int achouProduto = 0;
    char nomeProduto[20];

    cout << "Digite o nome completo do produto: ";
    cin >> nomeProduto;

    int registro = 0;

    for( ; ; ) {

        int a = fread(ponteiroInformacoes, tamanho, 1, ponteiroArquivo);

        if(a == 0) {
            break;
        }

        for(i = 0; nomeProduto[i] != '\0'; i++) {

            if(nomeProduto[i] != ponteiroInformacoes->produto[i]) {
                registro++;
                break;
            }
        }
    }

    if(nomeProduto[i] == '\0' && ponteiroInformacoes->produto[i] == '\0') {

        cout << endl << "\t***********************" << endl;
        cout << "\tFornecedor: " << ponteiroInformacoes->fornecedor << endl;
        cout << "\tProduto: " << ponteiroInformacoes->produto << endl;
        cout << "\tPreço: " << ponteiroInformacoes->preco << endl;
        cout << "\tQuantidade: " << ponteiroInformacoes->quantidade << endl;
        cout << "\t***********************" << endl << endl;

        achouProduto++;

        cout << "Alterar estoque do produto '" << ponteiroInformacoes->produto << "':" << endl;
        cout << "Número positivo = aumenta o estoque." << endl;
        cout << "Número negativo = diminui o estoque." << endl;

        int alteraEstoque;

        cout << "--> ";
        cin >> alteraEstoque;

        if(alteraEstoque < 0) {

            if((ponteiroInformacoes->quantidade + alteraEstoque) < 0) {

                cout << "Você está tentando retirar mais do que o produto tem disponível." << endl;
            }
        }

        ponteiroInformacoes->quantidade += alteraEstoque;

        fseek(ponteiroArquivo, registro * tamanho, 0);
        fwrite(ponteiroInformacoes, tamanho, 1, ponteiroArquivo);

        cout << "--> Estoque alterado com sucesso <--" << endl;
    }

    if(achouProduto == 0) {
        cout << "Nenhum produto com o nome '" << nomeProduto << "' foi encontrado." << endl;
    }

    fclose(ponteiroArquivo);
}

void alterarPreco(struct informacoes *ponteiroInformacoes, int tamanho) {

    FILE *ponteiroArquivo;
    ponteiroArquivo = fopen("dados.txt", "r");

    if(ponteiroArquivo == NULL) {
        cout << "Erro: o arquivo 'dados.txt' não foi encontrado." << endl;
        exit(0);
    }

    int i;
    int achouProduto = 0;
    char nomeProduto[20];

    cout << "Digite o nome completo do produto: ";
    cin >> nomeProduto;

    int registro = 0;

    for( ; ; ) {

        int a = fread(ponteiroInformacoes, tamanho, 1, ponteiroArquivo);

        if(a == 0) {
            break;
        }

        for(i = 0; nomeProduto[i] != '\0'; i++) {

            if(nomeProduto[i] != ponteiroInformacoes->produto[i]) {

                registro++;
                break;
            }
        }

        if(nomeProduto[i] == '\0' && ponteiroInformacoes->produto[i] == '\0') {

            cout << endl << "\t***********************" << endl;
            cout << "\tFornecedor: " << ponteiroInformacoes->fornecedor << endl;
            cout << "\tProduto: " << ponteiroInformacoes->produto << endl;
            cout << "\tPreço: " << ponteiroInformacoes->preco << endl;
            cout << "\tQuantidade: " << ponteiroInformacoes->quantidade << endl;
            cout << "\t***********************" << endl << endl;

            cout << "Digite um novo preço para o produto '" << ponteiroInformacoes->produto << "': ";
            cin >> ponteiroInformacoes->preco;

            fseek(ponteiroArquivo, registro * tamanho, 0);
            fwrite(ponteiroInformacoes, tamanho, 1, ponteiroArquivo);

            cout << "--> Produto alterado com sucesso <--" << endl;

            achouProduto++;
            break;
        }
    }

    if(achouProduto == 0) {
        cout << "Nenhum produto com o nome '" << nomeProduto << "' foi encontrado." << endl;
    }

    fclose(ponteiroArquivo);
}

void alterarProduto(struct informacoes *ponteiroInformacoes, int tamanho) {

    FILE *ponteiroArquivo;
    ponteiroArquivo = fopen("dados.txt", "r+");

    if(ponteiroArquivo == NULL) {
        cout << "Erro: o arquivo 'dados.txt' não foi encontrado." << endl;
        exit(0);
    }

    int i;
    int achouProduto = 0;
    char nomeProduto[20];

    cout << "Digite o nome completo do produto: ";
    cin >> nomeProduto;

    int registro = 0;

    for( ; ; ) {

        int a = fread(ponteiroInformacoes, tamanho, 1, ponteiroArquivo);

        if(a == 0) {
            break;
        }

        for(i = 0; nomeProduto[i] != '\0'; i++) {

            if(nomeProduto[i] != ponteiroInformacoes->produto[i]) {

                registro++;
                break;
            }
        }

        if(nomeProduto[i] == '\0' && ponteiroInformacoes->produto[i] == '\0') {

            cout << endl << "\t***********************" << endl;
            cout << "\tFornecedor: " << ponteiroInformacoes->fornecedor << endl;
            cout << "\tProduto: " << ponteiroInformacoes->produto << endl;
            cout << "\tPreço: " << ponteiroInformacoes->preco << endl;
            cout << "\tQuantidade: " << ponteiroInformacoes->quantidade << endl;
            cout << "\t***********************" << endl << endl;

            cout << "Digite um novo fornecedor: ";
            cin >> ponteiroInformacoes->fornecedor;

            cout << "Digite um novo nome: ";
            cin >> ponteiroInformacoes->produto;

            cout << "Digite um novo preço: ";
            cin >> ponteiroInformacoes->preco;

            cout << "Digite uma nova quantidade: ";
            cin >> ponteiroInformacoes->quantidade;

            fseek(ponteiroArquivo, registro * tamanho, 0);
            fwrite(ponteiroInformacoes, tamanho, 1, ponteiroArquivo);

            cout << "--> Produto alterado com sucesso <--" << endl;
            achouProduto++;
            break;
        }
    }

    if(achouProduto == 0) {
        cout << "Nenhum produto com o nome '" << nomeProduto << "' foi encontrado." << endl;
    }

    fclose(ponteiroArquivo);
}

void excluirProduto(struct informacoes *ponteiroInformacoes, int tamanho) {

    FILE *ponteiroArquivo;
    ponteiroArquivo = fopen("dados.txt", "r+");

    if(ponteiroArquivo == NULL) {
        cout << "Erro: o arquivo 'dados.txt' não foi encontrado." << endl;
        exit(0);
    }

    int i;
    int achouProduto = 0;
    char nomeProduto[20];

    cout << "Digite o nome completo do produto: ";
    cin >> nomeProduto;

    int registro = 0;

    for( ; ; ) {

        int a = fread(ponteiroInformacoes, tamanho, 1, ponteiroArquivo);

        if(a == 0) {
            break;
        }

        for(i = 0; nomeProduto[i] != '\0'; i++) {

            if(nomeProduto[i] != ponteiroInformacoes->produto[i]) {

                registro++;
                break;
            }
        }

        if(nomeProduto[i] == '\0' && ponteiroInformacoes->produto[i] == '\0') {


            cout << endl << "\t***********************" << endl;
            cout << "\tFornecedor: " << ponteiroInformacoes->fornecedor << endl;
            cout << "\tProduto: " << ponteiroInformacoes->produto << endl;
            cout << "\tPreço: " << ponteiroInformacoes->preco << endl;
            cout << "\tQuantidade: " << ponteiroInformacoes->quantidade << endl;
            cout << "\t***********************" << endl << endl;

            cout << "Você tem certeza de que quer excluir o produto '" << ponteiroInformacoes->produto << "'? (S/N)" << endl << endl;
            cout << "S -> Sim" << endl;
            cout << "N -> Não" << endl;

            char excluirProduto;

            cout << "--> ";
            cin >> excluirProduto;

            while((excluirProduto != 'S' && excluirProduto != 'N') && (excluirProduto != 's' && excluirProduto != 'n')) {

                cout << "Digite apenas 'S' ou 'N'." << endl;
                cout << "--> ";
                cin >> excluirProduto;
            }

            if(excluirProduto == 'S' || excluirProduto == 's') {

                ponteiroInformacoes->produto[0] = '*';

                fseek(ponteiroArquivo, registro * tamanho, 0);
                fwrite(ponteiroInformacoes, tamanho, 1, ponteiroArquivo);

                cout << "--> Produto excluído com sucesso <--" << endl;
            }

            achouProduto++;
            break;
        }
    }

    if(achouProduto == 0) {
        cout << "Nenhum produto com o nome '" << nomeProduto << "' foi encontrado." << endl;
    }

    fclose(ponteiroArquivo);
}

int main() {

    setlocale(LC_ALL, "");
    cout << setprecision(2) << fixed;

    struct informacoes produto;

    int tamanho;
    tamanho = sizeof(produto);

    int opcao;

    do {

        menu();

        cout << "--> ";
        cin >> opcao;

        system("cls || clear");

        switch(opcao) {

            case 1:
                cadastrarDados(&produto, tamanho);
            break;

            case 2:
                lerDados(&produto, tamanho);
            break;

            case 3:
                pesquisarProduto(&produto, tamanho);
            break;

            case 4:
                pesquisarFornecedor(&produto, tamanho);
            break;

            case 5:
                faixaDePreco(&produto, tamanho);
            break;

            case 6:
                alterarEstoque(&produto, tamanho);
            break;

            case 7:
                alterarPreco(&produto, tamanho);
            break;

            case 8:
                alterarProduto(&produto, tamanho);
            break;

            case 9:
                excluirProduto(&produto, tamanho);
            break;

            case 10:
                cout << "Saindo do programa..." << endl << endl;
            break;
        }

        system("pause");
        system("cls || clear");

    } while(opcao != 10);

    return 0;
}
