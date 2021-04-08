using namespace std;

#include <iostream>
#include "State.h"

State::State(int n, int k) {
    // Constructor that creates a state with n blocs and k stacks
    nbBlocs = n;
    nbStacks = k;
    stack = new int[nbBlocs];
    next = new int[nbBlocs];
    top = new int[nbStacks];
}

State::State(const State &state) {
    // Constructor that creates a copy of state
    nbBlocs = state.nbBlocs;
    nbStacks = state.nbStacks;
    stack = new int[nbBlocs];
    next = new int[nbBlocs];
    top = new int[nbStacks];
    for (int s = 0; s < nbStacks; s++) {
        top[s] = state.top[s];
    }
    for (int b = 0; b < nbBlocs; b++) {
        next[b] = state.next[b];
        stack[b] = state.stack[b];
    }
}

State::~State() {
    delete[] next;
    delete[] stack;
    delete[] top;
}

void State::setInitial() {
    // Initialise this with the initial state (blocs uniformly distributed on stacks)
    for (int s = 0; s < nbStacks; s++) {
        top[s] = -1;
    }
    for (int b = 0; b < nbBlocs; b++) {
        int s = b % nbStacks; // Put bloc b on top of stack s
        stack[b] = s;
        next[b] = top[s];
        top[s] = b;
    }
}

bool State::isFinal() {
    // Return true if this is a final state (all blocs on the last stack, from largest to smallest)
    for (int s = 0; s < nbStacks - 1; s++) {
        if (top[s] != -1) return false;
    }
    if (top[nbStacks - 1] != 0) return false;
    for (int b = 0; b < nbBlocs - 1; b++) {
        if (stack[b] != nbStacks - 1) return false;
        if (next[b] != b + 1) return false;
    }
    if (next[nbBlocs - 1] != -1) return false;
    return true;
}

void State::doMove(Move m) {
    // Precondition: 0 <= m.first < getNbStacks(), 0 <= m.second < getNbStacks(), and !emptyStack(m.first)
    // Apply the doMove (s1->s2) to this
    int b1 = top[m.first];
    int bb1 = next[b1];
    int b2 = top[m.second];
    next[b1] = b2;
    top[m.second] = b1;
    top[m.first] = bb1;
    stack[b1] = m.second;
}

void displayBlockStack(int b, int *next) {
    // Display all blocs below b (including b), from bottom to top
    if (b >= 0) {
        displayBlockStack(next[b], next);
        cout << b << " ";
    }
}

void State::display() const {
    // Display this
    for (int s = 0; s < nbStacks; s++) {
        cout << "stack " << s << ": ";
        displayBlockStack(top[s], next);
        cout << endl;
    }
}

int State::getNbStacks() {
    return nbStacks;
}

bool State::emptyStack(int s) {
    // Precondition: 0 <= s < getNbStacks()
    // Return true if stack s has no block
    return top[s] == -1;
}

bool State::operator<(const State &state) const {
    // Return true if this < state
    return state.compare(stack, top, next) < 0;
}

bool State::operator>(const State &state) const {
    // Return true if this > state
    return state.compare(stack, top, next) > 0;
}

bool State::operator==(const State &state) const {
    // Return true if this == state
    return state.compare(stack, top, next) == 0;
}

bool State::operator!=(const State &state) const {
    // Return true if this != state
    return state.compare(stack, top, next) != 0;
}

int State::compare(const int *stack2, const int *top2, const int *next2) const {
    for (int b = 0; b < nbBlocs; b++) {
        if (stack[b] < stack2[b]) return -1;
        if (stack[b] > stack2[b]) return 1;
        if (next[b] < next2[b]) return -1;
        if (next[b] > next2[b]) return 1;
    }
    for (int s = 0; s < nbStacks; s++) {
        if (top[s] < top2[s]) return -1;
        if (top[s] > top2[s]) return 1;
    }
    return 0;
}


int a = 0;

int State::heuristic() {

    int wrongStack = 0;
    int wrongOrder = 0;
    int lastStack = this->getNbStacks() - 1;
    int lastBlock = this->nbBlocs - 1;

    for (int i = 0; i < lastStack; i++) {
        int element = this->top[i];
        int toInverseCount = 0;
        while (element != -1) {
            wrongStack++;
            int el = this->top[i];
            int inferiorCount = 0;
            while (el != element) {
                if (el < element) {
                    inferiorCount++;
                }
                el = this->next[el];
            }
            if (inferiorCount > toInverseCount) {
                toInverseCount = inferiorCount;
            }
            element = this->next[element];
        }
        wrongStack += toInverseCount;
    }
    int element = this->top[lastStack];
    while (element != -1) {
        int j = element;
        while (j < lastBlock && this->next[j] == j + 1) {
            j++;
        }
        if (j != lastBlock || this->next[j] != -1) {
            wrongOrder++;
        }
        element = this->next[element];
    }
    int result = wrongStack + 2 * wrongOrder;


    int d = 0;
    for (int b = 0; b < this->nbBlocs; b++) {
        if (this->stack[b] != this->nbStacks - 1) d++;
        else {
            int n = b;
            while ((this->next[n] != -1) && (this->next[n] == n + 1)) n = this->next[n];
            if ((this->next[n] != -1) || (n != this->nbBlocs - 1)) d += 2;
        }
    }
    cout << "H2 = " << d << " | P1 = " << result << endl;
    if(d > result) return d;
    else return result;
}
