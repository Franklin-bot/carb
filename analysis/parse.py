import numpy as np

from typing import Dict
from collections import defaultdict


class TickerInfo:

    def __init__(self, timestamp: np.uint64, price: np.uint64, best_bid: np.uint64, best_ask: np.uint64, best_bid_q: np.uint64, best_ask_q: np.uint64):
        self.timestamp = timestamp
        self.price = price
        self.best_bid = best_bid
        self.best_ask = best_ask
        self.best_bid_q = best_bid_q
        self.best_ask_q = best_ask_q

class Orderbook_info:

    def __init__(self, timestamp: np.uint64, bids: Dict[np.uint64, np.uint64], asks: Dict[np.uint64, np.uint64]):
        self.timestamp = timestamp
        self.bids = bids
        self.asks = asks

def parseTickers(path) -> defaultdict[str, list]:

    res = defaultdict(list)

    with open(path, 'r') as file:
        for line in file:
            fields = line.strip().split()
            product = fields[0]
            info = map(np.uint64, fields[1:])
            res[product].append(TickerInfo(*info))

    return res

def parseBooks(path) -> defaultdict[str, list]:

    res = defaultdict(defaultdict)
    
    with open(path, 'r') as file:
        for line in file:
            fields = line.strip().split()




    return res
