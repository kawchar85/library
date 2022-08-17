//O(n)
int lp[MAX+1],phi[MAX+1];
vector<int> prm;
void pre()
{
    phi[1] = 1;
    for (int i = 2; i <= MAX; ++i){
        if (lp[i] == 0){
            lp[i] = i,phi[i] = i - 1;
            prm.push_back(i);
        }
        else{
            if (lp[i] == lp[i / lp[i]]) phi[i] = phi[i / lp[i]] * lp[i];
            else phi[i] = phi[i / lp[i]] * (lp[i] - 1);
        }
        for (int j = 0; j < (int)prm.size() && prm[j] <= lp[i] && i * prm[j] <= MAX; ++j) 
        	lp[i * prm[j]] = prm[j];
    }
}
