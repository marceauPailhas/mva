from itertools import product

import networkx as nx
import numpy as np
from networkx.utils import not_implemented_for
##definition de fonctions sur les graphes


"""
Graph products.
"""


def _dict_product(d1, d2):
    return {k: (d1.get(k), d2.get(k)) for k in set(d1) | set(d2)}


# Generators for producing graph products
def _node_product(G, H):
    for u, v in product(G, H):
        if (G.nodes[u])['labels'][0] != (H.nodes[v])['labels'][0]: #makes sure that only nodes with the same label get paired
            continue
        yield ((u, v), _dict_product(G.nodes[u], H.nodes[v]) )


def _directed_edges_cross_edges(G, H):
    if not G.is_multigraph() and not H.is_multigraph():
        #print(G.edges(data=True), H.edges(data=True))
        for u, v, c in G.edges(data=True):
            for x, y, d in H.edges(data=True):
                #print((u, x), (v, y), )
                if (G.nodes[u])['labels'][0] == (H.nodes[x])['labels'][0] and (G.nodes[v])['labels'][0] == (H.nodes[y])['labels'][0]:  
                    yield (u, x), (v, y), _dict_product(c, d)
                #the edge is (u,v) but it can also be described as (v,u)
                if (G.nodes[u])['labels'][0] == (H.nodes[y])['labels'][0] and (G.nodes[v])['labels'][0] == (H.nodes[x])['labels'][0]:
                    yield (u, y), (v, x), _dict_product(c, d)
                
    else:
        raise NotImplemented



def _init_product_graph(G, H):
    if G.is_directed() != H.is_directed():
        msg = "G and H must be both directed or both undirected"
        raise nx.NetworkXError(msg)
    if G.is_multigraph() or H.is_multigraph():
        GH = nx.MultiGraph()
    else:
        GH = nx.Graph()
    if G.is_directed():
        GH = GH.to_directed()
    return GH


def tensor_product(G, H):
    r"""Returns the tensor product of G and H.

    The tensor product $P$ of the graphs $G$ and $H$ has a node set that
    is the tensor product of the node sets, $V(P)=V(G) \times V(H)$.
    $P$ has an edge $((u,v), (x,y))$ if and only if $(u,x)$ is an edge in $G$
    and $(v,y)$ is an edge in $H$.

    Tensor product is sometimes also referred to as the categorical product,
    direct product, cardinal product or conjunction.


    Parameters
    ----------
    G, H: graphs
     Networkx graphs.

    Returns
    -------
    P: NetworkX graph
     The tensor product of G and H. P will be a multi-graph if either G
     or H is a multi-graph, will be a directed if G and H are directed,
     and undirected if G and H are undirected.

    Raises
    ------
    NetworkXError
     If G and H are not both directed or both undirected.

    Notes
    -----
    Node attributes in P are two-tuple of the G and H node attributes.
    Missing attributes are assigned None.

    Examples
    --------
    >>> G = nx.Graph()
    >>> H = nx.Graph()
    >>> G.add_node(0, a1=True)
    >>> H.add_node("a", a2="Spam")
    >>> P = nx.tensor_product(G, H)
    >>> list(P)
    [(0, 'a')]

    Edge attributes and edge keys (for multigraphs) are also copied to the
    new product graph
    """
    GH = _init_product_graph(G, H)
    GH.add_nodes_from(_node_product(G, H))
    GH.add_edges_from(_directed_edges_cross_edges(G, H))
    
    return GH



##definition du kernel, notament kernel n-th oder walk kernel



def n_th_order_kernel(G1,G2,n=3):
    
    G1G2 = tensor_product(G1, G2)
    #print('le matrix product a pris, ', time()-tic, 's')
    #tic=time()
    #adjency_matrix = scipy.sparse.coo_matrix( nx.to_numpy_array(G1G2) ) 
    
    try:
        adjency_matrix = nx.to_scipy_sparse_array(G1G2)  
    
    except nx.NetworkXError: 
            return 0
    #print('adejency matrix a pris le temps, ', time()-tic, 's')
    #tic=time()
    adj_mat_n = power (adjency_matrix,n)
    for i in range(n-1):
         adj_mat_n = adj_mat_n @ adjency_matrix #linalg.matrix_power(adjency_matrix, n)
            
    #print('la puissance de mat a pris le temps, ', time()-tic, 's')
    return np.sum(adj_mat_n)



def kernel_n_order(X,Y, same = False, n=3):
    if same == True:
        a = np.zeros((len(X), len(Y)))
        for i in range(len(X)):
            for j in range(i+1):
                a[i,j] = n_th_order_kernel(X[i],Y[j],n=n)

        return a + a.T - np.diag(a.diagonal())
        
    return np.array([[n_th_order_kernel(G1,G2,n=n) for G1 in Y] for G2 in X])
