#include "graph.h"


Graph::Graph(const int &size)
{
    this->labelList = QVector<int>(size);
    this->maxSize = size;
    this->adjMatrix = QVector<QVector<int>>(size, QVector<int>(size));
    for (int i = 0; i < this->maxSize; ++i) {
        for (int j = 0; j < this->maxSize; ++j) this->adjMatrix[i][j] = 0;
    };
}

Graph::Graph() : Graph(10) {}

inline bool Graph::isEmpty() { return this->vertexList.size() == 0; };

inline bool Graph::isFull() { return this->vertexList.size() == this->maxSize;};

inline int Graph::GetVertPos(const int& v) {
    for (int i = 0; i < this->vertexList.size(); ++i) {
        if (this->vertexList[i] == v) return i;
    }
    return -1;
};

inline int Graph::GetAmountVerts() { return this->vertexList.size(); };


bool Graph::insertVertex(int& vert) {
    if (this->isFull())
    {
        qDebug() << "Невозможно добавить вершину.";
        return false;
    };
    if (this->GetVertPos(vert) == -1) {
        this->vertexList.push_back(vert);
        return true;
    }
    qDebug() << vertexList;
    return false;
};

int Graph::GetAmountEdges() {
    int amount = 0;
    if (!this->isEmpty()){
        for (int i = 0; i < this->vertexList.size(); ++i) {
            for (int j = 0; j < this->vertexList.size(); ++j) if (this->adjMatrix[i][j] != 0) amount++;
        }
    }
    return amount;
};

inline int Graph::GetWeight(const int& v1, const int& v2) {
    if (this->isEmpty()) return 0;

    int v1_p = this->GetVertPos(v1);
    int v2_p = this->GetVertPos(v2);

    if (v1_p == -1 || v2_p == -1) {
        qDebug() << "Одного из узлов в графе не существует." << endl;
        return 0;
    };

    return this->adjMatrix[v1_p][v2_p];
};

QVector<int> Graph::GetNbrs(const int& vertex) {
    QVector<int> nbrsList;
    int pos = this->GetVertPos(vertex);
    if (pos != -1) {
        for (int i = 0; i < this->vertexList.size(); ++i) {
            if (this->adjMatrix[pos][i] != 0) nbrsList.push_back(this->vertexList[i]);
        }
    }
    return nbrsList;
}

QVector<int> Graph::getNbrsInd(const int &vert_index)
{
    QVector<int> nbrs_ind;
        for (int j = 0; j < this->adjMatrix.size(); ++j) {
            if (this->adjMatrix[vert_index][j]) nbrs_ind.push_back(j);
        }
        return nbrs_ind;
}

QVector<int> Graph::getVertexList()
{
    return this->vertexList;
}

void Graph::BFS(int &startVertex, QVector<bool>visitedVerts, QString &res)
{
        if (visitedVerts[this->GetVertPos(startVertex)] == false) {
            this->VertsQueue.push_back(startVertex);
            res += "Вершина " + QString::number(startVertex) + " обработана\n" ;
            visitedVerts[this->GetVertPos(startVertex)] = true;
        }
        QVector<int> neighbors = this->GetNbrs(startVertex);
        this->VertsQueue.pop_front();
        for (int i = 0; i < neighbors.size(); ++i) {
            if (!visitedVerts[this->GetVertPos(neighbors[i])]) {
                this->VertsQueue.push_back(neighbors[i]);
                visitedVerts[this->GetVertPos(neighbors[i])] = true;
                res += "Вершина " + QString::number(neighbors[i]) + " обработана\n";
            }
        }
        if (this->VertsQueue.empty()) return;

        BFS(VertsQueue.front(), visitedVerts, res);
}

void Graph::DFS(int &startVertex, QVector<bool>& visitedVerts, QString &res)
{
        res+= "Вершина " + QString::number(startVertex) + " посещена\n";
        visitedVerts[this->GetVertPos(startVertex)] = true;
        QVector<int> neighbors = this->GetNbrs(startVertex);
        for (int i = 0; i < neighbors.size(); ++i){
            if (!visitedVerts[this->GetVertPos(neighbors[i])])
                this->DFS(neighbors[i], visitedVerts, res); };

}

void Graph::Dijkstra(int &startVertex, QString &res)
{
    for (int i = 0; i < vertexList.size(); i++)
            for (int j = 0; j < vertexList.size(); j++)
                if (adjMatrix[i][j] < 0)
                    return;

        if (GetVertPos(startVertex) == -1)
            return;

        QVector<bool> visitedVerts(vertexList.size());
        for (auto it = visitedVerts.begin(); it!=visitedVerts.end(); ++it) *it = false;

        this->FillLabels(startVertex);
        int curSrc = startVertex;
        QVector<int> neighbors;

        while (!this->AllVisited(visitedVerts)){
            neighbors = this->GetNbrs(curSrc);
            int startLabel = labelList[GetVertPos(curSrc)];

            int* minNeighbor_ptr = nullptr;
            int minW = 1000000;

            for (int i = 0; i < neighbors.size(); ++i){
                int weight = this->GetWeight(curSrc, neighbors[i]);
                int nIndex = this->GetVertPos(neighbors[i]);
                int nextLabel = labelList[nIndex];

                if (startLabel + weight < nextLabel) labelList[nIndex] = startLabel + weight;

                if (!visitedVerts[nIndex] && minW > labelList[nIndex]) {
                    minW = labelList[nIndex];
                    minNeighbor_ptr = &neighbors[i];
                };
            };

            visitedVerts[GetVertPos(curSrc)] = true;
            if (minNeighbor_ptr != nullptr) curSrc = *minNeighbor_ptr;

        };


        for (int i = 0; i < vertexList.size(); ++i) {
            if (i != GetVertPos(startVertex)){
                res+= "Кратчайшее расстояние от вершины " + QString::number(startVertex)
                    + " до вершины "  + QString::number(vertexList[i]) + " равно "
                    + QString::number(labelList[GetVertPos(vertexList[i])]) + "\n";
            }
        };
}

bool Graph::AllVisited(QVector<bool> &visitedVerts)
{
    bool flag = true;
        for (int i = 0; i < this->vertexList.size(); i++)
            if (visitedVerts[i] != true)
                flag = false;
        return flag;
}

void Graph::FillLabels(int &startVertex)
{
    for (int i = 0, size = vertexList.size(); i < size; ++i)
            labelList[i] = 1000000;
        int pos = GetVertPos(startVertex);
        labelList[pos] = 0;
};


void Graph::InsertEdge(const int& vertex1, const int& vertex2, const int& weight) {
    if (GetVertPos(vertex1) != (-1) && this->GetVertPos(vertex2) != (-1)) {
        int vertPos1 = GetVertPos(vertex1);
        int vertPos2 = GetVertPos(vertex2);

        if (this->adjMatrix[vertPos1][vertPos2] != 0) {
            qDebug() << "Ребро между вершинами уже есть" << endl;
            return;
        }
        else this->adjMatrix[vertPos1][vertPos2] = weight;

    }
    else {
        qDebug() << "Обеих вершин (или одной из них) нет в графе " << endl;
        return;
    }
};

void Graph::showAdj()
{
    for (int i = 0; i < this->maxSize; ++i) qDebug() << this->adjMatrix[i] << ' ';

    qDebug() << endl;

}

QVector<QVector<int> > Graph::getAdj()
{
    return this->adjMatrix;
};

void Graph::eraseEdge(const int& vert, const int& vert2)
{
    int p1 = this->GetVertPos(vert);
    int p2 = this->GetVertPos(vert2);
    if (p1 != -1 && p2 != -1)
    {
        this->adjMatrix[p1][p2] = 0;
    }
};

void Graph::eraseVertex(const int& vert)
{
    int pos = this->GetVertPos(vert);
    if ( pos != -1)
    {
        for (int i = 0; i < this->vertexList.size(); ++i)
        {
            this->adjMatrix[i].erase(this->adjMatrix[i].begin() + pos);
        }
        this->adjMatrix.erase(this->adjMatrix.begin() + pos);
        this->vertexList.erase(this->vertexList.begin() + pos);
    }
};
