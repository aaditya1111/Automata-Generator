#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<map>

using namespace std;


struct trans {
        int vertex_from;
        int vertex_to;
        string trans_symbol;
};


class FSM {
public:
        vector<int> vertex;
        vector<trans> transitions;
        set<char> non_terminals;
        set<char> terminals;
        map<char, int> symbol_vertex;
        int final_state;
        int map_tracker;

        FSM() {
                vertex.push_back(-1);
                final_state = -1;
                non_terminals.insert('S');
                symbol_vertex.insert(pair<char, int>('S', 0));
                vertex.push_back(0);
                map_tracker = 1;
        }

        int get_vertex_count() {
                return vertex.size();
        }

        void set_new_vertex(int new_vertex) {
                vertex.push_back(new_vertex);
        }

        void set_final_state(int fs) {
                final_state = fs;
        }

        int get_final_state() {
                return final_state;
        }

        void set_transition(int vertex_from, int vertex_to, char trans_symbol) {
                trans new_trans;
                new_trans.vertex_from = vertex_from;
                new_trans.vertex_to = vertex_to;
                new_trans.trans_symbol = trans_symbol;
                transitions.push_back(new_trans);
        }

        void set_map(char non_terminal, int vertex_no) {
                symbol_vertex.insert(pair<char, int>(non_terminal, vertex_no));
        }

        void read_production(char lhs, char rhs_term, char rhs_nonterm) {
                int vertex_from, vertex_to;

                set<char>::iterator it = non_terminals.find(lhs);
                if(it == non_terminals.end()) {
                        non_terminals.insert(lhs);
                        terminals.insert(rhs_term);
                        set_map(lhs, map_tracker);
                        set_new_vertex(map_tracker);
                        map_tracker++;
                }
                vertex_from = symbol_vertex.find(*(non_terminals.find(lhs)))->second;

                if(rhs_nonterm == '$') {
                        vertex_to = -1;
                } else {
                        set<char>::iterator it = non_terminals.find(rhs_nonterm);
                        if(it == non_terminals.end()) {
                                non_terminals.insert(rhs_nonterm);
                                terminals.insert(rhs_term);
                                set_map(rhs_nonterm, map_tracker);
                                set_new_vertex(map_tracker);
                                map_tracker++;
                        }
                        vertex_to = symbol_vertex.find(*(non_terminals.find(rhs_nonterm)))->second;
                }

                set_transition(vertex_from, vertex_to, rhs_term);
        }

        void display() {
                trans new_trans;
                cout<<"\n\nThe set of transitions in the Finite State Machine are - \n";
                for(vector<trans>::iterator it = transitions.begin(); it != transitions.end(); ++it) {
                        new_trans = *it;
                        cout<<"S"<<new_trans.vertex_from<<" -> S";
                        if(new_trans.vertex_to == -1)
                                cout<<vertex.size() - 1;
                        else
                                cout<<new_trans.vertex_to;
                        cout<<" :: Symbol - "<<new_trans.trans_symbol<<endl;
                }
                set_final_state(vertex.size() - 1);
                cout<<"\n\nFinal state - "<<get_final_state();
        }
};


FSM read_grammar(int no_of_productions) {
        FSM automaton;
        char lhs;
        string rhs;
        char rhs_term;
        char rhs_nonterm;
        char intermediate_state = 47;
 
        for(int i = 0; i < no_of_productions; i++) { 
                cout<<"\nFor transition "<<i+1<<" - \n";
                cout<<"Enter LHS : ";
                cin>>lhs;
                cout<<"Enter RHS : ";
                cin>>rhs;

                if(rhs.find('.') == string::npos) {
                        while(rhs.size() > 1) {
                                rhs_term = rhs[0];
                                rhs_nonterm = intermediate_state;
                                automaton.read_production(lhs, rhs_term, rhs_nonterm);
                                lhs = intermediate_state;
                                rhs = rhs.substr(1);
                                ++intermediate_state;
                                if(intermediate_state == 65) intermediate_state = 91;
                        }
                        rhs_term = rhs[0];
                        rhs_nonterm = '$';
                } else {
                        while(rhs.size() > 3) {
                                rhs_term = rhs[0];
                                rhs_nonterm = intermediate_state;
                                automaton.read_production(lhs, rhs_term, rhs_nonterm);
                                lhs = intermediate_state;
                                rhs = rhs.substr(1);
                                ++intermediate_state;
                                if(intermediate_state == 65) intermediate_state = 91;
                        }
                        rhs_term = rhs[0];
                        rhs_nonterm = rhs[rhs.size() - 1];
                }

                automaton.read_production(lhs, rhs_term, rhs_nonterm);
        }

        return automaton;
}


int main() {
        int no_of_productions;
        FSM automaton;

        cout<<"Right Linear Grammar -> Finite State Machine \n\n"
                <<"INPUT FORMAT - \n"
                <<"> Enter the number of productions \n"
                <<"> For each production, enter the Left Hand Side (LHS) and the Right Hand Side (RHS) of the production \n"
                <<"> Represent the non-terminals with upper-case letters, and terminals with lower-case letters \n"
                <<"> Explicitly mention concatenation of the terminal and non-terminal with a '.' \n"
                <<"> If the production in the written form is written as (say) S -> aA | b , then give S -> aA and S -> b as separate productions \n"
                <<"> Please keep a correct count of the number of productions and enter accordingly \n\n";

        cout<<"Enter the number of productions in the right linear grammar : \n";
        cin>>no_of_productions;

        automaton = read_grammar(no_of_productions);

        automaton.display();
                        
        return 0;
}
