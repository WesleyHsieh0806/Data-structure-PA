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
    int index; //依照array的順序給的index root為1 到時候可用來判斷是否為每個level最左邊的node
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
    //三個print text的function
    //destructor
    //紀錄depth i有哪些vertex(index) 的vector 搭配levelorder traversal function
    //紀錄每個index 的vertex是否存在 直為多少的vector
    //紀錄每個index的 vertex的ranking  搭配inorder traversal function
    //樹高已決定樹的depth
    //所有insert完成後再來處理vector的事情
public:
    void insert_node(int);
    void STree_txt(fstream &);//用來印出STree_Prep.txt
    void inorder_traversal(SplayNode*,int &,int);
    void STree_PRep(fstream &);//用來印出STree_PRep.txt
    void print_STree_PRep(fstream &,SplayNode*);
    void STree_boundary(fstream &);
    void Splay (SplayNode*);
    void right_rotation( SplayNode* );//向右 必須寫入target的parent 可當成right rotation
    void level_order_traversal();
    void left_rotation( SplayNode* );//向左
    void Zig_Zag( SplayNode* );//right_rotate( target->parent ) left_rotate( target->parent );==Zig_Zag(target)
    void Zag_Zig( SplayNode* );//left_rotate( target->parent );right_rotate( target->parent );
    void Zig_Zig( SplayNode* );//right_rotate( target->parent->parent );right_rotate( target->parent );==ZigZig(target)
    void Zag_Zag( SplayNode* );//left_rotate( target->parent->parent );left_rotate( target->parent );==ZagZag(target)
    SplayTree();
    void delete_node_recursively(SplayNode *);
    ~SplayTree();

    SplayNode *root;
    vector< vector<int > > depth_value ; //[i][j]depth i 有哪些value

    vector< vector<int > > depth_ranking; //depth i 的vertex ranking為啥;
    int depth;//此樹depth最大值 搭配level order


};
//Splay tree function建構
SplayTree::SplayTree()
{
    root=NULL;
    vector <int >hi;


    depth_value.assign(1000,hi);
    depth_ranking.assign(1000,hi);

    depth=-1;
}
void SplayTree::STree_txt(fstream & fout)//用來印出STree_Prep.txt
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
{ //處理vector< int> ranking; //index i 的vertex ranking為啥;

    if (current)                            // if current != NULL
    {   Depth++;
        inorder_traversal(current->leftchild,Rank,Depth);      // L
        depth_ranking[Depth].push_back(Rank);
        Rank++;                          //每次碰到current node後 ranking都要++
        inorder_traversal(current->rightchild,Rank,Depth);       // R
    }
}


void SplayTree::level_order_traversal()
{ // depth
    //vector< vector<int > > depth_index ; //[i][j]depth i 有哪些index有vertex
    //vector< pair<int,bool > > value_exist; //[i],first代表index i的vertex的數值 [i].second代表index i 是否存在
     queue<SplayNode*> q;
    q.push(root);                     // 把root作為level-order traversal之起點
    if(root)
    {
        root->index=1;

    }                                      // 推進queue中
    while (!q.empty()){                     // 若queue不是空的, 表示還有node沒有visiting

       SplayNode *current = q.front();       // 取出先進入queue的node
        q.pop();

        depth_value[LOG(current->index)].push_back(current->key);

        depth=LOG(current->index);
        if (current->leftchild != NULL){   // 若leftchild有資料, 將其推進queue
            q.push(current->leftchild);
            current->leftchild->index=current->index*2;

        }
        if (current->rightchild != NULL){   // 若rightchild有資料, 將其推進queue
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
    //用第回
    print_STree_PRep(fout,root);
    fout<<endl;
    return;
}

void SplayTree::STree_boundary(fstream & fout)
{   //先做完level order 才可能有做出txt的資訊
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
            root=y;//可能有問題
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
            root=y; //可能有問題
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
    //利用splay 讓target跑到root
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
    SplayNode *y = 0;       // 準新手爸媽
    SplayNode *x = 0;        // 哨兵


     x = root;
    while (x != NULL) {                 // 在while中, 以如同Search()的方式尋找適當的位置
        y = x;                          // y先更新到原來x的位置
        if (newnode->key < x->key){ // 判斷x是要往left- 還是right- 前進
            x = x->leftchild;
        }
        else{
            x = x->rightchild;
        }
    }                                   // 跳出迴圈後, x即為NULL
                                        // y即為insert_node的parent
    newnode->parent = y;            // 將insert_node的parent pointer指向y

    if (y == NULL){                     // 下面一組if-else, 把insert_node接上BST
        root = newnode;
    }

    else if (newnode->key < y->key){
        y->leftchild=newnode;    //insert完成 要splay
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
    //處理input

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
    delim=char(-62); //這個字元是non breaking space
    stringstream ss;
    int tree=0;
    while(getline(fin,buffer))
    {   cout<<tree;

        int position=0;
        BST Binary_search_tree;

        SplayTree splay_tree;

        //利用for迴圈把BST所有node處理好
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

        //此部分利用BST的資訊 開始產出output file
        Binary_search_tree.BTree_txt(BTreetxt);

        Binary_search_tree.BTree_BTree_PRep(BTreePRep);
        Binary_search_tree.BTree_boundary(BTreeboundary);
        splay_tree.level_order_traversal();
        splay_tree.STree_PRep(STree_PRep);
        splay_tree.STree_boundary(STree_boundary); //boundary 一定要在Stree前面坐 因為有level order;

        splay_tree.STree_txt(STree_txt);  //STree.txt內部已經做了inorder traversal
        //把此BST東西都刪掉 已進入下一次利用 但是destructor不能主動呼叫compiler自己會叫


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

//BSTfunction建構
void BST::insert_node(int key)
{
    //創建新的node並且insert
    //記得改變index ranking
    Node *y=0;
    Node *x=0;
    Node *newnode= new Node;

    newnode->key=key;
    newnode->index=1; //從root開始
    newnode->ranking=0; //預設他是最小
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
                q.push(x->rightchild);                     // 把root作為level-order traversal之起點
                 //推進queue中
                while (!q.empty())                      // 若queue不是空的, 表示還有node沒有visiting
                {

                    Node *current = q.front();      // 取出先進入queue的node
                    q.pop();
                    current->ranking++;

                    if (current->leftchild != NULL)     // 若leftchild有資料, 將其推進queue
                    {
                        q.push(current->leftchild);
                    }
                    if (current->rightchild != NULL)    // 若rightchild有資料, 將其推進queue
                    {
                        q.push(current->rightchild);
                    }

                }
            }
            newnode->index=newnode->index*2; //往左邊index就瞬間*2
            x=x->leftchild;

        }
        else
        {   newnode->ranking=x->ranking+1;
            newnode->index=newnode->index*2+1; //往右邊就是2*n+1
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
    //利用level order去印出這個output
    //每個node前面的空白數是3*比他小的element數量
    //node的狀況要分成%2==0 和%2!=0 所以要給node index



    queue <Node*> q;
    q.push(root);                     // 把root作為level-order traversal之起點
    int i=1;
    Node *last;

                                  // 推進queue中
    while (!q.empty())
    {
        // 若queue不是空的, 表示還有node沒有visiting

        Node *current = q.front();      // 取出先進入queue的node

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
            if(((current->index )&(current->index-1))==0) //判斷是否為2的次方
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

                //空格數要改 因為key要空間
                for(int j=1; j<(current->ranking)-(last->ranking); j++)
                {
                    fout<<"   ";
                }
                fout<<current->key; //補滿3格
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
                if(((current->index +1 )&(current->index))==0) //是否為該行最後一個node
                {
                    fout<<endl;

                }
            }
        }
        //空掉狀況
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
        if (current->leftchild != NULL)     // 若leftchild有資料, 將其推進queue
        {
            q.push(current->leftchild);
        }
        if (current->rightchild != NULL)    // 若rightchild有資料, 將其推進queue
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
    //用第回
     print_BTree_PRep(fout,root);
     fout<<endl;
     return;
}
void BST::print_BTree_boundary( fstream & fout,Node * root)
{   int depth=-1;
    queue<Node*> q;
    q.push(root);                     // 把root作為level-order traversal之起點
                                            // 推進queue中
    while (!q.empty())
    {
        // 若queue不是空的, 表示還有node沒有visiting

        Node *current = q.front();      // 取出先進入queue的node
        q.pop();

        if(LOG(current->index)>depth )
        {
            fout<<current->key<<" ";
            depth=LOG(current->index);

        }

        if (current->leftchild != NULL)     // 若leftchild有資料, 將其推進queue
        {
            q.push(current->leftchild);
        }
        if (current->rightchild != NULL)    // 若rightchild有資料, 將其推進queue
        {
            q.push(current->rightchild);
        }
    }

}
void BST::BTree_boundary(fstream & fout)
{
    //一直往左邊child走即可
    print_BTree_boundary(fout,root);
    fout<<endl;

    return;



}
BST::BST()
{
    root=NULL;
}
//此兩個函數 把tree所有node都刪光光
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



