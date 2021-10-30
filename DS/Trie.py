from collections import defaultdict

class Node:
    def __init__(self, isword=False):
        self.children = defaultdict(Node)
        self.isword = isword

    def summarize(self, msg):
        if self.isword:
            msg.append(".")
        if self.children:
           msg.append(self.children.keys())

           for child in self.children.values():
               child.summarize(msg)

class Trie:
    def __init__(self, words):
        self.root = Node()
        for word in words:
            self.insert(word)
        
    def insert(self, word):
        current_node = self.root
        for letter in word:
            current_node = current_node.children[letter]
        current_node.isword = True

    def find(self, word):
        current_node = self.root
        for letter in word:
            if letter in current_node.children:
                current_node = current_node.children[letter]
            else:
                return False
        return current_node.isword
        
    def get_words(self):
        words = []
        self.root.summarize(words)
        return words
            
def demo():  
    trie = Trie(["Hagrid", "Harry", "Hermoine"])
    print(trie.find("Harry"))
    print(trie.find("Harald"))
    print(trie.get_words())

if __name__ == "__main__":
    demo()
