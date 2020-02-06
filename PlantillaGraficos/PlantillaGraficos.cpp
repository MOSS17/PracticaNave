// PlantillaGraficos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

// Declarar una ventana y variables
GLFWwindow* window;
float posXTriangulo = 0.0f, posYTriangulo = 0.0f;
float rotacionTriangulo = 0.0f;
double tiempoActual, tiempoAnterior;
double velocidadTriangulo = 0.7;
double velocidadRotacion = 60;

void teclado_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS || GLFW_REPEAT && key == GLFW_KEY_RIGHT) {
		posXTriangulo += 0.01;
	}

	if (action == GLFW_PRESS || GLFW_REPEAT && key == GLFW_KEY_LEFT) {
		posXTriangulo -= 0.01;
	}
	if (action == GLFW_PRESS || GLFW_REPEAT && key == GLFW_KEY_UP) {
		posYTriangulo += 0.01;
	}
	if (action == GLFW_PRESS || GLFW_REPEAT && key == GLFW_KEY_DOWN) {
		posYTriangulo -= 0.01;
	}
}

void actualizar() {
    tiempoActual = glfwGetTime();
    // Sacamos el DeltaTime
    double tiempoDiferencial = tiempoActual - tiempoAnterior;

    // Estados para cada tecla
	// Calcular el movimiento dependiendo del angulo de rotacion
    int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
    if (estadoArriba == GLFW_PRESS) {
		posYTriangulo += (velocidadTriangulo * sin((rotacionTriangulo + 90.0) * 3.1416 / 180)) * tiempoDiferencial;
		posXTriangulo += (velocidadTriangulo * cos((rotacionTriangulo + 90.0) * 3.1416 / 180)) * tiempoDiferencial;
    }

	int estadoAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoAbajo == GLFW_PRESS) {
		posYTriangulo -= (velocidadTriangulo * sin((rotacionTriangulo + 90.0) * 3.1416 / 180)) * tiempoDiferencial;
		posXTriangulo -= (velocidadTriangulo * cos((rotacionTriangulo + 90.0) * 3.1416 / 180)) * tiempoDiferencial;
	}

	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoIzquierda == GLFW_PRESS) {
		rotacionTriangulo += velocidadRotacion * tiempoDiferencial;
	}

    int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
    if (estadoDerecha == GLFW_PRESS) {
		rotacionTriangulo -= velocidadRotacion * tiempoDiferencial;
    }

	// Reset angulo
	if (rotacionTriangulo >= 360) {
		rotacionTriangulo = 0;
	}

	if (rotacionTriangulo <= -360) {
		rotacionTriangulo = 0;
	}

    tiempoAnterior = tiempoActual;
}

void dibujar() {
	glPushMatrix();
	
	// Loopear al triangulo al llegar limite de la ventana
	if (posXTriangulo >= 1.15) {
		posXTriangulo = -1.1;
	}
	if (posXTriangulo <= -1.15) {
		posXTriangulo = 1.1;
	}

	if (posYTriangulo >= 1.15) {
		posYTriangulo = -1.1;
	}
	if (posYTriangulo <= -1.15) {
		posYTriangulo = 1.1;
	}

	glTranslatef(posXTriangulo, posYTriangulo, 0.0f);

	glRotatef(rotacionTriangulo, 0, 0, 1);  // rotate your object
	glScalef(0.4f, 0.7f, 0.0f);

	glBegin(GL_TRIANGLES);

	glColor3f(0.2f, 0.3f, 0.6f);

	glVertex3f(0.0f, 0.15f, 0.0f);
	glVertex3f(0.15f, -0.15f, 0.0f);
	glVertex3f(-0.15f, -0.15f, 0.0f);

	glEnd();

	glPopMatrix();
}

int main()
{

	// Si no se pudo iniciar GLFW
	// Terminamos ejecución
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	// Si se pudo iniciar GLFW
	// Inicializamos la ventana
	window = glfwCreateWindow(600, 600, "Ventana", NULL, NULL);

	// Si no se pudo crear la ventana
	// Terminamos la ejecución
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Establecemos la ventana como contexto
	glfwMakeContextCurrent(window);

	// Una vez establecido el contexto
	// Se activan las funciones "modernas" (gpu)
	glewExperimental = true;

	GLenum errores = glewInit();
	if (errores != GLEW_OK) {
		glewGetErrorString(errores);
	}

	const GLubyte* versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	// Establecemos que con cada evento de teclado se llama a la función teclado_callback
	// glfwSetKeyCallback(window, teclado_callback);

	// Ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		// Establecer región de dibujo
		glViewport(0, 0, 600, 600);
		// Establecemos el color de borrado
		// Valores RGBA
		glClearColor(1, 0.2, 0.5, 1);
		// Borrar!
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Actualizar valores y dibujar		
		actualizar();
		dibujar();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	// Después del ciclo de dibujo
	// Eliminamos ventana y procesos de glfwr
	glfwDestroyWindow(window);
	glfwTerminate();
}
