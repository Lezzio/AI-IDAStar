using namespace std;

class State{
public:

    State(int n, int k);
    // Constructor that creates a state with n blocs and k stacks

    State(const State& s);
    // Constructor that creates a copy of s

    void setInitial();
    // Initialise this with the initial state (blocs uniformly distributed on stacks)

    bool isFinal();
    // Return true if this is a final state (all blocs on the last stack, from largest to smallest)

    typedef pair<int,int> Move;
    // A move is a pair of stacks: the bloc on top of the first stack is moved to the top of the second stack

    void doMove(Move m);
    // Precondition: 0 <= m.first < getNbStacks(), 0 <= m.second < getNbStacks(), and !emptyStack(m.first)
    // Postrelation: Apply the move (m.first->m.second) to this

    int heuristic();
    // Return a lower bound on the minimal number of moves necessary to transform this into the final state

    void display() const;
    // Display this

    bool operator<(const State&) const;
    bool operator>(const State&) const;
    bool operator==(const State&) const;
    bool operator!=(const State&) const;

    int getNbStacks();
    // Return the number of stacks

    bool emptyStack(int s);
    // Precondition: 0 <= s < getNbStacks()
    // Return true if stack s has no block

    ~State();
    // Destructor

private:
    int nbBlocs, nbStacks;
    int* stack; // For each bloc b: stack[b] = stack that contains b
    int* next;  // For each bloc b: if b is the lowest block of its stack,
    // then next[b]=-1, else next[b]=bloc immediately below b
    int* top;   // For each stack s: if s is empty, then top[s]=-1
    // else top[s]=bloc on top of s
    int compare(const int*, const int*, const int*) const; // function to compare states
};
