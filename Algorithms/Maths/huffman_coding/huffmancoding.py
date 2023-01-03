import heapq as hq
from collections import Counter
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt



class HuffmanTree:
    class Node:
        def __init__(self, frequency_map, l=None, r=None):
            symbol, freq = frequency_map
            self.symbol = symbol
            self.freq = freq
            self.l = l
            self.r = r
            self.code = None
            
        def __lt__(self, other):
            return self.freq < other.freq
    
        def __gt__(self, other):
            return self.freq > other.freq
        
        def is_leaf(self):
            return not (self.l or self.r)
        

    @classmethod
    def __init__(self, symbols, weights):
        queue = list(map(HuffmanTree.Node, zip(symbols,weights)))
        hq.heapify(queue)

        while len(queue) > 1:
            min_1 = hq.heappop(queue)
            min_2 = hq.heappop(queue)
            hq.heappush(queue, HuffmanTree.Node(
                r=min_1, l=min_2,
                frequency_map=(f"{min_1.symbol}||{min_2.symbol}", min_1.freq + min_2.freq)
            ))
            
        self.head = queue[0]
        self.entropy = -np.dot(weights, np.log2(weights))


    def encode(self):
        def _postorder(node, path=[]):
            l, r = node.l, node.r
            path.append(node)
            if r:
                r.code = node.code + "0"
                _postorder(r, path)
            if l:
                l.code = node.code + "1"
                _postorder(l, path)
            return path
        
        self.head.code = ""
        path = _postorder(self.head)
        codebook = {node.symbol: node.code for node in path if node.is_leaf()}
        return codebook


    def vis(self):
        if not self.head.code:
            self.encode()
        
        G = nx.Graph()
        edge_labels = {}
        node_labels = {}
        
        def _inorder(node, node_id=0, parent_id=None):
            G.add_node(node_id)
            node_labels[node_id] = f"{node.symbol!r} | {node.code or '-'}"
            
            if parent_id is not None:
                G.add_edge(parent_id, node_id)
                edge_labels[(parent_id, node_id)] = f"{node.freq:.2f}"
            
            l, r = node.l, node.r
            child_id = node_id
            if l:
                child_id += 1
                child_id = _inorder(l, child_id, node_id)
            if r:
                child_id += 1
                child_id = _inorder(r, child_id, node_id)
                
            return child_id
                
        _inorder(self.head)
        
        plt.figure(figsize=(15,10))
        ax = plt.gca()
        ax.set_title(f"Huffman Tree (Entropy = {self.entropy:.2f})")
        pos = nx.nx_agraph.graphviz_layout(G, prog="dot")
        nx.draw(
            G, pos, edge_color='black', width=1, linewidths=1,
            node_size=2_000, node_color='pink', alpha=0.9,
            labels=node_labels, font_size=7, ax=ax
        )
        nx.draw_networkx_edge_labels(
            G, pos,
            edge_labels=edge_labels,
            font_color='red',
            font_size=6
        )
        plt.axis('off')
        plt.show()



def huffman_code(document, verbose=False):
    sorted_frequencies = dict(sorted(Counter(document).items(), key=lambda x: (-x[1], x[0])))
    weights = [frequency / len(document) for frequency in sorted_frequencies.values()]
    tree = HuffmanTree(sorted_frequencies.keys(), weights)
    codebook = tree.encode()
    if verbose:
        tree.vis()

    return codebook


def test_encode1():
    sym =list("abcde")
    p = [0.10, 0.15, 0.30, 0.16, 0.29]
    expected = dict(zip(sym, ["010", "011", "11", "00", "10"]))
    T = HuffmanTree(sym, p)
    print("entropy", T.entropy)
    result =  T.encode()
    T.vis()
    print("exp",expected)
    print("res", result)
    assert expected == result


def test_encode2():
    sym = list("abcd")
    p = [.4, .3, .2, .1]
    expected = dict(zip(sym, ["0", "10", "110", "111"]))
    result =  HuffmanTree(sym,p).encode()
    print("exp",expected)
    print("res", result)
    assert expected == result


def test_on_document():
    print(huffman_code("this is an example of a huffman tree", True))


if __name__ == "__main__":
    test_encode1()
    test_encode2()
    test_on_document
    