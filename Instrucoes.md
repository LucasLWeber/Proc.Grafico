# Instrucoes para instalar e configurar ambiente Linux Debian 12

+ Baixar arquivo ISO do Debian 12
+ Usar interface grafica GNOME na VM

## Em sudo
+ Instalar em modo super usuario

``` $ su - ```

``` $ apt install libglew-dev ```

``` $ apt install libglm-dev ```

``` $ apt install libglfw3-dev ```

``` $ apt install g++ ```

**Obs.:** Se necessario comentar a primeira linha do arquivo sources.list no dir /etc/apt

+ Editor de text
``` $ apt install kate ```

+ Git
``` $ apt install git ```
**Obs.:** Se necessario gerar arquivo GLAD no site dav1d.de

---

## Repositorio para referencia
[Prof. Rossana](https://github.com/fellowsheep/PG2024-1/tree/main/HelloTriangle%20-%20SpritesAnimados/HelloTriangle)

- (Source.cpp)[https://github.com/fellowsheep/PG2024-1/blob/main/HelloTriangle%20-%20SpritesAnimados/HelloTriangle/Source.cpp]
- (Sprite.cpp)[https://github.com/fellowsheep/PG2024-1/blob/main/HelloTriangle%20-%20SpritesAnimados/HelloTriangle/Sprite.cpp]

Criar classe sprite para facilitar na reutilizacao e desenhar diversar sprites na tela.
