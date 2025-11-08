# Consigna general
> Hacer el ABM de una concesionaria de motos con distintas Sucursales (S_i) y una Casa Central (CC). Las S_is son clientes de la CC.
* La CC atiende a distintos clientes (S_i), multithreaded. Un thread es creado por S_i.
* Es centralizada la base de datos. O sea, siempre la CC tiene una copia de todas las sucursales. Se puede hacer tipo guirnalda (lista de listas).
* Cada nueva S_i, al iniciar, carga todos los datos de la CC.
* Se guardan los datos automáticamente cada 1 minuto tanto en CC como en el S_i correspondiente. Se utiliza la señal de ALARM.
	* NO ES BLOQUEANTE.
	* Antes de terminar, también se guarda. Atrapar SIGINT de Ctrl+C.
* Los datos de las S_i se guardan de manera local en un archivo (temporal). Estos luego se mandan a la casa central como copia.
A