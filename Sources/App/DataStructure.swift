//
//  Created by liuliu on 2021/9/3.
//

import Foundation

public class TreeNode<T: Equatable>: Hashable {
    public var val: T
    public var left: TreeNode?
    public var right: TreeNode?
    
    public init(_ val: T) {
        self.val = val
        left = nil
        right = nil
    }
    
    public func hash(into hasher: inout Hasher) {
        hasher.combine(ObjectIdentifier(self).hashValue)
    }
    
    public static func == (lhs: TreeNode<T>, rhs: TreeNode<T>) -> Bool {
        return ObjectIdentifier(lhs) == ObjectIdentifier(rhs)
    }
}

extension TreeNode {
    /// 顺序创建二叉树
    public class func buildTree(order: [T?]) -> TreeNode<T>? {
        guard let rootVal = order.first, let rootVal = rootVal else {
            return nil
        }
        
        let root = TreeNode<T>(rootVal)
        var Q = [root]
        var front = 0
        var index = 1
        
        while index < order.count {
            let node = Q[front]
            front += 1
            
            if let val = order[index] {
                let item = TreeNode(val)
                node.left = item
                Q.append(item)
            }
            
            index += 1
            
            if index >= order.count {
                break
            }
            
            if let val = order[index] {
                let item = TreeNode(val)
                node.right = item
                Q.append(item)
            }
            index += 1
        }
        
        return root
    }
    
    /// 先序与中序构造二叉树
    public class func buildTree(preorder: [T], inorder: [T]) -> TreeNode<T> {
        func create(_ preorder: [T], _ l1: Int, _ h1: Int, _ inorder: [T], _ l2: Int, _ h2: Int) -> TreeNode {
            let root = TreeNode(preorder[l1])
            var i = l2
            var llen = 0
            var rlen = 0
            while inorder[i] != root.val {
                i += 1
            }
            llen = i - l2
            rlen = h2 - i

            if llen != 0 {
                root.left = create(preorder, l1 + 1, l1 + llen, inorder, l2, l2 + llen - 1)
            } else {
                root.left = nil
            }

            if rlen != 0 {
                root.right = create(preorder, h1 - rlen + 1, h1, inorder, h2 - rlen + 1, h2)
            } else {
                root.right = nil
            }
            return root
        }
        let l1 = 0
        let l2 = 0
        let h1 = preorder.count - 1
        let h2 = inorder.count - 1
        return create(preorder, l1, h1, inorder, l2, h2)
    }
    
    /// 打印二叉树中值为x的结点的所有祖先（假设值x的结点不多于1个）
    public func isAncestor(_ t: TreeNode?, x: T) -> Bool {
        guard let t = t else {
            return false
        }
        
        if let val = t.left?.val, val == x {
            print("isAncestor \(t.val)")
            return true
        }
        
        if let val = t.right?.val, val == x {
            print("isAncestor \(t.val)")
            return true
        }
        
        if isAncestor(t.left, x: x) || isAncestor(t.right, x: x) {
            print("isAncestor \(t.val)")
            return true
        }
        return false
    }
    
    /// 找出p和q的最近公共祖先结点
    public func lowestCommonAncestor(_ t: TreeNode?, _ p: TreeNode, _ q: TreeNode) -> TreeNode? {
        guard let t = t else {
            return nil
        }
        
        if p == t || q == t {
            return t
        }
        
        let l = lowestCommonAncestor(t.left, p, q)
        let r = lowestCommonAncestor(t.right, p, q)
        
        if l != nil && r != nil {
            return t
        }
        
        if l == nil {
            return r
        }
        return l
    }
    
    /// 求二叉树的宽度，二叉树的宽度定义为具有最多结点数的层中包含的结点数
    public func width() -> Int {
        let t = self
        
        var Q = [TreeNode]()
        var w = 1
        var temp: TreeNode?
        Q.append(t)
        while !Q.isEmpty {
            w = max(w, Q.count)
            for _ in 0..<Q.count {
                temp = Q.removeFirst()
                if let l = temp?.left {
                    Q.append(l)
                }
                
                if let r = temp?.right {
                    Q.append(r)
                }
            }
        }
        
        return w
    }
    
    /// 二叉树的最大宽度(包括空结点)
    public func maxWidth() -> Int {
        let t = self
        
        var Q = [(TreeNode, Int)]() // 队列中还要存储结点的位置
        var w = 1
        var left = 0 // 记录每层第一个结点的位置
        Q.append((t, 1))
        while !Q.isEmpty {
            for i in 0..<Q.count {
                let (temp, pos) = Q.removeFirst()
                
                if i == 0 {
                    left = pos
                }
                
                if let l = temp.left {
                    // 会有大数越界的问题。因此使用&*
                    Q.append((l, pos &* 2)) // pos * 2 就是左孩子的位置
                }
                
                if let r = temp.right {
                    Q.append((r, pos &* 2 &+ 1)) // pos * 2 + 1 就是右孩子的位置
                }
                
                w = max(pos &- left &+ 1, w) // pos - left + 1 就是当前宽度
            }
        }
        
        return w
    }
}

/// 已知一个满二叉树（所有结点值均不同）的先序序列，求其后序序列
/// 先：1 2 4 5 3 6 7
/// 后：4 5 2 6 7 3 1
/// l1,h1为先序的第一和最后一个结点的下标，l2，h2为后序的第一个和最后一个结点的下标
public func preToPost(_ pre: inout [Int], _ post: inout [Int], _ l1: Int, _ h1: Int, _ l2: Int, _ h2: Int) {
    var half = 0
    if h1 >= l1 {
        post[h2] = pre[l1]
        half = (h1 - l1) / 2
        preToPost(&pre, &post, l1 + 1, l1 + half, l2, l2 + half - 1)
        preToPost(&pre, &post, l1 + half + 1, h1, l2 + half, h2 - 1)
    }
}

