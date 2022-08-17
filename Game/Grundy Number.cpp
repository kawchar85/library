/*
Grundy/Nimbers: smallest number jei state a jawa jabe nah
Problem: Divide pile in two unequal piles
*/
int G[sz];
void Grandy(int n){
    set<int>s;
    for(i=1; ; i++){
        j=n-i;
        if(j<=i) break;
        //i,j te jabo. insert i,j othoba i^j
        s.insert(G[i]^G[j]);
    }
    i=0;
    while(s.find(i)!=s.end())
        i++;
    G[n]=i;
}