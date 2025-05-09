#include <stdio.h>
#include <string.h>
#include <windows.h>                              
#include <stdlib.h>
#include <time.h>

// CRIANDO AS STRUCTS DOS JOGADORES

typedef struct jogadores{ // Struct com dados do jogador
    char nome[30]; // Nome do jogador
    char cor[10]; // Cor do jogador
    int cor_sistema; // Mudança de cor do sistema
    int peao[5]; // Peões do jogador
    int dado; // Dado do jogador
    int final; // Posição final
    int inicial; // Posição inicial do j1
}jogador;

jogador j1; // Jogador 1
jogador j2; // Jogador 2
int dado[3] = {0,0,0};

void posicao_tabuleiro (jogador *j) { // Selecionar em qual posição do tabuleiro o jogador começa
    // Posição inicial e final dos jogadores
    if (strcmp(j->cor,"Vermelho") == 1) {
        j->inicial = 1; // Posição inicial
        for (int i = 1; i <= 4; i++) {
            j->peao[i] = j->inicial;
        }
        j->final = 52; // Posição final
        j->cor_sistema = 4;
    }
    else if (strcmp(j->cor,"Verde") == 1) {
        j->inicial = 14; // Posição inicial
        for (int i = 1; i <= 4; i++) {
            j->peao[i] = j->inicial;
        }
        j->final = 13; // Posição final
        j->cor_sistema = 2;
    }
    else if (strcmp(j->cor,"Azul") == 1) {
        j->inicial = 40; // Posição inicial
        for (int i = 1; i <= 4; i++) {
            j->peao[i] = j->inicial;
        }
        j->final = 39; // Posição final
        j->cor_sistema = 1;
    }
    else if (strcmp(j->cor,"Amarelo") == 1) {
        j->inicial = 27; // Posição inicial
        for (int i = 1; i <= 4; i++) {
            j->peao[i] = j->inicial;
        }
        j->final = 26; // Posição final
        j->cor_sistema = 6;
    }
}
void rolagem_dado (int *dado_total, int dado[]) { // Função para rolar o dado
    *dado_total = 0; // Zerar o dado
    printf ("\nRolando DADOS");
    printf ("."); Sleep(1000);
    printf ("."); Sleep(1000);
    printf ("."); Sleep(1000);
    printf ("\n");
    srand(time(NULL));
    for (int i = 0; i < 3; i++) {
        dado[i] = rand()%6 + 1;
        printf ("DADO [%d] = %d\n",i+1 ,dado[i]); Sleep(500);
        if (dado[i] == 6) { // Se dado for igual a 6, passa para o próximo
            *dado_total = *dado_total + dado[i];
        }
        else {
            *dado_total = *dado_total + dado[i]; // Se dado for diferente de 6, quebra o comando de repetição
            break;
        }
    }      
    if (dado[0] == 6 && dado[1] == 6 && dado[2] == 6) { // Se os 3 dados forem 6, iguala dado é zerado
        *dado_total = 0;
    }
}
void system_color (jogador j) { // Função para alterar cor do sistema correspondente a vez do jogador
    if (j.cor_sistema == 4) {
        system("color 4");
    }
    else if (j.cor_sistema == 2) {
        system("color 2");
    }
    else if (j.cor_sistema == 1) {
        system("color 1");
    }
    else if (j.cor_sistema == 6) {
        system("color 6");
    }
}
void pulando_casa (jogador *j, int escolha_peao, int dado[]) { // Função para pular casas
    do { 
        for (int vez = 1; vez > 0; vez++) { // Loop infinito até o peão 1 chegar a casa final
            printf ("\nMovendo PEAO(%d)" ,escolha_peao);
            printf ("."); Sleep(1000);
            printf ("."); Sleep(1000);
            printf (".\n"); Sleep(1000);
                if (j->peao[escolha_peao] == j->inicial) { // Peão na base
                    printf ("[BASE] comeca da [%d]\n" , j->inicial); Sleep(2000);
                    printf ("PEAO(%d) esta na [BASE]: para sair, primeiro DADO tem que ser = 6\n" ,escolha_peao); Sleep(2000);
                    if (j->dado >= 6) {
                        if ((j->peao[escolha_peao] + (j->dado - 5)) >= 52) { // Saltando direto da base, para casa 0 ou mais
                            printf ("DADO saiu %d, portanto:\n" ,j->dado); Sleep(2000);
                            (j->peao[escolha_peao]) = (j->peao[escolha_peao] + (j->dado - 5)) - 52;
                            printf ("\nPEAO(%d) se moveu da [BASE] ---> [%d]\n" ,escolha_peao, j->peao[escolha_peao]); Sleep(2000);
                        }
                        else {
                            j->peao[escolha_peao] += (j->dado - 5); // Saltando normalmente
                            printf ("DADO saiu %d, portanto:\n" ,j->dado); Sleep(2000);
                            printf ("\nPEAO(%d) se moveu da [BASE] ---> [%d]\n" ,escolha_peao, j->peao[escolha_peao]); Sleep(2000);
                        }
                    }
                    else {
                        printf ("DADO saiu %d, portanto, PEAO(%d) continua na [BASE]!!\n" ,j->dado, escolha_peao); Sleep(2000);
                    }
                }
                else { // Peão fora da base
                    if ((j->peao[escolha_peao] + dado[0]) >= 52 && strcmp(j->cor,"Vermelho") != 1) { // Saltando da casa 52 para a 0, e se a cor não for vermelho
                        printf ("Primeiro DADO caiu %d:" ,dado[0]);
                        printf ("\nPEAO(%d) se moveu da [%d] ---> ", escolha_peao, j->peao[escolha_peao]);
                        (j->peao[escolha_peao]) = (j->peao[escolha_peao] + dado[0]) - 52;
                        printf ("[%d]\n" ,j->peao[escolha_peao]); Sleep(2000);
                    }
                    else {
                        printf ("Primeiro DADO caiu %d:" ,dado[0]); // Saltando normalmente
                        printf ("\nPEAO(%d) se moveu da [%d] ---> ", escolha_peao, j->peao[escolha_peao]);
                        j->peao[escolha_peao] += dado[0];
                        printf ("[%d]\n" ,j->peao[escolha_peao]); Sleep(2000);
                    }
                    if (j->peao[escolha_peao] - dado[0] <= j->final) { // Se posição antiga for menor que as casas finais
                        if (j->peao[escolha_peao] == j->final + 5) {  // Peao pular direto pra chegada
                            printf ("PEAO(%d) chegou ao fim!!\n" ,escolha_peao); Sleep(2000);
                            break;
                        }
                        else {
                            if ((j->peao[escolha_peao]) >= j->final) { // Peão está nas casas finais
                                printf ("\nPEAO(%d) esta quase na chegada!!\n" ,escolha_peao); Sleep(2000);
                                printf ("Proximo DADO tem que sair %d para chegar ao fim\n" ,(j->final + 5) - j->peao[escolha_peao]); Sleep(5000);
                            }
                        }
                    }
                    else {
                        if (j->peao[escolha_peao] == j->final + 5) {  // Peao nao pular direto pra chegada
                            printf ("PEAO(%d) chegou ao fim!!\n" ,escolha_peao); Sleep(2000);
                            break;
                        }
                    }
                }
            break;
            }
        break;
        } while (j->peao[escolha_peao] != j->final + 5); // Casa final do peão 1
    }
void comendo_peao2 (jogador *j, jogador *j2, int escolha_peao, int dado[]) { // Função para comer o peão do jogador 2
    if (j->peao[escolha_peao] == 9 || j->peao[escolha_peao] == 22 || j->peao[escolha_peao] == 35 || j->peao[escolha_peao] == 48 || j->peao[escolha_peao] == j->inicial || (j->peao[escolha_peao] - dado[0] <= j->final && j->peao[escolha_peao] >= j->final)) { // Casas seguras gerais do tabuleiro
        // Permanece na casa
    }
    else { // Casa não segura
        for (int i = 1; i <= 4; i++) {
            if (j->peao[escolha_peao] == j2->peao[i]) { // Se casa tiver ocupada
                printf ("\nCasa [%d] esta ocupada pelo PEAO(%d) do jogador 2" ,j->peao[escolha_peao] ,i); Sleep(2000);
                printf ("PEAO(%d) do jogador 2 se moveu da [%d] ---> [BASE]\n" ,i ,j2->peao[i]); Sleep(2000);
                j2->peao[i] = j2->inicial; // Mandando para base
            }
        }
    }
}
void comendo_peao1 (jogador *j, jogador *j1, int escolha_peao, int dado[]) { // Função para comer o peão do jogador 1
    if (j->peao[escolha_peao] == 9 || j->peao[escolha_peao] == 22 || j->peao[escolha_peao] == 35 || j->peao[escolha_peao] == 48 || j->peao[escolha_peao] == j->inicial || (j->peao[escolha_peao] - dado[0] <= j->final && j->peao[escolha_peao] >= j->final)) { // Casas seguras gerais do tabuleiro
        // Permanece na casa
    }
    else { // Casa não segura
        for (int i = 1; i <= 4; i++) {
            if (j->peao[escolha_peao] == j1->peao[i]) { // Se casa tiver ocupada
                printf ("\nCasa [%d] esta ocupada pelo PEAO(%d) do jogador 1\n" ,j->peao[escolha_peao] ,i); Sleep(2000);
                printf ("PEAO(%d) do jogador 1 se moveu da [%d] ---> [BASE]\n" ,i ,j1->peao[i]);  Sleep(2000);
                j1->peao[i] = j1->inicial; // Mandando para base
            }
        }
    }
}

// FUNÇÃO PRINCIPAL

int main () { 
    printf ("Seja bem vindo ao jogo do LUDO:\n"); Sleep(1000);
    
    printf ("\nInforme os dados do PRIMEIRO jogador:\n"); // Dados a serem informados pelo jogador 1

    printf ("Nome: ");
    setbuf (stdin, NULL);
    fgets (j1.nome, 30, stdin);

    printf ("Escolha uma cor:\n-Vermelho\n-Verde\n-Azul\n-Amarelo\nCor desejada: ");
    setbuf (stdin, NULL);
    fgets (j1.cor, 10, stdin);
    j1.nome[(strlen(j1.nome)) - 1] = '\0';
    
    printf ("\nAgora, informe os dados do SEGUNDO jogador:\n"); // Dados a serem informados pelo jogador 2

    printf ("Nome: ");
    setbuf (stdin, NULL);
    fgets (j2.nome, 30, stdin);
    j2.nome[(strlen(j2.nome)) - 1] = '\0';
    
    printf ("Escolha uma cor:\n-Vermelho\n-Verde\n-Azul\n-Amarelo\nCor desejada: ");
    setbuf (stdin, NULL);
    fgets (j2.cor, 10, stdin);

    if (strcmp (j1.cor,j2.cor) == 0) { // Comparando se as cores são iguais, se sim, ordenando para selecionar nova cor
        printf ("Cor ja utilizada!!\n");
        printf ("Escolha outra cor: ");
        fgets (j2.cor, 10, stdin);
    }
    
    posicao_tabuleiro(&j1); // Chamando função
    posicao_tabuleiro(&j2); // Chamando função
    
    int escolha_peao; // Variável contendo a escolha do peão a se mover
    
    printf ("\nPronto, vamos comecar o jogo!!\n");
    system ("cls");

    for (int i = 1; i > 0; i++) { // Loop infinito até alguém vencer
        for (int vezj1 = 1; vezj1 > 0; vezj1++) { // Vez do jogador 1
            system_color(j1);
            printf ("Posicoes dos PEOES no tabuleiro:\n");
            printf ("%s: [%d] [%d] [%d] [%d]\n", j1.nome, j1.peao[1], j1.peao[2], j1.peao[3], j1.peao[4]);
            printf ("%s: [%d] [%d] [%d] [%d]\n", j2.nome, j2.peao[1], j2.peao[2], j2.peao[3], j2.peao[4]); Sleep(1000);
            printf ("\nVez do(a) %s:\n" ,j1.nome);
            rolagem_dado (&j1.dado, &dado[3]); // Rolando dados
            printf ("Soma dos DADOS = %d\n" ,j1.dado);
            escolha_peao = 0; // Zerando o antigo peão selecionado
            if (j1.dado != 0) { // Se o dado não cair 0
                printf ("Qual PEAO deseja mover?: "); 
                scanf ("%d" ,&escolha_peao); // Selecionando um novo peão
                if (escolha_peao == 1) {
                    pulando_casa (&j1, escolha_peao, &dado[3]);
                    comendo_peao2 (&j1, &j2, escolha_peao, &dado[3]);
                }
                else if (escolha_peao == 2) {
                    pulando_casa (&j1, escolha_peao, &dado[3]);
                    comendo_peao2 (&j1, &j2, escolha_peao, &dado[3]);
                }
                else if (escolha_peao == 3) {
                    pulando_casa (&j1, escolha_peao, &dado[3]);
                    comendo_peao2 (&j1, &j2, escolha_peao, &dado[3]);
                }
                else if (escolha_peao == 4) {
                    pulando_casa (&j1, escolha_peao, &dado[3]);
                    comendo_peao2 (&j1, &j2, escolha_peao, &dado[3]);
                }
            }
            else { // Se o dado cair 0
                printf ("DADO caiu %d, portanto, passou a vez!!\n", j1.dado); Sleep (1000);
            }  
            system ("cls");
            break; // Finalizando a vez do jogador 1
        }
        for (int vezj2 = 1; vezj2 > 0; vezj2++) { // Vez do jogador 2
            system_color (j2);
            printf ("Posicoes dos PEOES no tabuleiro:\n");
            printf ("%s: [%d] [%d] [%d] [%d]\n", j1.nome, j1.peao[1], j1.peao[2], j1.peao[3], j1.peao[4]);
            printf ("%s: [%d] [%d] [%d] [%d]\n", j2.nome, j2.peao[1], j2.peao[2], j2.peao[3], j2.peao[4]); Sleep(1000);
            printf ("\nVez do(a) %s:\n" ,j2.nome);
            rolagem_dado (&j2.dado, &dado[3]); // Rolando dados
            printf ("Soma dos DADOS = %d\n" ,j2.dado);
            escolha_peao = 0; // Zerando o antigo peão selecionado
            if (j2.dado != 0) { // Se o dado não cair 0
                printf ("Qual PEAO deseja mover?: "); 
                scanf ("%d" ,&escolha_peao); // Selecionando um novo peão
                if (escolha_peao == 1) {
                    pulando_casa (&j2, escolha_peao, &dado[3]);
                    comendo_peao2 (&j2, &j1, escolha_peao, &dado[3]);
                }
                else if (escolha_peao == 2) {
                    pulando_casa (&j2, escolha_peao, &dado[3]);  
                    comendo_peao2 (&j2, &j1, escolha_peao, &dado[3]);
                }
                else if (escolha_peao == 3) {
                    pulando_casa (&j2, escolha_peao, &dado[3]);                  
                    comendo_peao2 (&j2, &j1, escolha_peao, &dado[3]);
                }
                else if (escolha_peao == 4) {
                    pulando_casa (&j2, escolha_peao, &dado[3]);        
                    comendo_peao2 (&j2, &j1, escolha_peao, &dado[3]);
                }
            }
            else { // Se o dado cair 0
                printf ("DADO caiu %d, portanto, passou a vez!!\n", j2.dado); Sleep (1000);
            }  
        system ("cls");
        break; // Finalizando a vez do jogador 2
        }
    if (j1.peao[1] == (j1.final + 5) && j1.peao[2] == (j1.final + 5) && j1.peao[3] == (j1.final + 5) && j1.peao[4] == (j1.final + 5)) { // Se todos peões do jogador 1 chegarem no final
        printf ("\nParabens %s, voce venceu o jogo!!" ,j1.nome); Sleep(5000);
        return 0;
    }
    if (j2.peao[1] == (j2.final + 5) && j2.peao[2] == (j2.final + 5) && j2.peao[3] == (j2.final + 5) && j2.peao[4] == (j2.final + 5)) { // Se todos peões do jogador 2 chegarem no final
        printf ("\nParabens %s, voce venceu o jogo!!" ,j2.nome); Sleep(5000);
        return 0;
    }
    }
    return 0;
}