#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include  <queue>
#include  <cmath>
#include <assert.h>
using namespace std;
class Node
{
public:

    int key;
    int ranking; //the number of nodes which are smaller than this node
    int index; //�̷�array�����ǵ���index root��1 ��ɭԥi�ΨӧP�_�O�_���C��level�̥��䪺node
private:
    Node *parent;
    Node *leftchild;
    Node *rightchild;
    friend class BST;

};

int LOG(int index)
{

    return floor(log10(index)/log10(2));

}
class BST
{
public:
    void insert_node(int);
    void BTree_txt(fstream &);
    void BTree_BTree_PRep(fstream &);
    void BTree_boundary(fstream &);
    void delete_node_recursively(Node *);
    void print_BTree_PRep( fstream &,Node * );
    void print_BTree_boundary( fstream &,Node * );
    BST();
    ~BST();

    Node *root;

};

class SplayNode
{
public:

    int key;
    int index;
private:
    SplayNode *parent;
    SplayNode *leftchild;
    SplayNode *rightchild;
    SplayNode()
    {
        index=0;
        parent=0;
        leftchild=0;
        rightchild=0;

    };
    friend class SplayTree;

};
class SplayTree
{
    //insertion
    //splay
    //Rotation
    //�T��print text��function
    //destructor
    //����depth i������vertex(index) ��vector �f�tlevelorder traversal function
    //�����C��index ��vertex�O�_�s�b �����h�֪�vector
    //�����C��index�� vertex��ranking  �f�tinorder traversal function
    //�𰪤w�M�w��depth
    //�Ҧ�insert������A�ӳB�zvector���Ʊ�
public:
    void insert_node(int);
    void STree_txt(fstream &);//�ΨӦL�XSTree_Prep.txt
    void inorder_traversal(SplayNode*,int &,int);
    void STree_PRep(fstream &);//�ΨӦL�XSTree_PRep.txt
    void print_STree_PRep(fstream &,SplayNode*);
    void STree_boundary(fstream &);
    void Splay (SplayNode*);
    void right_rotation( SplayNode* );//�V�k �����g�Jtarget��parent �i��right rotation
    void level_order_traversal();
    void left_rotation( SplayNode* );//�V��
    void Zig_Zag( SplayNode* );//right_rotate( target->parent ) left_rotate( target->parent );==Zig_Zag(target)
    void Zag_Zig( SplayNode* );//left_rotate( target->parent );right_rotate( target->parent );
    void Zig_Zig( SplayNode* );//right_rotate( target->parent->parent );right_rotate( target->parent );==ZigZig(target)
    void Zag_Zag( SplayNode* );//left_rotate( target->parent->parent );left_rotate( target->parent );==ZagZag(target)
    SplayTree();
    void delete_node_recursively(SplayNode *);
    ~SplayTree();

    SplayNode *root;
    vector< vector<int > > depth_value ; //[i][j]depth i ������value

    vector< vector<int > > depth_ranking; //depth i ��vertex ranking��ԣ;
    int depth;//����depth�̤j�� �f�tlevel order


};
//Splay tree function�غc
SplayTree::SplayTree()
{
    root=NULL;
    vector <int >hi;


    depth_value.assign(1000,hi);
    depth_ranking.assign(1000,hi);

    depth=-1;
}
void SplayTree::STree_txt(fstream & fout)//�ΨӦL�XSTree_Prep.txt
{   int Rank=0;
    inorder_traversal(root,Rank,-1);
    for(int i=0; i<=depth; i++)
    {
        for(int j=0; j<depth_value[i].size(); j++)
        {
            if(j==0)
            {
                for(int k=0; k<depth_ranking[i ][j] ; k++)
                {
                    fout<<"   ";
                }
                fout<<depth_value[i][j];
                if(depth_value[i][j]/100 >0)
                {

                }
                else
                {
                    if(depth_value[i][j]/10 >0)
                    {
                        fout<<" ";
                    }
                    else
                    {
                        fout<<"  ";
                    }


                }
            }
            else
            {
                for(int k=0; k<depth_ranking[i ][j]-depth_ranking[i][j-1]-1 ; k++)
                {
                    fout<<"   ";
                }
                fout<<depth_value[i][j];
                if(depth_value[i][j]/100 >0)
                {

                }
                else
                {
                    if(depth_value[i][j]/10 >0)
                    {
                        fout<<" ";
                    }
                    else
                    {
                        fout<<"  ";
                    }


                }
            }

        }
        fout<<endl;
    }
}

void SplayTree::inorder_traversal(SplayNode* current,int &Rank,int Depth)
{ //�B�zvector< int> ranking; //index i ��vertex ranking��ԣ;

    if (current)                            // if current != NULL
    {   Depth++;
        inorder_traversal(current->leftchild,Rank,Depth);      // L
        depth_ranking[Depth].push_back(Rank);
        Rank++;                          //�C���I��current node�� ranking���n++
        inorder_traversal(current->rightchild,Rank,Depth);       // R
    }
}


void SplayTree::level_order_traversal()
{ // depth
    //vector< vector<int > > depth_index ; //[i][j]depth i ������index��vertex
    //vector< pair<int,bool > > value_exist; //[i],first�N��index i��vertex���ƭ� [i].second�N��index i �O�_�s�b
     queue<SplayNode*> q;
    q.push(root);                     // ��root�@��level-order traversal���_�I
    if(root)
    {
        root->index=1;

    }                                      // ���iqueue��
    while (!q.empty()){                     // �Yqueue���O�Ū�, ����٦�node�S��visiting

       SplayNode *current = q.front();       // ���X���i�Jqueue��node
        q.pop();

        depth_value[LOG(current->index)].push_back(current->key);

        depth=LOG(current->index);
        if (current->leftchild != NULL){   // �Yleftchild�����, �N����iqueue
            q.push(current->leftchild);
            current->leftchild->index=current->index*2;

        }
        if (current->rightchild != NULL){   // �Yrightchild�����, �N����iqueue
            q.push(current->rightchild);
            current->rightchild->index=(current->index)*2+1;

        }
    }
}
void SplayTree::print_STree_PRep(fstream &fout,SplayNode* current)
{
    if(current!=NULL)
    {
        if((current->leftchild !=NULL)||(current->rightchild !=NULL))
        {


            fout<<current->key;
            fout<<"(";
            print_STree_PRep(fout,current->leftchild);
            fout<<" ";
            print_STree_PRep(fout,current->rightchild);
            fout<<")";
        }
        else
        {
            fout<<current->key;
        }
    }
    else
        fout<<"-";


}
void SplayTree::STree_PRep(fstream &fout)
{
    //�βĦ^
    print_STree_PRep(fout,root);
    fout<<endl;
    return;
}

void SplayTree::STree_boundary(fstream & fout)
{   //������level order �~�i�঳���Xtxt����T
    for(int i=0; i<=depth; i++)
    {
        fout<<depth_value[i][0]<<" ";


    }
    fout<<endl;



}
void SplayTree::right_rotation( SplayNode* x)
{
    SplayNode *y;
    y=x->leftchild;
    if(y)
    {
        x->leftchild=y->rightchild;
        if (y->rightchild !=NULL)
            y->rightchild->parent=x;
        y->parent=x->parent;
        if(x->parent == NULL)
            root=y;//�i�঳���D
        else if(x==x->parent->rightchild)
        {
            x->parent->rightchild=y;
        }
        else
        {
            x->parent->leftchild=y;
        }
        y->rightchild=x;
        x->parent=y;
    }
}

void SplayTree::left_rotation( SplayNode* x)
{
    SplayNode *y;
    if(x->rightchild)
    {
        y=x->rightchild;
    }
    if(y)
    {
        x->rightchild = y->leftchild;
        if (y->leftchild !=NULL)
        {
            y->leftchild->parent=x;
        }
        y->parent=x->parent;
        if(x->parent == NULL)
            root=y; //�i�঳���D
        else if(x==x->parent->leftchild)
        {
            x->parent->leftchild=y;
        }
        else
        {
            x->parent->rightchild=y;
        }
        y->leftchild=x;
        x->parent=y;
    }
}
void SplayTree::Zig_Zag( SplayNode* target )//right_rotate( target->parent ) left_rotate( target->parent );==Zig_Zag(target)
{
    right_rotation(target->parent);
    left_rotation(target->parent);
}
void SplayTree::Zag_Zig( SplayNode* target)//left_rotate( target->parent );right_rotate( target->parent );
{
    left_rotation(target->parent);
    right_rotation(target->parent);
}
void SplayTree::Zig_Zig( SplayNode* target)//right_rotate( target->parent->parent );right_rotate( target->parent );==ZigZig(target)
{
    right_rotation(target->parent->parent);
    right_rotation(target->parent);
}
void SplayTree::Zag_Zag( SplayNode* target)//left_rotate( target->parent->parent );left_rotate( target->parent );==ZagZag(target)
{
    left_rotation(target->parent->parent);
    left_rotation(target->parent);
}
void SplayTree::Splay (SplayNode* target)
{
    //�Q��splay ��target�]��root
    while(target->parent)
    {
        if( !target->parent->parent )
        {
            if( target->parent->leftchild == target )
                right_rotation( target->parent );
            else
                left_rotation(target->parent) ;
        }
        else if( target->parent->leftchild == target && target->parent->parent->leftchild == target->parent )
        {
            Zig_Zig(target);
        }
        else if( target->parent->rightchild == target && target->parent->parent->rightchild == target->parent )
        {
            Zag_Zag(target);
        }
        else if( target->parent->leftchild == target && target->parent->parent->rightchild == target->parent )
        {
            Zig_Zag(target);
        }
        else {
            Zag_Zig(target);
        }
    }
    root=target;
}
void SplayTree::insert_node(int key)
{   SplayNode *newnode=new SplayNode;


    newnode->key=key;
    newnode->leftchild=NULL;
    newnode->rightchild=NULL;
    newnode->parent=NULL;
    SplayNode *y = 0;       // �Ƿs�⪨��
    SplayNode *x = 0;        // ��L


     x = root;
    while (x != NULL) {                 // �bwhile��, �H�p�PSearch()���覡�M��A����m
        y = x;                          // y����s����x����m
        if (newnode->key < x->key){ // �P�_x�O�n��left- �٬Oright- �e�i
            x = x->leftchild;
        }
        else{
            x = x->rightchild;
        }
    }                                   // ���X�j���, x�Y��NULL
                                        // y�Y��insert_node��parent
    newnode->parent = y;            // �Ninsert_node��parent pointer���Vy

    if (y == NULL){                     // �U���@��if-else, ��insert_node���WBST
        root = newnode;
    }

    else if (newnode->key < y->key){
        y->leftchild=newnode;    //insert���� �nsplay
        Splay(newnode);

    }
    else{
        y->rightchild=newnode;
        Splay(newnode);

    }

}
void SplayTree::delete_node_recursively(SplayNode *current)
{
    if(current!=NULL)
    {


        delete_node_recursively(current->leftchild);
        delete_node_recursively(current->rightchild);

        delete current;

    }

}
SplayTree::~SplayTree()
{
    delete_node_recursively(root);

    for(int i=0;i<=999;i++){
    depth_ranking[i].clear();
    depth_value[i].clear();
    }


}
int main()
{
    //�B�zinput

    fstream fin;
    fstream BTreetxt;
    fstream BTreePRep;
    fstream BTreeboundary;
    fstream STree_PRep;
    fstream STree_boundary;
    fstream STree_txt;
    string buffer;


    int key;

    system("chcp 65001");
    fin.open("Prog1_note/input.txt",ios::in);
    BTreetxt.open("BTree.txt",ios::out);
    BTreePRep.open("BTree_PRep.txt",ios::out);
    BTreeboundary.open("BTree_boundary.txt",ios::out);
    STree_PRep.open("STree_ PRep.txt",ios::out);
    STree_boundary.open("STree_boundary.txt",ios::out);
    STree_txt.open("STree.txt",ios::out);

    char delim;
    delim=char(-62); //�o�Ӧr���Onon breaking space
    stringstream ss;
    int tree=0;
    while(getline(fin,buffer))
    {   cout<<tree;

        int position=0;
        BST Binary_search_tree;

        SplayTree splay_tree;

        //�Q��for�j���BST�Ҧ�node�B�z�n
        for( int i=0; i<=buffer.size()-1; i++)
        {
            if(int(buffer[i])==int(delim))
            {
                ss.str(buffer.substr(position,i-position));
                ss>>key;
                Binary_search_tree.insert_node(key);
                splay_tree.insert_node(key);

                position=i+2;
                ss.str("");
                ss.clear();
            }
            else if(i==buffer.size()-1)
            {
                ss.str(buffer.substr(position,i-position+1));
                ss>>key;
                Binary_search_tree.insert_node(key);
                splay_tree.insert_node(key);

                ss.str("");
                ss.clear();
            }
        }

        //�������Q��BST����T �}�l���Xoutput file
        Binary_search_tree.BTree_txt(BTreetxt);

        Binary_search_tree.BTree_BTree_PRep(BTreePRep);
        Binary_search_tree.BTree_boundary(BTreeboundary);
        splay_tree.level_order_traversal();
        splay_tree.STree_PRep(STree_PRep);
        splay_tree.STree_boundary(STree_boundary); //boundary �@�w�n�bStree�e���� �]����level order;

        splay_tree.STree_txt(STree_txt);  //STree.txt�����w�g���Finorder traversal
        //�⦹BST�F�賣�R�� �w�i�J�U�@���Q�� ���Odestructor����D�ʩI�scompiler�ۤv�|�s


//        Binary_search_tree.~BST();
//        splay_tree.~SplayTree();

               tree++;

    }












    //BST part






    fin.close();
    BTreetxt.close();
    BTreePRep.close();
    BTreeboundary.close();
    STree_PRep.close();
    STree_boundary.close();
    STree_txt.close();
    return 0;
}

//BSTfunction�غc
void BST::insert_node(int key)
{
    //�Ыطs��node�åBinsert
    //�O�o����index ranking
    Node *y=0;
    Node *x=0;
    Node *newnode= new Node;

    newnode->key=key;
    newnode->index=1; //�qroot�}�l
    newnode->ranking=0; //�w�]�L�O�̤p
    newnode->leftchild=NULL;
    newnode->rightchild=NULL;
    newnode->parent=NULL;
    y=NULL;
    x=root;

    while(x!=NULL)
    {
        y=x;
        if (newnode->key < x->key)
        {   x->ranking++;

            if(x->rightchild!=NULL)
            {
                queue<Node*> q;
                q.push(x->rightchild);                     // ��root�@��level-order traversal���_�I
                 //���iqueue��
                while (!q.empty())                      // �Yqueue���O�Ū�, ����٦�node�S��visiting
                {

                    Node *current = q.front();      // ���X���i�Jqueue��node
                    q.pop();
                    current->ranking++;

                    if (current->leftchild != NULL)     // �Yleftchild�����, �N����iqueue
                    {
                        q.push(current->leftchild);
                    }
                    if (current->rightchild != NULL)    // �Yrightchild�����, �N����iqueue
                    {
                        q.push(current->rightchild);
                    }

                }
            }
            newnode->index=newnode->index*2; //������index�N����*2
            x=x->leftchild;

        }
        else
        {   newnode->ranking=x->ranking+1;
            newnode->index=newnode->index*2+1; //���k��N�O2*n+1
            x=x->rightchild;
        }
    }
    newnode->parent=y;
    if(y==NULL)
    {
        root=newnode;
    }
    else if(newnode->key < y->key)
    {
        y->leftchild=newnode;
    }
    else
    {
        y->rightchild=newnode;
    }

}
void BST::BTree_txt(fstream & fout)
{
    //�Q��level order�h�L�X�o��output
    //�C��node�e�����ťռƬO3*��L�p��element�ƶq
    //node�����p�n����%2==0 �M%2!=0 �ҥH�n��node index



    queue <Node*> q;
    q.push(root);                     // ��root�@��level-order traversal���_�I
    int i=1;
    Node *last;

                                  // ���iqueue��
    while (!q.empty())
    {
        // �Yqueue���O�Ū�, ����٦�node�S��visiting

        Node *current = q.front();      // ���X���i�Jqueue��node

        q.pop();
        if(current->index==1)
        {

            for(int j=1; j<=current->ranking; j++)
            {
                fout<<"   ";
            }

            fout<<current->key;
            fout<<"\n";


        }
        else if(current->index==i)
        {
            if(((current->index )&(current->index-1))==0) //�P�_�O�_��2������
            {
                for(int j=1; j<=current->ranking; j++)
                {
                    fout<<"   ";
                }

                fout<<current->key;

                if(current->key/100 >0)
                {

                }
                else
                {
                    if(current->key/10 >0)
                    {
                        fout<<" ";
                    }
                    else
                    {
                        fout<<"  ";
                    }


                }



            }
            else if(((current->index )&(current->index-1))!=0)
            {

                //�Ů�ƭn�� �]��key�n�Ŷ�
                for(int j=1; j<(current->ranking)-(last->ranking); j++)
                {
                    fout<<"   ";
                }
                fout<<current->key; //�ɺ�3��
                if(current->key/100 >0)
                {

                }
                else
                {
                    if(current->key/10 >0)
                    {
                        fout<<" ";
                    }
                    else
                    {
                        fout<<"  ";
                    }


                }
                if(((current->index +1 )&(current->index))==0) //�O�_���Ӧ�̫�@��node
                {
                    fout<<endl;

                }
            }
        }
        //�ű����p
        else if(current->index!=i)
        {
            if(LOG(last->index)<LOG(current->index))
            {   fout<<endl;

                for(int j=1; j<=current->ranking; j++)
                {
                    fout<<"   ";
                }
                fout<<current->key;
                if(current->key/100 >0)
                {

                }
                else
                {
                    if(current->key/10 >0)
                    {
                        fout<<" ";
                    }
                    else
                    {
                        fout<<"  ";
                    }


                }
                i=current->index;

            }
            else if(LOG((last->index))==LOG((current->index)))
            {
                for(int j=1; j<=((current->ranking)-(last->ranking)-1); j++)
                {
                    fout<<"   ";
                }
                fout<<current->key;
                if(current->key/100 >0)
                {

                }
                else
                {
                    if(current->key/10 >0)
                    {
                        fout<<" ";
                    }
                    else
                    {
                        fout<<"  ";
                    }


                }
                i=current->index;
            }
//            if(((current->index +1 )&(current->index))==0)
//            {
//                fout<<endl;
//            }
        }
        if (current->leftchild != NULL)     // �Yleftchild�����, �N����iqueue
        {
            q.push(current->leftchild);
        }
        if (current->rightchild != NULL)    // �Yrightchild�����, �N����iqueue
        {
            q.push(current->rightchild);
        }
        i++;
        last=current;
    }


    fout<<endl;


}
void BST::print_BTree_PRep( fstream &fout,Node * current)
{
    if(current!=NULL)
    {
        if((current->leftchild !=NULL)||(current->rightchild !=NULL))
        {


            fout<<current->key;
            fout<<"(";
            print_BTree_PRep(fout,current->leftchild);
            fout<<" ";
            print_BTree_PRep(fout,current->rightchild);
            fout<<")";
        }
        else
        {
            fout<<current->key;
        }
    }
    else
        fout<<"-";



}
void BST::BTree_BTree_PRep(fstream &fout)
{
    //�βĦ^
     print_BTree_PRep(fout,root);
     fout<<endl;
     return;
}
void BST::print_BTree_boundary( fstream & fout,Node * root)
{   int depth=-1;
    queue<Node*> q;
    q.push(root);                     // ��root�@��level-order traversal���_�I
                                            // ���iqueue��
    while (!q.empty())
    {
        // �Yqueue���O�Ū�, ����٦�node�S��visiting

        Node *current = q.front();      // ���X���i�Jqueue��node
        q.pop();

        if(LOG(current->index)>depth )
        {
            fout<<current->key<<" ";
            depth=LOG(current->index);

        }

        if (current->leftchild != NULL)     // �Yleftchild�����, �N����iqueue
        {
            q.push(current->leftchild);
        }
        if (current->rightchild != NULL)    // �Yrightchild�����, �N����iqueue
        {
            q.push(current->rightchild);
        }
    }

}
void BST::BTree_boundary(fstream & fout)
{
    //�@��������child���Y�i
    print_BTree_boundary(fout,root);
    fout<<endl;

    return;



}
BST::BST()
{
    root=NULL;
}
//����Ө�� ��tree�Ҧ�node���R����
void BST::delete_node_recursively(Node *current)
{
    if(current!=NULL)
    {

        delete_node_recursively(current->leftchild);
        delete_node_recursively(current->rightchild);
//        cout<<"delete"<<current->key<<endl;
        delete current;
    }

}
BST::~BST()
{
    delete_node_recursively(root);

}



