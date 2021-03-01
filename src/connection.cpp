#include "connection.h"

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

connection::connection(int fdSocket) : m_socket(fdSocket){}

connection::~connection()
{
  close(m_socket);
  m_socket = -1;
}

void connection::quit()
{
}

//=========================
//***** COMMUNICATION *****
//=========================

//requete format : En TETE [Taille message, type du message]
                  //Corps Message

void connection::setMessageDestination(void (*function)(Message))
{
  m_functionCall = function;
}

void connection::sendMessage(connection_type type, std::string message)
{
  mtxSend.lock();
    char requete[TAILLE_TAMPON];

    int longueur = snprintf(requete, (int)message.length()+3,
                        "%c%c%s",
                        (int)message.length()+'\0', type+'\0',
                        message.c_str());
    send(m_socket, requete, longueur, 0);
  mtxSend.unlock();
}

void connection::startReadMessage()
{


    tWaitForMessage = new std::thread(&connection::readMessage, this);
    tWaitForMessage->detach();



    // Décriptage de la requete

}

void connection::readMessage()
{

  char tampon[TAILLE_TAMPON];

  #ifdef _WIN32
      while(recv(m_socket, tampon, TAILLE_TAMPON, 0)!=0)     /* lecture par bloc */
  #else //Linux
      while(read(m_socket, tampon, TAILLE_TAMPON)!=0)
  #endif // _WIN32
  {
  std::cout<<"Message recu!"<<std::endl;

    // std::cout<<"Taille du message : "<< tampon[0]-'\0' <<std::endl;
    // std::cout<<"Type de message : " << tampon[1]-'\0' << std::endl;
    // tampon[tampon[0]-'\0'+2] = '\0';
    // std::cout << &tampon[2] << std::endl;

    Message t = tampon;
    std::thread computeMessage(m_functionCall, t);
    computeMessage.detach();
  }
  std::cout<<"mort X)"<<std::endl;
  //mort du thread
}
