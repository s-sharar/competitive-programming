#include <bits/stdc++.h>
using namespace std;

// Giant Pizza (CSES) - 2-SAT using Kosaraju SCC
// Node mapping for topping i (0-indexed):
//   +i  -> 2*i
//   -i  -> 2*i + 1
// Negation: x ^ 1

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numCustomers, numToppings;
    cin >> numCustomers >> numToppings;

    int N = 2 * numToppings;
    vector<vector<int>> g(N), gr(N);

    auto litNode = [&](char sign, int toppingIdx0) -> int {
        int base = 2 * toppingIdx0;
        return (sign == '+') ? base : (base ^ 1);
    };
    auto negNode = [&](int node) -> int { return node ^ 1; };

    auto addEdge = [&](int u, int v) {
        g[u].push_back(v);
        gr[v].push_back(u);
    };

    for (int i = 0; i < numCustomers; i++) {
        char s1, s2;
        int a, b;
        cin >> s1 >> a >> s2 >> b;
        --a; --b;

        int A = litNode(s1, a);
        int B = litNode(s2, b);

        // (A OR B) => (!A -> B) and (!B -> A)
        addEdge(negNode(A), B);
        addEdge(negNode(B), A);
    }

    // Kosaraju pass 1: build finish order
    vector<int> seen(N, 0), order;
    order.reserve(N);

    function<void(int)> dfs1 = [&](int u) {
        seen[u] = 1;
        for (int v : g[u]) if (!seen[v]) dfs1(v);
        order.push_back(u);
    };

    for (int i = 0; i < N; i++) {
        if (!seen[i]) dfs1(i);
    }

    // Kosaraju pass 2: assign components on reversed graph in reverse(order)
    vector<int> comp(N, -1);
    int compCount = 0;

    function<void(int)> dfs2 = [&](int u) {
        comp[u] = compCount;
        for (int v : gr[u]) if (comp[v] == -1) dfs2(v);
    };

    for (int i = N - 1; i >= 0; i--) {
        int u = order[i];
        if (comp[u] == -1) {
            dfs2(u);
            compCount++;
        }
    }

    // Check contradictions
    for (int i = 0; i < numToppings; i++) {
        int pos = 2 * i;       // +i
        int neg = pos ^ 1;     // -i
        if (comp[pos] == comp[neg]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    // Build assignment: choose +i if comp(+i) > comp(-i)
    for (int i = 0; i < numToppings; i++) {
        int pos = 2 * i;
        int neg = pos ^ 1;
        bool choosePos = comp[pos] > comp[neg];
        cout << (choosePos ? '+' : '-') << (i + 1 == numToppings ? '\n' : ' ');
    }

    return 0;
}
