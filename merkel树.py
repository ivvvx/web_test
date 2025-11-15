import hashlib

# 给定叶节点列表，生成Merkle树根
def merkle_root(leaf_nodes):
    if len(leaf_nodes) == 0: # 如果没有叶节点，则返回空字符串
        return ''
    elif len(leaf_nodes) == 1: # 如果只有一个叶节点，则该节点为Merkle树根
        return leaf_nodes[0]
    else:
        new_leaf_nodes = [] # 定义新的叶节点列表
        for i in range(0, len(leaf_nodes), 2): # 每次处理两个叶节点
            left_child = leaf_nodes[i]
            right_child = leaf_nodes[i+1] if i+1 < len(leaf_nodes) else left_child # 如果没有右侧节点，则将其设置为左侧节点
            hash_value = hashlib.sha256((left_child + right_child).encode('utf-8')).hexdigest() # 计算两个子节点的哈希值
            new_leaf_nodes.append(hash_value) # 将哈希值加入新的叶节点列表中
        return merkle_root(new_leaf_nodes) # 递归调用，继续构建Merkle树

#验证数据完整性
def verify_integrity(leaf_nodes, merkle_tree_root):
    tree_root = merkle_root(leaf_nodes)
    return merkle_tree_root == tree_root

# 定义一个叶节点列表
leaf_nodes = ['transaction1', 'transaction2', 'transaction3', 'transaction4']

# 生成Merkle树根并打印结果
merkle_tree_root = merkle_root(leaf_nodes)
print("The Merkle tree root is:", merkle_tree_root)

#模拟验证数据完整性
print("Is Data Valid?", verify_integrity(leaf_nodes, merkle_tree_root))

#修改数据，验证数据完整性
leaf_nodes[2] = 'block5'
print("Is Data Valid?", verify_integrity(leaf_nodes, merkle_tree_root))
