class r_b_bst:
    type_list = {}
    def __init__(self, data):
        self.data = data
        self.data_type = type(data)
        self.right = None
        self.left = None
        self.parent = None
        self.clr = "r"

        r_b_bst.insert_data_type(self.data_type)

    def insert(self, data):
        if (self.data_type == type(data)):
            while self is not None:
                if data == self.data:
                    print("Element already exists!")
                    pass
                elif data < self.data:
                    if self.left is None:
                        self.left = r_b_bst(data)
                        self.left.parent = self
                        self = self.left
                        break
                    else:
                        self = self.left
                elif data > self.data:
                    if self.right is None:
                        self.right = r_b_bst(data)
                        self.right_parent = self
                        self = self.right
                        break
                    else:
                        self = self.right
            
            
            def node_recoloring(tree):
                tree = tree.parent.parent
                if tree.left is not None:
                    tree.left.clr = "b"
                if tree.right is not None:
                    tree.right.clr = "b"
                tree.clr = "r"
                return tree
            
            def node_left_left_rotation(tree):
                temp_tree = tree.parent.parent
                tree.parent.clr = "b"
                temp_tree.clr = "r"
                temp_tree.left = tree.parent.right
                if tree.parent.right is not None:
                    tree.parent.right.parent = tree.parent.right
                tree.parent.right = temp_tree
                temp_tree.parent = tree.parent.right
                return temp_tree
                
            def node_left_right_rotation(tree):
                temp_tree = tree.parent.left
                temp_data = tree.data
                tree.parent.left = tree
                tree.parent = tree.parent.left
                tree.data = tree.parent.data
                tree.parent.data = temp_data
                tree.parent.right = tree.right
                tree.right.parent = tree.parent.right
                tree.right = tree.left
                tree.left = temp_tree
                temp_tree = node_left_left_rotation(tree)
                return temp_tree
                
            def node_right_left_rotation(tree):
                temp_tree = tree.parent.right
                temp_data = tree.data
                tree.parent.right = tree
                tree.data = tree.parent.data
                tree.parent.data = temp_data
                tree.parent.left = tree.left
                if tree.left is not None:
                    tree.left.parent = tree.left
                tree.left = tree.right
                tree.right = temp_tree
                temp_tree = node_right_right_rotation(tree)
                return temp_tree
                
            def node_right_right_rotation(tree):
                temp_tree = tree.parent.parent
                tree.parent.clr = "b"
                temp_tree.clr = "r"
                temp_tree.right = tree.parent.left
                tree.parent.parent = temp_tree.parent
                if temp_tree.parent is not None:
                    temp_temp = temp_tree.parent.left if (temp_tree.parent.left == temp_tree) else temp_tree.parent.right
                    temp_temp = tree.parent
                tree.parent.left = temp_tree
                temp_tree = tree.parent
                return temp_tree

            while tree.parent is not None:
                grandparent = tree.parent.parent
                if grandparent is not None:
                    return None
                    uncle = grandparent.left if (grandparent.right = tree.parent) else grandparent.right
                    if tree.parent.clr == "r":
                        if ("b" if (uncle is None) else uncle.clr) == "r":
                            self = 
                        
        else:
            print("Wrong data type:", type(data),"Correct data type:", self.data_type)

    def print_tree(self):
        string = "[Data Type : {}]"
        
        def sub_tree_list(tree):
            sub_list = []
            
            def list_unravel(list_data):
                unravel_list = []
                for i,temp_list in enumerate(list_data):
                    if (list == type(temp_list)):
                        unravel_list.extend(list_unravel(temp_list))
                    else:
                        unravel_list.append(temp_list)
                return unravel_list
        
            if tree.left is not None:
                temp_list =  sub_tree_list(tree.left)
                sub_list.extend(list_unravel(temp_list))
        
            sub_list.append(tree.data)
            
            if tree.right is not None:
                temp_list = sub_tree_list(tree.right)
                sub_list.extend(list_unravel(temp_list))
            return sub_list
        
        build_list = sub_tree_list(self)
        print(string.format(self.data_type, build_list, sep = "\n"))
        return build_list
    
    @staticmethod
    def insert_data_type(data_type):
        count = r_b_bst.type_list.get(data_type)
        if count is None:
            r_b_bst.type_list.update({data_type:1})
        else:
            count += 1
            r_b_bst.type_list.update({data_type:count})

    def __del__(self):
        count = r_b_bst.type_list.get(self.data_type)
        count -= 1
        r_b_bst.type_list.update({self.data_type:count})
        if count == 0:
            r_b_bst.type_list.pop(self.data_type)
