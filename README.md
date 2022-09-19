# Organización del computador

## QEMU

En una carpeta bajar los paquetes necesarios con los comandos:

```
$ wget https://people.debian.org/~jcowgill/qemu-mips/debian-stretch-mips.qcow2
```

```
$ wget https://people.debian.org/~jcowgill/qemu-mips/initrd.img-4.9.0-4-5kc-malta.mips.stretch
```

```
$ wget https://people.debian.org/~jcowgill/qemu-mips/vmlinux-4.9.0-4-5kc-malta.mips.stretch
```

También conviene agregar en la misma carpeta el archivo `start_qemu.sh`.

## Encendido de la máquina virtual

En la máquina local, en la carpeta donde se encuentran los archivos descargados anteriormente, ejecutar el comando:

```
$ ./start_qemu.sh
```

## Preparación del sistema guest

Una vez encendida se ingresa con nombre de usuario `root`. Luego de iniciado el sistema ejecutar los siguientes comandos:

```
# dhclient
# apt-get update
# apt-get install gcc
# apt-get install gdb
# apt-get install vim
# apt-get install ssh
```

Ahora se puede asignar una contraseña a `root`.

```
# passwd root
```

Luego se configura el `sshd`.

```
# vim etc/ssh/sshd_config
```

En el final del archivo agregar la línea `PermitRootLogin yes` y reiniciar el servicio de sshd con

```
# service sshd restart
```

## Apagado de la máquina virtual

En la máquina virtual (no desde una terminal local) ejecutar el comando:

`# shutdown -h now`

## Acceso a la máquina guest desde una terminal del sistema host

En una terminal ejecutar:

```
$ ssh root@localhost -p 5555
```

Se pedirá la contraseña asignada a `root`.

## Desconexión de terminal local para máquina virtual

Desde cualquier directorio de la máquina virtual:

```
# logout
```

## Copia de archivos

Desde la máquina local. Para copiar un archivo desde la máquina remota, la emulada por QEMU, hacia la máquina local:

`````
$ scp -P 5555 root@localhost:/root/<ruta_fuente>/ejemplo.txt /home/<usuario>/<ruta_destino>/
`````

Desde la máquina local. Para copiar un archivo desde la máquina local hacia la máquina emulada:

```
$ scp -P 5555 ejemplo.txt root@localhost:/root/<ruta_destino>/
```

En este caso, esto funciona si  el archivo `ejemplo.txt` se encuentra en el directorio desde el cual se ejecutan los comandos.
