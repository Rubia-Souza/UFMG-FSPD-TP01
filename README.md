# Fundamentos Sistemas Paralelos e Distribuidos - TP01 
 
Descisões de Implementação: As duas principais classes do projeto
são Entidade e Sala.
 - Entidade: É uma thread que irá entrar e sair das salas.
 - Sala: Regiões que as entidades irão entrar, sair e passar o tempo nelas.
  
Os métodos entrar() e sair() da Sala são responsáveis por controlar a sincronização,
a entrada e a saida das entidades.
  
A função runThreadEntidade() realiza a simulação do caminho das entidades.

De forma geral, a Sala tem uma contagem da quantidade de entidades que estão dentro
dela e que estão esperando para entrar. Sempre que uma entidade sai da sala com o
método sair(), o contador é atualizado. Quando ele chega em zero e as condições de 
entrada são atendidas, a Sala notifica as entidades em espera que elas podem entrar. 
Por outro lado, o método de entrar() incrementa o contador de entidades presentes
dentro da sala e, quando a terceira thread entra, a entrada na sala é bloqueada
novamente. Durante todas operações dos métodos entrar() e sair(), a região crítica
está envolvida por um mutex.
 