import hashlib
import time
def mine_block(difficulty,block_data):
    start_time=time.time()
    nonce=0
    target='0'*difficulty

    while True:
        data_str=str(block_data)+str(nonce)
        block_hash=hashlib.sha256(data_str.encode('utf-8')).hexdigest()

        if block_hash[:difficulty]==target:
            end_time=time.time()
            mining_time=end_time-start_time
            return block_hash,mining_time

        nonce+=1

block_hash,mining_time = mine_block(2,"Hello,World!")
print("Block Hash:",block_hash)
print("Mining Time:",mining_time)