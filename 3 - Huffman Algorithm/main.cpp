#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include "node.h"

using namespace std;

//Huffmans tree
list<Node*> t;
//freequencies of leter or symbols
map<char,int> freek;
//binary code of each letter or symbol
vector<bool> code;
//letter or symbol and its binary huffmann code
map<char,vector<bool> > table;

void BuildTable(Node *root) {
    if (root->left!=NULL) {
        code.push_back(0);
        BuildTable(root->left);
    }
    if (root->right!=NULL){
        code.push_back(1);
        BuildTable(root->right);
    }
    if (root->left==NULL && root->right==NULL) {
        table[root->c]=code;
    }
    code.pop_back();
}

void make_newTree(map<char,int> m){
    // make a list of start nodes of tree
    for( map<char,int>::iterator itr=m.begin(); itr!=m.end(); ++itr) {
        Node *p = new Node;
        p->c = itr->first;
        p->a = itr->second;
        t.push_back(p);
    }
    //making a tree
    while (t.size()!=1)
    {
        t.sort(MyCompare());
        Node *SonL = t.front();
        t.pop_front();
        Node *SonR = t.front();
        t.pop_front();
        Node *parent = new Node(SonL,SonR);
        t.push_back(parent);
    }
    Node *root = t.front();   //the root of the tree
    //makin a binary code of file
    BuildTable(root);
}

compress(ifstream &f,list<Node*> &t,string s){
    //vector of frequencies of chars that i will push to the out file with binary code of file
    vector<Node>tab;
    //reading frequencies of symbols//
    while (!f.eof()){
        char c = f.get();
        freek[c]++;
    }
    //make a tree of huffman
    make_newTree(freek);
    // going to the start o file
    f.clear(); f.seekg(0);
    string file = s;
    file =file +".zap";
    //writing it to the compressed file
    ofstream g(file.c_str(),ios::binary);
    map<char,int>::iterator it;
    for (it =freek.begin(); it!=freek.end();it++) {
        int size=tab.size();
        Node n(it->second,it->first,size);
        tab.push_back(n);
    }

    // write to the file tree's size for future read tree from file
    int treeSize = tab.size();
    g.write((char*) &treeSize, sizeof (treeSize));
    //write to the file the tree
    for (int i = 0; i < treeSize; i++) {
        g.write((char*) &tab[i], sizeof (tab[i]));
    }
    //count of bites;
    int count = 0;
    //buff of letter or symbol at the tree
    char buf = 0;

    while (!f.eof()){
        char c = f.get();
        vector<bool> x = table[c];
        for(int n = 0; n < x.size(); n++){
            buf = buf | x[n]<<(7-count);
            count++;
            if (count == 8) {
                count = 0;
                g << buf;
                buf = 0;
            }
        }
    }
    f.close();
    g.close();
    cout<<"File succssesfully compressed to "<<file<<"!!!"<<endl;

}

void decompress(string &s) {
    ifstream f(s.c_str(),ios::binary);
    //name of file without .zap
    string file = "";
    for(int i = 0;i<s.size()-3;i++){
        file = file + s[i];
    }
    //output stream
    ofstream g(file.c_str());
    //decoded vec of letter and symbol freequencies
    vector<Node>tab;
    //map of freequencies
    map<char,int> fin;
    //the size of our vector of freequencies
    unsigned int treeSize;
    f.read((char*) &treeSize, sizeof (treeSize));
    //nodes of vector(char<int)
    for (int i = 0; i < treeSize; i++) {
        Node n ;
        f.read((char*) &n, sizeof (n));
        tab.push_back(n);
    }
    //pushing vector to the map
    for(int i(0);i<tab.size();i++){
        fin.insert(pair<char,int>(tab.at(i).c,tab.at(i).a));
    }
    //makes a tree
    make_newTree(fin);
    //takes the root of the tree
    Node *root = t.front();
    int count=0;
    Node *p = root;
    count = 0;
    char byte;
    byte = f.get();
    while(!f.eof())    {
        bool b = byte & (1 << (7-count) ) ;
        if (b){ p=p->right;
        }else {
            p=p->left;
        }
        if (p->left==NULL && p->right==NULL) {
            cout<<p->c;
            char k =p->c;
            g.write((char*) &k, sizeof (k));
            p=root;
        }
        count++;
        if (count == 8) {count =0 ; byte = f.get();}
    }
    f.close();
    g.close();
    cout<<"File succssesfully decompressed!"<<endl;
}

int main(){
    //name of file
    string fileName;
    cout <<"Wellcom to the HUFFMAN algorithm programm"<<endl;
    cout <<endl;
    cout <<"Please enter name of the file which you want to work with"<<endl;
    getline(cin, fileName);
    ifstream f(fileName.c_str());
    if(f){
    cout<<"To compress file - put  1.                  to decompress - put 2."<<endl;
    }else{
        cout<<"No such file"<<endl;
    }
    string p;
    while(true){
        getline(cin,p);
        if(p == "1"){
            compress(f,t,fileName);
            break;
        }else if(p == "2") {
            decompress(fileName);
            break;
        }else{
            break;
        }
    }
}
