#include <iostream>

using namespace std;

template <typename T>
class myVector {
private:
    T* data;
    long long capacity;
    long long current_size;

public:
    myVector() : data(nullptr), capacity(0), current_size(0) {}

    myVector(long long initial_size) : capacity(initial_size), current_size(0) {
        data = new T[capacity];
    }

    ~myVector() {
        delete[] data;
    }

    myVector(const myVector& other) : data(nullptr), capacity(other.capacity), current_size(other.current_size) {
        if (capacity > 0) {
            data = new T[capacity];
            for (long long i = 0; i < current_size; ++i) {
                data[i] = other.data[i];
            }
        }
    }

    myVector(myVector&& other) noexcept : data(other.data), capacity(other.capacity), current_size(other.current_size) {
        other.data = nullptr;
        other.capacity = 0;
        other.current_size = 0;
    }

    myVector& operator=(const myVector& other) { // copy assignment operator
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            current_size = other.current_size;
            if (capacity > 0) {
                data = new T[capacity];
                for (long long i = 0; i < current_size; ++i) {
                    data[i] = other.data[i];
                }
            }
            else {
                data = nullptr;
            }
        }
        return *this;
    }

    myVector& operator=(myVector&& other) noexcept { // move assignment operator
        if (this != &other) {
            delete[] data;
            data = other.data;
            capacity = other.capacity;
            current_size = other.current_size;

            other.data = nullptr;
            other.capacity = 0;
            other.current_size = 0;
        }
        return *this;
    }

    long long size() const {
        return current_size;
    }

    T* begin() {
        return data;
    }

    T* end() {
        return data + current_size;
    }

    void push_back(const T& value) {
        if (current_size >= capacity) {
            reserve((capacity == 0) ? 1 : capacity * 2);
        }
        data[current_size++] = value;
    }

    void reserve(long long new_capacity) { // memory reservation for new_capacity
        if (new_capacity > capacity) {
            T* new_data = new T[new_capacity];
            for (long long i = 0; i < current_size; ++i) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
    }

    T& operator[](long long index) {
        if (index >= current_size) {
            throw std::out_of_range("index out of range");
        }
        return data[index]; 
    }

    const T& operator[](long long index) const {
        if (index >= current_size) {
            throw std::out_of_range("index out of range");
        }
        return data[index];
    }
    myVector(long long initial_size, const T& value) : capacity(initial_size), current_size(initial_size) {
        data = new T[capacity];
        for (long long i = 0; i < initial_size; ++i) {
            data[i] = value;
        }
    }
};

struct vertex { // single node in the graph
    int index = -1;
    myVector<int> neighbors;
    bool visited = false;
    char side = 'X';
    int color = 0;
};

template<typename T>
class myStack { // own stack implementation
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };
    Node* top_node;

public:
    myStack() : top_node(nullptr) {}

    ~myStack() {
        while (!empty()) {
            pop();
        }
    }

    void push(const T& value) {
        Node* new_node = new Node(value);
        new_node->next = top_node;
        top_node = new_node;
    }

    void pop() {
        if (top_node) {
            Node* temp = top_node;
            top_node = top_node->next;
            delete temp;
        }
    }

    T& top() {
        if (!top_node) {
            throw std::out_of_range("stack is empty");
        }
        return top_node->data;
    }

    bool empty() const {
        return top_node == nullptr;
    }
};

template <typename T>
class mySet { // own set implementation
private:
    myVector<T> elements;

public:
    void insert(const T& value) {
        for (long long i = 0; i < elements.size(); ++i) {
            if (elements[i] == value) {
                return;  
            }
        }
        elements.push_back(value);
    }

    bool contains(const T& value) const {
        for (long long i = 0; i < elements.size(); ++i) {
            if (elements[i] == value) {
                return true;
            }
        }
        return false;
    }
};



void merge(myVector<int>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    myVector<int> L;
    myVector<int> R;

    for (int i = 0; i < n1; ++i)
        L.push_back(vec[left + i]);
    for (int j = 0; j < n2; ++j)
        R.push_back(vec[mid + 1 + j]);

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) { // sorting in descending order
            vec[k] = L[i];
            ++i;
        }
        else {
            vec[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        vec[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        vec[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(myVector<int>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

void degreeSequence(const myVector<vertex>& graph) {
    myVector<int> degSeq;
    degSeq.reserve(graph.size());

    for (int i = 0; i < graph.size(); i++) {
        const auto& v = graph[i];
        degSeq.push_back(v.neighbors.size());
    }

    mergeSort(degSeq, 0, degSeq.size() - 1);

    for (int number : degSeq) {
        printf("%d ", number);
    }
    printf("\n");
}

bool search(myVector<vertex>& graph, int i, myVector<int>& component) {
    if (!graph[i].visited) {
        graph[i].visited = true;
        component.push_back(i);
        for (int j : graph[i].neighbors) {
            int neighborIndex = j - 1;
            if (!graph[neighborIndex].visited) {
                search(graph, neighborIndex, component);
            }
        }
        return true;
    }
    return false;
}


int connectedComponents(myVector<vertex>& graph, myVector<myVector<int>>& components) {
    int connectedCount = 0;

    for (int i = 0; i < graph.size(); i++) {
        if (!graph[i].visited) {
            myVector<int> component;
            search(graph, i, component);
            components.push_back(component);
            connectedCount++;
        }
    }
    return connectedCount;
}

void graphBipartite(myVector<vertex>& graph, int connectedCount) {
    int current;
    int n;
    for (int i = 0; i < graph.size(); i++) {
        if (graph[i].side == 'X') {
            myStack<int> stack;
            stack.push(i);
            while (!stack.empty()) {
                current = stack.top();
                stack.pop();
                if (graph[current].side == 'X') {
                    graph[current].side = 'A';
                }
                for (int j = 0; j < graph[current].neighbors.size(); j++) {
                    n = graph[current].neighbors[j] - 1;
                    if (n >= 0 && n < graph.size()) {
                        if ((graph[n].side == 'X') && (graph[current].side == 'A')) {
                            graph[n].side = 'B';
                            stack.push(n);
                        }
                        else if ((graph[n].side == 'X') && (graph[current].side == 'B')) {
                            graph[n].side = 'A';
                            stack.push(n);
                        }
                        else if (graph[n].side == graph[current].side) {
                            printf("F\n");
                            return;
                        }
                    }
                }
            }
        }
    }
    printf("T\n");
}

void greedyColors(const myVector<vertex>& graph) {
    int n = graph.size();
    myVector<int> colors(n, -1);

    for (int i = 0; i < n; ++i) {
        myVector<bool> available(n, true);
        for (int j = 0; j < graph[i].neighbors.size(); j++) {
            int x = graph[i].neighbors[j];
            int s = x - 1;
            if (colors[s] != -1) {
                available[colors[s]] = false;
            }
        }

        int color;
        for (color = 0; color < n; ++color) {
            if (available[color]) {
                break;
            }
        }
        colors[i] = color;
    }

    for (int c : colors) {
        printf("%d ", c + 1);
    }
    printf("\n");
}

void lfColors(myVector<vertex>& graph) {
    int n = graph.size();
    myVector<int> sorted(n);
    for (int i = 0; i < n; i++) {
        sorted.push_back(i);
    }

    for (int i = 1; i < n; i++) { // insertion sort
        int key = sorted[i];
        int left = 0;
        int right = i - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (graph[sorted[mid]].neighbors.size() < graph[key].neighbors.size()) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }

        for (int j = i - 1; j >= left; j--) {
            sorted[j + 1] = sorted[j];
        }
        sorted[left] = key;    
    }

    for (int i = 0; i < n; i++) {
        graph[i].color = 0;
    }

    int k;
    for (int i = 0; i < n; i++) {
        int number = sorted[i];
        bool* colors = new bool[n + 2];
        for (int j = 0; j < n + 2; j++) {
            colors[j] = true;
        }

        for (int j = 0; j < graph[number].neighbors.size(); j++) {
            int neighborIndex = graph[number].neighbors[j] - 1;
            if (neighborIndex >= 0 && neighborIndex < n) {
                colors[graph[neighborIndex].color] = false;
            }
        }
        k = 1;
        while (k <= n && !colors[k]) {
            k++;
        }
        graph[number].color = k;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", graph[i].color);
    }
    printf("\n");
}

long long graphComplement(myVector<vertex> graph) {
    long long edges = 0;
    for (long long i = 0; i < graph.size(); i++) {
        vertex v = graph[i];
        for (long long j = 0; j < v.neighbors.size(); j++) {
            edges++;
        }
    }
    edges /= 2;

    long long allEdges = static_cast<long long>(graph.size()) * (graph.size() - 1) / 2;
    return (allEdges - edges);
}

void c4(myVector<vertex>& graph, const myVector<myVector<int>>& parts) {
    int n = graph.size();
    int x, y;
    long long count = 0;
    int l = 0, m;
    myVector<int> close;
    for (int i = 0; i < n; i++)
        close.push_back(-1);

    for (int i = 0; i < parts.size(); i++) {
        const auto& part = parts[i];
        for (int j = 0; j < part.size(); j++) {
            x = part[j];
            if (graph[x].neighbors.size() > 1) {
                for (int k = j + 1; k < part.size(); k++) {
                    y = part[k];
                    if (graph[y].neighbors.size() > 1) {
                        m = 0;
                        for (int s = 0; s < graph[x].neighbors.size(); s++) {
                            int neighborIndex = graph[x].neighbors[s] - 1;
                            if (neighborIndex >= 0 && neighborIndex < n) {
                                close[neighborIndex] = l;
                            }
                        }

                        for (int s = 0; s < graph[y].neighbors.size(); s++) {
                            if (close[graph[y].neighbors[s] - 1] == l) {
                                m++;
                            }
                        }
                        count += ((m - 1) * m) / 2;
                        l++;
                    }
                }
            }
        }
    }
    printf("%lld\n", count / 2);
}


int main() {
    int numberOfGraphs;
    cin >> numberOfGraphs;

    for (int graphIndex = 0; graphIndex < numberOfGraphs; graphIndex++) {
        long long numberOfVertices;
        cin >> numberOfVertices;
        myVector<vertex> graph(numberOfVertices);
        for (long long i = 0; i < numberOfVertices; i++) {
            vertex v;
            v.index = i;
            int numberOfNeighbors;
            cin >> numberOfNeighbors;
            v.neighbors.reserve(numberOfNeighbors);
            for (int j = 0; j < numberOfNeighbors; j++) {
                int neighbor;
                cin >> neighbor;
                v.neighbors.push_back(neighbor);
            }
            graph.push_back(v);
        }

        myVector<myVector<int>> parts;
        degreeSequence(graph);
        int connectedCount = connectedComponents(graph, parts);
        printf("%d\n", connectedCount);
        graphBipartite(graph, connectedCount);
        greedyColors(graph);
        lfColors(graph);
        c4(graph, parts);
        printf("%lld\n", graphComplement(graph));
    }

    return 0;
}
