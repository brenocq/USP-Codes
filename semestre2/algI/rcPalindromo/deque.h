#ifndef DEQUE_H
#define DEQUE_H

typedef struct _item Item;
typedef struct _deque Deque;

#define bool int
#define true 1
#define false 0

Deque* deque_criar();
Item* item_criar(char c);

bool deque_inserir_frente(Deque* d, Item *item);
bool deque_inserir_fundo(Deque* d, Item *item);

Item* deque_remover_frente(Deque* d);
Item* deque_remover_fundo(Deque* d);

Item* deque_frente(Deque* d);
Item* deque_fundo(Deque* d);

bool deque_cheio(Deque* d);
bool deque_vazio(Deque* d);

void deque_print(Deque* d);
void deque_deletar(Deque **d);

char char_valido_fundo(Deque *d);
char char_valido_frente(Deque *d);

#endif// DEQUE_H
