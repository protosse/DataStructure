//  Created by liuliu on 2021/9/3.
//

import Foundation
import App

// ----------------------------------------------------------------
// 宽度
_ = {
    let root = TreeNode.buildTree(preorder: [3, 9, 7, 2, 4, 6, 5, 8, 1, 10], inorder: [2, 7, 4, 9, 6, 3, 1, 8, 5, 10])
    print(root.width())
}

// ----------------------------------------------------------------
// 最大宽度
_ = {
    if let root = TreeNode.buildTree(order: [0, 0, 0, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil, nil, 0, 0, nil]) {
        print(root.maxWidth())
    }
}

// ----------------------------------------------------------------
// 满二叉树先序转后序
_ = {
    var pre = [1, 2, 4, 5, 3, 6, 7]
    var post = pre.map { _ in 0 }
    preToPost(&pre, &post, 0, pre.count - 1, 0, post.count - 1)
}

// ----------------------------------------------------------------
// 输出中缀表达式
// 基于中序遍历的思想
_ = {
    let root = TreeNode.buildTree(order: ["*", "+", "*", "a", "b", "c", "-",
                                          nil, nil, nil, nil, nil, nil, nil, "d"])!
    var str = ""
    func preOrder(_ t: TreeNode<String>, _ depth: Int = 1) {
        if t.left == nil && t.right == nil { // 根节点直接输出
            str += t.val
            return
        }
        if depth > 1 { // 深度大于1才打印括号
            str += "("
        }
        if let left = t.left {
            preOrder(left, depth + 1) // 递归遍历左子树
        }
        str += t.val
        if let right = t.right {
            preOrder(right, depth + 1) // 递归遍历右子树
        }
        if depth > 1 { // 深度大于1才打印括号
            str += ")"
        }
    }
    preOrder(root) // 初始深度就是默认的1
    print(str)
}()
