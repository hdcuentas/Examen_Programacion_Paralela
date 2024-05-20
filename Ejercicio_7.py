import math
import multiprocessing as np
from multiprocessing import Pool
def calcular_pi(inicial,final):
  v=[]
  for i in range(inicial,final):
    if (i==0):
      continue
    term = (1/(i**4))
    v.append(term)
  return v
if __name__=='__main__':
  limite = 1000000
  parametros = [((i*limite),(limite*(i+1))) for i in range(np.cpu_count())]
  print(parametros)
  pool=Pool()
  resultado = pool.starmap(calcular_pi,parametros)
  pi=(90*sum(sum(resultado,[])))**(1/4)
  print(pi)