#include "../include/logs.hpp"

Metrics g_metrics;

static void writeReport(FILE* f) {
    const Metrics& m = g_metrics;

    double avgCmp  = m.searchCount > 0 ? (double)m.searchComparisons / m.searchCount : 0.0;
    long   lookups = m.hashHits + m.hashMisses;
    double hitRate = lookups > 0 ? 100.0 * m.hashHits / lookups : 0.0;
    double lambda  = m.hashM > 0 ? (double)m.hashN / m.hashM : 0.0;

    fprintf(f, "=== PERFORMANCE REPORT ===\n\n");
    
    // 1. AVL (Carregamento)
    fprintf(f, "--- AVL (Loading) ---\n");
    fprintf(f, "Nodes inserted: %ld\n", m.avlNodes);
    fprintf(f, "Tree height: %d\n", m.avlHeight);
    fprintf(f, "Rotations (insertion): %ld\n", m.avlRotations);
    fprintf(f, "Total load time: %.6f s\n\n", m.loadTime);

    // 2. Histórico (Contexto)
    fprintf(f, "--- History (Context) ---\n");
    fprintf(f, "Loaded entries: %ld\n\n", m.historyEntries);

    // 3. AVL (Buscas na partida)
    fprintf(f, "--- AVL (Searches during match) ---\n");
    fprintf(f, "Total searches: %ld\n", m.searchCount);
    fprintf(f, "Total comparisons: %ld\n", m.searchComparisons);
    fprintf(f, "Average comparisons per search: %.2f\n", avgCmp);
    fprintf(f, "Total accumulated search time: %.6f s\n\n", m.searchTime);

    // 4. Tabela Hash (Cache)
    fprintf(f, "--- Hash Table (Cache) ---\n");
    fprintf(f, "Table size (m): %ld\n", m.hashM);
    fprintf(f, "Occupied entries (n): %ld\n", m.hashN);
    fprintf(f, "Load factor (lambda): %.4f\n", lambda);
    fprintf(f, "Total hits: %ld\n", m.hashHits);
    fprintf(f, "Total misses: %ld\n", m.hashMisses);
    fprintf(f, "Hit rate: %.2f%%\n", hitRate);
    fprintf(f, "Total collisions: %ld\n\n", m.hashCollisions);

    // 5. Ordenação do Histórico
    fprintf(f, "--- History Sorting ---\n");
    if (m.sortRuns > 0) {
        fprintf(f, "Executions: %d\n", m.sortRuns);
        fprintf(f, "Sorting execution time: %.6f s\n", m.sortTime);
    } else {
        fprintf(f, "Not executed yet\n");
    }
}

void writeLog(const char* path) {
    // "w" cria ou sobrescreve o arquivo medicoes.log a cada execução
    FILE* f = fopen(path, "w");          
    if (!f) return;
    writeReport(f);
    fclose(f);
}

void printReport() { 
    writeReport(stdout); 
}