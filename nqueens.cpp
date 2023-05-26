#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int N = 10; // 8개짜리
unsigned long numOfSol = 0;
vector<string> solutions;

bool isPromising(string currently) {
    // 노드를 처음 배치하는 경우 -> 길이가 1이다 -> TRUE
    if (currently.length() == 1)
        return true;

    unsigned short currentLevel = currently.length() - 1;
    short currentNode = stoi(currently.substr(currentLevel, 1));

    bool result = true;
    short i = 0; // 반복문용
    // 이전 노드들 중, 같은 열/같은대각에 놓였다면 NON-PROMISING
    while (i < currentLevel && result) {
        if (stoi(currently.substr(i, 1)) == currentNode || currentLevel - i == abs(currentNode - stoi(currently.substr(i, 1))))
            result = false;

        /*
        같은대각선
        (a,c) 와 (a+k,c+k) 또는 (a-k,c+k) 에서 공통점
        k는 양의 실수
        뺐ㅇ르때 k,k 랑 -k, k
        가로는 양옆으로 가능, 세로는 밑으로만
        ==> 밑으로만 움직이는건 i, curernt
        양옆 둘다는 타겟
        */
        i++;
    }
    return result;
}

void nQueens(short prevNode, string currently) {
    // 이전까지 전부 Promising하게 배치했다면 이것은 해를 의미
    if (currently.length() == N) {
        numOfSol++;
        solutions.push_back(currently);
    }
    else {
        for (unsigned short i = 0; i < N; i++) {
           // 직전과 같은 열, 같은대각에는 아예 놓지 않는다.
           if (prevNode == i || prevNode-1 == i || prevNode+1 == i )
                continue;
            string next = currently + to_string(i);
            if (isPromising(next))
                nQueens(i, next);
        }
    }
}

int main(void) {
    nQueens(-99, "");
    std::cout << numOfSol << "개" << std::endl;
    for (int i = 0; i < solutions.size(); i++) {
        std::cout << solutions.at(i) << std::endl;
    }
}
