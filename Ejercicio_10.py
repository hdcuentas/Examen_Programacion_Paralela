import math
import multiprocessing as np
from multiprocessing import Pool
def generar_serie(inicial, final):
    serie = []
    for i in range(inicial, final + 1):
        serie.append(i * 2)
    return serie
if __name__=='__main__':
  limite = 100  # Número de términos en la serie
  num_proc = np.cpu_count()    # Número de procesadores (vectores) para distribuir el trabajo
  parametros = [(i*(limite//num_proc), (i+1)*(limite//num_proc)) for i in range(num_proc)]
  print(num_proc)
  print(parametros)
  with Pool() as pool:
      vectorResultados = pool.starmap(generar_serie, parametros)
  print(vectorResultados)