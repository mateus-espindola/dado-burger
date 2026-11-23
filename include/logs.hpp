#pragma once
#include <cstdio>
#include "timer.hpp"

struct Metrics {
    // 1. AVL (Carregamento / Loading)
    long   avlNodes = 0;
    int    avlHeight = 0;
    long   avlRotations = 0;
    double loadTime = 0.0;

    // 2. Histórico (Contexto / Context)
    long   historyEntries = 0;

    // 3. AVL (Buscas durante a partida / Searches during match)
    long   searchCount = 0;
    long   searchComparisons = 0;
    double searchTime = 0.0;

    // 4. Tabela Hash (Cache)
    long   hashHits = 0;
    long   hashMisses = 0;
    long   hashCollisions = 0;
    long   hashN = 0; // Entradas ocupadas
    long   hashM = 0; // Tamanho da tabela

    // 5. Ordenação do Histórico (History Sorting)
    double sortTime = 0.0;
    int    sortRuns = 0;
};

extern Metrics g_metrics;

// Funções para gravar o log (medicoes.log) e exibir na tela
void writeLog(const char* path = "medicoes.log");
void printReport();