#include <iostream>
#include <fstream>
#include "Dados_Servidor.h"

using namespace std;

ostream &operator<<(ostream &O,ComandoWhatsProg CMD)
{
  switch(CMD)
  {
  case(CMD_NEW_USER):
    O << "CMD_NEW_USER";
    break;
  case(CMD_LOGIN_USER):
    O << "CMD_LOGIN_USER";
    break;
  case(CMD_LOGIN_OK):
    O << "CMD_LOGIN_OK";
    break;
  case(CMD_LOGIN_INVALIDO):
    O << "CMD_LOGIN_INVALIDO";
    break;
  case(CMD_NOVA_MSG):
    O << "CMD_NOVA_MSG";
    break;
  case(CMD_MSG_RECEBIDA):
    O << "CMD_MSG_RECEBIDA";
    break;
  case(CMD_MSG_ENTREGUE):
    O << "CMD_MSG_ENTREGUE";
    break;
  case(CMD_MSG_LIDA1):
    O << "CMD_MSG_LIDA1";
    break;
  case(CMD_MSG_LIDA2):
    O << "CMD_MSG_LIDA2";
    break;
  case(CMD_ID_INVALIDA):
    O << "CMD_ID_INVALIDA";
    break;
  case(CMD_USER_INVALIDO):
    O << "CMD_USER_INVALIDO";
    break;
  case(CMD_MSG_INVALIDA):
    O << "CMD_MSG_INVALIDA";
    break;
  case(CMD_LOGOUT_USER):
    O << "CMD_LOGOUT_USER";
    break;
  default:
    O << "COMANDO NAO RECONHECIDO";
    break;
  }
  return O;
}
//este metodo deve ser usado apos verificar que o Dest existe
//na lista de cadastrados do servidor
//E a mensagem esta dentro do limite de caracteres


bool Usuario::enviar_msg(const Mensagem &M,Usuario &Dest)
{
  if( Dest.s.connected() == false)
  {
    add_Mensagem(M);
    return false;
  }
  if(Dest.write_int(CMD_NOVA_MSG) == false)
    return false;
  if( Dest.write_int(M.getId()) == false)
    return false;
  if( Dest.write_string( M.getRemetente() ) == false)
    return false;
  if( Dest.write_string( M.getTexto()) == false)
    return false;

  return true;
}

void Usuario::reenvia_msg(Usuario &Dest)
{

  for(iter_Msg i_msg = LM_buffer.begin(); i_msg != LM_buffer.end(); i_msg++ )
  {
    if( i_msg->getDestinatario() == Dest.get_login())
    {
      if(enviar_msg(*i_msg, Dest) == true)
      {
        i_msg->setStatus(MSG_ENTREGUE);
        this->write_int(CMD_MSG_ENTREGUE);
        this->write_int(i_msg->getId());
      }
    }
  }
  this->atualizar_buffer();
}

void Usuario::atualizar_buffer()
{
  for(iter_Msg i_msg = LM_buffer.begin(); i_msg != LM_buffer.end(); i_msg++ )
    if(i_msg->getStatus() != MSG_RECEBIDA)
      LM_buffer.erase(i_msg);
}

bool Usuario::write_int(const int32_t num)
{
  if(s.write_int(num) == SOCKET_ERROR)
  {
    s.shutdown();
    return false;
  }
  return true;
}

bool Usuario::write_string(const string &str)
{
  if(s.write_string(str) == SOCKET_ERROR)
  {
    s.shutdown();
    return false;
  }
  return true;
}

bool Usuario::read_int(int32_t &num)
{
  if(s.read_int(num) == SOCKET_ERROR)
  {
    s.shutdown();
    return false;
  }
  return true;
}

bool Usuario::read_string(string &str)
{
  if(s.read_string(str) == SOCKET_ERROR)
  {
    s.shutdown();
    return false;
  }
  return true;
}

bool Usuario::set_login(const string &Login)
{
  if(Login.size() < TAM_MIN_NOME_USUARIO || Login.size() > TAM_MAX_NOME_USUARIO)
    return false;
  login = Login;
  return true;
}

bool Usuario::set_senha(const string &Senha)
{
  if(Senha.size() < TAM_MIN_SENHA || Senha.size() > TAM_MAX_SENHA)
    return false;
  senha = Senha;
  return true;
}

bool Usuario::add_Mensagem(const Mensagem &M)
{
  iter_Msg i_msg;
  if(M.getStatus() != MSG_RECEBIDA)return false;
  for(i_msg = LM_buffer.begin(); i_msg != LM_buffer.end(); i_msg++)
    if(i_msg->getId() == M.getId() )
      return false;
  LM_buffer.push_back(M);
  return true;
}

void Usuario::salvar(ostream &O)
{
  unsigned i = 1;
  O << "LOGIN: "<<login<<endl;
  O << "SENHA: "<<senha<<endl;
  O << "NumMsg: "<<LM_buffer.size()<<endl;
  for(iter_Msg i_Msg = LM_buffer.begin(); i_Msg != LM_buffer.end(); i_Msg++)
  {
    O << "Msg "<<i++<<':'<<' '
      << i_Msg->getId() << ','
      << i_Msg->getDestinatario()<<','
      << i_Msg->getTexto()<<'\n';
  }
}

bool Usuario::ler(istream &I)
{
  string str;
  string dest,texto;
  Mensagem M;
  uint32_t id;
  int NumMsg,index;

  getline(I,str,' ');
  if(str != "LOGIN:")return false;

  getline(I,str,'\n');

  login = str;

  getline(I,str,' ');

  if(str != "SENHA:")return false;
  getline(I,str,'\n');
  senha = str;

  getline(I,str,':');

  if(str != "NumMsg")return false;
  I >> NumMsg;
  I.ignore(1,'\n');
  for(int i = 0; i < NumMsg; i++)
  {

    getline(I,str,' ');

    if(str != "Msg")return false;
    I >> index;

    if(index-1 != i)return false;
    I.ignore(1,' ');
    I >> id;

    I.ignore(1,',');
    getline(I,dest,',');

    getline(I,texto,'\n');

    M.setDestinatario(dest);
    M.setTexto(texto);
    M.setId(id);
    M.setRemetente(login);
    M.setStatus(MSG_RECEBIDA);

    LM_buffer.push_back(M);
  }
  return true;
}

DadosServidor::DadosServidor()
{
  WSADATA wsaData;
  // All processes that call Winsock functions must first initialize the use of the Windows Sockets DLL (WSAStartup)
  // before making other Winsock functions calls
  // The MAKEWORD(2,2) parameter of WSAStartup makes a request for version 2.2 of Winsock on the system
  WINSOCKET_STATUS iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (iResult != 0) {
    cerr << "WSAStartup failed: " << iResult << endl;
    Status = OFF;
  }
  if (c.listen(PORTA_WHATSPROG) != SOCKET_OK)
    Status = OFF;
  else
  {
    ler();
    Status = ON;
  }
}

DadosServidor::~DadosServidor()
{
  c.close();
  for(iter_Usuario i= LU.begin(); i!= LU.end(); i++)
    i->s.close();
  salvar();
}

unsigned DadosServidor::conectados()
{
  unsigned cnt = 0;
  for(iter_Usuario i = LU.begin(); i!= LU.end(); i++)if (i->s.connected())
    cnt++;
  return cnt;
}

bool DadosServidor::isUsuario(const string &Login, const string &Senha)
{
  for(iter_Usuario i = LU.begin(); i!= LU.end(); i++)
  {
    if(i->is_login(Login) && i->is_senha(Senha))
      return true;
  }
  return false;
}

bool DadosServidor::isUsuario(const string &Login)
{
  for(iter_Usuario i = LU.begin(); i!= LU.end(); i++)
    if(*i == Login)
      return true;
  return false;
}

bool DadosServidor::cadastro(const string &Login,const string &Senha,Usuario &User)
{
  if( isUsuario(Login) == true )//Teste se o login ja esta em uso
    return false;
  if(User.set_login(Login) == false)//Testa o login
    return false;
  if(User.set_senha(Senha) == false)//Testa a senha
    return false;
  LU.push_back(User);
  return true;
}

void DadosServidor::salvar(const char*arq)
{
  ofstream O;
  unsigned cnt = 1;
  O.open(arq);
  if(O.is_open() == false)
  {
    cerr << "ERRO NA ABERTURA DO ARQUIVO " << endl;
    return;
  }

  O <<"SERVIDOR WHATSPROG\n";
  O <<"Usuarios: "<< size()<<endl;

  for(iter_Usuario i = LU.begin(); i!= LU.end(); i++)
  {
    O << "User "<<cnt++<<'\n';
    i->salvar(O);
  }
  O.close();
}

void DadosServidor::ler(const char*arq)
{
  ifstream I;
  string key;
  Usuario User;
  unsigned index;
  unsigned NumUser;

  I.open(arq);

  if(I.is_open() == false)
  {
    cerr << "ERRO NA ABERTURA DO ARQUIVO " << endl;
    return;
  }

  getline(I,key,'\n');
  if(key != "SERVIDOR WHATSPROG")
  {
    cerr << "ERRO NA LEITURA DO ARQUIVO, NAO ESTA NO FORMATO RECONHECIDO\n";
    return;
  }
  getline(I,key,':');
  if(key != "Usuarios")
  {
    cerr << "ERRO NA LEITURA DO ARQUIVO, NAO ESTA NO FORMATO RECONHECIDO\n";
    return;
  }
  I >> NumUser;
  I.ignore(1,'\n');
  for(unsigned i = 0; i < NumUser; i++)
  {

    getline(I,key,' ');
    if(key != "User")
    {
      cerr << "ERRO NA LEITURA DO ARQUIVO, NAO ESTA NO FORMATO RECONHECIDO\n";
      LU.clear();
      return;
    }
    I >> index;

    I.ignore(1,'\n');
    if(index -1 != i)
    {
      cerr << "ERRO NA LEITURA DO ARQUIVO, NAO ESTA NO FORMATO RECONHECIDO\n";
      LU.clear();
      return;
    }
    if( User.ler(I) == true)LU.push_back(User);
    else
    {
      cout << "Erro na leitura do Arquivo \n";
      LU.clear();
      return;
    }
  }
  cout << " DADOS CARREGADOS " << endl;
  I.close();
}

void DadosServidor::Resposta_Servidor(ComandoWhatsProg CMD,Usuario &cliente)
{
  string login,senha,remetente;
  string dest,msg;
  iter_Msg i_msg;
  iter_Usuario User;
  Mensagem M;
  int32_t id;

  switch(CMD)
  {
  case(CMD_NEW_USER):
    if(cliente.read_string(login) == true)
    {
      //Usuario ja cadastrado
      if( isUsuario(login) == true )
      {
        cliente.write_int(CMD_LOGIN_INVALIDO);
        cliente.shutdown();
        return;
      }
      if( cliente.read_string(senha) == false)
        return;
    }
    if( cadastro(login,senha, cliente) == false)
    {
      cliente.write_int(CMD_LOGIN_INVALIDO);
      cliente.shutdown();
      return;
    }
    cliente.write_int(CMD_LOGIN_OK);
    break;
  case(CMD_LOGIN_USER):
    if( cliente.read_string(login) == false)
      return;
    if( cliente.read_string(senha) == false )
        return;
    if(isUsuario(login,senha) == false)
    {
      cliente.write_int(CMD_LOGIN_INVALIDO);
      cliente.shutdown();
      return;
    }

    User = find(LU.begin(),LU.end(), login);
    if(User->s.connected())//Caso tente conectar e ja estiver conectado
    {
      User->shutdown();
      return;
    }
    cliente.write_int(CMD_LOGIN_OK);
    //User->s.close();
    //User->shutdown();
    User->set_socket(cliente.s);
    //Envia para este cliente todas as mensagens que
    //Estao no buffer dos outros usuarios que possuem
    //este usuario como destinatario
    for(iter_Usuario UserRemetente = LU.begin(); UserRemetente != LU.end(); UserRemetente++)
    {
      if(UserRemetente->get_login() != login)UserRemetente->reenvia_msg(*User);
    }
    break;
  case(CMD_NOVA_MSG):
    if( cliente.read_int(id) == false)
      return;
    i_msg = find(cliente.LM_buffer.begin(),cliente.LM_buffer.end(), id);

    //Testa se a id ja foi usada
    if(i_msg != cliente.LM_buffer.end())
    {
      cliente.write_int(CMD_ID_INVALIDA);
      cliente.write_int(id);
      return;
    }
    cliente.read_string(dest);
    if(isUsuario(dest) == false)
    {
      cliente.write_int(CMD_USER_INVALIDO);
      cliente.write_int(id);
      return;
    }
    cliente.read_string(msg);
    if(msg.size() >  TAM_MAX_MSG )
    {
      cliente.write_int(CMD_MSG_INVALIDA);
      cliente.write_int(id);
      return;
    }
    //Se chegou aqui eh porque esta tudo OK com a msg
    //O servidor recebeu corretamente a msg
    cliente.write_int(CMD_MSG_RECEBIDA);
    cliente.write_int(id);
    //Preparacao para enviar a mensagem para o destinatario
    M.setId(id);
    M.setDestinatario(dest);
    M.setRemetente(cliente.get_login());
    M.setTexto(msg);
    M.setStatus(MSG_RECEBIDA);
    //Tentativa de enviar a mensagem para o destinatario

    User = find(LU.begin(),LU.end(),dest);
    if(User == LU.end())
      return; // cliente nao cadastrado

    if(cliente.enviar_msg(M, *User) == false)
    {
      User->shutdown();
      return;
    }
    //Se deu certo o envio da mensagem
    cliente.write_int(CMD_MSG_ENTREGUE);
    cliente.write_int(id);

    break;
  case(CMD_MSG_LIDA1):{
    //COMO N TENHO UM BUFFER DE TODAS AS MENSAGENS N POSSO VERIFICAR
    //A ID DA MENSAGEM, ENTAO APENAS REPASSO PARA O CLIENTE REMETENTE
    if(cliente.read_int(id) == false)
      return;
    if(cliente.read_string(remetente) == false)
      return;
    User = find(LU.begin(),LU.end(),remetente);
    iter_Msg iMsg = find(User->LM_buffer.begin(),User->LM_buffer.end(),id);
    iMsg->setStatus(MSG_LIDA);
    User->write_int(CMD_MSG_LIDA2);
    User->write_int(id);
    break;}
    case(CMD_LOGOUT_USER):
    cliente.shutdown();
    cliente.s.close();
    break;
  default:
    cliente.shutdown();
    cliente.s.close();
    break;
  }
}

void DadosServidor::run()
{
  tcp_winsocket t;
  winsocket_queue f;
  WINSOCKET_STATUS iResult;
  int32_t CMD_Whats;
  iter_Usuario i;

  while ( Status == ON)
  {
    // Inclui na fila de sockets para o select todos os sockets que eu
    // quero monitorar para ver se houve chegada de dados
    f.clean();
    this->set_Status(c.accepting());
    cout << " Status do servidor :  "<<((Status)?"ON":"OFF") <<endl;
    for(iter_Usuario USER =  LU.begin(); USER != LU.end(); USER++)
    {
      cout << USER->get_login() << " " << ((USER->connected())?"ON":"OFF") << endl;
    }

    if ( Status == ON)
    {
      f.include(c);
      for (i = LU.begin(); i!= LU.end(); i++)
        if (i->s.connected())f.include(i->s);
    }
    // Espera que chegue alguma dados em qualquer dos sockets da fila
    iResult = f.wait_read(TIMEOUT_WHATSPROG*1000);
    if (iResult==SOCKET_ERROR)
    {
      if ( Status == ON )cerr << "Erro na espera por alguma atividade\n";
      set_Status(OFF);
    }
    if ( Status == ON)
    {
      if (iResult !=0 )
      {
        // Não saiu por timeout: houve atividade em algum socket da fila
        // Testa em qual socket houve atividade.

        // Primeiro, testa os sockets dos clientes

        for (i= LU.begin(); i != LU.end(); i++)
        {
          if (i->s.connected() && f.had_activity(i->s))
          {

            iResult = i->s.read_int(CMD_Whats,1000*TIMEOUT_WHATSPROG);

            if (iResult == SOCKET_ERROR)i->s.shutdown();
            if (i->s.connected())
            {
              Resposta_Servidor((ComandoWhatsProg)CMD_Whats, *i);
            }
          }
        }

        // Depois, Testa se houve atividade no socket de conexao
        if (f.had_activity(c))
        {
          if (c.accept(t) != SOCKET_OK)
          {
            cerr << "Não foi possível estabelecer uma conexao\n";
            set_Status(OFF);
          }
          if ( Status == ON)
          {
            // Le o comando enviado pelo cliente
            iResult = t.read_int(CMD_Whats,TEMPO_MAXIMO*1000);
            if (iResult == SOCKET_ERROR)
            {
              cerr << "Erro no recebimento do comando do cliente que se conectou.\n";
              t.close();
            }
            else
            {
              Usuario new_Client;
              //cout<<"Parte critica " << endl;
              new_Client.set_socket(t);
              //cout <<"Comando recebido de uma conexao nova : " << CMD_Whats << endl;
              Resposta_Servidor((ComandoWhatsProg)CMD_Whats, new_Client);
            }
          }
        }
      }
    }
  }
  Status = OFF;
}

void DadosServidor::shutdown()
{
  c.shutdown();
  for (iter_Usuario i = LU.begin(); i!= LU.end(); i++)
  if(i->s.connected())
  {
    cout << "Encerrando o socket do cliente " << i->get_login() << endl;
    i->s.shutdown();
  }
}

void DadosServidor::imprimir_conectados()
{
  for(iter_Usuario user = LU.begin(); user != LU.end(); user++ )
    if(user->s.connected())
      cout << user->get_login() << endl;
}

void DadosServidor::imprimir_All()
{
  for(iter_Usuario user = LU.begin(); user != LU.end(); user++ )
    cout << user->get_login() << endl;
}

void DadosServidor::write_int(int32_t cmd)
{
  for(iter_Usuario iUser = LU.begin(); iUser != LU.end(); iUser++)
    iUser->write_int(cmd);
}
