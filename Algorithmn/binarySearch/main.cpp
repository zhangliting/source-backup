#include <iostream>
#include <queue>


using namespace std;

/**
 *  二分查找法,在有序数组arr中,查找target
 *  如果找到target,返回相应的索引index
 *  如果没有找到target,返回-1
 */
template<typename T>
int binarySearch(T arr[], int n, T target) {
    int l = 0, r = n - 1;
    while (l <= r) {
        //防止整数溢出，等价于(l+r)/2
        int mid = l + (r - l) / 2;
        if (arr[mid] == target) {
            return mid;
        }
        if (arr[mid] > target) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return -1;
}

template<typename T>
int __binarySearch2(T arr[], int l, int r, T target) {
    if (l > r) {
        return -1;
    }
    int mid = l + (r - l) / 2;
    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] > target) {
        return __binarySearch2(arr, 0, mid - 1, target);
    } else {
        return __binarySearch2(arr, mid + 1, r, target);
    }
}

template<typename T>
int binarySearch2(T arr[], int n, T target) {
    return __binarySearch2(arr, 0, n - 1, target);
}

//二叉搜索树
template<typename Key, typename Value>
class BST {
private:
    struct Node {
        Key key;
        Value value;
        Node *left;
        Node *right;

        Node(Key key, Value value) {
            this->key = key;
            this->value = value;
            this->left = this->right = NULL;
        }

        Node(Node* node){
            this->key = node->key;
            this->value = node->value;
            this->left = node->left;
            this->right = node->right;
        }
    };

    Node *root;
    int count;

    Node *insert(Node *node, Key key, Value value) {
        if (node == NULL) {
            count++;
            return new Node(key, value);
        }
        if (key == node->key) {
            node->value = value;
        } else if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else {
            node->right = insert(node->right, key, value);
        }

        return node;
    }

    bool contain(Node *node, Key key) {
        if (node == NULL) {
            return false;
        }
        if (key == node->key) {
            return true;
        } else if (key < node->key) {
            return contain(node->left, key);
        } else {
            return contain(node->right, key);
        }
    }

    Value *search(Node *node, Key key) {
        if (node == NULL) {
            return NULL;
        }
        if (key == node->key) {
            return &(node->value);
        } else if (key < node->key) {
            return search(node->left, key);
        } else {
            return search(node->right, key);
        }
    }

    void preOrder(Node *node) {
        if (node != NULL) {
            cout << node->key << endl;
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void inOrder(Node *node) {
        if (node != NULL) {
            inOrder(node->left);
            cout << node->key << endl;
            inOrder(node->right);
        }
    }

    void postOrder(Node *node) {
        if (node != NULL) {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->key << endl;
        }
    }

    void destroy(Node *node) {
        if (node != NULL) {
            destroy(node->left);
            destroy(node->right);
            delete node;
            count--;
        }
    }

    Node *minimum(Node *node) {
        if (node->left == NULL) {
            return node;
        }
        return minimum(node->left);
    }

    Node *maximum(Node *node) {
        if (node->right == NULL) {
            return node;
        }
        return maximum(node->right);
    }

    Node *removeMin(Node *node) {
        if (node->left == NULL) {
            Node *righNode = node->right;
            delete node;
            count--;
            return righNode;
        }

        node->left = removeMin(node->left);
        return node;
    }

    Node *removeMax(Node *node) {
        if (node->right == NULL) {
            Node *leftNode = node->left;
            delete node;
            count--;
            return leftNode;
        }

        node->right = removeMax(node->right);
        return node;
    }

    //删除以node为根的二分搜索树种键值为key的节点，返回新的根
    Node *remove(Node *node, Key key) {
        if (node == NULL) {
            return NULL;
        }
        if (key < node->key) {
            node->left = remove(node->left, key);
            return node;
        } else if (key > node->key) {
            node->right = remove(node->right, key);
            return node;
        } else {
            //key == node->key
            if (node->left == NULL) {
                Node *righNode = node->right;
                delete node;
                count--;
                return righNode;
            }
            if (node->right == NULL) {
                Node *leftNode = node->left;
                delete node;
                count--;
                return leftNode;
            }
            //node->left != NULL && node->right != NULL
            Node *successor = new Node(minimum(node->right));
            count++;
            successor->right = removeMin(node->right);
            successor->left = node->left;

            delete node;
            count--;
            return successor;
        }
    }

public:
    BST() {
        root = NULL;
        count = 0;
    }

    ~BST() {
        destroy(root);
    }

    int size() {
        return count;
    }

    bool isEmpty() {
        return count == 0;
    }

    void insert(Key key, Value value) {
        root = insert(root, key, value);
    }

    bool contain(Key key){
        return contain(root, key);
    }
    Value *search(Key key) {
        return search(root, key);
    }

    //前序遍历
    void preOrder() {
        preOrder(root);
    }

    //中序遍历
    void inOrder() {
        inOrder(root);
    }

    //后序遍历
    void postOrder() {
        postOrder(root);
    }

    //层序遍历
    void levelOrder() {
        queue<Node *> q;
        q.push(root);
        while (!q.empty()) {
            Node *node = q.front();
            q.pop();
            cout << node->key << endl;

            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }
        }
    }

    //最小键值
    Key minimun() {
        assert(count != 0);
        Node *minNode = minimun(root);
        return minNode->key;
    }

    //最大键值
    Key maximum() {
        assert(count != 0);
        Node *maxNode = maximum(root);
        return maxNode->key;
    }

    //删除最小的值得节点
    void removeMin() {
        if (root) {
            root = removeMin(root);
        }
    }

    //删除最大的值得节点
    void removeMax() {
        if (root) {
            root = removeMax(root);
        }
    }

    //从二叉树中删除键值为Key的节点
    void remove(Key key) {
        root = remove(root, key);
    }


};

void shuffle( int arr[], int n ){

    srand( time(NULL) );
    for( int i = n-1 ; i >= 0 ; i -- ){
        int x = rand()%(i+1);
        swap( arr[i] , arr[x] );
    }
}

int main() {
    /*int n = 1000000;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
        a[i] = i;

    // 测试非递归二分查找法
    clock_t startTime = clock();
    for (int i = 0; i < 2 * n; i++) {
        int v = binarySearch(a, n, i);
        if (i < n)
            assert(v == i);
        else
            assert(v == -1);
    }
    clock_t endTime = clock();
    cout << "Binary Search (Without Recursion): " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

    // 测试递归的二分查找法
    startTime = clock();
    for (int i = 0; i < 2 * n; i++) {
        int v = binarySearch2(a, n, i);
        if (i < n)
            assert(v == i);
        else
            assert(v == -1);
    }
    endTime = clock();
    cout << "Binary Search (Recursion): " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;


    delete[] a;

    string filename = "/Users/zhangliting/github/source-backup/Algorithmn/binarySearch/bible.txt";
    vector<string> words;
    if (FileOps::readFile(filename, words)) {

        cout << "There are totally " << words.size() << " words in " << filename << endl;

        cout << endl;


        // test BST
        time_t startTime = clock();
        BST<string, int> bst = BST<string, int>();
        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
            int *res = bst.search(*iter);
            if (res == NULL)
                bst.insert(*iter, 1);
            else
                (*res)++;
        }

        cout << "'god' : " << *bst.search("god") << endl;
        time_t endTime = clock();
        cout << "BST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;

        cout << endl;*/


    // test SST
    /* startTime = clock();
     SequenceST<string, int> sst = SequenceST<string, int>();
     for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
         int *res = sst.search(*iter);
         if (res == NULL)
             sst.insert(*iter, 1);
         else
             (*res)++;
     }

     cout << "'god' : " << *sst.search("god") << endl;

     endTime = clock();
     cout << "SST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
*/
//}


    /*srand(time(NULL));
    BST<int, int> bst = BST<int, int>();

    int m = 10;
    for (int i = 0; i < m; i++) {
        int key = rand() % n;
        // 为了后续测试方便,这里value值取和key值一样
        int value = key;
        cout << key << " ";
        bst.insert(key, value);
    }
    cout << endl;

    // test size
    cout << "size: " << bst.size() << endl << endl;

    // test preOrder
    cout << "preOrder: " << endl;
    bst.preOrder();
    cout << endl << endl;

    // test inOrder
    cout << "inOrder: " << endl;
    bst.inOrder();
    cout << endl << endl;

    // test postOrder
    cout << "postOrder: " << endl;
    bst.postOrder();
    cout << endl << endl;

    // test levelOrder
    cout << "levelOrder: " << endl;
    bst.levelOrder();
    cout << endl << endl;
*/
//
//    srand(time(NULL));
//    BST<int, int> bst = BST<int, int>();
//
//    int n = 10000;
//    for (int i = 0; i < n; i++) {
//        int key = rand() % n;
//        // 为了后续测试方便,这里value值取和key值一样
//        int value = key;
//        //cout<<key<<" ";
//        bst.insert(key, value);
//    }

    // test removeMin
//    while( !bst.isEmpty() ){
//        cout<<"min: "<<bst.minimum()<<endl;
//        bst.removeMin();
//        cout<<"After removeMin, size = "<<bst.size()<<endl;
//    }

    // test removeMax
//    while (!bst.isEmpty()) {
//        cout << "max: " << bst.maximum() << endl;
//        bst.removeMax();
//        cout << "After removeMax, size = " << bst.size() << endl;
//    }



    srand(time(NULL));
    BST<int,int> bst = BST<int,int>();

    int n = 10000;
    for( int i = 0 ; i < n ; i ++ ){
        int key = rand()%n;
        // 为了后续测试方便,这里value值取和key值一样
        int value = key;
        //cout<<key<<" ";
        bst.insert(key,value);
    }

    // test remove
    // remove elements in random order
    int order[n];
    for( int i = 0 ; i < n ; i ++ )
        order[i] = i;
    shuffle( order , n );

    for( int i = 0 ; i < n ; i ++ )
        if( bst.contain( order[i] )){
            bst.remove( order[i] );
            cout<<"After remove "<<order[i]<<" size = "<<bst.size()<<endl;
        }

    return 0;
}