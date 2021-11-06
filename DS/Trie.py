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
            if not letter in current_node.children:
                return False
            current_node = current_node.children[letter]
        return current_node.isword
        
    def get_words(self):
        words = []
        self.root.summarize(words)
        return words
   
    def __contains__(self, word):
        return self.find(word)
    
    def __repr__(self):
        words = self.get_words()
        return ", ".join(map(str, words))
        
        
def demo():  
    trie = Trie(["Hagrid", "Harry", "Hermoine"])
    print("Harry" in trie)
    print(trie.find("Harald"))
    print(trie)

if __name__ == "__main__":
    demo()
