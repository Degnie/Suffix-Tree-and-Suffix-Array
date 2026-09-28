#include "suffix_array.h"
#include <iostream>
#include <vector>
#include <string>

int main() {
    // Caso 1: Ejemplo de la diapositiva 66 ("mississippi")
    std::string texto1 = "mississippi";
    SuffixArrayAccelerator acc1(texto1);
    
    std::cout << "=== CASO 1: Cadena 'mississippi' ===" << std::endl;
    
    std::cout << "Suffix Array (SA): [";
    for(size_t i = 0; i < acc1.get_sa().size(); ++i) {
        std::cout << acc1.get_sa()[i] << (i == acc1.get_sa().size() - 1 ? "" : ", ");
    }
    std::cout << "]\n";
    
    std::cout << "Arreglo LCP:      [";
    for(size_t i = 0; i < acc1.get_lcp().size(); ++i) {
        std::cout << acc1.get_lcp()[i] << (i == acc1.get_lcp().size() - 1 ? "" : ", ");
    }
    std::cout << "]\n\n";
    
    std::cout << "Resultados de busqueda:\n";
    std::vector<std::string> patterns1 = {"is", "ssi", "p", "mississippi", "issa"};
    for(const auto& pat : patterns1) {
        std::vector<int> pos = acc1.search(pat);
        std::cout << " - Patron '" << pat << "': Encontrado en indices [";
        for(size_t i = 0; i < pos.size(); ++i) {
            std::cout << pos[i] << (i == pos.size() - 1 ? "" : ", ");
        }
        std::cout << "]\n";
    }
    
    // Caso 2: Ejemplo de la diapositiva 61 ("ABAABBABBAC")
    std::string texto2 = "ABAABBABBAC";
    SuffixArrayAccelerator acc2(texto2);
    
    std::cout << "\n=== CASO 2: Cadena 'ABAABBABBAC' ===" << std::endl;
    
    std::cout << "Suffix Array (SA): [";
    for(size_t i = 0; i < acc2.get_sa().size(); ++i) {
        std::cout << acc2.get_sa()[i] << (i == acc2.get_sa().size() - 1 ? "" : ", ");
    }
    std::cout << "]\n";
    
    std::cout << "Arreglo LCP:      [";
    for(size_t i = 0; i < acc2.get_lcp().size(); ++i) {
        std::cout << acc2.get_lcp()[i] << (i == acc2.get_lcp().size() - 1 ? "" : ", ");
    }
    std::cout << "]\n\n";
    
    std::cout << "Resultados de busqueda:\n";
    std::vector<std::string> patterns2 = {"BB", "AB", "AC", "A"};
    for(const auto& pat : patterns2) {
        std::vector<int> pos = acc2.search(pat);
        std::cout << " - Patron '" << pat << "': Encontrado en indices [";
        for(size_t i = 0; i < pos.size(); ++i) {
            std::cout << pos[i] << (i == pos.size() - 1 ? "" : ", ");
        }
        std::cout << "]\n";
    }
    
    return 0;
}
