#include <iostream>
#include "mylist.h"
#include <fstream>
#include "node.h"
#include "myvector.h"
using namespace std;


//method makes the table of every character and its code using the huffmans tree
void buildTable(Node *root, myVector<myVector<bool> > &table, myVector<bool> &code) {

    //if current Node has left son pushing to code '0' and going to the left branch using recursion
    if (root->left != NULL) {
        code.pushBack(0);
        buildTable(root->left,table,code);
    }
    //if current Node has not left son but has right pushing to code '1' and going to the right using recursion
    if (root->right != NULL) {
        code.pushBack(1);
        buildTable(root->right,table,code);
    }
    //if current Node has no sons - pushing code to table cell that matches character in this Node
    if (root->left == NULL && root->right == NULL) {
        table[int(root->c)] = code;
    }
    //remove last symbol in code because recursion going to previous Node(branch)
    code.PopBack();

}

//make a tree according to huffman algorithm
void makeTree(myVector<int> frequencies, myList<Node*> &tree) {

    // make a list of start nodes of tree
    for(int i(0); i < frequencies.size(); i++) {
        Node *p = new Node;
        p->c = char(i);
        p->f = frequencies[i];
        tree.push_back(p);
    }
    //makes the tree until one Node left
    while (tree.size() != 1) {
        tree.sort();
        Node *SonL = tree.front();
        tree.pop_front();
        Node *SonR = tree.front();
        tree.pop_front();
        Node *parent = new Node(SonL,SonR);
        tree.push_back(parent);
    }
}

//compressing file to "file".cmp
void compress(ifstream &f,string s) {

    //frequencies of letters or symbols
    myVector<int> frequencies(256);
    for(int i = 0; i < frequencies.size(); i++) {
        frequencies[i] = 0;
    }
    //reading frequencies of symbols
    while (!f.eof()) {
        unsigned char c = f.get();
        frequencies[c]++;
    }

    //make a tree of huffman
    myList<Node*> tree;
    makeTree(frequencies,tree);

    Node *root = tree.front();   //the root of the tree

    //this vector stores binary code of each symbol or character
    myVector<myVector<bool> > table(256);
    //buffer vector that will store binary code of each letter or symbol
    myVector<bool> code;
    //making a binary code of each symbol or character and put in to the table
    buildTable(root,table,code);

    // going to the start of file
    f.clear(); f.seekg(0);

    //writing the name of file with "cmp"
    string name = s.substr(0, s.length() - 3) + "cmp";
    ofstream g(name.c_str(), ios::binary);

    //writing format of the "file" to the output file
    string cmp = s.substr(s.length() - 3, s.length());
    for(int i = 0; i < cmp.length(); i++) {
        g.write((char*) &cmp[i], sizeof(cmp[i]));
    }

    // write to the file tree's size for future reading it from file
    int treeSize = frequencies.size();
    g.write((char*) &treeSize, sizeof (treeSize));
    //write to the file the tree
    for (int i = 0; i < treeSize; i++) {
        g.write((char*) &frequencies[i], sizeof (frequencies[i]));
    }
    //count of bites;
    int count = 0;
    //buffer of letter or symbol at the tree
    unsigned char buf;

    while (!f.eof()) {
        unsigned char c = f.get();
        myVector<bool> x = table[c];
        //fill bits of char buf by using bitwise "OR" and write it to the file
        for(int n = 0; n < x.size(); n++) {
            buf = buf | x[n] << (7 - count);
            count++;
            //all 8 bits of char buf are filled
            if (count == 8) {
                count = 0;
                g << buf;
                buf = 0;
            }
        }
    }
    f.close();
    g.close();
}

//decompressing "file"
void decompress(string &s) {
    ifstream f(s.c_str(), ios::binary);
    //name of compressed file
    string file = s;

    //read start format of the file in compressed file and replace "cmp" in name of compresse file
    for(int i = file.length() - 3; i < file.length(); i++) {
        f.read((char*) &file[i], sizeof(file[i]));
    }
    //output stream
    ofstream g(file.c_str());

    //vector of frequencies
    myVector<int> frequencies(256);

    //the size of vector of freequencies
    int treeSize;
    f.read((char*) &treeSize, sizeof (treeSize));

    //nodes of vector(char,int)
    for (int i = 0; i < treeSize; i++) {
        f.read((char*) &frequencies[i], sizeof (frequencies[i]));
    }
    //makes a tree
    myList<Node*> tree;
    makeTree(frequencies,tree);
    //takes the root of the tree
    Node *root = tree.front();
    int count = 0;
    Node *p = root;
    unsigned char byte;
    byte = f.get();
    while(!f.eof()) {
        //read the data byte size and check all its bits and aacording them going by the tree to the last Node in this branch
        bool b = byte & (1 << (7 - count));
        if (b) {
            p = p->right;
        }else {
            p = p->left;
        }
        //last Node in current branch its char - write it to the file
        if (p->left == NULL && p->right == NULL) {
            unsigned char k = p->c;
            g.put(k);
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
}

int main(){
    setlocale(LC_ALL, "Russian");
    cout <<"Wellcome to the HUFFMAN algorithm programm"<<endl;
    cout <<"Please enter name of the file which you want to work with!"<<endl;
    //name of file
    string fileName;
    getline(cin, fileName);
    ifstream f(fileName.c_str(),ios::binary);
    if(f) {
        cout<<"To compress file - enter 'compress'     to decompress - 'decompress' "<<endl;
    }else {
        cout<<"No such file"<<endl;
    }
    string cmd;
    getline(cin,cmd);
    if(cmd == "compress") {
        compress(f,fileName);
        cout<<"File succssesfully compressed to "<<fileName.substr(0, fileName.length() - 3)<<"cmp !!!"<<endl;
    }else if(cmd == "decompress") {
        decompress(fileName);
        cout<<"File succssesfully decompressed!"<<endl;
    }else {
        cout<<"To compress file - enter 'compress'     to decompress - 'decompress' "<<endl;
    }

}
