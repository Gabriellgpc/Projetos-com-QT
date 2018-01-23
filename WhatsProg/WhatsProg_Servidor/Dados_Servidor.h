#ifndef DADOS_SERVIDOR_H_INCLUDED
#define DADOS_SERVIDOR_H_INCLUDED

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

#include "socket_whatsprog.h"
#include "dados_whatsprog.h"
#include "winsocket.h"

using namespace std;

#define TEMPO_MAXIMO 60  // Tempo máximo de espera em segundos
#define TEMPO_ENVIO_LOGIN 30 // 60 segundos para o cliente enviar o nome de login apos conexao

enum{ ON  = 1, OFF = 0 };

class Usuario;

typedef list<Usuario>::iterator iter_Usuario;
typedef list<Mensagem>::iterator iter_Msg;

DWORD WINAPI thread_servidor(LPVOID lpParameter);

class Usuario
{
private:
  string login;
  string senha;
  //MENSAGENS ENVIADAS POR ESTE USUARIO
  //com status de recebida
  list<Mensagem> LM_buffer;
  //Socket do cliente
  tcp_winsocket s;
public:
  Usuario():login(""),senha(""),LM_buffer(),s() {}

  const string &get_login() const { return login; }
  inline bool connected() { return s.connected(); }

  void set_socket(tcp_winsocket &t) { s = t; }
  //Os metodos de alteracao retornam true caso a operacao seja bem sucedida
  bool set_login(const string &Login);//Valida o login antes de atribuir
  bool set_senha(const string &Senha);//Validar a senha antes de atribuir

  bool add_Mensagem(const Mensagem &M);
  /** Metodos para trabalhar com as mensagens*/
  //Tenta enviar uma mensagem para o Destinatario especificado
  //Retorna true caso consiga, caso contrario retorna false
  //caso nao consiga enviar a mensagem pois o Dest nao esta conectado
  //armazena a mensagem no buffer
  bool enviar_msg(const Mensagem &M,Usuario &Dest);
  //Toda vez que este metodo eh chamado eh feito uma tentativa de enviar as mensagens
  //que estao no buffer deste usuario,para o Dest
  void reenvia_msg(Usuario &Dest);
  //Atualiza a lista de Mensagens nao entregues
  //Excluindo da lista as que nao estao com status recebida
  void atualizar_buffer();
  /********************************************/

  /** Metodos para operacao no socket */
  //Todos os metodos abaixo retornam true caso a operacao seja bem sucedida
  //caso contrario, retorna false e desconecta o socket
  bool write_int(const int32_t num);
  bool write_string(const string &str);
  bool read_string(string &str);
  bool read_int( int32_t &num);
  /*************************************/
  inline void shutdown() { if(s.connected())s.shutdown(); };

  inline bool is_login(const string &Login) { return Login == login; }
  inline bool is_senha(const string &Senha) { return Senha == senha; }

  bool operator==(const string&Login) { return Login == login; }
  // Salva os dados do cliente
  void salvar(ostream &O);
  bool ler(istream &I);

  friend class DadosServidor;
};

class DadosServidor
{
private:
  //Socket do servidor
  tcp_winsocket_server c;
  //Lista de clientes cadastrados
  list<Usuario> LU;
  //flag que indica se o sofware deve encerrar todas as threads
  // Se 0 todas as threads devem ser encerradas
  bool Status;
public:
  DadosServidor();
  ~DadosServidor();
  /** Metodos de consulta */
  void imprimir_conectados();
  void imprimir_All();
  //Retorna o numero de clientes no momento
  unsigned conectados();
  //Retorna o numero de usuarios cadastrados ate o momento
  inline unsigned size() const { return LU.size(); }
  inline bool status() const { return Status; }
  /** Metodos de Alteracao */
  bool cadastro(const string &Login,const string &Senha,Usuario &User);
  //Esses metodos retornam false caso a operacao falhe ou true para
  //operacao bem sucedida
  //Exclui um cliente da lista de cadastro
  void set_Status(bool on_off) { Status = on_off; }
  /** Carga e Descarga de dados em arquivo */
  //Retornam true caso a operacao seja bem sucedida
  //e false caso contrario
  //Salva todos os dados dos usuarios
  void salvar(const char*arq = "Dados_Servidor.txt");
  //Carrega os dados para os usuarios cadastrados
  void ler(const char*arq = "Dados_Servidor.txt");
  /**  Metodos de verificacao */
  //Metodo que testa se existe um usuario com esse login e senha
  //Retora true caso encontre do contrario false
  bool isUsuario(const string &Login, const string &Senha);
  //Recebe um login e verifica se existe um usuario com o mesmo
  //login
  bool isUsuario(const string &login);
  /** Outros */
  //Metodo que desempenha as tarefas do servidor
  //ou seja, responde aos clientes seguindo o protocoloco
  // do whatsProg
  void run();
  //Metodo auxiliar do metodo run(), esse recebe um Comando CMD do protocoloco WhatsProg
  //E realiza as operacoes segundo o protocoloco
  void Resposta_Servidor(ComandoWhatsProg CMD_IN,Usuario &cliente);
  // encerra todos os sockets conectados
  void shutdown();

  //Excluir este metodo, eh apenas para testes
  void write_int(int32_t cmd);
};

/** Imprimi o nome do comando ao em vez do inteiro correspondente */
ostream &operator<<(ostream &O,ComandoWhatsProg CMD);

extern HANDLE tHandle;

#endif // DADOS_SERVIDOR_H_INCLUDED
