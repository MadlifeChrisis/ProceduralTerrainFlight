#include "Terrain.h"

Terrain::Terrain()
{
	

	float width = 100.0f;
	cols = 50;
	rows = 50;
	float scale = width / rows;
	
	for (int y = 0; y < rows; y++) {
		 
		for (int x = 0; x < cols; x++) {

			terrainPositions[(x * 3) + (y * cols * 3)	 ] = x * scale;
			terrainPositions[(x * 3) + (y * cols * 3) + 1] = y * scale;
			terrainPositions[(x * 3) + (y * cols * 3) + 2] = (pn->noise(float(x) / 4.0f, float(y) / 4.0f, 0.0f)) * 10.0f;

			
			/*
			terrainPositions[(x * 3) + (y * cols * 3) + 2] = (float(std::rand()) / (RAND_MAX/ 2 ));
			std::cout << "Array index " << (x * 3) + (y * cols * 3) << ": " << terrainPositions[(x * 3) + (y * cols * 3)] << std::endl;
			std::cout << "Array index " << (x * 3) + (y * cols * 3) + 1 << ": " << terrainPositions[(x * 3) + (y * cols * 3) + 1] << std::endl;
			std::cout << "Array index " << (x * 3) + (y * cols * 3) + 2 << ": " << terrainPositions[(x * 3) + (y * cols * 3) + 2] << std::endl;
			*/
			perlinX = float(x) / 4.0f;
		}
		
		perlinY = float(y) / 4.0f;
	}


	int arrayOffset = 6 * (cols - 1);

	for (int k = 0; k < cols - 1; k++) {

		for (int i = 0; i < rows -1; i++) {

			terrainIndices[0 + (6 * i) + (k * arrayOffset)] = 0					+ (cols * i) + k;
			terrainIndices[1 + (6 * i) + (k * arrayOffset)] = 1					+ (cols * i) + k;
			terrainIndices[2 + (6 * i) + (k * arrayOffset)] = cols				+ (cols * i) + k;
			terrainIndices[3 + (6 * i) + (k * arrayOffset)] = 1					+ (cols * i) + k;
			terrainIndices[4 + (6 * i) + (k * arrayOffset)] = cols				+ (cols * i) + k;
			terrainIndices[5 + (6 * i) + (k * arrayOffset)] = 1 + cols			+ (cols * i) + k;

		}

	}

	/*
	for (int l = 0; l < terrainIndexCount; l++) {
		std::cout << "Index: " << l << " Value: " << terrainIndices[l] << std::endl;
	}

	*/

	
}

Terrain::~Terrain()
{
}
void Terrain::update()
{
	// Shift values down
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			terrainPositions[(x * 3) + (y * cols * 3) + 2] = terrainPositions[(x * 3) + ((y + 1) * cols * 3) + 2];
		}
	}

	// Generate new
	for (int k = 0; k < rows; k++) {

		for (int i = 0; i < cols; i++) {
			terrainPositions[(i * 3) + ((rows - 1) * cols * 3) + 2] = (pn->noise((perlinX) , (perlinY) , 0.0f)) * 9.0f;
			perlinX += 0.15f;
		}
		perlinY += 0.2f;
	}
	
}


/*
void Terrain::update()
{
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			terrainPositions[(x * 3) + (y * cols * 3) + 2] = terrainPositions[(x * 3) + ((y + 1) * cols * 3) + 2];	
		}
	}

	int wasPositive = 1;
	float decision = 0.0f;
	float randIncrement = (((float(std::rand()) / (RAND_MAX / 2)) - 1.0f));

	for (int i = 0; i < cols; i++) {
	
		
		if (randIncrement < 0) {
			wasPositive = -1;
		}
		else {
			wasPositive = 1;
		}

		// Lower bound
		if (terrainPositions[(i * 3) + ((rows - 1) * cols * 3) + 2] < -20) {
			terrainPositions[(i * 3) + ((rows - 1) * cols * 3) + 2] += abs(randIncrement);

		}
		// Upper bound
		else if(terrainPositions[(i * 3) + ((rows - 1) * cols * 3) + 2] > 20) {
			terrainPositions[(i * 3) + ((rows - 1) * cols * 3) + 2] += -abs(randIncrement);

		}
		// in between
		else {
			terrainPositions[(i * 3) + ((rows - 1) * cols * 3) + 2] += randIncrement;

		}
		
		randIncrement = (((float(std::rand()) / (RAND_MAX / 3)) - 1.5f));

		if ( (float(std::rand()) / RAND_MAX) < 0.8f ) {
			randIncrement = wasPositive * abs(randIncrement);
		}

	}
	
}
*/

void Terrain::render(Renderer renderer, Shader shader)
{
	
	// VAO
	VertexArray va;

	//Buffer objects
	VertexBuffer vb(terrainPositions, terrainVertexCount * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(3);

	va.addBuffer(vb, layout);
	IndexBuffer ib(terrainIndices, terrainIndexCount);


	shader.setUniform4f("uColor", 0.8f, 0.8f, 0.8f, 1.0f);

	renderer.drawTriangle(va, ib, shader);

	//renderer.drawPoint(va, ib, shader);
}
