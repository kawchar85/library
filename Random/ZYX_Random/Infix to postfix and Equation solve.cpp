/**
* this work for both space seperated or not
* but will not work for negative number (-60)
* [ -60 + ( 3 * 8 - ( 16 / 2 ^ 3 ) * 6 ) * 5 ] will not work (-60)!!
*/

#include<bits/stdc++.h>
#include<string>
using namespace std;

string ex[10001];
int cnt=0;

int precedence(string s)
{
    if(s=="^")
        return 3;
    if(s=="*" || s=="/")
        return 2;
    if(s=="+" || s=="-")
        return 1;
    return -1;
}

string calculation(string a, string op, string b)
{
    /**
    * for c++ 11 above, easy method
    * int x= stoi(a) + stoi(b);
    * string ret = to_string(x);
    */

    string ret;
    int x,y;
    char temp[100];
    sscanf(a.c_str(),"%d",&x);
    sscanf(b.c_str(),"%d",&y);
    if(op=="+")
    {
        sprintf(temp,"%d",x+y);
        ret=temp;
    }
    else if(op=="-")
    {
        sprintf(temp,"%d",x-y);
        ret=temp;
    }
    else if(op=="/")
    {
        sprintf(temp,"%d",x/y);
        ret=temp;
    }
    else if(op=="*")
    {
        sprintf(temp,"%d",x*y);
        ret=temp;
    }
    else if(op=="^")
    {
        int res=1;
        for(int i=0;i<y;i++)
            res*=x;
        sprintf(temp,"%d",res);
        ret=temp;
    }

    return ret;
}

void InToPost(string s[],int x)
{
    string temp;
    stack <string> st;
        st.push("$");
        cnt=0;
    for(int i=0; i<x; i++)
    {
        if(s[i]=="(")
            st.push(s[i]);
        else if(s[i]==")")
        {
            while(st.top()!="(")
            {
                ex[cnt++]=st.top();
                st.pop();
            }
            st.pop();
        }
        else if(isdigit(s[i][s[i].size()-1]))
        {
            ex[cnt++]=s[i];
        }
        else
        {
            while(precedence(st.top())>=precedence(s[i]))
            {
                ex[cnt++]=st.top();
                st.pop();
            }
            st.push(s[i]);
        }

    }

    while(st.top()!="$")
    {
        ex[cnt++]=st.top();
        st.pop();
    }
    st.pop();

    for(int i=0;i<cnt;i++)
    {
        cout<< ex[i] <<" ";
    }
    puts("");
}

void evaluate()
{
    stack <string> st;
    string a,b,op,res;
    ex[cnt++]="$";

    for(int i=0; i<cnt; i++)
    {
        if(ex[i]=="$")
            cout<<"Result = "<<st.top()<<endl;

        else if(isdigit(ex[i][ex[i].size()-1]))
        {
            st.push(ex[i]);
        }
        else
        {
            b=st.top();
            st.pop();
            a=st.top();
            st.pop();
            op=ex[i];
            res=calculation(a,op,b);
            st.push(res);
        }
    }
}


int main()
{
    int i,x,t,num;
    string s,p[10001];
    char temp[100];
    cin>>t;
    getchar();
    while(t--)
    {
        x=0;
        getline(cin,s);
        for(i=0;i<s.size(); i++)
        {
            if(s[i]==' ')
                continue;
            if(isdigit(s[i]))
            {
                num=0;
                while(isdigit(s[i]))
                {
                    num=num*10+(s[i]-'0');
                    i++;
                }
                sprintf(temp,"%d",num);
                p[x++]=temp;
                i--;
            }
            else
            {
                p[x++]=s[i];
            }
        }
        InToPost(p,x);
        evaluate();
    }
    return 0;

}
