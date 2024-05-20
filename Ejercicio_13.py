import multiprocessing
from multiprocessing import Pool
def fibonacci(n):
    fibo = [0, 1]
    for i in range(2, n):
        fibo.append(fibo[-1] + fibo[-2])
    return fibo
def calcular_fibonacci(inicio, fin):
    return fibonacci(fin)[inicio:fin]
if __name__ == "__main__":
    num_terminos = 20
    num_procesadores = multiprocessing.cpu_count()
    # Calcular el número de términos por procesador
    terminos_por_procesador = num_terminos // num_procesadores
    # Generar los rangos de términos para cada procesador
    rangos = [(i * terminos_por_procesador, (i + 1) * terminos_por_procesador) for i in range(num_procesadores)]
    with Pool() as pool:
        resultados = pool.starmap(calcular_fibonacci, rangos)
    # Imprimir los términos de Fibonacci
    print(resultados)
    serie = []
    for i in resultados:
      for j in i:
        serie.append(j)
    print(serie)