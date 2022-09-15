# Organización del computador

## Copia de archivos

Desde la máquina local. Para copiar un archivo desde la máquina remota, la emulada por QEMU, hacia la máquina local:

`$ scp -P 5555 root@localhost:/root/<directorio_fuente>/ejemplo.txt /home/<usuario>/<directorio_destino>/`

Desde la máquina local. Para copiar un archivo desde la máquina local hacia la máquina emulada:

`$ scp -P 5555 ejemplo.txt root@localhost:/root/<directorio_destino>/`

En este caso, esto funciona si  el archivo `ejemplo.txt` se encuentra en el direcorio desde el cual se ejecutan los comandos.
