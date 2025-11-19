# 2° Parcial.
## Funciones:
1. load_conf(): Toma un nombre de un archivo (string), abre y devuelve struct con 3 campos (el último es string, el resto enteros).
    1. PORT=num
    2. BACKLOG=num
    3. ARCHIVOS=arch01.txt,arch02.txt,… [indefinido: max 1024 B]

2. Cliente TCP que se conecta a srv, recibe "`READY`" y envía comandos en forma de string: "`DATnnn`", donde "nnn" es una secuencia numérica de 000~999. El programa cliente recibe por línea de comandos que numero deberá comenzar a pedir, y hasta cúal numero. Por ejemplo: `cliente 10.10.1.5 3255 015-025`.
Donde el primer valor es la IP (10.10.1.5), el segundo el puerto (3255) y el último está compuesto
por un primer valor `nnn` (`DAT015`) y el segundo (`DAT025`). De esta manera el programa debería
pedirle al server desde el dato `DAT015` al dato `DAT025`. Luego de cada comando “`DATnnn`” el
cliente se deberá preparar para recibir una cadena de 256 caracteres como máximo. Al terminar de
recibir la cadena, deberá confirmar la recepción enviando la cadena “`ACK`” al server. Este proceso
se repite hasta terminar de recibir los datos indicados por línea de comandos.

3. A