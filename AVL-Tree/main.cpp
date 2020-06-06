#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
template <typename T>
class AVL_Tree{
private:
    //AVL树结点
    class AVLTreeNode{
    public:
        AVLTreeNode(){}
        AVLTreeNode(T data_,int height_ = 1){
            data = data_;
            left_son = right_son = nullptr;
            height = height_;
        }
        AVLTreeNode(T data_,AVLTreeNode* left_son_,AVLTreeNode* right_son_,int height_ = 1){
            data = data_;
            left_son = left_son_;
            right_son = right_son_;
            height = height_;
        }
        const T& getData() const{
            return data;
        }
        void setData(const T& data_){
            data = data_;
        }

        AVLTreeNode*& getLeftSon(){
            return left_son;
        }
        void setLeftSon(const AVLTreeNode*& left_son_){
            left_son = left_son_;
        }

        AVLTreeNode*& getRightSon(){
            return right_son;
        }
        void setRightSon(const AVLTreeNode*& right_son_){
            right_son = right_son_;
        }

        int& getHeight(){
            return height;
        }
        void setHeight(const int& height_){
            height = height_;
        }
    private:
        //数据，左儿子指针，右儿子指针，当前节点高度
        T data;
        AVLTreeNode* left_son;
        AVLTreeNode* right_son;
        int height;
    };
    //根节点
    AVLTreeNode* root;
    int size;

    //新建一个节点
    inline AVLTreeNode* newAVLTreeNode(const T& data_){
        return new AVLTreeNode(data_);
    }

    inline const int Max(int x,int y) const{
        return x<y?y:x;
    }
    //求树节点高度
    inline const int height(AVLTreeNode*& rt)const {
        return rt == nullptr?0:rt->getHeight();
    }

    //比较x和y的大小
    inline const int Compare(const T& x,const T& y) const{
        if(x<y){
            return -1;
        } else if(x==y){
            return 0;
        } else{
            return 1;
        }
    }

    //左旋
    void LeftRotate(AVLTreeNode* &rt){
        AVLTreeNode *tempNode = rt->getRightSon();
        rt->getRightSon() = tempNode->getLeftSon();
        tempNode->getLeftSon() = rt;
        rt->getHeight() = Max(height(rt->getLeftSon()),height(rt->getRightSon()))+1;
        tempNode->getHeight() = Max(height(tempNode->getLeftSon()),height(tempNode->getRightSon()))+1;
        rt = tempNode;
    }
    //右旋
    void RightRotate(AVLTreeNode* &rt){                           //h(lst)>h(rst)时使用
        AVLTreeNode *tempNode = rt->getLeftSon();   //        rt                     ls
        rt->getLeftSon() = tempNode->getRightSon(); //      ls    rst     ==>    lst    rt
        tempNode->getRightSon() = rt;               //   lst  lrst                   lrst   rst
        rt->getHeight() = Max(height(rt->getLeftSon()),height(rt->getRightSon()))+1;
        tempNode->getHeight() = Max(height(tempNode->getLeftSon()),height(tempNode->getRightSon()))+1;
        rt = tempNode;
    }
    //左旋+右旋（双旋）
    void LeftAndRightRotate(AVLTreeNode* rt){
        LeftRotate(rt->getLeftSon());
        RightRotate(rt);
    }
    //右旋+左旋（双旋）
    void RightAndLeftRotate(AVLTreeNode* rt){
        RightRotate(rt->getRightSon());
        LeftRotate(rt);
    }
    //插入一个节点
    void Insert(AVLTreeNode*& rt,T data_){
        if(rt == nullptr){
            size++;
            rt = newAVLTreeNode(data_);
            return;
        }
        int CompareResult = Compare(data_,rt->getData());
        //相等时也放进左子树
        if(CompareResult <= 0){
            //放在左子树
            Insert(rt->getLeftSon(),data_);
            int leftHeight = height(rt->getLeftSon()),rightHeight = height(rt->getLeftSon());
            if(leftHeight >= rightHeight + 2){
                if(data_ < rt->getLeftSon()->getData()){
                    RightRotate(rt);
                } else {
                    LeftAndRightRotate(rt);
                }
            }
        } else {
            //放在右子树
            Insert(rt->getRightSon(),data_);
            int leftHeight = height(rt->getLeftSon()),rightHeight = height(rt->getLeftSon());
            if(leftHeight + 2 <= rightHeight) {
                if (data_ < rt->getRightSon()->getData()) {
                    RightAndLeftRotate(rt);
                } else {
                    LeftRotate(rt);
                }
            }
        }
        rt->getHeight() = Max(height(rt->getLeftSon()),height(rt->getRightSon()))+1;
    }

    //TODO:返回下一个节点的迭代器
    void Erase(AVLTreeNode* rt,T date_){

    }




    //找到一个值在AVL树中的位置，如果没有返回空指针 TODO:实现迭代器，返回end()
    const AVLTreeNode* Find(AVLTreeNode*& rt,T date_) const {
        if(rt == nullptr){
            return nullptr;
        }
        int CompareResult = Compare(date_,rt->getData());
        if(CompareResult == -1){
            return Find(rt->getLeftSon(),date_);
        } else if (CompareResult == 1){
            return Find(rt->getRightSon(),date_);
        } else {
            return rt;
        }
    }

public:
    AVL_Tree(){
        root = nullptr;
        size=0;
    }
    ~AVL_Tree(){
        //TODO:后序遍历析构树
        std::queue<AVLTreeNode*> nodequeue;
        while (!nodequeue.empty()) nodequeue.pop();
        nodequeue.push(root);
        while(!nodequeue.empty()){
            AVLTreeNode* temp = nodequeue.front();
            nodequeue.pop();
            if(temp->getLeftSon()!= nullptr) nodequeue.push(temp->getLeftSon());
            if(temp->getRightSon()!= nullptr) nodequeue.push(temp->getRightSon());
            temp->getLeftSon() = temp->getRightSon() = nullptr;
            delete temp;
        }
        root = nullptr;
        size=0;
    }

    void insert(T data_){
        Insert(root,data_);
    }

    const AVLTreeNode* find(T data_) const{
        return Find(root,data_);
    }

    //前序遍历输出
    void printBypre() const{
        std::cout<<"前序遍历"<<std::endl;
        int tol=0;
        std::stack<AVLTreeNode*> nodestack;
        while(!nodestack.empty()) nodestack.pop();
        nodestack.push(root);
        while(!nodestack.empty()){
            AVLTreeNode* temp=nodestack.top();
            nodestack.pop();
            std::cout<<"第"<<++tol<<"个节点是："<<temp->getData()<<std::endl;
            if(temp->getLeftSon()!= nullptr) nodestack.push(temp->getLeftSon());
            if(temp->getRightSon()!= nullptr) nodestack.push(temp->getRightSon());
        }
    }

    //中序遍历输出
    void printBymid()const {
        std::cout<<"中序遍历"<<std::endl;
        int tol=0;
        std::stack<AVLTreeNode*> nodestack;
        while(!nodestack.empty()) nodestack.pop();
        nodestack.push(root);
        while(!nodestack.empty()){
            while (nodestack.top()->getLeftSon()!= nullptr){
                nodestack.push(nodestack.top()->getLeftSon());
            }
            while(!nodestack.empty()){
                AVLTreeNode* temp=nodestack.top();
                nodestack.pop();
                std::cout<<"第"<<++tol<<"个节点是："<<temp->getData()<<std::endl;
                if(temp->getRightSon()!= nullptr){
                    nodestack.push(temp->getRightSon());
                    break;
                }
            }
        }
    }

    //后序遍历输出
    void printBysuf()const{
        std::cout<<"后序遍历"<<std::endl;
        int tol=0;
        std::stack<AVLTreeNode*> nodestack;
        AVLTreeNode* lstNode = nullptr;
        while(!nodestack.empty()) nodestack.pop();
        nodestack.push(root);
        while(!nodestack.empty()){
            while (nodestack.top()->getLeftSon()!= nullptr){
                nodestack.push(nodestack.top()->getLeftSon());
            }
            while(!nodestack.empty()){
                AVLTreeNode* temp=nodestack.top();
                if(temp->getRightSon() == nullptr||lstNode == temp->getRightSon()){
                    nodestack.pop();
                    std::cout<<"第"<<++tol<<"个节点是："<<temp->getData()<<std::endl;
                    lstNode = temp;
                } else if(temp->getRightSon()!= nullptr){
                    nodestack.push(temp->getRightSon());
                    break;
                }
            }
        }
    }
};



int main() {
    AVL_Tree<int> mytree;
    srand(time(NULL));
    std::string ss;
    for(int i=1;i<=10;i++)
        mytree.insert(rand()%100000);
    //mytree.printBypre();
    mytree.printBymid();
    return 0;
}