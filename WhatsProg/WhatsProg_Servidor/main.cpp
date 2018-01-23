#include <iostream>
#include <stdio.h>
#include "Dados_Servidor.h"
#include "winsocket.h"

using namespace std;
// Thread que efetivamente desempenha as tarefas do servidor
DWORD WINAPI servidor(LPVOID lpParameter)
{
  DadosServidor *X = (DadosServidor*)lpParameter;
  X->run();
  return 0;
}

void getIP()
{
  WORD wVersionRequested = MAKEWORD( 1, 1 );
	WSADATA wsaData;
	char Name[256], *ip;
	PHOSTENT host;

	ip = (char *)malloc(256);
	WSAStartup( wVersionRequested, &wsaData );
	gethostname(Name, sizeof(Name));

	host = gethostbyname(Name);
	ip = inet_ntoa(*(struct in_addr *)host->h_addr_list[0]);
	std::cout<<"IP: " << ip << std::endl;

}

int main(int argc, char **argv)
{
  DadosServidor Whats_Server;
  int32_t cmd;

  // Cria a thread que recebe e reenvia as mensagens
  HANDLE tHandle = CreateThread(NULL, 0, servidor, &Whats_Server , 0, NULL);
  if (tHandle == NULL) exit(1);

  //Falta fazer
  getIP();
  //Menu de comandos do servidor
  while (Whats_Server.status() == ON)
  {
    cout << endl;
    cout << Whats_Server.size() << " Usuarios Cadastrados ate o momento " << endl;
    cout << "**LISTA DE COMANDOS**\n"
         << "0) Desliga o Servidor \n"
         << "1) Clientes conectados \n"
         << "2) Listar Usuarios \n"
         << "3) Lista Clientes \n"
         << "4)    MOSTRAR IP  \n";
    cin >> cmd;
    //cin>>ws;
    system("cls");
    switch(cmd)
    {
    case(0):
      Whats_Server.set_Status(OFF);
      break;
    case(1):
      cout << "No momento " << Whats_Server.conectados() << " estao conectados "
      <<endl;
      cout << endl;
      break;
    case(2):
      Whats_Server.imprimir_All();
      cout << endl;
      break;
    case(3):
      Whats_Server.imprimir_conectados();
      cout << endl;
      break;
      case(4):
      cout << endl;
      getIP();
      cout << endl;
      break;
    default:
      cout << "comando invalido\n";
      break;
    }
  }

  // Desliga os sockets
  cout << "Encerrando o socket de conexoes\n";
  Whats_Server.shutdown();
  // Espera pelo fim da thread do servidor (máximo de 5 segundos)
  WaitForSingleObject(tHandle, 5000);
  // Encerra na "força bruta" a thread do servidor caso ela não tenha terminado sozinha
  // (ou seja, a função WaitForSingleObject tenha saído por timeout)
  TerminateThread(tHandle,0);
  // Encerra o handle da thread
  CloseHandle(tHandle);
  /* call WSACleanup when done using the Winsock dll */
  WSACleanup();
  return 0;
}
