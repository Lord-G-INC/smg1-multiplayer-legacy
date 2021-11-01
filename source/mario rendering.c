#include <defines.h>

const u32 textColor = DecToColor(100, 100, 100, 0xFF);


u32* model = 1;
Vector3f position = { 1, 1, 1 };
float rotation[3] = { 0, 0, 90 };
float velocityY = 1.0f;
short* PAD1 = 0x8039d400;
u32* texture = 1;

#define DPP_RETURN_SUCCESS 0x80000000
/* int DrawPlugPiki()
{
	// Set the colour of the text before printing
	DGXGraphics__setColour(ADDR_GFX, &textColor, 1);
	// Print "hello! 122" to showcase variadic argument printing at the (X, Y) position of 50, 50
	PrintText(50, 50, "hello! %d", 122);

	// This is required to show that 
	return DPP_RETURN_SUCCESS;
} */

int LoadMeeoCube(u32 unk) {
//	texture = loadTexture((*(u32**)(SDA + 0x2DEC)), "MEEO.txe", 1);
	return unk; // do not erase
}
void UpdateMeeoCube(u32 data) {
	controlMario();
	renderMario(data);
}

void controlMario() {
	float moveSpeed = 8.0f;
	u32* controller = getNavi((*(u32**)(SDA + 0x3120)), 0);
	controller = controller[0x2e4 / 4];

	position.z += -getMainStickY(controller) * moveSpeed;
	position.x +=  getMainStickX(controller) * moveSpeed;
	position.y += velocityY; 

	if (getMinY((*(u32**)(SDA + 0x2f00)), position.x, position.z) < position.y) {
		velocityY -= 0.5f;
	}
	else {
		velocityY = 0;
	}
	if (PAD1[0] == 0x0100) {
		velocityY = 8;
	}
}

void renderMario(u32 data) {
	if (texture == 1) {
		texture = loadTexture((*(u32**)(SDA + 0x2DEC)), "MEEO.txe", 1);
	}
	char matrix[0x100];
	Vector3f scale = { 2.0f, 2.0f, 2.0f };
	makeSRT(matrix, &scale, rotation, &position);
	//GXLoadTexObj(texture[0x24 / 4], 0);
	GXLoadPosMtxImm(matrix, 0);
	draw_P2DWindowTexture(&texture, 0, 0, 0, (*(short*)(texture + 0x8 / 4)), (*(short*)(texture + 0xa / 4)), 0x8000, 0x8000);	
}

/*
void renderMario(u32 data) {
	if (model == 1) {
		//model = loadShape(0, "objects/rocket/mario.mod", 1);
		model = loadShape(0, "pikis/kinModel.mod", 1);
	}

	// model rendering section THIS WORKS!
	u32* unk = (*(u32**)(SDA + 0x2E34));
	Vector3f scale = { 2.0f, 2.0f, 2.0f };

	if (position.x == 1) {
		float* navi = getNavi((*(u32**)(SDA + 0x3120)), 0);
		position.x = navi[0x94 / 4]; position.y = navi[0x98 / 4]; position.z = navi[0x9c / 4];
	}

	char _[0x100];
	makeSRT(_, &scale, rotation, &position);
	useMatrix(unk, 0x80398840, 0);
	char _a[0x100];
	PSMTXConcat(unk[0x2e4 / 4] + 0x1e0, _, _a);

	updateAnim(model, unk, _a, 0);
	drawshape(model, unk, unk[0x2e4 / 4], 0);
};
*/
