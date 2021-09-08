//----------------------------------------------------------------
// 判断完全二叉树
// 层序遍历，如果遇到空节点就再出队，这时如果有遇到非空节点则表示空节点之后还有节点，则就不是完全二叉树
bool isCompleteTree(BiTree T){
  InitQueue(Q); //初始化队列
  EnQueue(Q, T); //根节点入队
  BiTree p;
  while(!IsEmpty(Q)){
    DeQueue(Q,p);
    if(p){ // 正常层序遍历
      EnQueue(Q,p->left);
      EnQueue(Q,p->right);
    }else {
      while(!IsEmpty(Q)){ // 遇到空节点，开始出队
        DeQueue(Q,p);
        if(p) // 还有非空节点
        	return false;
      }
    }
  }
  return true;
}

//----------------------------------------------------------------
// 判断两棵树相同
// 如果两棵树都是空树那么必然相同
// 两棵树都非空+根节点值相同+左子树相同+右子树相同
bool isSameTree(BiTree p, BiTree q){
    if (!p && !q) return true;
    return p && q && p->val == q->val && 
			isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

//----------------------------------------------------------------
// 二叉树的最大高度
// 树非空，那么最大深度就是左子树最大深度和右子树最大深度的较大者加上根节点的1
int height(BiTree T){
  if(!T) 
    return 0;
  else
    return max(height(T->left), height(T->right)) + 1;
}

//----------------------------------------------------------------
// 判断平衡二叉树
// 根节点的左右子树高度差<=1 + 左子树是平衡二叉树 + 右子树是平衡二叉树
bool isBalanced(BiTree T){
  if(!T) // 空树是平衡树
    return true;
  else
    return abs(height(T->left) - height(T->right)) <= 1 && isBalanced(T->left) && isBalanced(T->right);
}

//----------------------------------------------------------------
// 判断单值二叉树
// 如果左子树非空且根节点的值异与左子节点值(即根节点与左子节点不同)，返回false,右子树同理
bool isUnivalTree(BiTree T){
  if(!T)
    return true; // 空树是单值二叉树
  if((T->left && T->left->val != T->val) || (T->right && T->right->val != T->val))
    return false;
  return isUnivalTree(T->left) && isUnivalTree(T->right);
}

//----------------------------------------------------------------
// 判断一个树是不是另一棵树的子树
// 有一颗树为空就不成立
// 先判断两棵树是否是相同
// 然后判断一棵树的左子树是否是另一颗树的子树/一棵树的右子树是否是另一颗树的子树
bool isSubTree(BiTree T, BiTree p){
  if(!T || !p)
    return false;
  if(isSameTree(T, p))
    return true;
  return isSubTree(T->left, p) || isSubTree(T->right, p);
}

//----------------------------------------------------------------
// 翻转二叉树
// 翻转左子树后替换右子树，翻转右子树后替换左子树
BiTree invertTree(BiTree T){
  if(!T) // 空树的镜像翻转树仍然是本身
    return NULL;
  BiTNode *left = invertTree(T->left);
  BiTNode *right = invertTree(T->right);
  T->left = right;
  T->right = left;
  return T;
}

//----------------------------------------------------------------
// 合并二叉树
// 都是空树返回null, 其中有一个空返回另一个树的根节点
// 都不空的话先把两棵树根节点值相加，然后递归合并左右子树(以第一棵树为合并后的树)
BiTree mergeTrees(BiTree p, BiTree q){
  if(!p)
    return q;
  if(!q)
    return p;
  p->val += q->val;
  p->left = mergeTrees(p->left, q->left); // 递归合并
  p->right = mergeTrees(p->right, q->right); // 递归合并
  return p;
}

//----------------------------------------------------------------
// 判断一棵树是否为对称二叉树

// 辅助函数,判断两棵树是否是镜像对称的
bool isMirror(BiTree p, BiTree q){
  if(!p && !q) // 都是空树则满足
    return true;
  if(!p || !q) // 其中有一棵空树则不满足
    return false;
  // 比较两棵树是否镜像对称，先比较值是否相等
  // 再看一棵树的左子树和另一棵树的右子树，以及一棵树的右子树和另一棵树的左子树是否镜像对称
  return (p->val == q->val) && isMirror(p->left, q->right) && isMirror(p->right, q->left);
}

// 判断一棵树是否对称
bool isSymmetric(BiTree T){
   return isMirror(root, root);
}

//----------------------------------------------------------------
// 判断一棵树是否是另一棵树的子结构，注意子结构与子树的区别

// 辅助函数,判断如果A,B根节点相同，B是不是A的子结构
bool hasSubStructure(BiTree A, BiTree B){
  if(!B) // 递归结束条件1:A的一个节点在B中没有对应的位置，可以认为是子结构
    return true;
  // 递归结束条件2:如果B的一个节点在A中没有对应的位置，或者A，B对应位置节点值不同，肯定不是子结构
  if(!A || A->val != B->val)
    return false;
  // 继续在对应位置递归判断
  return hasSubStructure(A->left, B->left) && hasSubStructure(A->right, B->right);
}

// 子结构不能只利用根节点进行对称性递归，需要构造辅助函数，判断当两棵树根节点值相同时一棵树是否为另一棵树子结构
bool isSubStructure(BiTree T, BiTree p){
  if(!T || !p) // 有一个为空就false
    return false;
  // 根节点相同的话直接进入比较，根节点不相同看p是不是T的左/右子树的子结构
  return hasSubStructure(T, p) || isSubStructure(T->left, p) || isSubStructure(T->right, p);
}

//----------------------------------------------------------------
// 二叉树的(最大/最小)高度（非递归）
// 层序遍历
int depth(BiTree T){
  if(!T)
    return 0;
  int maxDeep = 0, width;
  InitQueue(Q); // 初始化队列
  EnQueue(Q, T); // 根节点入队
  BiTree p;
  while(!IsEmpty(Q)){
    width = GetSize(Q); // 获取队列长度
    maxDeep += 1;
    for(int i=0;i<width;i++){
      DeQueue(Q, p); //出队
      
      // 如果是要求最小高度，那么就在这里加这一个判断，如果左右结点都是空，那么一定是叶子节点，直接返回maxDeep就行了
      // if(!p->left && !p->right)
      //  return maxDeep;
      
      if(p->left)
        EnQueue(Q, p->left);
      if(p->right)
        EnQueue(Q, p->right);
      
    }
  }
  return maxDeep;
}

//----------------------------------------------------------------
// 先序与中序还原二叉树
BiTree PreInCreate(ElemType A[], ElemType B[], int l1, int h1, int l2, int h2)
{
    // l1,h1为先序的第一和最后一个结点的下标，l2，h2为中序的第一个和最后一个结点的下标
    // 初始调用时，l1 = l2 = 1, h1 = h2 = n

    BiTree root = (BiTree)malloc(sizeof(BiTNode));
    root->val = A[l1];
    int i = 0;
    for (i = l2; B[i] != root->val; i++)
        ; // 找到节点root在中序中的下标i
    // i的左边就是左子树，右边是右子树
    int llen = i - l2; // 左子树的长度
    int rlen = h2 - i; // 右子树的长度
    if (llen)          // 递归建立左子树
        root->left = PreInCreate(A, B, l1 + 1, l1 + llen, l2, l2 + llen - 1);
    else
        root->left = NULL;

    if (rlen) // 递归建立右子树
        root->right = PreInCreate(A, B, h1 - rlen + 1, h1, h2 - rlen + 1, h2);
    else
        root->right = NULL;

    return root;
}

//----------------------------------------------------------------
// 双分支结点个数
int DoNode(BiTree T){
    if (!T) // 空树
        return 0;
    if (T->left && T->right) // 是双分支就加1
        return DoNode(T->left) + DoNode(T->right) + 1;
    return DoNode(T->left) + DoNode(T->right);
}

//----------------------------------------------------------------
// 先序的第k个结点的值
int i = 1;
ElemType PreNode(BiTree T, int k) {
    if(!T) // 空树，返回一个特殊的值
        return "#";
    if(i==k)
        return T->val;
    i++; // 下一个结点
    ElemType val = PreNode(T->left, i); //在左子树中递归查找
    if(val != "#") // 在左子树中找到了
        return val;
    val = PreNode(T->right, i); //在右子树中递归查找
    return val;
}

//----------------------------------------------------------------
// 求孩子兄弟法存储的森林的叶子结点个数
typedef struct node {
    ElemType val;
    struct node *fch, *nsib; // 第一个孩子与右兄弟
} *Tree;

int LeaveNode(Tree T) {
    if(!T) // 空树返回0
        return 0;
    if(!T->fch) // 如果结点的孩子为空，那么肯定是叶子结点
        return LeaveNode(T->nsib) + 1; // 递归查找兄弟子树
    return LeaveNode(T->fch) + LeaveNode(T->nsib); // 递归查找孩子与兄弟子树
}

//----------------------------------------------------------------
// 求孩子兄弟链表法存储的树的高度
int Height(Tree T) {
    if(!T) // 空树返回0
        return 0;
    return max(Height(T->fch) + 1, Height(T->nsib));
}

//----------------------------------------------------------------
//删除二叉树中以元素值x为根的子树并释放相应的空间

// 辅助函数，删除以T为根的子树
void DeleteXTree(BiTree T){
    if(T){
        DeleteXTree(T->left);
        DeleteXTree(T->right);
        free(T);
    }
}

// 层序遍历
void Search(BiTree T, ElemType x){
    if(!T) // 空树
        return;

    if(T->val == x){ // 根节点就等于x，直接删掉整个树
        DeleteXTree(T);
        return;
    }

    InitQueue(Q); // 初始化队列
    EnQueue(Q, T); // 根节点入队
    BiTree p;
    while(!IsEmpty(Q)){
        DeQueue(Q, p);
        if(p->left){
            if(p->left->val == x){ // 如果左孩子节点值等于x，就删除左子树
                DeleteXTree(p->left);
                p->left = NULL;
            }else {
                EnQueue(Q, p->left); // 左孩子入队
            }
        }

        if(p->right){
            if(p->right->val == x){ // 如果右孩子节点值等于x，就删除左子树
                DeleteXTree(p->right);
                p->right = NULL;
            }else {
                EnQueue(Q, p->right); // 有孩子入队
            }
        }

    }
}

//----------------------------------------------------------------
// 打印二叉树中值为x的结点的所有祖先（假设值x的结点不多于1个）
bool IsAncestor(BiTree T, ElemType x){
  if(!T) // 空树
    return false;

  // 在左孩子或是右孩子找到这个值了就返回true
  if((T->left && T->left->val == x) || (T->right && T->right->val == x)) {
    printf("%d", T->val);
    return true;
  }

  // 递归查找左子树和右子树
  if(IsAncestor(T->left, x) || IsAncestor(T->right)) {
    printf("%d", T->val);
    return true;
  }

  return false;
}

//----------------------------------------------------------------
// 找出p和q的最近公共祖先结点

BiTree lowestCommonAncestor(BiTree T, BiTree p, BiTree q){
  if(!T) // 空结点
    return NULL;

  if(p->val == T->val || q->val == T->val) // 这个节点是我们要找的结点
    return T;

  BiTree l = lowestCommonAncestor(T->left, p, q); //在左子树中递归查找
  BiTree r = lowestCommonAncestor(T->right, p, q); //在左子树中递归查找

  // 在T的左右子树中都找到了p或者q，T一定是祖先结点，而由于我们是自底向下找的，它就是最近公共结点
  if(l && r)
    return T;

  // 返回l或者r，也有可能是null
  if(!l)
    return r;
  return l;
}

//----------------------------------------------------------------
// 求二叉树的宽度，二叉树的宽度定义为具有最多结点数的层中包含的结点数
// 就是层序遍历
int width(BiTree T) {
  if(!T)
    return 0;
  InitQueue(Q); // 初始化队列
  int w = 1; // 记录最大宽度
  EnQueue(Q, T); // 根节点入队
  BiTree p;
  while (!IsEmpty(Q)) {
    int width = GetSize(Q); // 获取队列长度
    w = max(w, width); // 下面那个循环走下来Q的大小就是这一层的宽度
    for(int i=0;i<width;i++){
      DeQueue(Q, p); //出队
      if(p->left)
        EnQueue(Q, p->left);
      if(p->right)
        EnQueue(Q, p->right);
    }
  }
}

//----------------------------------------------------------------
// 已知一个满二叉树（所有结点值均不同）的先序序列，求其后序序列
// 先：1 2 4 5 3 6 7
// 后：4 5 2 6 7 3 1
// l1,h1为先序的第一和最后一个结点的下标，l2，h2为后序的第一个和最后一个结点的下标
void PreToPost(ElemType pre[], ElemType post[], int l1, int h1, int l2, int h2){
  int half;
  if(h1>=l1) {
    post[h2] = pre[l1]; // 后序最后一个结点等于先序第一个结点
    half = (h1 - l1) / 2;
    PreToPost(pre, post, l1 + 1, l1 + half, l2, l2 + half - 1);
    PreToPost(pre, post, l1 + half + 1, h1, l2 + half, h2 - 1);
  }
}

//----------------------------------------------------------------
// 将二叉树的叶结点按从左到右的顺序合成一个单链表，表头指针为head，链接时使用叶结点的右指针
// 前、中、后序遍历对于叶结点的访问都是从左到右，这里用中序
LinkList head, pre = NULL; // 全局变量，head就是头结点
void LinkNode(BiTree T) {
  if(!T)
    return;

  LinkNode(T->left);

  if(T->left == NULL && T->right == NULL) { // 叶结点
    if(pre == NULL){ // 第一个叶结点
      head = T;
      pre = T;
    }else { // 后序的叶结点
      pre->right = T;
      pre = T;
    }
  }
  LinkNode(T->right);

  pre->right = NULL; // 表尾设置为空
}

//----------------------------------------------------------------
// 判断两棵二叉树是否相似
bool isSimilar(BiTree p, BiTree q) {
  if(p == NULL && q == NULL) return true; // 两树都为空则相似

  if(p == NULL || q == NULL) return false; // 只有一个为空则不相似

  // 递归遍历左右子树
  bool left = isSimilar(p->left, q->left);
  bool right = isSimilar(p->right, q->right);

  return left && right;
}

//----------------------------------------------------------------
// 在中序线索二叉树中查找指定结点在后序的前驱结点
// 对于结点p，其前驱依次有可能是：
// 1. p的右孩子 
// 2.没有右孩子，那就可能是左孩子 
// 3.没有孩子，那就可能是其父结点的左孩子
// 4.否则，可能是其爷爷结点的左孩子，以此类推

BiTree InPostPre(BiTree T, BiTree p) {
  if(P==NULL) return NULL; // p空，不存在前驱结点
  if(p->rtag == 0) return p->right; // 有右孩子
  if(p->ltag == 0) return p->left; // 有左孩子

  // 访问p的中序前驱也就是父结点
  while(p&&p->ltag == 1)
    p = p->left;
  if(p) // 找到了
    return p->left;
  return NULL;
}

//----------------------------------------------------------------
// 计算二叉树的带权路径长度
// 基于先序遍历的思想，先定义一个全局的wpl值记录长度，把每个结点的深度作为参数传下去
// 如果遍历的是非叶结点，就继续递归遍历，深度就是当前的深度加一
// 如果遍历的是叶结点，就计算当前结点的路径长度，就是结点的权值*深度，再加到wpl上
static int wpl = 0; // 定义一个全局变量
int WPL(BiTree T) {
  return preOrder(T, 0);
}

int preOrder(BiTree T, int depth) {
  if(T->left == NULL && T->right == NULL) // 如果是叶结点，就累加值
    wpl += depth * T->weight;
  if(T->left != NULL) // 递归遍历左子树
    preOrder(T->left, depth + 1);
  if(T->right != NULL) // 递归遍历右子树
    preOrder(T->right, depth + 1);
  return wpl;
}

