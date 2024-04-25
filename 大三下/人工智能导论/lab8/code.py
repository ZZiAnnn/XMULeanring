import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from collections import Counter
import matplotlib.pyplot as plt


def euclidean_distance(x1, x2):
    return np.sqrt(np.sum((x1 - x2) ** 2))


def knn(X_train, y_train, X_test, k=3):
    y_pred = []

    for test_point in X_test:
        distances = []

        # 计算测试点与每个训练点之间的距离
        for x_train in X_train:
            distances.append(euclidean_distance(test_point, x_train))

        # 获取k个最近邻居的索引
        k_neighbors_indices = np.argsort(distances)[:k]

        # 获取k个最近邻居的类别
        k_neighbors_labels = [y_train[i] for i in k_neighbors_indices]

        # 确定最常见的类别作为预测类别
        most_common = Counter(k_neighbors_labels).most_common(1)
        y_pred.append(most_common[0][0])

    return y_pred


if __name__ == '__main__':
    iris = pd.read_csv('iris.csv')

    data = iris.iloc[:, :4]
    target = iris.iloc[:, -1].values

    X_train, X_test, y_train, y_test = train_test_split(data.values, target, test_size=0.2, random_state=41)

    predictions = knn(X_train, y_train, X_test, k=3)

    accuracy = np.mean(predictions == y_test)
    print(f"Accuracy: {accuracy:.2f}")

    # 设置K值的范围
    k_range = range(1, 31)
    # 用于存储不同K值对应的交叉验证得分
    k_scores = []

    # 遍历K值范围
    for k in k_range:
        # 创建KNN分类器，设置当前K值
        predictions = knn(X_train, y_train, X_test, k)
        # 进行交叉验证，并计算得分，使用10折交叉验证，评分为准确率
        # 将当前K值对应的平均得分添加到k_scores列表中
        k_scores.append(np.mean(predictions == y_test))

        # 绘制K值与交叉验证得分的关系图
    plt.plot(k_range, k_scores)
    plt.xlabel('Value of K for KNN')  # 设置X轴标签
    plt.ylabel('Cross-Validated Accuracy')  # 设置Y轴标签
    plt.show()  # 显示图形
