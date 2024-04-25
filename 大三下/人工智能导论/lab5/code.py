from graphviz import Digraph, Source
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, classification_report
import numpy as np


class DecisionTree:
    def __init__(self, min_samples_split=2, max_depth=None):
        self.min_samples_split = min_samples_split
        self.max_depth = max_depth

    def entropy(self, y):  # 计算熵
        classes = np.unique(y)
        entropy = 0
        for cls in classes:
            p_cls = np.mean(y == cls)
            entropy += -p_cls * np.log2(p_cls)
        return entropy

    def information_gain(self, X, y, feature_idx, threshold):  # 计算信息增益
        parent_entropy = self.entropy(y)
        left_idxs = X[:, feature_idx] < threshold
        right_idxs = ~left_idxs
        if np.sum(left_idxs) == 0 or np.sum(right_idxs) == 0:
            return 0
        left_entropy = self.entropy(y[left_idxs])
        right_entropy = self.entropy(y[right_idxs])
        child_entropy = np.mean(left_idxs) * left_entropy + np.mean(right_idxs) * right_entropy
        return parent_entropy - child_entropy

    def find_best_split(self, X, y):  # 找出最优划分
        best_gain = 0
        best_feature_idx = None
        best_threshold = None
        for feature_idx in range(X.shape[1]):
            thresholds = np.unique(X[:, feature_idx])
            for threshold in thresholds:
                gain = self.information_gain(X, y, feature_idx, threshold)
                if gain > best_gain:
                    best_gain = gain
                    best_feature_idx = feature_idx
                    best_threshold = threshold
        return best_feature_idx, best_threshold

    def fit(self, X, y, depth=0):
        if (self.max_depth is not None and depth >= self.max_depth) or \
                len(y) < self.min_samples_split or len(np.unique(y)) == 1:
            return {'class': np.argmax(np.bincount(y.astype(int)))}
        else:
            best_feature_idx, best_threshold = self.find_best_split(X, y)
            left_idxs = X[:, best_feature_idx] < best_threshold
            right_idxs = ~left_idxs
            tree = {
                'feature_idx': best_feature_idx,
                'threshold': best_threshold,
                'left': self.fit(X[left_idxs], y[left_idxs], depth + 1),
                'right': self.fit(X[right_idxs], y[right_idxs], depth + 1)
            }
            return tree

    def predict_sample(self, sample, tree):
        if 'class' in tree:
            return tree['class']
        else:
            if sample[tree['feature_idx']] < tree['threshold']:
                return self.predict_sample(sample, tree['left'])
            else:
                return self.predict_sample(sample, tree['right'])

    def predict(self, X, tree):
        return [self.predict_sample(sample, tree) for sample in X]


def visualize_tree(tree, parent=None, graph=None, node_id=None, leaf_colors=None):
    if leaf_colors is None:
        leaf_colors = {}

    colors = ['lightblue', 'lightgreen', 'lightcoral', 'lightskyblue', 'lightpink', 'lightyellow']

    if graph is None:
        graph = Digraph()
        graph.attr('node', shape='box')

    if node_id is None:
        node_id = '1'

    if 'class' in tree:  # Leaf node
        class_label = tree['class']
        if class_label not in leaf_colors:
            leaf_colors[class_label] = colors[len(leaf_colors) % len(colors)]
        graph.node(node_id, label=f'Class: {class_label}', color=leaf_colors[class_label], style='filled')
    else:  # Decision node
        feature_idx = tree['feature_idx']
        threshold = tree['threshold']
        graph.node(node_id, label=f'Feature {feature_idx} <= {threshold:.2f}')

        left_child_id = f'{node_id}L'
        right_child_id = f'{node_id}R'

        graph.edge(node_id, left_child_id, label='Yes')
        graph.edge(node_id, right_child_id, label='No')

        visualize_tree(tree['left'], parent=node_id, graph=graph, node_id=left_child_id, leaf_colors=leaf_colors)
        visualize_tree(tree['right'], parent=node_id, graph=graph, node_id=right_child_id, leaf_colors=leaf_colors)

    if parent is None:
        return graph


def read_data():
    data = np.genfromtxt('traindata.txt')
    X_train = data[:, :-1]
    y_train = data[:, -1]

    data = np.genfromtxt('testdata.txt')
    X_test = data[:, :-1]
    y_test = data[:, -1]
    return X_train, X_test, y_train, y_test


if __name__ == '__main__':
    X_train, X_test, y_train, y_test = read_data()
    dt = DecisionTree()
    tree = dt.fit(X_train, y_train)

    graph = visualize_tree(tree)
    graph.view()
    Source(graph.source)

    y_pred = dt.predict(X_test, tree)
    accuracy = accuracy_score(y_test, y_pred)
    print("Accuracy:", accuracy)
    print("Classification Report:")
    print(classification_report(y_test, y_pred))
