int padovan(int n) {
    int p_n = 1;
    int p_n_1 = 1;
    int p_n_2 = 1;
    int p_n_3 = 1;
    
    for (int i = 4; i <= n; i++) {
        p_n = p_n_2 + p_n_3;
        p_n_3 = p_n_2;
        p_n_2 = p_n_1;
        p_n_1 = p_n;
    }

    return p_n;
}
