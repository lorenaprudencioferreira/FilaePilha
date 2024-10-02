/*Cabecalho.
 *
 *Nome do aluno(a): Lorena Prudencio Ferreira
 *
 *Objetivo do programa: fazer um programa que armazene matricula e notas de alunos inseridos pelo usuario em uma fila
 *e depois ordene esses dados em uma pilha de forma que fiquem ordenados pela nota, com a maior no topo da pilha.
 *caso tenha empate de notas, levar em consideraçao a ordem de insercao das matriculas, a mais antiga fica no topo.
 *e por fim, exibir na tela os dados ordenados.
 *
 *Como deve ser feita a entrada de dados: o usuario fornece os dados, matricula e nota de cada aluno, quantos alunos
 *ele quiser inserir.
 *
 *Resultado da execução do programa: o resultado sera a exibicao dos alunos de forma ordenada baseado-se em sua nota
 *e matricula, de acordo com as especificacoes mencionadas no objetivo do programa. nota maior no topo, se for igual,
 *matricula mais antiga no topo.
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"
#include "Fila.h"

using namespace std;

int main() {
    Aluno aluno; //variavel do tipo struct declarada dentro da fila.h
    char continuar;

    Fila_Construtor();
    Pilha_Construtor();

    do {
        cout << "Digite o numero de matricula: " << endl;
        cin >> aluno.matricula;

        cout << "Digite a nota do aluno: " << endl;
        cin >> aluno.nota;

        Fila_Enfileirar(aluno);

        cout << "Inserir outro aluno? ('s' ou 'n'): " << endl;
        cin >> continuar;
    } while (continuar == 's' || continuar == 'S');

    //transferir da fila para pilha em ordem
    while (!Fila_Vazia()) {
        Fila_Desenfileirar(aluno); //retira o primeiro elemento da fila

        Aluno alunoTopo;//variavel para declarar o novo aluno que fica no topo da pilha
        int elementosDesempilhados = 0; //contador para saber quantos elementos foram desempilhados

        //verifica se o aluno pode ser empilhado de uma vez ou se tem q desempilhar da pilha
        while (!Pilha_Vazia()) {
            Pilha_Topo(alunoTopo); //pega o aluno no topo da pilha

            //compara as notas e desempilha os maiores ou iguais, mas com matrícula mais antiga
            if (alunoTopo.nota > aluno.nota ||(alunoTopo.nota == aluno.nota && alunoTopo.matricula < aluno.matricula)) {
                //testa se o aluno do topo tem nota maior ou igual que o do aluno fila ou matrícula mais antiga
                Pilha_Desempilhar(alunoTopo); //remove o q ta no topo e insere na fila temporaria
                Fila_Enfileirar(alunoTopo); //coloca novamente o aluno na fila temporaria
                elementosDesempilhados++;
            } else {
                break;
            }
        }
        //empilha o novo aluno
        Pilha_Empilhar(aluno);

        //coloca os alunos que foram retirados temporariamente de volta na pilha
        for (int i = 0; i < elementosDesempilhados; ++i) {
            Fila_Desenfileirar(alunoTopo); //remove da fila temporaria
            Pilha_Empilhar(alunoTopo); //coloca de volta na pilha
        }
    }

    cout << "\nAlunos ordenados por nota (da maior para a menor) e matricula (desempate):\n";
    while (!Pilha_Vazia()) {
        Pilha_Desempilhar(aluno); //desempilha o aluno para exibir na tela
        cout << "Matricula: " << aluno.matricula << ", Nota: " << aluno.nota << endl;
    }
    //para destruir a fila e a pilha
    Fila_Destrutor();
    Pilha_Destrutor();

    return 0;
}
