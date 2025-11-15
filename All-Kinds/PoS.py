import hashlib
import random

def hash(block_str):
    """哈希函数，用于计算区块哈希值"""
    return hashlib.sha256(block_str.encode()).hexdigest()

def generate_block(prev_block,transactions,difficulty):
    """
    生成区块函数
    prev_block: str前一个区块的哈希值
    transactions: list区块中包含的所有交易信息列表
    difficulty: int当前网络的难度系数
    """
    nonce=0 #初始化随机数
    while True:
        rand=random.randint(0,100000)
        block_str=(str(prev_block)+str(transactions)+str(nonce)+str(rand))
        block_hash=hash(block_str)
        if block_hash.startswith('0'*difficulty):
            return{
                'prev_block':prev_block,
                'transactions':transactions,
                'nonce':nonce,
                'rand':rand,
                'hash':block_hash
            }
        else:
            nonce+=1
if __name__=='__main__':
    prev_block='00000000000000000000000000000000'
    transaactions=['A给B转账100元','B给C转账50元']
    difficulty=4
    block=generate_block(prev_block,transaactions,difficulty)
    print(block)
