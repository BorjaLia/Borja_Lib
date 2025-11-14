#include "BorjaLib.h" // Incluimos la cabecera principal

namespace cam
{
	Camera mainCamera;

	void Init(vec::Vector2 startPos, float startZoom, float startRotation)
	{
		mainCamera.pos = startPos;
		mainCamera.zoom = startZoom;
		mainCamera.rotation = startRotation;
	}

	void Move(vec::Vector2 amount)
	{
		mainCamera.pos += amount;
	}

	void Zoom(float amount)
	{
		float newZoom = mainCamera.zoom + amount;
		if (newZoom < 0.01f) {
			newZoom = 0.01f;
		}
		mainCamera.zoom = newZoom;
	}

	void Rotate(float degrees)
	{
		mainCamera.rotation += degrees;
	}

	void SetPosition(vec::Vector2 newPos)
	{
		mainCamera.pos = newPos;
	}

	void SetZoom(float newZoom)
	{
		if (newZoom < 0.01f) {
			newZoom = 0.01f;
		}
		mainCamera.zoom = newZoom;
	}

	void SetRotation(float newRotation)
	{
		mainCamera.rotation = newRotation;
	}

	vec::Vector2 WorldToScreen(vec::Vector2 worldPos)
	{
		// 1. Calcular el offset del punto relativo al centro de la cámara
		vec::Vector2 offset = worldPos - mainCamera.pos;

		// 2. Aplicar la rotación INVERSA de la cámara
		// Si la cámara rota +10, el mundo rota -10 alrededor de ella
		// (Asumo que tu vec::Vector2 tiene este método)
		offset = offset.rotatedDegree(-mainCamera.rotation);

		// 3. Definir el "tamaño de la vista" de la cámara.
		// Esta es la parte clave:
		// El eje Y (0-1) es nuestra referencia.
		// viewHeight = 1.0f -> significa que el zoom es 1.0f
		// viewHeight = 0.5f -> significa que el zoom es 2.0f (ves la mitad)
		float viewHeight = 1.0f / mainCamera.zoom;
		float viewWidth = viewHeight * rend::windowRatio; // Asumimos que rend::windowRatio está actualizado

		// 4. Normalizar el offset.
		// Convertimos el offset del mundo (ej: {50, 20})
		// a un offset normalizado (ej: {0.1, 0.05})
		vec::Vector2 normalizedOffset = { 0.0f, 0.0f };
		if (viewWidth != 0) {
			normalizedOffset.x = offset.x / viewWidth;
		}
		if (viewHeight != 0) {
			normalizedOffset.y = offset.y / viewHeight;
		}

		// 5. Añadir el offset normalizado al centro de la pantalla (0.5, 0.5)
		return { 0.5f + normalizedOffset.x, 0.5f + normalizedOffset.y };
	}

	vec::Vector2 ScreenToWorld(vec::Vector2 screenPos)
	{
		// Esta es la operación inversa exacta de WorldToScreen

		// 1. Convertir la posición de pantalla (0-1) a un offset normalizado (-0.5 a +0.5)
		vec::Vector2 normalizedOffset = { screenPos.x - 0.5f, screenPos.y - 0.5f };

		// 2. Definir el "tamaño de la vista" (igual que antes)
		float viewHeight = 1.0f / mainCamera.zoom;
		float viewWidth = viewHeight * rend::windowRatio;

		// 3. "Des-normalizar" el offset: escalarlo de vuelta a unidades de mundo
		vec::Vector2 offset = { normalizedOffset.x * viewWidth, normalizedOffset.y * viewHeight };

		// 4. Aplicar la rotación NORMAL de la cámara
		offset = offset.rotatedDegree(mainCamera.rotation);

		// 5. Añadir el offset del mundo al centro de la cámara
		return mainCamera.pos + offset;
	}

	vec::Vector2 GetWorldToScreenSize(vec::Vector2 worldSize)
	{
		// Esto es solo una operación de escalado. No le afecta la posición
		// de la cámara ni (generalmente) su rotación.

		// 1. Calculamos el factor de escala X e Y
		// (Cuánto del mundo es visible)
		float viewHeight = 1.0f / mainCamera.zoom;
		float viewWidth = viewHeight * rend::windowRatio;

		// 2. Calculamos el tamaño de pantalla
		// screenSize.y = worldSize.y / viewHeight
		// screenSize.x = worldSize.x / viewWidth
		vec::Vector2 screenSize = { 0.0f, 0.0f };
		if (viewWidth != 0) {
			screenSize.x = worldSize.x / viewWidth;
		}
		if (viewHeight != 0) {
			screenSize.y = worldSize.y / viewHeight;
		}

		return screenSize;

		/*
		// Alternativa más simple (basada en la lógica de ScreenToWorldSize):
		float scaleX = mainCamera.zoom / rend::windowRatio;
		float scaleY = mainCamera.zoom;
		return { worldSize.x * scaleX, worldSize.y * scaleY };
		*/
	}

	vec::Vector2 GetScreenToWorldSize(vec::Vector2 screenSize)
	{
		// La operación inversa de la anterior

		// 1. Calcular el tamaño de la vista
		float viewHeight = 1.0f / mainCamera.zoom;
		float viewWidth = viewHeight * rend::windowRatio;

		// 2. Escalar el tamaño de pantalla a tamaño de mundo
		// worldSize.y = screenSize.y * viewHeight
		// worldSize.x = screenSize.x * viewWidth
		return { screenSize.x * viewWidth, screenSize.y * viewHeight };
	}

} // fin del namespace cam