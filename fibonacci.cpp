int fibonacci(int n) {
    int f_n = 1;
    int f_n_1 = 1;
    int f_n_2 = 1;

    for (int i = 3; i <= n; i++) {
        f_n = f_n_1 + f_n_2;
        f_n_2 = f_n_1;
        f_n_1 = f_n;
    }
    return f_n;
}
