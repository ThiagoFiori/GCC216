#include <iostream>

using namespace std;

typedef int Dado;

class noh {
    friend class lista;
    private:
        const Dado dado;
        noh* proximo;
    public:
        noh(Dado d = 0);
};

noh::noh(Dado d) : dado(d) {
    proximo = NULL;
}

class lista {
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
    public:
        lista();
        ~lista();
        void insere(Dado dado);
        void insere(Dado dado, int pos);
        void remove(int posicao);
        int procura(Dado valor);
        void imprime();
        inline bool vazia();
};

// constrÃ³i uma lista inicialmente vazia
lista::lista() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

lista::~lista() {
    noh* iter = primeiro;
    noh* proximo = NULL;
    while (iter != NULL) {
        proximo = iter->proximo;
        delete iter;
        iter = proximo;
    }
}

// mÃ©todo bÃ¡sico que *percorre* a lista, imprimindo seus elementos
void lista::imprime() {
    noh* aux = primeiro;
    while (aux != NULL) {
        cout << aux->dado << " ";
        aux = aux->proximo;
    }
    cout << endl;
}

// insere por padrÃ£o no final da lista
void lista::insere(Dado dado) {
	noh* novo = new noh(dado);
	if (tamanho == 0){
		primeiro = novo;
		ultimo = novo;
	} else {
		ultimo->proximo = novo;
		ultimo = novo;
	}
	tamanho++;
}

// insere um dado em uma determinada posicao da lista
void lista::insere(Dado dado, int posicao) {
    noh* novo = new noh(dado);
    if (vazia()){
		primeiro = novo;
		ultimo = novo;
	} else if (posicao == 0){
		novo->proximo = primeiro;
		primeiro = novo;
	} else if (posicao == (tamanho-1)){
		ultimo->proximo = novo;
		ultimo = novo;
	} else {
		noh* aux = primeiro;
		int cont = 0;
		while (cont < (posicao-1)){
			aux = aux->proximo;
			cont++;
		}
		novo->proximo = aux->proximo;
		aux->proximo = novo;	
	}
	tamanho++;
}

// remove o item da posiÃ§Ã£o passada por parÃ¢metro
// AtenÃ§Ã£o - o cÃ³digo deve tratar de posiÃ§Ã£o invÃ¡lidas
void lista::remove(int posicao) {
	if (posicao == 0){
		primeiro = primeiro->proximo;
		tamanho--;
	} else if (posicao > 0 and posicao < tamanho){
		noh* aux = primeiro;
		int cont = 0;
		while (cont < (posicao-1)){
			aux = aux->proximo;
			cont++;
		}
		noh* temp = aux->proximo;
		aux->proximo = temp->proximo;
		tamanho--;
	} else {
		cout << "Erro! Posicao invalida" << endl;
	}
}

// procura por um elemento e retorna a posiÃ§Ã£o ou -1 se nÃ£o encontrado
int lista::procura(Dado valor) {
	noh* aux = primeiro;
	bool achou = false;
	int pos = 0;
	while (pos < tamanho and achou == false){
		if (aux->dado == valor){
			achou = true;
		} else {
			aux = aux->proximo;
			pos++;
		}
	}
	if (achou == true){
		return pos;
	} else {
		return -1;
	}
	
}

// verifica se a lista estÃ¡ vazia
inline bool lista::vazia() {
	return (tamanho == 0);
}

int main() { // NÃƒO MODIFIQUE!
    lista minhaLista;
    char opcao;
    int valor, pos;
    cin >> opcao;
    while (opcao != 'Q') {
        switch(opcao) {
            case 'I':
                cin >> valor;
                minhaLista.insere(valor);
                break;
            case 'W':
                cin >> valor;
                cin >> pos;
                minhaLista.insere(valor, pos);
                break;
            case 'P':
                cin >> valor;
                cout << minhaLista.procura(valor) << endl;
                break;
            case 'R':
                cin >> pos;
                minhaLista.remove(pos);
                break;
            case 'V':
                cout << minhaLista.vazia() << endl;
                break;
        }
        cin >> opcao;
    }
    minhaLista.imprime();
    return 0;
}
