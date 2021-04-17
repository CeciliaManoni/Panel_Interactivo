# Panel_Interactivo

El panel interactivo es una herramienta lúdica desarrollada para formar parte de una Sala Multisensorial.

Está integrada por un *panel*, o componente principal, y dos accesorios: *colchoneta* y *tablero*.

### Panel
Es el componente principal de la herramienta debido a que se encarga de procesar la información
que proviene de los accesorios y ejecutar la acción de respuesta correspondiente de acuerdo al modo de 
funcionamiento seleccionado en la configuración.

![image](https://user-images.githubusercontent.com/71729076/115129402-edaa6500-9fbb-11eb-8d93-c477bec4cb93.png)

### Colchoneta
Está constituida por un soporte de madera, ubicado en el suelo, que cuenta con la siguiente distribución:

![image](https://user-images.githubusercontent.com/71729076/115129449-67dae980-9fbc-11eb-8528-989a0f2b0501.png)

Cada cuadrado es del mismo tamaño, de diferente color y posee dos sensores conectados en serie. Cuando el usuario pisa uno 
de ellos se envía una señal al panel, y como consecuencia se enciende o apaga una de sus luces LED y se reproduce un sonido.

### Tablero
Este accesorio también trata de un soporte de madera con seis cuadrados de diferentes colores que representan
pulsadores. La diferencia entre los accesorios es su tamaño, así, el tablero presenta un tamaño reducido 
donde los cuadrados son de 8x8cm cada uno. Esto permite que el paciente pueda colocar-lo sobre alguna superficie
y presionarlo con la mano.

![image](https://user-images.githubusercontent.com/71729076/115129520-239c1900-9fbd-11eb-939e-5a408240cfb7.png)

## Modos de funcionamiento
Se encuentran dos modos de funcionamiento disponibles *Sonidos* y *Simon Dice*.

![image](https://user-images.githubusercontent.com/71729076/115129390-dc615880-9fbb-11eb-864d-9f69c2eae9f6.png)

### Sonidos
Si la configuración elegida contiene el modo Sonidos el usuario deberá presionar los pulsadores de la colchoneta
o del tablero y como consecuencia se prenderán luces del panel y, al mismo tiempo, se reproducirá el sonido de 
un animal (vaca, gato, perro, pato, gallo o cerdo) dependiendo de qué pulsador se está presionando.

![image](https://user-images.githubusercontent.com/71729076/115129570-855c8300-9fbd-11eb-9e51-144aaed60a89.png)

### Simón Dice
Si la configuración elegida contiene el modo Simón Dice se va a presentar una secuencia de luces y sonidos en
el panel que el usuario deberá repetir en la colchoneta o en el tablero. En este caso los sonidos son los
correspondientes a los de un teclado numérico.

La secuencia comienza desde el Nivel 1, brindando la posibilidad de que el paciente repita un solo color, 
y llega hasta el Nivel 10, con una secuencia de diez (10) colores. A medida que se van produciendo aciertos en
cada partida, la secuencia de colores se vuelve cada vez más larga y se van produciendo itera-ciones entre la 
respuesta del paciente en el accesorio y la ejecución del juego en el panel.

A continuación, se muestra el diagrama de flujo que lo representa:

![image](https://user-images.githubusercontent.com/71729076/115129597-dc625800-9fbd-11eb-9180-08836022846d.png)

