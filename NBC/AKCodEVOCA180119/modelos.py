import pandas as pd
from sklearn.naive_bayes import GaussianNB
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from joblib import dump, load
import numpy as np


def train():
    df = pd.read_table("datos.txt", delimiter=",", header=None)
    Y= df.iloc[:,-1:]
    df.drop(df.columns[len(df.columns)-1], axis=1, inplace=True)

    #X_train, X_test, y_train, y_test = train_test_split(df, Y, test_size=0.1, random_state=0)
    
    clf = GaussianNB()
    clf.fit(df, Y.values.ravel())
    
    #name= '{name}.joblib'.format(name=modelName)
    #y_pred = clf.predict(X_test)
    dump(clf, "modeloEVOKA.joblib")
    return 1


def load_model(*args):
    
    clf = load('modeloEVOKA.joblib')
    predi= np.array(args).reshape(1,-1)
    
    
    return clf.predict(predi)[0]
    
    

'''
pred= [18,4263,5000,20100,167,1]
print(load_model(pred))
'''
