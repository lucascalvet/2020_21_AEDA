#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) : lotacao(lot),
                                                                                     numMaximoClientes(nMaxCli) {
    vagas = lotacao;
}

unsigned ParqueEstacionamento::getNumLugares() const {
    return lotacao;
}

unsigned ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string &nome) const {
    int index = 0;
    for (vector<InfoCartao>::const_iterator cliente = clientes.begin(); cliente < clientes.end(); cliente++) {
        if ((*cliente).nome == nome)
            return index;
        index += 1;
    }
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string &nome) {
    if (clientes.size() == numMaximoClientes || posicaoCliente(nome) != -1)
        return false;
    InfoCartao cliente = {nome, false};
    clientes.push_back(cliente);
    return true;
}

bool ParqueEstacionamento::entrar(const string &nome) {
    int pos = posicaoCliente(nome);
    if (pos == -1 || clientes.at(pos).presente || vagas == 0)
        return false;
    clientes.at(pos).presente = true;
    vagas--;
    return true;
}

bool ParqueEstacionamento::retiraCliente(const string &nome) {
    int pos = posicaoCliente(nome);
    if (pos == -1 || clientes.at(pos).presente)
        return false;
    clientes.erase(clientes.begin() + pos);
    return true;
}

bool ParqueEstacionamento::sair(const string &nome) {
    int pos = posicaoCliente(nome);
    if (pos == -1 || !clientes.at(pos).presente)
        return false;
    clientes.at(pos).presente = false;
    vagas++;
    return true;
}

unsigned ParqueEstacionamento::getNumLugaresOcupados() const {
    return lotacao - vagas;
}

unsigned ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}