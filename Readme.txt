Para compilar el proyecto en VisualStudio:
En propiedades
	En C/C++->General incluir en Directorios adiocionales:
		$(SolutionDir)Dependencies\GLFW\include
		$(SolutionDir)Dependencies\GLM
		$(SolutionDir)Dependencies\GLEW\include
		$(SolutionDir)Dependencies
	(*Nota: Tuve problemas para usar mis propias clases en el
	 proyecto de Visual Studio por eso en la Carpeta Dependencies
	 tengo una copia de las clases y sus cabeceras en ese lugar)

	En Vinculador->General incluir en Directorios de bibliotecas adicionales:
		$(SolutionDir)Dependencies\GLEW\lib\Release\Win32
		$(SolutionDir)Dependencies\GLFW\lib-vc2015

	En Vinculador->Entrada verificar en Dependencias adicionales que esten:
		glew32s.lib
		opengl32.lib
		glfw3.lib
		User32.lib
		Gdi32.lib
		Shell32.lib

Con estas configuraciones se debe leer las librerias de GLFW, GLM y GLEW para
poder compilar y ejecutar el proyecto. De preferencia usar el Depurador Local
de Windows. 
(*Nota: en cierta ocasion tuve que deshabilitar temporalmente mi antivirus para poder ejecutar
 mi proyecto)


Controles:

W-Adelante
S-Atras
A-Izquierda
D-Derecha
UP_ARROW-Arriba
DOWN_ARROW-Abajo
[ESC]-Cerrar ventana


Las referencias usadas fueron:

The Cherno:
https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2
Para configurar OpenGL y GLEW en el proyecto de Visual y una introducción 
a OpenGL.

Sonar Systems:
https://www.youtube.com/watch?v=vcMox6i8f4Y
Para tener una nocion de como dibujar en 3D y dibujar un cubo
en ese espacio.

PDF's:
https://www.cs.utexas.edu/~theshark/courses/cs354/lectures/cs354-13.pdf
https://courses.cs.washington.edu/courses/csep557/03au/lectures/hierarchical-modeling.pdf
Para entender bien lo de las operaciones undo/rendo de la pila de Matrices.

Curso Udemy:
https://www.udemy.com/course/graphics-with-modern-opengl/
Con este curso tome como base de mi proyecto lo que se programo hasta Texturas.




