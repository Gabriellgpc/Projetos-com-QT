
#include <fstream>
#include <string>
#include <conio.h>
#include "sudoku.h"
#include <stack>

using namespace std;

// Construtor (por default, cria Jogada que termina o jogo)
Jogada::Jogada(int I, int J, int V)
{
  i = I;
  j = J;
  v = V;
}

// Cria um tabuleiro com o conteudo do arquivo nome_arq
// Caso nao consiga ler do arquivo, cria tabuleiro vazio
Sudoku::Sudoku()
{
    novo_jogo();
}
void Sudoku::novo_jogo(const char *nome_arq)
{
    for (unsigned i=0; i<9; i++) for (unsigned j=0; j<9; j++)
    {
      x[i][j] = 0;
    }
    // Le o tabuleiro inicial de arquivo
    ifstream arq(nome_arq);
    if (!arq.is_open()) return;

    string prov;
    int valor;

    arq >> prov;
    if (prov != "SUDOKU") return;
    for (unsigned i=0; i<9; i++) for (unsigned j=0; j<9; j++)
    {
      arq >> valor;
      if (valor != 0)
      {
        Jogada J(i,j,valor);
        if (jogada_valida(J)) x[i][j] = valor;
      }
    }
    arq.close();
}
void Sudoku::operator=(const Sudoku &Tab)
{
    for(int i = 0 ; i < 9; i++) for(int j = 0 ; j < 9; j++)
        x[i][j] = Tab.x[i][j];
}

// Testa se a jogada J eh possivel para o tabuleiro
bool Sudoku::jogada_valida(Jogada J) const
{
  unsigned i,j;
  // Testar a jogada
  if (J.i<0 || J.i>8) return false;
  if (J.j<0 || J.j>8) return false;
  if (J.v<0 || J.v>9) return false;

  // Testar se a casa nao estah vazia
  if (x[J.i][J.j] != 0)
  {
    // Soh pode apagar
    return (J.v == 0);
  }

  // Se chegou aqui, eh pq a casa estah vazia.
  // Portanto, nao pode apagar
  if (J.v == 0) return false;

  // Testar a linha
  for (i=0; i<9; i++)
  {
    if (x[i][J.j] == J.v) return false;
  }
  // Testar a coluna
  for (j=0; j<9; j++)
  {
    if (x[J.i][j] == J.v) return false;
  }
  // Testar o bloco
  unsigned iIni = 3*(J.i/3);
  unsigned jIni = 3*(J.j/3);
  for (i=0; i<3; i++) for (j=0; j<3; j++)
  {
    if (x[iIni+i][jIni+j] == J.v) return false;
  }
  return true;
}

// Testa se o tabuleiro estah completo (fim de jogo)
bool Sudoku::fim_de_jogo() const
{
  for (unsigned i=0; i<9; i++) for (unsigned j=0; j<9; j++)
  {
    if (x[i][j] == 0) return false;
  }
  return true;
}

// Retorna o numero de casas vazias no tabuleiro
unsigned Sudoku::num_casas_vazias() const
{
  unsigned N(0);
  for (unsigned i=0; i<9; i++) for (unsigned j=0; j<9; j++)
  {
    if (x[i][j] == 0) N++;
  }
  return N;
}
//Retorna o i,j da primeira casa vazia do tabuleiro  (first home null)
void Sudoku::FHN(int &f_i,int &f_j)
{
    for(int i = 0; i < 9; i++) for(int j = 0; j < 9; j++)
        if( x[i][j] == 0)
        {
            f_i = i;
            f_j = j;
            return;
        }
}
//Preenche as casas com apens 1 no
bool Sudoku::pre_resolver()
{
    int Valor_unico;
    unsigned possibilidades = 0;
    bool tente_novamente = false;

    do
    {
        tente_novamente = false;
        for(int i = 0; i < 9; i++ )for(int j = 0; j < 9; j++ )
        {
            possibilidades = 0;
            for(int v = 1; v < 10; v++)if (jogada_valida( Jogada(i,j,v) ))
             {
                    Valor_unico = v;
                    possibilidades++;
             }

            if( possibilidades == 1)
            {
                fazer_jogada( Jogada(i,j,Valor_unico) );
                tente_novamente = true;
            }
            else if(possibilidades == 0)
                return false;
        }
    }while(tente_novamente == true);
return true;
}
// Determina automaticamente a solucao do tabuleiro (preenche as casas vazias)
int Sudoku::resolver(void)
{

  stack<Sudoku> Aberto;
  int i_vazio,j_vazio;

  Aberto.push(*this);
  Sudoku Tab;
  unsigned tabuleiros_gerados = 0;

  do
  {
    Tab = Aberto.top();
    Aberto.pop();

    Tab.pre_resolver();

    tabuleiros_gerados++;

    if(Tab.num_casas_vazias() != 0 )
    {
        Tab.FHN(i_vazio,j_vazio);

        for(uint8_t valor = 1 ; valor < 10 ; valor++)
        {
            if( Tab.jogada_valida( Jogada(i_vazio,j_vazio,valor) ) )
            {
                Sudoku prov(Tab);
                prov.fazer_jogada( Jogada(i_vazio,j_vazio,valor) );
                Aberto.push(prov);
            }
        }
    }

  }while( Tab.num_casas_vazias() != 0 && Aberto.size() != 0 );

  if(Tab.num_casas_vazias() == 0 )
      *this = Tab;
  return tabuleiros_gerados;
}
