#include <iostream>
#include "mylist.h"
#include <fstream>
#include "node.h"
#include "myvector.h"
using namespace std;

//Huffmans tree
MyList<Node*> t;
//freequencies of leter or symbols
MyVector<int> freek(256);
//binary code of each letter or symbol
MyVector<bool> code;
//letter or symbol and its binary huffmann code
MyVector<MyVector<bool> > table(256);

void BuildTable(Node *root) {

    if (root->left != NULL) {
        code.pushBack(0);
        BuildTable(root->left);
    }
    if (root->right != NULL){
        code.pushBack(1);
        BuildTable(root->right);
    }
    if (root->left == NULL && root->right == NULL) {
        table[int(root->c)] = code;
        for(int i(0); i<code.size();i++){
        }
   }
    code.PopBack();
}
//make a tree according to huffman algorithm
void makeTree(MyVector<int> frequency){

    // make a list of start nodes of tree
    for(int i(0); i < frequency.size(); i++) {
        Node *p = new Node;
        p->c = char(i);
        p->a = frequency[i];  
        t.push_back(p);
    }
    //making a tree
    while (t.size()!=1)
    {
        t.sort();
        Node *SonL = t.front();
        t.pop_front();
        Node *SonR = t.front();
        t.pop_front();
        Node *parent = new Node(SonL,SonR);
        t.push_back(parent);
    }
    Node *root = t.front();   //the root of the tree

    //makin a binary code of each symbol or character
    BuildTable(root);
}
//compressing file to "file".cmp
void compress(ifstream &f,string s){
    for(int i = 0;i<freek.size();i++){
        freek[i]=0;
    }
    //reading frequencies of symbols//
    while (!f.eof()){
        unsigned char c = f.get();
        freek[c]++;
    }
    //make a tree of huffman
    makeTree(freek);

    // going to the start o file
    f.clear(); f.seekg(0);

    //writing the name of file with "cmp"
    string name = s.substr(0,s.length()-3);
    name = name +"cmp";
    ofstream g(name.c_str(),ios::binary);

    //writing format of the "file" to the output file
    char a = s[s.length()-3];
    char b = s[s.length()-2];
    char c = s[s.length()-1];
    g.write((char*) &a,sizeof(a));
    g.write((char*) &b,sizeof(b));
    g.write((char*) &c,sizeof(c));

    // write to the file tree's size for future reading it from file
    int treeSize = freek.size();
    g.write((char*) &treeSize, sizeof (treeSize));
    //write to the file the tree
    for (int i = 0; i < treeSize; i++) {
        g.write((char*) &freek[i], sizeof (freek[i]));
    }
    //count of bites;
    int count = 0;
    //buff of letter or symbol at the tree
    unsigned char buf = 0;

    while (!f.eof()){
        unsigned char c = f.get();
        MyVector<bool> x = table[c];
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
    cout<<"File succssesfully compressed to "<<name<<"!!!"<<endl;
}
//decompressing "file"
void decompress(string &s) {
    ifstream f(s.c_str(),ios::binary);
    //name of file without "cmp"
    string file = s.substr(0,s.length()-3);

    //vector of freequencies
    MyVector<int> fin(256);

    //read star format of the file in compressed file
    char a,b,c;
    f.read((char*) &a,sizeof(a));
    f.read((char*) &b,sizeof(b));
    f.read((char*) &c,sizeof(c));
    file = file + a + b + c;
    //output stream
    ofstream g(file.c_str());

    //the size of our vector of freequencies
    int treeSize;
    f.read((char*) &treeSize, sizeof (treeSize));

    //nodes of vector(char,int)
    for (int i = 0; i < treeSize; i++) {
        f.read((char*) &fin[i], sizeof (fin[i]));
    }
    //makes a tree
    makeTree(fin);
    //takes the root of the tree
    Node *root = t.front();
    int count = 0;
    Node *p = root;
    count = 0;
    unsigned char byte;
    byte = f.get();
    while(!f.eof())    {
        bool b = byte & (1 << (7-count) ) ;
        if (b){ p = p->right;
        }else {
            p = p->left;
        }
        if (p->left==NULL && p->right==NULL) {
            unsigned char k = p->c;
            g.write((char*) &k, sizeof (k));
            p = root;
        }
        count++;
        if (count == 8) {
            count = 0;
            byte = f.get();
        }
    }
    f.close();
    g.close();
    cout<<"File succssesfully decompressed!"<<endl;
}
void enterFileName(){
    cout <<"Please enter name of the file which you want to work with!"<<endl;
    //name of file
    string fileName;
    getline(cin, fileName);
    ifstream f(fileName.c_str(),ios::binary);
    if(f){
    cout<<"To compress file - enter 'compress'     to decompress - 'decompress' "<<endl;
    }else{
        cout<<"No such file"<<endl;
    }
    string cmd;
    while(true){
            getline(cin,cmd);
        if(cmd == "compress"){
            compress(f,fileName);
            break;
        }else if(cmd == "decompress") {
            decompress(fileName);
            break;
        }else if (cmd == "QUIT") {
            break;
        }else{
            break;
        }
    }
}
int main(){
    setlocale(LC_ALL, "Russian");
    cout <<"Wellcome to the HUFFMAN algorithm programm"<<endl;
    enterFileName();
}
