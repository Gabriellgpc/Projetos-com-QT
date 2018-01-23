#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <stack>

using namespace std;

// Classe que representa uma possivel jogada (coordenadas e valor)
class Jogada
{
private:
  int i,j,v;
public:
  // Construtor (por default, cria Jogada que termina o jogo)
  Jogada(int I,int J, int V);
  friend class Sudoku;
};

class Sudoku
{
private:
  // Matriz que contem os valores das casas do tabuleiro
  int x[9][9];

  bool pre_resolver();
public:
  // Cria um tabuleiro com o conteudo do arquivo nome_arq
  // Caso nao consiga ler do arquivo, cria tabuleiro vazio
  Sudoku();
  Sudoku(const Sudoku &Tab) { operator=(Tab); }

  void operator=(const Sudoku &Tab);

  bool jogada_valida(Jogada J) const;
  // Executa uma jogada (altera o tabuleiro)
  inline void fazer_jogada(Jogada J) {if (jogada_valida(J)) x[J.i][J.j] = J.v;}
  // Testa se o tabuleiro estah completo (fim de jogo)
  bool fim_de_jogo() const;
  // Retorna o numero de casas vazias no tabuleiro
  unsigned num_casas_vazias() const;
  // Determina automaticamente a solucao do tabuleiro (preenche as casas vazias)
  int resolver(void);
  //first home null
  void FHN(int &i,int &j);
  inline int operator()(int i, int j) const { return x[i][j]; }
  void novo_jogo(const char *nome_arq="D:/Documents/Desktop/Sudoku_QT/Sudoku_QT/sudoku.txt");
};

extern Sudoku Tab;
#endif // _SUDOKU_H_
