#include <stdint.h>
#include <stdio.h>
#include <cstdlib>
#include <assert.h>
#include <glut/glut.h>
#include <memory.h>
#include <iostream>

#include "ClosedList.h"
#include "OpenList.h"
#include "SearchNode.h"
#include "SearchLevel.h"
// Function prototypes
void plasmaTest();
void drawLevel();

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Global variables

// OpenGL texture ids for rendering.
GLuint  inputTexture = 0;
GLuint  outputTexture = 0;
// Input and output data in pixels. outputData is updated to outputTexture each frame
uint8_t* inputData = 0;
uint8_t* outputData = 0;
// width and height of the input and output datas
int levelWidth = 0;
int levelHeight = 0;
// start and end position for path finding. These are found automatically from input file.
int startX = -1;
int startY = -1;
int endX = -1;
int endY = -1;

SearchLevel searchLevel;
ClosedList closedList;
OpenList openList;
// current node beign evaluated
//SearchNode* current = nullptr;
//SearchNode* whyUnoWork = nullptr;

bool isPathFound = false;
bool isPathingStarted = false;
bool isDone = false;


namespace
{
	// Sets a pixel of rgb color into memory
	void setPixel(uint8_t* data, int x, int y, int width, int height, uint8_t r, uint8_t g, uint8_t b)
	{
		uint8_t* pixel = &data[3 * (y*width + x)];
		pixel[0] = b;
		pixel[1] = g;
		pixel[2] = r;
		
	}

	double dist(double a, double b, double c, double d) { // pythagorian distance
		return sqrt(double((a - c) * (a - c) + (b - d) * (b - d)));
	}
	// STUDENT_TODO: Make implementation for doPathFinding function, which writes found path to outputData
	/*
		A(*) algorithm
		
		Init:
		1. create open and closed list and search level data
		2. create pointer to current node beign evaluated
		3.add start position to open list

		algorithm:
		1. make current the node with the lowest F in the open list
		2. move current from open list to closed list
		3. if the current is the goal, break the loop for the path has been found. 

		4. get current nodes adjacent nodes
		5. for each neighbor:
			(i) if the neighbor is in the closed list -> ignore it
			(ii) if the neighbor is not in the open list -> add it to open list
			(iii) if the neighbor is in the open list
					-> check if current.G + neighbor.H < neighbor.F 
					true: update neigbor.F and reparent it to current. 
					false: ignore


	*/
	void doPathFinding(int startX, int startY, int endX, int endY)
	{
		//printf("STUDENT_TODO: Do path finding from <%d,%d> to <%d,%d>\n", startX, startY, endX, endY);
	
		// copy input data to output data
		//memcpy(outputData, inputData, 3 * width*height);

		

		SearchNode* current = nullptr;

		// if pathfinding has not yet been started, insert the first node to open list
		if (!isPathingStarted)
		{
			// add start position to open list, set f to 0.
			SearchNode* start = new SearchNode(Position(startX, startY), dist(startX, startY, endX, endY), 0.0f, nullptr);
			openList.insertToOpenList(start);
			isPathingStarted = true;
		}

		

		// A* star pathfinding - main loop
		if (!openList.isEmpty() && !isPathFound)
		{
			// clear the left side
			memcpy(outputData, inputData, 3 * levelWidth*levelHeight);

			// sort the open list
			openList.sortOpenList();

			current = openList.RemoveSmallestFFromOpenList();
			// add the node with smallest f to closed list. 
			closedList.addToClosedList(current);

			if (current->prevNode != nullptr) {

				assert(current->prevNode->pos.first >= 0 && current->prevNode->pos.first < 1000);
				assert(current->prevNode->pos.second >= 0 && current->prevNode->pos.second < 1000);
			}


			// coloring here
			///////////////////////////////////////////

			// color open list nodes magenta
			for (auto itr : openList.getList())
			{
				setPixel(outputData, itr->pos.first, itr->pos.second, levelWidth, levelHeight, 126, 0, 126);
			}

			// color closed lists according to F
			for (auto itr : closedList.getList()) {
				/*
				setPixel(outputData, itr.first.first, itr.first.second, levelWidth, levelHeight,
					(itr.second->getF() / (levelWidth+levelHeight + 256)) * 126.0f, 
					(itr.second->getF() / (levelWidth+levelHeight + 256)) * 256.0f,
					(itr.second->getF() / (levelWidth+levelHeight + 256)) * 64.0f
				);
				*/
				
				setPixel(outputData, itr.first.first, itr.first.second, levelWidth, levelHeight,
					itr.second->getF() ,
					itr.second->G,
					itr.second->H
				);
			}

			// color current node yellow
			setPixel(outputData, current->pos.first, current->pos.second, levelWidth, levelHeight, 255, 255, 0);

			// if the current node is the goal
			if (current->pos.first == endX && current->pos.second == endY)
			{
				// path found, set flag
				isPathFound = true;
			}

			//////////////////////////////////////////

			if (!isPathFound) // check the neighbors only if the path has not been found yet
			{

				// find current nodes walkable neighbors 
				auto neighbors = searchLevel.getAdjacentNodes(current->pos.first, current->pos.second);
				
				for (auto n_itr : neighbors)
				{
					// is neighbor in closed list
					if (closedList.isInClosedList(n_itr))
					{
						continue; // to next neighbor
					}

					// neighbor is not in open list
					if (!openList.isInOpenList(n_itr))
					{
						// push into openlist
						openList.insertToOpenList(new SearchNode(
							n_itr,
							SearchLevel::manhattanDist(n_itr.first, n_itr.second, endX, endY),
							SearchLevel::euclideanDist(current->pos.first, current->pos.second, n_itr.first, n_itr.second),
							current
						));
						printf("**added to openlist**: %d\n\n", openList.getList().size());

					}
					// neighbor is in open list
					else
					{
						/*
						->check if current.G + neighbor.H < neighbor.F
						true: update neigbor.F and reparent it to current.
						false : ignore and go to next neighbor
						*/
						auto evaluateThis = openList.findFromOpenList(n_itr);
						if ((current->G + evaluateThis->H) < evaluateThis->getF())
						{
							evaluateThis->resetPrev(current, 1.0f);
						}
						else
						{
							continue; // go to next neighbor
						}
					}
				}

			}
		}
		// A* star pathfinding - end loop

		if (openList.isEmpty() && isPathingStarted)
		{
			printf("No path found \n");
		}
		
		// traverse the path and set path pixels. 
		if (isPathFound && !isDone)
		{
			// clear the left side
			//memcpy(outputData, inputData, 3 * levelWidth*levelHeight);

			// ERROR: Eternally looping, prev node pointing doesn't work
			do { 
				// color the current node black
				setPixel(outputData, current->pos.first, current->pos.second, levelWidth, levelHeight, 0, 20, 0);
				// make current point to previous node
				assert(current != current->prevNode);
				current = current->prevNode;
			} while (current != nullptr); // do, until we point to the start node, which has no parent

			isDone = true; // if done, just draw
		}
	}
};


namespace
{
	// Quick and dirty function for reading bmp-files to opengl textures.
	GLuint loadBMPTexture(const char *fileName, int* w, int* h, uint8_t** data)
	{
		assert(w != 0);
		assert(h != 0);
		assert(data != 0);
		FILE *file;
		if ((file = fopen(fileName, "rb")) == NULL)
			return 0;
		fseek(file, 18, SEEK_SET);

		int width = 0;
		fread(&width, 2, 1, file);
		fseek(file, 2, SEEK_CUR);
		int height = 0;
		fread(&height, 2, 1, file);
		printf("Image \"%s\" (%dx%d)\n", fileName, width, height);

		*data = new uint8_t[3 * width * height];
		assert(data != 0);
		fseek(file, 30, SEEK_CUR);
		fread(*data, 3, width * height, file);
		fclose(file);

		GLuint  texId;
		glGenTextures(1, &texId);
		glBindTexture(GL_TEXTURE_2D, texId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, *data);
		glBindTexture(GL_TEXTURE_2D, 0);
		if (w) *w = width;
		if (h) *h = height;
		return texId;
	}

	

	// Initialization
	bool init()
	{
		glMatrixMode(GL_PROJECTION);
		
		glOrtho(0, 512 + 4, 256 + 2, 0, -1, 1); //for original input
		//glOrtho(0, 128 + 4, 64 + 2, 0, -1, 1);

		// Load input file
		inputTexture = loadBMPTexture("input.bmp", &levelWidth, &levelHeight, &inputData);
		if (0 == inputTexture)
		{
			printf("Error! Cannot open file: \"input2.bmp\"\n");
			return false;
		}

		// Make outputTexture
		glGenTextures(1, &outputTexture);
		glBindTexture(GL_TEXTURE_2D, outputTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (searchLevel.init(inputData, levelWidth, levelHeight ))
		{
			printf("failed to init searchlevel\n");
		}

		// Copy inputData also to outputData
		outputData = new uint8_t[3 * levelWidth*levelHeight];
		memcpy(outputData, inputData, 3 * levelWidth*levelHeight);

		// find start and end
		for (int y = 0; y < levelHeight; ++y)
		{
			for (int x = 0; x < levelWidth; ++x)
			{
				uint8_t* pix = &inputData[3 * (y*levelWidth + x)]; // get pixel
				uint8_t r = pix[0];
				uint8_t g = pix[1];
				uint8_t b = pix[2];
				if (255 == r && g == 0 && b == 0) // Red?
				{
					// Start
					startX = x;
					startY = y;
					printf("Start position: <%d,%d>\n", x, y);
				}
				if (255 == b && r == 0 && g == 0) // Blue?
				{
					// End
					endX = x;
					endY = y;
					printf("End position: <%d,%d>\n", x, y);
				}
			}
		}

		if (startX < 0 || startY < 0)
		{
			printf("Error! Start position not found\n");
			return false;
		}

		if (endX < 0 || endY < 0)
		{
			printf("Error! End position not found\n");
			return false;
		}
		
		return true;
	}

	// Draw/Render
	void draw()
	{
		// clear the output data
		//memset(outputData, 0, 3 * width*height);
		
		// Run plasmatest

		// draw the level 
		doPathFinding(startX, startY, endX, endY);

		drawLevel();
	}
} // end - anonymous namespace


  // Main
int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(2 * (512 + 4), 2 * (256 + 2));
	glutCreateWindow("Pathfinding Demo");
	glutDisplayFunc(draw);
	if (!init()) return -1;
	glutMainLoop();
	delete inputData;
	delete outputData;
	return 0;
}

void plasmaTest() {

	// PLASMA TEST ///////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////

	static double time = 10.0;

	time += 0.5;
	for (int y = 0; y < levelHeight; y++)
		for (int x = 0; x < levelWidth; x++)
		{
			double value = sin(dist(x + time, y, 128.0, 128.0) / 8.0)
				+ sin(dist(x, y, 64.0, 64.0) / 8.0)
				+ sin(dist(x, y + time / 7, 192.0, 64) / 7.0)
				+ sin(dist(x, y, 192.0, 100.0) / 8.0);
			int color1 = int((4 + value)) * 32;

			value = sin(dist(x + time + 1.0, y, 128.0, 128.0) / 8.0)
				+ cos(dist(x, y, 64.0, 64.0) / 8.0)
				+ sin(dist(x, y + time + 1.0 / 7, 192.0, 64) / 7.0)
				+ cos(dist(x, y, 192.0, 100.0) / 8.0);
			int color2 = int((4 + value)) * 32;

			value = cos(dist(x + time + 1.0, y, 128.0, 128.0) / 8.0)
				+ cos(dist(x, y, 64.0, 64.0) / 8.0)
				+ cos(dist(x, y + time + 1.0 / 7, 192.0, 64) / 7.0)
				+ cos(dist(x, y, 192.0, 100.0) / 8.0);
			int color3 = int((4 + value)) * 32;

			setPixel(outputData, x, y, levelWidth, levelHeight, color1, color2, color3);
		}
}
// Plasma Test end /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void drawLevel()
{
	// Copy outputData to outputTexture
	glBindTexture(GL_TEXTURE_2D, outputTexture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, levelWidth, levelHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, outputData);
	glBindTexture(GL_TEXTURE_2D, 0);

	glClear(GL_COLOR_BUFFER_BIT);

	// Draw input texture to left half of the screen
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, inputTexture);
	glBegin(GL_QUADS);
	
	glTexCoord2d(0, 1); glVertex2d(1, 1);
	glTexCoord2d(0, 0); glVertex2d(1, 1 + (levelHeight * 2));
	glTexCoord2d(1, 0); glVertex2d(1 + (levelWidth * 2), 1 + (levelHeight * 2));
	glTexCoord2d(1, 1); glVertex2d(1 + (levelWidth * 2), 1);
	/*
	glTexCoord2d(0, 1); glVertex2d(1, 1);
	glTexCoord2d(0, 0); glVertex2d(1, 1);
	glTexCoord2d(1, 0); glVertex2d(1 + 64, 1 + 64);
	glTexCoord2d(1, 1); glVertex2d(1 + 64, 1);
	*/
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Draw output texture to right half of the screen
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, outputTexture);
	glBegin(GL_QUADS);
	
	glTexCoord2d(0, 1); glVertex2d(2 + (levelWidth * 2), 1);
	glTexCoord2d(0, 0); glVertex2d(2 + (levelWidth * 2), 1 + (levelHeight * 2));
	glTexCoord2d(1, 0); glVertex2d(2 + (levelWidth * 4), 1 + (levelHeight * 2));
	glTexCoord2d(1, 1); glVertex2d(2 + (levelWidth * 4), 1);
	/*
	glTexCoord2d(0, 1); glVertex2d(2 + 64, 1);
	glTexCoord2d(0, 0); glVertex2d(2 + 64, 1 + 64);
	glTexCoord2d(1, 0); glVertex2d(2 + 128, 1 + 64);
	glTexCoord2d(1, 1); glVertex2d(2 + 128, 1);
	*/
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}