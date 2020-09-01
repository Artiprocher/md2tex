#include <bits/stdc++.h>
#define rep(i,a,b) for(ll i=a;i<=b;i++)
using namespace std;
typedef long long ll;

string word;
fstream tex_std,md;

bool check_equation_begin(){
    if(word=="$$")return true;
    return false;
}
bool check_equation_end(){
    if(word=="$$")return true;
    return false;
}
void translate_equation(){
    cout<<"\\begin{equation}"<<endl;
    while(getline(md,word)){
        if(check_equation_end()){
            cout<<"\\end{equation}"<<endl;
            break;
        }else{
            cout<<word<<endl;
        }
    }
}

int check_head_level(){
    int ans=0;
    for(auto i:word){
        if(i=='#')ans++;
        else break;
    }
    return ans;
}
void translate_head(){
    if(check_head_level()<=1)return;
    static vector<string> head_name={"","","section","subsection","subsubsection"};
    assert(check_head_level()<(int)head_name.size());
    cout<<"\\"<<head_name[check_head_level()]<<"{";
    for(int j=check_head_level()+1;j<(int)word.size();j++)cout<<word[j];
    cout<<"}"<<endl;
}

int check_table(){
    int ans=0;
    for(auto i:word)if(i=='|')ans++;
    if(ans>0)ans--;
    return ans;
}
void translate_table_line(int col){
    int c=0;
    for(auto i:word){
        if(i=='|'){
            c++;
            if(c>1 and c<=col)cout<<"&";
            else if(c>col)break;
        }else{
            cout<<i;
        }
    }
    cout<<"\\\\"<<endl;
}
void translate_table(){
    cout<<endl;
    int col=check_table();
    cout<<"\\begin{tabular}{"<<string(col,'l')<<"}"<<endl;
    cout<<"\\toprule"<<endl;
    translate_table_line(col);
    cout<<"\\midrule"<<endl;
    getline(md,word);
    while(getline(md,word)){
        if(check_table()!=col)break;
        translate_table_line(col);
    }
    cout<<"\\bottomrule"<<endl;
    cout<<"\\end{tabular}"<<endl;
    cout<<endl;
}

void translate(){
    string last_line="_";
    while(getline(md,word)){
        if(check_head_level()!=0){
            translate_head();
        }else if(check_equation_begin()){
            translate_equation();
        }else if(check_table()!=0){
            translate_table();
        }else{
            if(word!="" and last_line!="")cout<<endl;
            cout<<word<<endl;
        }
        last_line=word;
    }
}

int main(){
    system("chcp 65001");
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    string file_name;
    getline(cin,file_name);
    md.open(file_name.data(),ios::in);
    tex_std.open("std.tex",ios::in);
    freopen((file_name.substr(0,(int)file_name.size()-3)+"_result.tex").data(),"w",stdout);
    while(getline(tex_std,word)){
        if(word=="% 内容")translate();
        else cout<<word<<endl;
    }
    md.close();
    tex_std.close();
    return 0;
}
/*

*///
