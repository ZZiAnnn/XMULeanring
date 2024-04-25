import torch
import torch.nn as nn
import numpy as np
from sklearn.model_selection import train_test_split


class NeuralNet(nn.Module):
    def __init__(self, input_size, hidden_size, num_classes):
        super(NeuralNet, self).__init__()
        self.fc1 = nn.Linear(input_size, hidden_size)
        self.fc2 = nn.Linear(hidden_size, num_classes)

    def forward(self, x):
        out = torch.sigmoid(self.fc1(x))
        out = self.fc2(out)
        return out


def train(model, X_train, y_train, learning_rate, num_epochs):
    criterion = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)
    for epoch in range(num_epochs):
        inputs = torch.FloatTensor(X_train)
        labels = torch.LongTensor(y_train)
        optimizer.zero_grad()
        outputs = model(inputs)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()
        # if epoch % 100 == 0:
        #     print("Epoch: %d, Loss: %.4f" % (epoch, loss.item()))


def model_test(X_test, y_test, model):
    inputs = torch.FloatTensor(X_test)
    labels = torch.LongTensor(y_test)
    outputs = model(inputs)
    predictions = torch.argmax(outputs, dim=1)
    accuracy = (predictions == labels).float().mean().item()
    return accuracy


def read_data(file_name):
    with open(file_name, 'r') as file:
        data = []
        label = {'Iris-setosa': 0, 'Iris-versicolor': 1, 'Iris-virginica': 2}
        for line in file:
            line = line.strip()
            if line:
                features = line.split(',')
                features[:-1] = [float(feature) for feature in features[:-1]]
                features[-1] = label.get(features[-1], features[-1])
                data.append(features)
        return np.array(data)

if __name__ == '__main__':
    iris = read_data('Iris.txt')

    X = iris[:, :-1]
    y = iris[:, -1]

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=75, stratify=y, random_state=42)

    np.savetxt('Iris-train.txt', np.column_stack((X_train, y_train)), delimiter=',')
    np.savetxt('Iris-test.txt', np.column_stack((X_test, y_test)), delimiter=',')

    train_data = np.loadtxt('Iris-train.txt', delimiter=',')
    X_train = train_data[:, :-1]
    y_train = train_data[:, -1]

    input_size = 4
    hidden_size = 10
    output_size = 3
    learning_rate = 0.01
    epochs = 1500

    test_data = np.loadtxt('Iris-test.txt', delimiter=',')
    X_test = test_data[:, :-1]
    y_test = test_data[:, -1]

    accuracies = []
    for _ in range(10):
        model = NeuralNet(input_size, hidden_size, output_size)
        train(model, X_train, y_train, learning_rate, epochs)
        accuracy = model_test(X_test, y_test, model)
        accuracies.append(accuracy)

    print("准确率列表:",np.round(accuracies,2))
    print("平均准确率:", np.mean(accuracies))
    print("准确率标准差:", np.std(accuracies))