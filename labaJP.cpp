#include "stack.h"
#include "userInput.h"
#include <vector>
#include <iterator>

//Языки программирования ИКМ задача - 13
int main()
{
    int n{};
    cout << "Enter number of stacks of containers: ";
    correctIntInput(n, 0, 500); // ввод числа типов контейнеров и стопок с ними

    vector<stack> stacksOfContainers{}; // вектор стеков: стек - стопка контейнеров, число стеков - n

    bool allContainersInTheRightStack = true; // true - все контейнеры изначально правильно расположены

    bool inFirstStack2OnlyAfter1 = true; // если всего 2 типа товара, проверяем чтобы в первой стопке не было первого товара после второго

    bool inSecondStack1OnlyAfter2 = true; // если всего 2 типа товара, проверяем чтобы во второй стопке не было второго товара после первого

    int* topElementOfStacks = new int[n];// верхний контейнер в каждой стопке
    for (int i = 0; i < n; i++) {
        topElementOfStacks[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        stacksOfContainers.push_back(stack());

        int k{};//  количество контейнеров в стопке
        cout << endl << "Enter number of containers in the current stack: ";
        correctIntInput(k, 0, 500);

        int currentTopContainerOFStack = -1;// для n = 2, верхний контейнер в стопке на данный момент

        for (int j = 0; j < k; j++) {// считываем k контейнеров
            int typeOfContainer{};
            cout << endl << "Enter type of product in container: ";
            correctIntInput(typeOfContainer, 1, n);


            if (n == 2) {
                if (i == 0) {
                    if (currentTopContainerOFStack == 2 && typeOfContainer == 1)
                        inFirstStack2OnlyAfter1 = false;
                }
                if (i == 1) {
                    if (currentTopContainerOFStack == 1 && typeOfContainer == 2)
                        inSecondStack1OnlyAfter2 = false;
                }
            }


            if (typeOfContainer != i + 1) {
                allContainersInTheRightStack = false;
            }
            stacksOfContainers[i].push_forward(typeOfContainer);// добавляем контейнер в стопку
            currentTopContainerOFStack = typeOfContainer;

            if (j == k - 1) {
                topElementOfStacks[i] = typeOfContainer;
            }
        }
    }

    vector<pair<int, int>> actions{};// вектор дейсвтий по перемещению контейнеров: первое число - стопка из которой взят контейнер, второе - тип контейнера, который был взят 


    if (allContainersInTheRightStack) {
        cout << "All containers in the right stack.";
        return 0;
    }

    if (n == 2) {
        if (inFirstStack2OnlyAfter1 && inSecondStack1OnlyAfter2 && !(topElementOfStacks[0] == 2 && topElementOfStacks[1] == 1)) {
            pnode container = stacksOfContainers[0].top();
            if (container->getData() == 2) { // если верхний контейнер первой стопки с товаром 2
                while (container->getData() == 2) {
                    actions.push_back(make_pair(1, 2));// перемещаем его во вторую
                    stacksOfContainers[1].push_forward(2);
                    delete container;
                    container = stacksOfContainers[0].top();
                }
                if (container->getData() == 1) { // если после перемещению взяли контейнер с товаром 1, положить его обратно в первую стопку
                    delete container;
                    stacksOfContainers[0].push_forward(1);
                }
            }
            else {
                if (container->getData() == 1) {
                    delete container;
                    stacksOfContainers[0].push_forward(1);
                }
                container = stacksOfContainers[1].top();
                if (container->getData() == 1) {// аналогично для второй стопки
                    while (container->getData() == 1) {
                        actions.push_back(make_pair(2, 1));
                        stacksOfContainers[0].push_forward(1);
                        delete container;
                        container = stacksOfContainers[1].top();
                    }
                    if (container->getData() == 2) {
                        delete container;
                        stacksOfContainers[1].push_forward(2);
                    }
                }
            }

            int i = 1;
            for (auto it{ actions.begin() }; it != actions.end(); ++it) {
                pair<int, int> p = *it;
                cout << "action " << i << ": ";
                cout << p.first << " " << p.second << endl;
                i++;
            }

            cout << endl << "Final view of the stacks: " << endl;
            for (int i = 0; i < n; i++) {
                cout << "Stack " << i + 1 << ": ";
                cout << stacksOfContainers[i];
                cout << endl;
            }
            return 0;
        }
        else {
            cout << 0;
            return 0;
        }
    }



    // переносим все контейнеры в последнюю стопку
    for (int i = 0; i < n - 1; i++) {
        pnode currentNode = stacksOfContainers[i].top();
        while (currentNode->getData() != -1) {
            stacksOfContainers[n - 1].push_forward(currentNode->getData());
            topElementOfStacks[n - 1] = currentNode->getData();
            actions.push_back(make_pair(i + 1, n));
            delete currentNode;
            currentNode = stacksOfContainers[i].top();
        }
    }
    for (int i = 0; i < n - 1; i++) {// после перемещения во всех стопках кроме последней верхнего элемента нет
        topElementOfStacks[i] = -1;
    }


    int numberOfLastContainersInTheWrongStack = 0;
    int indexOfStackWithLastContainers = n - 2; // индекс стопки, в которой хранятся контейнеры с номером n, может принимать значения: n - 2, n - 3
    pnode currentContainer = stacksOfContainers[n - 1].top();
    while (currentContainer->getData() != -1) {
        if (currentContainer->getData() != n) { // если контейнер не должен быть в последней стопке
            if (topElementOfStacks[currentContainer->getData() - 1] != n) { // если верхний контейнер в перемещаемую стопку не должен быть в последней
                stacksOfContainers[currentContainer->getData() - 1].push_forward(currentContainer->getData());
                topElementOfStacks[currentContainer->getData() - 1] = currentContainer->getData();
                actions.push_back(make_pair(n, currentContainer->getData()));
                delete currentContainer;
            }
            else {
                // иначе перемещаем все контейнеры, который должны находиться в последней стопки, в предпоследнюю или в предпердпоследнюю
                if (indexOfStackWithLastContainers == n - 2) { // если контейнеры были в n - 2(предпоследней) -> переместить левее
                    for (int i = 0; i < numberOfLastContainersInTheWrongStack; i++) {
                        pnode moveNode = stacksOfContainers[currentContainer->getData() - 1].top();
                        indexOfStackWithLastContainers = n - 3;
                        stacksOfContainers[indexOfStackWithLastContainers].push_forward(moveNode->getData());
                        topElementOfStacks[indexOfStackWithLastContainers] = n;
                        actions.push_back(make_pair(n - 1, n - 2));
                        delete moveNode;
                    }
                }
                else { // иначе переместить правее
                    for (int i = 0; i < numberOfLastContainersInTheWrongStack; i++) {
                        pnode moveNode = stacksOfContainers[currentContainer->getData() - 1].top();
                        indexOfStackWithLastContainers = n - 2;
                        stacksOfContainers[indexOfStackWithLastContainers].push_forward(moveNode->getData());
                        topElementOfStacks[indexOfStackWithLastContainers] = n;
                        actions.push_back(make_pair(n - 2, n - 1));
                        delete moveNode;
                    }
                }
                stacksOfContainers[currentContainer->getData() - 1].push_forward(currentContainer->getData());
                topElementOfStacks[currentContainer->getData() - 1] = currentContainer->getData();
                actions.push_back(make_pair(n, currentContainer->getData()));
                delete currentContainer;
            }
        }
        else {// контейнер должен быть последней в стопке
            stacksOfContainers[indexOfStackWithLastContainers].push_forward(currentContainer->getData());
            topElementOfStacks[indexOfStackWithLastContainers] = n;
            actions.push_back(make_pair(n, indexOfStackWithLastContainers + 1));
            delete currentContainer;
            numberOfLastContainersInTheWrongStack++;
        }
        currentContainer = stacksOfContainers[n - 1].top();// берем следующий контейнер из последней стопки
    }

    for (int i = 0; i < numberOfLastContainersInTheWrongStack; i++) { // перемещаем контейнеры, которые должны быть в последней стопке
        pnode moveNode = stacksOfContainers[indexOfStackWithLastContainers].top();
        stacksOfContainers[n - 1].push_forward(moveNode->getData());
        actions.push_back(make_pair(indexOfStackWithLastContainers + 1, n));
        delete moveNode;
    }

    int i = 1;
    for (auto it{ actions.begin() }; it != actions.end(); ++it) {
        pair<int, int> p = *it;
        cout << "action " << i << ": ";
        cout << p.first << " " << p.second << endl;
        i++;
    }

    cout << endl << "Final view of the stacks: " << endl;
    for (int i = 0; i < n; i++) {
        cout << "Stack " << i << ": ";
        cout << stacksOfContainers[i];
        cout << endl;
    }

    delete[] topElementOfStacks;
    return 0;
}