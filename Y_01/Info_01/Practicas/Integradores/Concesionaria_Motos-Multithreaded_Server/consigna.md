# Consigna general
| Hacer el ABM de una concesionaria de motos con distintas Sucursales (S_i) y una Casa Central (CC).
* Las distintas Sucursales atienden a distintos clientes (multithreaded), guardando datos.
* Es centralizada la base de datos. O sea, siempre la CC tiene una copia de todas las sucursales.
* Se guardan los datos automáticamente cada 1 minuto tanto en CC como en el S_i correspondiente.
	* NO ES BLOQUEANTE.
A
