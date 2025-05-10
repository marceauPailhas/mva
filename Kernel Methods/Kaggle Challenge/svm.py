import numpy as np
import pickle as pkl
from scipy import optimize
from scipy.linalg import cho_factor, cho_solve
#from kernel import kernel_n_order
from time import time

class KernelSVC:
    
    def __init__(self, kernel,C=1.0, epsilon = 1e-3):
        self.type = 'non-linear'
        self.C = C                               
        self.kernel = kernel        
        self.alpha = None
        self.support = None
        self.support_label = None #added this attribute
        self.epsilon = epsilon
        self.norm_f = None
       
    
    def fit(self, X, y):
       #### You might define here any variable needed for the rest of the code
        N = len(y)

        tic=time()
        print('Start of the computation of the gramm matrix')
        K = self.kernel(X,X, same=True)
        print('End of the computation of the gramm matrix.\nTemps écoulé', time()-tic, 's')
        
        self.gram_matrix = K
        ## transfo des classes
        #weights = (2/len(y))*( np.sum(y==0)*(y==0) + np.sum(y==1)*(y==1))
        #weights = 1/weights
        weights = np.ones(N)
        #print('on a calculer les poids', weights)
        
        y = 2*y-1 #on passe de {0,1} à {-1,1}
        #print('classes have been relabeled {-1,1}',y)
        #print("qu'est ce qui se passe?")
        
        
        # Lagrange dual problem
        def loss(alpha):
            lamda = y * alpha # * is the component-wise product, it is faster than the matrix product
            return (1/2)*(lamda.T @K @ lamda).item() - np.sum(weights*alpha)#'''--------------dual loss ------------------ ''' 
        ## we minimize -g(alpha)
        
        # Partial derivate of Ld on alpha
        def grad_loss(alpha):
            return y* (K @ (y*alpha)) - weights#np.ones(N)# '''----------------partial derivative of the dual loss wrt alpha -----------------'''


        # Constraints on alpha of the shape :
        # -  d - C*alpha  = 0
        # -  b - A*alpha >= 0

        fun_eq = lambda alpha: np.dot(alpha,y)  # '''----------------function defining the equality constraint------------------'''        
        jac_eq = lambda alpha: y    #'''----------------jacobian wrt alpha of the  equality constraint------------------'''
        
        fun_ineq = lambda alpha: - np.concatenate([weights*alpha, -weights*alpha], axis = 0)  + np.concatenate([self.C*np.ones(N), np.zeros(N)], axis = 0) 
            # '''---------------function defining the inequality constraint-------------------'''     
        
        jac_ineq = lambda alpha: -np.block( [[np.diag(weights)], [ -np.diag(weights) ]])  #np.eye(N)np.eye(N)
        ##becarefull the ineq should be b - A alpha!!
        # '''---------------jacobian wrt alpha of the  inequality constraint-------------------'''
        
        
        constraints = ({'type': 'eq',  'fun': fun_eq, 'jac': jac_eq},
                       {'type': 'ineq', 
                        'fun': fun_ineq , 
                        'jac': jac_ineq})

        tic = time()
        print('\n\nStart of the minimization of the cost function')
        
        optRes = optimize.minimize(fun=lambda alpha: loss(alpha),
                                   x0=np.ones(N), 
                                   method='SLSQP', 
                                   jac=lambda alpha: grad_loss(alpha), 
                                   constraints=constraints)
        
        print('End of the minimization.\nTemps écoulé', time()-tic, 's')
        self.alpha = optRes.x
        
        ## Assign the required attributes

        
        self.margin_points = (self.alpha < self.C - self.epsilon) * (self.alpha > self.epsilon)
        
        #'''------------------- A matrix with each row corresponding to a point that falls on the margin ------------------'''
        
        
        self.b = np.sum(self.margin_points * ( y - K @ (self.alpha*y) ) ) / np.sum(self.margin_points) 
        #''' -----------------offset of the classifier------------------ '''
            
        self.norm_f = ( (self.alpha*y).T @ K @ (self.alpha*y) ).item()
        # '''------------------------RKHS norm of the function f ------------------------------'''
        
        
        self.support =  X[self.alpha > self.epsilon]
        #concatenation of x that have alpha != 0, we keep support vectors, here it is a list of graph
        
        self.support_label = y [ self.alpha > self.epsilon ]
        self.alpha = self.alpha[ self.alpha> self.epsilon ] 
        #we keep alpha of support vectors

    ### Implementation of the separting function $f$ 
    def separating_function(self,x):
        # Input : matrix x of shape N data points times d dimension
        # Output: vector of size N
        K = self.kernel(x,self.support, same=False)
        return K@(self.alpha*self.support_label) 
    
    
    def predict(self, X):
        """ Predict y values in {0, 1} """
        d = self.separating_function(X)
        return np.array( d+self.b> 0 , dtype=int )