# this time, in graph_type we specify we want a DIrected GRAPH
import pydot
import graphviz

#Reading Tranisition Table from File
f = open("dfa.txt", "r")
arr = map(int, f.readline().split())
row_c = arr[0]
column_c = arr[1]
fstate_c = arr[2]
states = f.readline().split()
symbols = f.readline().split()
fstates = f.readline().split()
transition_table=[]
for i in range(row_c):
    temp = f.readline().split()
    transition_table.append(temp)
    
#Printing File Data  
'''print(row_c)
print(column_c)
print(fstate_c)
print(states)
print(symbols)
print(fstates)
print(transition_table)'''

f.close()

#Drawing Graph
graph = pydot.Dot(graph_type='digraph',rankdir='LR')
node_list = []
strt_node=pydot.Node("s", fillcolor="white", shape="circle", style="invis")
graph.add_node(strt_node)
for i in range(row_c):
    if(states[i] in fstates):
        node_temp = pydot.Node(states[i], style="filled", fillcolor="white", shape="doublecircle", color="red")
    else:
        node_temp = pydot.Node(states[i], style="filled", fillcolor="white", shape="circle")
    node_list.append(node_temp)
    graph.add_node(node_list[i])

#Adding start node
graph.add_edge(pydot.Edge(strt_node,node_list[0], label="", color="black"))

for i in range(row_c):
    for j in range(column_c):
        if(transition_table[i][j] != '_'):
            #k=int(transition_table[i][j])-1
            k=states.index(transition_table[i][j])
            graph.add_edge(pydot.Edge(node_list[i],node_list[k], label=symbols[j], labelfontcolor="#109933", fontsize="10.0", color="black"))

graph.write_svg('e1.svg')
