#!/usr/bin/python

import sys
from matplotlib.colors import Colormap
import numpy as np
import pandas as pd
import matplotlib
import matplotlib.pyplot as plt
import locale
from matplotlib.ticker import (MultipleLocator, AutoMinorLocator)
from scipy.interpolate import interp1d
import math

def ImportarDados():
    print("Importando R-BEP")
    dadosRBEP = ImportarAlgoritmo('R-BEP')
    print(dadosRBEP)
    
    print("Importando R-CEP")
    dadosRCEP = ImportarAlgoritmo('R-CEP')
    print(dadosRCEP)
    
    print("Importando R-EEP")
    dadosREEP = ImportarAlgoritmo('R-EEP')
    print(dadosREEP)
    
    print("Importando R-CEEP")
    dadosRCEEP = ImportarAlgoritmo('R-CEEP')
    print(dadosRCEEP)
    
    print("Unificando Resultados")        
    dfTotal = pd.concat([dadosRBEP,dadosRCEP.reindex(dadosRBEP.index), dadosREEP.reindex(dadosRBEP.index), dadosRCEEP.reindex(dadosRBEP.index)], axis=1)    
    return dfTotal

def ImportarAlgoritmo(algoritmo, primeiro=False):
    dados = []
    nomeArquivo = algoritmo + '.txt';
    arquivo = open(nomeArquivo, "r")
    for linha in arquivo:
        s = linha.rstrip().split('\t')
        s2 = s[0].split('.')[0].split('_');
        
        n = s2[2]
        m = s2[3]
        seed = s2[4]
        nome = n + '_' + m + '_' + seed
        
        sol = int(s[1])
        tempo = float(s[2])

        dados.append([nome, int(n), int(m), sol, tempo]);
    
    df = pd.DataFrame(dados, columns=['Instancia', 'n', 'm', algoritmo+'_BV', algoritmo+'_TE'])    
    df = df.set_index(['Instancia','n','m'])
    return df

def ApresentarGrafico(dados, instancia):
    figure, axis = plt.subplots(1, 2)
    print(axis)

    dadosF = dados.query("Instancia == '"+instancia+"'")
    print(dadosF)

    lineWidth = 0.7
    cores = ["#AAD9F4", "#7FCEB9", "#F7F1A0", "#EAAE7F", "#E5BCD3"]

    boxplotBV = dadosF.boxplot(column=['R-BEP_BV', 'R-CEP_BV', 'R-EEP_BV', 'R-CEEP_BV'],patch_artist=True,\
                notch=False, meanline=False, showmeans=True, zorder=3,\
                flierprops=dict(marker='o', markerfacecolor='red', markersize=1, markeredgecolor='red'),\
                meanprops=dict(marker='+', markersize=3.5, markeredgecolor='#0043ce', markerfacecolor='#0043ce'), \
                medianprops=dict(linestyle='-', linewidth=lineWidth, color="black"),\
                boxprops=dict(color='black',linewidth=lineWidth),\
                whiskerprops=dict(linewidth=lineWidth),\
                capprops = dict(linewidth=lineWidth), ax=axis[0], return_type='dict')

    boxplotTE = dadosF.boxplot(column=['R-BEP_TE', 'R-CEP_TE', 'R-EEP_TE', 'R-CEEP_TE'],patch_artist=True,\
                notch=False, meanline=False, showmeans=True, zorder=3,\
                flierprops=dict(marker='o', markerfacecolor='red', markersize=1, markeredgecolor='red'),\
                meanprops=dict(marker='+', markersize=3.5, markeredgecolor='#0043ce', markerfacecolor='#0043ce'), \
                medianprops=dict(linestyle='-', linewidth=lineWidth, color="black"),\
                boxprops=dict(color='black',linewidth=lineWidth),\
                whiskerprops=dict(linewidth=lineWidth),\
                capprops = dict(linewidth=lineWidth), ax=axis[1], return_type='dict')

    x = 0
    for patch in boxplotBV['boxes']:
        patch.set(facecolor=cores[x]) 
        x += 1
    
    x = 0
    for patch in boxplotTE['boxes']:
        patch.set(facecolor=cores[x]) 
        x += 1
    
    mBV=dadosF[['R-BEP_BV', 'R-CEP_BV', 'R-EEP_BV', 'R-CEEP_BV']].mean()
    mTE=dadosF[['R-BEP_TE', 'R-CEP_TE', 'R-EEP_TE', 'R-CEEP_TE']].mean()
    
    for i, line in enumerate(boxplotBV['means']):
        x, y = line.get_xydata()[0]
        text = ' {:.3f}'.format(mBV[i])
        axis[0].annotate(text, xy=(x, y))
        
    for i, line in enumerate(boxplotTE['means']):
        x, y = line.get_xydata()[0]
        text = ' {:.3f}'.format(mTE[i])
        axis[1].annotate(text, xy=(x, y))
    
    
    axis[0].set_title(instancia)
    axis[1].set_title(instancia)

    #boxplotBV.plot()
    #boxplotTE.plot()

    plt.show()
    
def ApresentarGraficoMedia(dados, n, m=None):
    figure, axis = plt.subplots(1, 2)
    print(axis)

    if m != None:
        dadosF = dados.query("n == "+str(n)+" & m == "+str(m))
    else:
        dadosF = dados.query("n == "+str(n))
    print(dadosF)

    lineWidth = 0.7
    cores = ["#AAD9F4", "#7FCEB9", "#F7F1A0", "#EAAE7F", "#E5BCD3"]

    boxplotBV = dadosF.boxplot(column=['R-BEP_BV', 'R-CEP_BV', 'R-EEP_BV', 'R-CEEP_BV'],patch_artist=True,\
                notch=False, meanline=False, showmeans=True, zorder=3,\
                flierprops=dict(marker='o', markerfacecolor='red', markersize=1, markeredgecolor='red'),\
                meanprops=dict(marker='+', markersize=3.5, markeredgecolor='#0043ce', markerfacecolor='#0043ce'), \
                medianprops=dict(linestyle='-', linewidth=lineWidth, color="black"),\
                boxprops=dict(color='black',linewidth=lineWidth),\
                whiskerprops=dict(linewidth=lineWidth),\
                capprops = dict(linewidth=lineWidth), ax=axis[0], return_type='dict')

    boxplotTE = dadosF.boxplot(column=['R-BEP_TE', 'R-CEP_TE', 'R-EEP_TE', 'R-CEEP_TE'],patch_artist=True,\
                notch=False, meanline=False, showmeans=True, zorder=3,\
                flierprops=dict(marker='o', markerfacecolor='red', markersize=1, markeredgecolor='red'),\
                meanprops=dict(marker='+', markersize=3.5, markeredgecolor='#0043ce', markerfacecolor='#0043ce'), \
                medianprops=dict(linestyle='-', linewidth=lineWidth, color="black"),\
                boxprops=dict(color='black',linewidth=lineWidth),\
                whiskerprops=dict(linewidth=lineWidth),\
                capprops = dict(linewidth=lineWidth), ax=axis[1], return_type='dict')

    x = 0
    for patch in boxplotBV['boxes']:
        patch.set(facecolor=cores[x]) 
        x += 1
    
    x = 0
    for patch in boxplotTE['boxes']:
        patch.set(facecolor=cores[x]) 
        x += 1
    
    mBV=dadosF[['R-BEP_BV', 'R-CEP_BV', 'R-EEP_BV', 'R-CEEP_BV']].mean()
    mTE=dadosF[['R-BEP_TE', 'R-CEP_TE', 'R-EEP_TE', 'R-CEEP_TE']].mean()
    
    for i, line in enumerate(boxplotBV['means']):
        x, y = line.get_xydata()[0]
        text = ' {:.3f}'.format(mBV[i])
        axis[0].annotate(text, xy=(x, y))
        
    for i, line in enumerate(boxplotTE['means']):
        x, y = line.get_xydata()[0]
        text = ' {:.3f}'.format(mTE[i])
        axis[1].annotate(text, xy=(x, y))
    
    if m != None:
        titulo = "n: " + str(n) + " m:" + str(m)
    else:
        titulo = "n: " + str(n)
    axis[0].set_title(titulo)
    axis[1].set_title(titulo)

    #boxplotBV.plot()
    #boxplotTE.plot()

    plt.show()


locale.setlocale(locale.LC_ALL , 'en_US')

if len(sys.argv) >= 2:
    dados = ImportarDados()
    if sys.argv[1].isnumeric():
        if len(sys.argv) == 2:
            ApresentarGraficoMedia(dados, int(sys.argv[1]))
        else:
            ApresentarGraficoMedia(dados, int(sys.argv[1]), int(sys.argv[2]))
    else:
        ApresentarGrafico(dados,sys.argv[1])
else:
    print("Faltou informar os parâmetros para gerar o gráfico")

#ApresentarGrafico(dados,"1000_1047_6011")
#ApresentarGraficoMedia(dados,1000,1047)
#ApresentarGraficoMedia(dados,1000)

#dados.to_csv('file_name.csv', encoding='utf-8')









