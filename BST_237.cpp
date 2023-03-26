#include<iostream>
#define SPACE 10
using namespace std;

struct node
{
    node* left;
    int data;
    node* right;
};
class BST
{
    private:
        node* root;
    public:
        BST();
        ~BST();
        node* getRoot();
        void inorder(node* r);
        void iInsert(int key);
        node* rinsert(node* r, int key);
        node* iSearch(int );
        node* rSearch(node* r, int key);
        void del(int key);
        int height(node* r);
        node* inPre(node* r);
        node* inSucc(node* r);
        void print2D(node * r, int space);
};
BST::BST()
{
    root=NULL;
}
node* BST::getRoot()
{
    return root;
}
void BST::iInsert(int key)
{
    node* n=new node;
    n->data=key;
    n->left=NULL;
    n->right=NULL; 

    if(root==NULL)
    {
        root=n;
        return;
    } 
    else
    {
        node *curr=root;
        node *par=NULL;
        while(curr != NULL)
        {
            par=curr;
            if(key < curr->data)
                curr=curr->left;
            else if(key > curr->data)
                curr=curr->right;
            else if(key == curr->data)
            {   
                cout<<"\nDuplicate value not allowed";
                break;
            }
        }
        if(key < par->data)
            par->left=n;
        else
            par->right=n;
    }
}

node* BST::rinsert(node* r, int key)
{
    if(r==NULL)
    {
        node* n= new node;
        n->data=key;
        n->left=NULL;
        n->right=NULL;
        return n;
    }
    if(key < r->data)
    {
        r->left = rinsert(r->left, key);
    }
    else if(key > r->data)
    {
        r->right = rinsert(r->right, key);
    }
    else if(key == r->data)
    {
        cout<<"\nDuplicate key not allowed";
    }
    return r;
}

void BST::inorder(node* r)
{
    if(r)
    {
        inorder(r->left);
        cout<<r->data<<" ";
        inorder(r->right);
    }
}

node* BST::iSearch(int key)
{
    node* t=root;
    while(t)
    {
        if(key == t->data)
        {
            return t;
        }
        if(key < t->data)
        {
            t=t->left;
        }
        else 
        {
            t=t->right;
        }
    }
    return NULL; // root==NULL or key is not found
}

node* BST::rSearch(node* r, int key)
{
    if(r==NULL)
        return NULL;
    if(key == r->data)
        return r;
    else if(key < r->data)
        rSearch(r->left, key);
    else
        rSearch(r->right, key);
}

node* BST::inPre(node* r)
{
    while(r != NULL && r->right != NULL)
        r=r->right;
    return r;
}

node* BST::inSucc(node* r)
{
    while(r != NULL && r->left != NULL)
        r=r->left;
    return r;
}

// deletion without recursion
void BST::del(int key)
{
    node* par=NULL;
    node* curr=root;

    //set curr = node to be deleted , and par to it's previous
    while(key != curr->data) 
    {
        par=curr;
        if(key < curr->data)
            curr=curr->left;
        else
            curr=curr->right;
    }
    //Return if data not found
    if(curr==NULL)
        return;

    //root note to be deleted
    if(par==NULL && curr != NULL)
    {
        //0 child of root node
        if(curr->left==NULL && curr->right==NULL) 
        {
            delete curr;
            root=NULL;
        }
        //Two child of root node
        else if(curr->left != NULL && curr->right != NULL)
        {
            node *succ=curr->left;            
            node *parSucc=curr;               
            while(succ->right !=NULL)         
            {                                 
                parSucc=succ;                 
                succ=succ->right;             
            }     
            curr->data=succ->data;                            
            if(curr->left == succ)
                curr->left=succ->left;
            else
                parSucc->right=succ->left;         
            delete succ;
        }
        //one child of root node
        else
        {
            if(curr->right!=NULL)
                root=curr->right;
            else
                root=curr->left;
            delete curr;
        }
    }
    //node to be deleted is not a root node
    else
    //if data is at leaf node or no children
    {
        if(curr->left==NULL && curr->right==NULL)                                                              
        {                                                                                                                                                           
            if(par->left==curr)                                                                                                                                     
                par->left=NULL;                                                                                                                                     
            else                                                                                                                                                    
                par->right=NULL;                                                                                                                                    
            delete curr;                                                                                                                                            
        }                                                                                                                                                           
                                                                                                               
        //  if node to be deleted has two children                                                               
        //  First get the value of Successor                                                                        
        else if(curr->left != NULL && curr->right != NULL)                                                                                                       
        {                                                                                                      
            node *succ=curr->left;                                                                                                                  
            node *parSucc=curr;                                                                                                                     
            while(succ->right !=NULL)                                                                                                               
            {                                                                                                                                       
                parSucc=succ;                                                                                                                       
                succ=succ->right;                                                                                                                   
            }                                                                                                           
            curr->data=succ->data;                                                                                                                                  
            if(succ->left != NULL)                                                                                                      
                parSucc->right=succ->left;                                                                                                      
            else
                parSucc->left=succ->left;           
            delete succ;
        }

        // if node to be deleted has one children
        else 
        {
            if(par->right == curr)
            {
                if(curr->left == NULL) 
                    par->right=curr->right;  
                else
                    par->right=curr->left;
                delete curr;
            }
            else                           
            {
                if(curr->left == NULL)
                    par->left=curr->right;
                else
                    par->left=curr->left;
                delete curr;
            }
        }
    }
}
BST::~BST()
{
    while(root)
        del(root->data);
}
void BST::print2D(node* r, int space) {
    if (r == NULL) // Base case  1
      return;
    space += SPACE; // Increase distance between levels   2
    print2D(r -> right, space); // Process right child first 3 
    cout << endl;
    for (int i = SPACE; i < space; i++) // 5 
      cout << " "; // 5.1  
    cout << r -> data << "\n"; // 6
    print2D(r -> left, space); // Process left child  7
  }
int main()
{
    BST b1;
    b1.iInsert(80);               /*                       80                              */
    b1.iInsert(70);               /*                      /  \                             */
    b1.iInsert(90);               /*                    70    90                           */
    b1.iInsert(60);               /*                   /     /  \                          */
    b1.iInsert(85);               /*                  60    85   100                       */
    b1.iInsert(100);              /*                       /  \                            */
    b1.iInsert(83);               /*                     83    87                          */
    b1.iInsert(87);               /*                           /                           */
    b1.iInsert(86);               /*                          86                           */
    
    b1.inorder(b1.getRoot());
    //b1.del(80);
    //b1.del(70);
    //b1.del(90);
    //b1.del(60);
    //b1.del(85);
    //b1.del(100);
    //b1.del(83);
    //b1.del(87);
    //b1.del(86);
   
    b1.print2D(b1.getRoot(),5);
    
    cout<<endl;
}