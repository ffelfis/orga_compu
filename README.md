# Organización del computador

## QEMU

En una carpeta bajar los paquetes necesarios con los comandos:

`user@user-PCName:~/qemu_dir$ wget https://people.debian.org/~jcowgill/qemu-mips/debian-stretch-mips.qcow2`

`user@user-PCName:~/qemu_dir$ wget https://people.debian.org/~jcowgill/qemu-mips/initrd.img-4.9.0-4-5kc-malta.mips.stretch`

`user@user-PCName:~/qemu_dir$ wget https://people.debian.org/~jcowgill/qemu-mips/vmlinux-4.9.0-4-5kc-malta.mips.stretch`

También conviene agregar en la misma carpeta el archivo `start_qemu.sh`.

## Apagar la máquina virtual

En la máquina virual (no desde una terminal local) ejecutar el comando:

`# shutdown -h now`

## Desconexión de terminal local para máquina virtual

Desde cualquier directorio de la máquina virtual:

`# logout`

## Copia de archivos

Desde la máquina local. Para copiar un archivo desde la máquina remota, la emulada por QEMU, hacia la máquina local:

`$ scp -P 5555 root@localhost:/root/<directorio_fuente>/ejemplo.txt /home/<usuario>/<directorio_destino>/`

Desde la máquina local. Para copiar un archivo desde la máquina local hacia la máquina emulada:

`$ scp -P 5555 ejemplo.txt root@localhost:/root/<directorio_destino>/`

En este caso, esto funciona si  el archivo `ejemplo.txt` se encuentra en el direcorio desde el cual se ejecutan los comandos.
