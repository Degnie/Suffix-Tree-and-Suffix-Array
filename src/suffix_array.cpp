#include "suffix_array.h"
#include <algorithm>
#include <cmath>

SuffixArrayAccelerator::SuffixArrayAccelerator(const std::string& text) : text(text) {
    n = text.length();
    sa = build_suffix_array();
    lcp = build_lcp_array();
    rmq = build_rmq_table();
}

std::vector<int> SuffixArrayAccelerator::build_suffix_array() {
    std::vector<std::pair<std::string, int>> suffixes;
    for (int i = 0; i < n; ++i) {
        suffixes.push_back({text.substr(i), i});
    }
    std::sort(suffixes.begin(), suffixes.end());
    
    std::vector<int> sa_result(n);
    for (int i = 0; i < n; ++i) {
        sa_result[i] = suffixes[i].second;
    }
    return sa_result;
}

std::vector<int> SuffixArrayAccelerator::build_lcp_array() {
    std::vector<int> rank(n, 0);
    for (int i = 0; i < n; ++i) {
        rank[sa[i]] = i;
    }

    std::vector<int> lcp_result(n, 0);
    int h = 0;
    for (int i = 0; i < n; ++i) {
        if (rank[i] > 0) {
            int j = sa[rank[i] - 1];
            while (i + h < n && j + h < n && text[i + h] == text[j + h]) {
                h++;
            }
            lcp_result[rank[i]] = h;
            if (h > 0) {
                h--;
            }
        }
    }
    return lcp_result;
}

std::vector<std::vector<int>> SuffixArrayAccelerator::build_rmq_table() {
    if (n == 0) return {};
    
    int log_n = 0;
    while ((1 << log_n) <= n) {
        log_n++;
    }
    
    std::vector<std::vector<int>> st(n, std::vector<int>(log_n, 0));
    
    for (int i = 0; i < n; ++i) {
        st[i][0] = lcp[i];
    }
    
    for (int j = 1; j < log_n; ++j) {
        int i = 0;
        while (i + (1 << j) <= n) {
            st[i][j] = std::min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            i++;
        }
    }
    return st;
}

int SuffixArrayAccelerator::get_sa_lcp(int i, int j) {
    if (i == j) {
        return n - sa[i];
    }
    if (i > j) {
        std::swap(i, j);
    }
    int L = i + 1;
    int R = j;
    int length = R - L + 1;
    
    int k = 0;
    while ((1 << (k + 1)) <= length) {
        k++;
    }
    
    return std::min(rmq[L][k], rmq[R - (1 << k) + 1][k]);
}

int SuffixArrayAccelerator::lcp_with_pattern(const std::string& pattern, int sa_idx, int offset) {
    int suf_start = sa[sa_idx] + offset;
    int pat_start = offset;
    int match = 0;
    
    while (pat_start + match < pattern.length() && 
           suf_start + match < n && 
           pattern[pat_start + match] == text[suf_start + match]) {
        match++;
    }
    return offset + match;
}

std::vector<int> SuffixArrayAccelerator::search(const std::string& pattern) {
    int m = pattern.length();
    if (n == 0 || m == 0) {
        return {};
    }
    
    int L = 0;
    int R = n - 1;
    int l = lcp_with_pattern(pattern, L, 0);
    int r = lcp_with_pattern(pattern, R, 0);
    
    int left_bound = -1;
    
    if (l == m || pattern < text.substr(sa[L])) {
        left_bound = L;
    } else if (pattern > text.substr(sa[R])) {
        return {};
    } else {
        while (R - L > 1) {
            int M = (L + R) / 2;
            if (l >= r) {
                int lcp_LM = get_sa_lcp(L, M);
                if (lcp_LM < l) {
                    R = M;
                    r = lcp_LM;
                } else if (lcp_LM > l) {
                    L = M;
                } else { // lcp_LM == l
                    int match = lcp_with_pattern(pattern, M, l);
                    if (match == m || pattern < text.substr(sa[M])) {
                        R = M;
                        r = match;
                    } else {
                        L = M;
                        l = match;
                    }
                }
            } else { // l < r
                int lcp_MR = get_sa_lcp(M, R);
                if (lcp_MR < r) {
                    L = M;
                    l = lcp_MR;
                } else if (lcp_MR > r) {
                    R = M;
                } else { // lcp_MR == r
                    int match = lcp_with_pattern(pattern, M, r);
                    if (match == m || pattern < text.substr(sa[M])) {
                        R = M;
                        r = match;
                    } else {
                        L = M;
                        l = match;
                    }
                }
            }
        }
        
        if (text.substr(sa[L], m) != pattern) {
            left_bound = R;
        } else {
            left_bound = L;
        }
    }
    
    if (left_bound == -1 || text.substr(sa[left_bound], m) != pattern) {
        return {};
    }
    
    int L_temp = left_bound;
    int R_temp = n - 1;
    int right_bound = left_bound;
    
    while (L_temp <= R_temp) {
        int M = (L_temp + R_temp) / 2;
        if (text.substr(sa[M], m) == pattern) {
            right_bound = M;
            L_temp = M + 1;
        } else {
            R_temp = M - 1;
        }
    }
    
    std::vector<int> result;
    for (int i = left_bound; i <= right_bound; ++i) {
        result.push_back(sa[i]);
    }
    std::sort(result.begin(), result.end());
    
    return result;
}
