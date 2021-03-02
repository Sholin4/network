#include <iostream>
#include "src/Gateway.h"

#include <stdio.h>
#include <time.h>
#include <unistd.h>



int main(int argc, char *argv[]){
  //usage
  if (argc != 3) {
      printf("Usage: %s serveur message\n", argv[0]);
      perror("nombre de paramètres incorrect");
      return -1;
  }


  //L.join();
  Client cli(argv[1]);

  // connection co(1);
  // co.setDestination(&Client::printMessage, &cli);
  // co.readMessage();
  // //cli.m_co->setDestination(&Client::printMessage, &cli);
  // cli.m_co->startReadMessage();
  sleep(1);
  cli.m_co->sendMessage(TEST, argv[2]);
  Message input;
  std::cout<<"entrez 'exit' pour quitter"<<std::endl;
  while(input != "exit")
  {
    input="";
    std::cout<<"> ";
    std::cin>>input;
    std::cout<<std::endl;
    cli.m_co->sendMessage(TEST, input);
  }
  // for(int i=0; i<20; i++)
  // {
  //   cli.m_co->sendMessage(TEST, "un pti elephant");
  //   sleep(1);
  // }

  return 0;
}
