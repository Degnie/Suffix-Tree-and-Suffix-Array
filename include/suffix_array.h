#ifndef SUFFIX_ARRAY_ACCELERATOR_H
#define SUFFIX_ARRAY_ACCELERATOR_H

#include <string>
#include <vector>

class SuffixArrayAccelerator {
private:
    std::string text;
    int n;
    std::vector<int> sa;
    std::vector<int> lcp;
    std::vector<std::vector<int>> rmq;

    std::vector<int> build_suffix_array();
    std::vector<int> build_lcp_array();
    std::vector<std::vector<int>> build_rmq_table();
    
    int get_sa_lcp(int i, int j);
    int lcp_with_pattern(const std::string& pattern, int sa_idx, int offset = 0);

public:
    SuffixArrayAccelerator(const std::string& text);
    std::vector<int> search(const std::string& pattern);
    
    // Getters para acceder a los datos internos en pruebas
    const std::vector<int>& get_sa() const { return sa; }
    const std::vector<int>& get_lcp() const { return lcp; }
};

#endif // SUFFIX_ARRAY_ACCELERATOR_H
