# graph_visualization.py
#-*-coding: utf-8 -*-

import matplotlib.pyplot as plt
import networkx as nx
import numpy as np


def draw_graphs(graph1_file, graph2_file):

    G1 = nx.Graph()
    G2 = nx.Graph()

    with open(graph1_file, 'r') as file1:
        max_node = -1
        for line in file1:
            a, b = map(int, line.split())
            G1.add_edge(a, b)
            G2.add_edge(a, b)
            max_node = max(max_node, a, b)

    with open(graph2_file, 'r') as file2:
        pairs = []
        for line in file2:
            a, b = map(int, line.split())
            pairs.append((a, b))

        for node in range(1, max_node + 1):
            if node not in G1:
                G1.add_node(node)
            if node not in G2:
                G2.add_node(node)

    plt.figure(figsize=(12, 5))

    sorted_nodes_G1 = sorted(G1.nodes())
    pos1 = nx.circular_layout(G1)

    num_nodes = len(sorted_nodes_G1)
    angle_step = 2 * 3.14159 / num_nodes
    for i, node in enumerate(sorted_nodes_G1):
        pos1[node] = (0.5 * num_nodes * np.cos(i * angle_step), 0.5 * num_nodes * np.sin(i * angle_step))

    sorted_nodes_G2 = sorted(G2.nodes())
    pos2 = nx.circular_layout(G2)

    num_nodes = len(sorted_nodes_G2)
    angle_step = 2 * 3.14159 / num_nodes
    for i, node in enumerate(sorted_nodes_G2):
        pos2[node] = (0.5 * num_nodes * np.cos(i * angle_step), 0.5 * num_nodes * np.sin(i * angle_step))

    plt.subplot(1, 2, 1)
    nx.draw(G1, pos=pos1, with_labels=True, font_weight='bold', node_color = 'white', edgecolors = "black")
    plt.title('Graph 1')

    edge_colors = ['black' if (e[1], e[0]) not in pairs and (e[0], e[1]) not in pairs else 'red' for e in G2.edges()]

    plt.subplot(1, 2, 2)
    nx.draw(G2, pos=pos2, with_labels=True, font_weight='bold', node_color = 'white', edgecolors = "black", edge_color = edge_colors)
    plt.title('Graph 2')

    plt.show()

def draw_graphs_with_weight(graph1_file, graph2_file):

    G1 = nx.Graph()
    G2 = nx.Graph()

    with open(graph1_file, 'r') as file1:
        max_node = -1
        for line in file1:
            a, b, weight = map(int, line.split())
            G1.add_edge(a, b, weight=weight)
            max_node = max(max_node, a, b)

    with open(graph2_file, 'r') as file2:
        pairs = []
        for line in file2:
            a, b, weight = map(int, line.split())
            G2.add_edge(a, b, weight = weight)
            pairs.append((a, b))

        for node in range(1, max_node + 1):
            if node not in G1:
                G1.add_node(node)

    plt.figure(figsize=(12, 5))

    sorted_nodes_G1 = sorted(G1.nodes())
    pos1 = nx.circular_layout(G1)

    num_nodes = len(sorted_nodes_G1)
    angle_step = 2 * np.pi / num_nodes
    for i, node in enumerate(sorted_nodes_G1):
        pos1[node] = (0.5 * num_nodes * np.cos(i * angle_step), 0.5 * num_nodes * np.sin(i * angle_step))

    pos2 = pos1.copy()

    plt.subplot(1, 2, 1)
    nx.draw(G1, pos=pos1, with_labels=True, font_weight='bold', node_color='white', edgecolors="black")

    edge_labels1 = {(u, v): d['weight'] for u, v, d in G1.edges(data=True)}
    nx.draw_networkx_edge_labels(G1, pos1, edge_labels=edge_labels1, label_pos=0.55, font_size=10)

    plt.title('Graph 1')

    edge_colors = ['black' if (e[1], e[0]) not in pairs and (e[0], e[1]) not in pairs else 'red' for e in G2.edges()]

    plt.subplot(1, 2, 2)
    nx.draw(G2, pos=pos2, with_labels=True, font_weight='bold', node_color='white', edgecolors="black", edge_color=edge_colors)

    edge_labels2 = {(u, v): d['weight'] for u, v, d in G2.edges(data=True)}
    nx.draw_networkx_edge_labels(G2, pos=pos2, edge_labels=edge_labels2, label_pos=0.55, font_size=10)

    plt.title('Graph 2')

    plt.show()
    
def draw_directed_graphs_with_weight(graph1_file, graph2_file):
    
    G1 = nx.DiGraph()
    G2 = nx.DiGraph()

    with open(graph1_file, 'r') as file1:
        max_node = -1
        for line in file1:
            a, b, weight = map(int, line.split())
            G1.add_edge(a, b, weight=weight)
            max_node = max(max_node, a, b)

    with open(graph2_file, 'r') as file2:
        pairs = []
        for line in file2:
            a, b, weight = map(int, line.split())
            G2.add_edge(a, b, weight = weight)
            pairs.append((a, b))

        for node in range(1, max_node + 1):
            if node not in G1:
                G1.add_node(node)

    plt.figure(figsize=(12, 5))

    sorted_nodes_G1 = sorted(G1.nodes())
    pos1 = nx.circular_layout(G1)

    num_nodes = len(sorted_nodes_G1)
    angle_step = 2 * np.pi / num_nodes
    for i, node in enumerate(sorted_nodes_G1):
        pos1[node] = (0.5 * num_nodes * np.cos(i * angle_step), 0.5 * num_nodes * np.sin(i * angle_step))

    pos2 = pos1.copy()

    plt.subplot(1, 2, 1)
    nx.draw(G1, pos=pos1, with_labels=True, font_weight='bold', node_color='white', edgecolors="black")

    edge_labels1 = {(u, v): d['weight'] for u, v, d in G1.edges(data=True)}
    nx.draw_networkx_edge_labels(G1, pos1, edge_labels=edge_labels1, label_pos=0.55, font_size=10)

    plt.title('Graph 1')

    edge_colors = ['black' if (e[1], e[0]) not in pairs and (e[0], e[1]) not in pairs else 'red' for e in G2.edges()]

    plt.subplot(1, 2, 2)
    nx.draw(G2, pos=pos2, with_labels=True, font_weight='bold', node_color='white', edgecolors="black", edge_color=edge_colors)

    edge_labels2 = {(u, v): d['weight'] for u, v, d in G2.edges(data=True)}
    nx.draw_networkx_edge_labels(G2, pos=pos2, edge_labels=edge_labels2, label_pos=0.55, font_size=10)

    plt.title('Graph 2')

    plt.show()

def read_and_draw(algorithm_file):
    with open(algorithm_file, "r") as file:
        algorithm = int(file.read().strip())

    if algorithm in [1, 2]:
        draw_graphs("graph1.txt", "graph2.txt")
    elif algorithm in [3, 4]:
        draw_graphs_with_weight("graph1.txt", "graph2.txt")
    elif algorithm in range(5, 11):
        draw_directed_graphs_with_weight("graph1.txt", "graph2.txt")

read_and_draw("algorithm.txt")