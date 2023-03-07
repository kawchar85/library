ll F(int x) {
    return 100 + x*x;
}

void ternarySearch() {
    ll mn = INT_MAX;
    int l = -1000, r = 1000, m1, m2;
    while(l <= r) {
        m1 = l + (r - l) / 3;
        m2 = r - (r - l) / 3;

        auto f1 = F(m1);
        auto f2 = F(m2);

        if(f1 == f2) {
            mn = f1;
        }

        if(f1 < f2) {
            r = m2 - 1;
        }
        else {
            l = m1 + 1;
        }
    }

    cout << mn << endl;
    
}
