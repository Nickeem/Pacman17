#pragma once

#pragma warning(disable : 4996)
#pragma comment(lib, "shell32.lib")

#define _USE_MATH_DEFINES

#pragma managed(push, off)
#define generic GenericFromFreeTypeLibrary
#include <cmath>
#include "pngwriter.h"
#include <algorithm>
#include <Windows.h>
#include <string>
#undef generic
#pragma managed(pop)


/*
* done by Nickeem Payne-Deacon 400008889
List of methods used:
laplacian
resize
png_rename
getWidth
getHeight
setText
plot_text
plot_text_blend
close**
filledcircle
circle
polygon
polygon_blend
triangle
filledtriangle
filledtriangel_blend
square
square_blend
filledsquare
filledsquare_blend
arrow
filledarrow
get_text_width
cross
maltesescross
d_read
line
line_blend
diamond
plot_CMYK
write_png
dreadHSV
plotHSV
flood_fill
flood_fill_blend
scale_wh
invert
getgamma 
getbitdepth
39/35
*/


const int C_RANGE = 65535;
const int MAX_RADIUS = 40;
const int MIN_RADIUS = 10;
const int HEADER = 50;
const int WIDTH = 1920;
const int HEIGHT = 1080;
const int T_LIMIT = 100;

int r_color() {
	return rand() % C_RANGE + 1;
}

int rotateY(int currentX, int currentY, int orginX, int orginY, int angle) {
	double _cos = cos(angle * M_PI / 180);
	double _sin = sin(angle * M_PI / 180);
	return ((currentX - orginX) * _sin + (currentY - orginY) * _cos) + orginY;
}

int rotateX(int currentX, int currentY, int orginX, int orginY, int angle) {
	double _cos = cos(angle * M_PI / 180);
	double _sin = sin(angle * M_PI / 180);
	return ((currentX - orginX) * _cos - (currentY - orginY) * _sin) + orginX;
}

void spinograph(pngwriter* png, int orginX, int orginY, int radius, int rotation) {


	// coordinate of  first inner circle
	int startingX = orginX; // starting x
	int startingY = orginY + radius / 2; // starting y

	int x, y;

	// create outer circle
	png->filledcircle(orginX, orginY, radius, 1.0, 1.0, 1.0);


	double temp;

	int red = r_color(), green = r_color(), blue = r_color();

	for (int angle = 0; angle < 360; angle += rotation) {
		png->circle(rotateX(startingX, startingY, orginX, orginY, angle), rotateY(startingX, startingY, orginX, orginY, angle), radius / 2, red, green, blue); // draw an inner circle
	}

} // spinograph

void createPolygon(pngwriter* png, int x, int y, int radius, int angle) {
	// coordinate starting point of polygon
	int startingX = x; // starting x
	int startingY = y + radius; // starting y

	const int numPoints = (int)(360 / angle) + 1;
	int currentAngle = angle;
	int* points = new int[(numPoints * 2)];

	int i = 0;
	int red = r_color();
	int green = r_color();
	int blue = r_color();
	while (currentAngle <= 360)
	{

		points[i] = rotateX(startingX, startingY, x, y, currentAngle); // x value
		i++;
		points[i] = rotateY(startingX, startingY, x, y, currentAngle); // Y value
		i++;
		currentAngle += angle;
	}
	points[i] = points[0];
	points[i + 1] = points[1];
	png->polygon(points, numPoints, red, green, blue);
	png->polygon_blend(points, numPoints, 0.2, 1.0, 1.0, 1.0);
}

void triangleSpin(pngwriter* png, int x1, int y1, int x2, int y2, int x3, int y3, int angle) {
	int currentAngle = angle;

	// points to rotate from
	int centerX = x1; // these are very specific and should be more dynamic
	int centerY = y2; // it would be better to require as parameters

	int _x1, _y1, _x2, _y2, _x3, _y3;
	int red = r_color();
	int green = r_color();
	int blue = r_color();

	while (currentAngle <= 360) {
		_x1 = rotateX(x1, y1, centerX, centerY, currentAngle);
		_x2 = rotateX(x2, y2, centerX, centerY, currentAngle);
		_x3 = rotateX(x3, y3, centerX, centerY, currentAngle);
		_y1 = rotateY(x1, y1, centerX, centerY, currentAngle);
		_y2 = rotateY(x2, y2, centerX, centerY, currentAngle);
		_y3 = rotateY(x3, y3, centerX, centerY, currentAngle);
		png->triangle(_x1, _y1, _x2, _y2, _x3, _y3, blue, green, red);
		png->filledtriangle(_x1, _y1, _x2, _y2, _x3, _y3, red, green, blue);
		png->filledtriangle_blend(_x1, _y1, _x2, _y2, _x3, _y3, 0.5, red, green, blue);
		currentAngle += angle;
	}
}

void placeholderSpin(pngwriter* png, int x, int y, int x_height, int y_height, int bar_height, int angle) {
	int currentSngle = angle;
	int red = r_color();
	int green = r_color();
	int blue = r_color();
	

} 

void arrowSpin(pngwriter* png, int x1, int y1, int x2, int y2, int size, int angle) {
	int currentAngle = angle;
	int orginX = (x1 + x2) / 2;
	int orginY = (y1 + y2) / 2;
	int _x1, _x2, _y1, _y2;
	int red = r_color();
	int blue = r_color();
	int green = r_color();
	while (currentAngle <= 360)
	{
		_x1 = rotateX(x1, y1, orginX, orginY, currentAngle);
		_x2 = rotateX(x2, y2, orginX, orginY, currentAngle);
		_y1 = rotateY(x1, y1, orginX, orginY, currentAngle);
		_y2 = rotateY(x2, y2, orginX, orginY, currentAngle);
		png->arrow(_x1, _y1, _x2, _y2, 150, 90, red, blue, green);
		currentAngle += angle;
	}

}

std::string GetCurrentDirectory()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");

	return std::string(buffer).substr(0, pos);
}

int _max(int a, int b) {
	if (a > b)
		return a;
	return b;
}

void createImage() {
	
	pngwriter* image = new pngwriter();

	// laplacian
	image->laplacian(1.0, 1.0);

	// resize image 
	image->resize(WIDTH, HEIGHT);

	// rename image
	char* projectName = (char*)("Project.png");
	image->pngwriter_rename(projectName);


	// image height and width
	int height = image->getheight();
	int width = image->getwidth();

	// image info
	image->settext("COMP3420 Project1", "Nickeem Payne-Deacon", "Abstract Image(1920x1080)", "Visual Studio, Windows 11");
	image->flood_fill(width / 2, height / 2, 65535, 65535, 65535);
	image->flood_fill_blend(width / 2, height / 2, 1.0, 65535, 65535, 65535);

	int font_size = HEADER;

	// geometry
	int x = WIDTH / 2; // orgin of x 
	int y = HEIGHT / 2; // orgin of y
	int radius = 300; // radius of outer circle
	int rotation = 3; // degree to rotate coordinates


	arrowSpin(image, x - radius, y, x + radius, y, 150, 30);
	triangleSpin(image, x, y + 359, x - 100, y, x + 100, y, 45);
	// Original: triangleSpin(image, x, y + 500, x - 500, y - 300, x + 500, y - 300, 45);
	// spinograph 
	spinograph(image, x, y, radius, rotation);
	createPolygon(image, x, y, radius, 30);

	//image->filledtriangle(x, y + 310, x - 100, y - 290, x + 100, y - 290, 1.0, 1.0, 1.0);

	// plot text on image
	image->filledsquare(0, HEIGHT, 600, HEIGHT - HEADER - 20, 1.0, 1.0, 1.0);
	image->filledsquare_blend(0, HEIGHT, 600, HEIGHT - HEADER - 20, 0.2, 1.0, 1.0, 1.0);
	image->square(0, HEIGHT, 600 + 1, HEIGHT - HEADER - 20 - 1, 0.5, 0.12, 0.78);
	image->square_blend(0, HEIGHT, 600 + 1, HEIGHT - HEADER - 20 - 1, 0.5, 0.5, 0.12, 0.78);

	char* font_path = (char*)("Allura-Regular.ttf");
	char* title = (char*)("Nickeem Payne-Deacon  400008889  Geometry");
	image->plot_text(font_path, font_size, 10, height - font_size, 0.0, title, 40000, 12300, 23000);
	image->plot_text_blend(font_path, font_size, 10, height - font_size, 0.0, title, 0.55, 39168, 63232, 56576);

	int title_width = image->get_text_width(font_path, font_size, title);
	// arrow pointing towards title
	int arrow_y = WIDTH - font_size / 2;
	image->filledarrow(title_width + 150, arrow_y, title_width + 50, arrow_y, 30, 0.5, r_color(), r_color(), r_color());

	//image->arrow(x - radius, y, x + radius, y, 150, 0.5, r_color(), r_color(), r_color());
	arrowSpin(image, x - radius, y, x + radius, y, 150, 30);

	// maltcross in the center of the circle
	image->cross(WIDTH / 2, HEIGHT / 2, radius * 2 + 190, radius * 2 + 190, r_color(), r_color(), r_color());
	image->maltesecross(WIDTH / 2, HEIGHT / 2, radius + 410, radius + 410, 80, 80, r_color(), r_color(), r_color());

	// diamond in center of spinograph
	image->diamond(WIDTH / 2, HEIGHT / 2, radius * 2, radius * 2, 0.5, 0.5, 0.5);

	// draw line and convert line to hsv and cymk
	int red = r_color();
	int green = r_color();
	int blue = r_color();

	// plot lines between 50 and 70 and make 150 pixels from 50 (creates box)
	for (int __y = 50; __y < 70; __y++)
	{
		image->line(50, __y, 200, __y, red, blue, green);
		image->line_blend(50, __y, 200, __y, 0.5, blue, green, red);
	}

	// read each value within line box
	double C, M, Y, K;
	for (int __y = 50; __y < 70; __y++)
	{
		for (int __x = 50; __x < 200; __x++)
		{
			double r = image->dread(__x, __y, 1);
			double g = image->dread(__x, __y, 2);
			double b = image->dread(__x, __y, 3);
			double H = image->dreadHSV(__x, __y, 1);
			double S = image->dreadHSV(__x, __y, 2);
			double V = image->dreadHSV(__x, __y, 3);

			// convert rgb to cmyk
			K = (1 - (_max(r, _max(g, b))));
			C = (1 - r - K) / (1 - K);
			M = (1 - g - K) / (1 - K);
			Y = (1 - b - K) / (1 - K);

			// plot duplicate rectanlgle from previous lines
			image->plotCMYK(__x + 200, __y, C, M, Y, K);
			image->plotHSV(__x + 400, __y, H, S, V);


		}
	}

	image->invert();
	image->scale_wh(WIDTH, 1080); // scale from 1920x1200 to 1920x1080
	image->write_png();

	// image properties
	double image_gc = image->getgamma(); // image's gamma coefficient
	double image_bitDepth = image->getbitdepth();
	double pngWriter_version = image->version();

	image->close();
}

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ProjectForm
	/// </summary>
	public ref class ProjectForm : public System::Windows::Forms::Form
	{
	public:
		ProjectForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ProjectForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ displayBox;
	protected:

	private: System::Windows::Forms::Button^ quitButton;
	private: System::Windows::Forms::Button^ button1;


	private: System::Windows::Forms::TextBox^ textBox1;
	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			srand(time(NULL));
			this->displayBox = (gcnew System::Windows::Forms::PictureBox());
			this->quitButton = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->displayBox))->BeginInit();
			this->SuspendLayout();
			// 
			// displayBox
			// 
			this->displayBox->Location = System::Drawing::Point(9, 34);
			this->displayBox->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->displayBox->Name = L"displayBox";
			this->displayBox->Size = System::Drawing::Size(1173, 695);
			this->displayBox->TabIndex = 0;
			this->displayBox->TabStop = false;
			// 
			// quitButton
			// 
			this->quitButton->Font = (gcnew System::Drawing::Font(L"Cooper Black", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->quitButton->Location = System::Drawing::Point(1050, 747);
			this->quitButton->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->quitButton->Name = L"quitButton";
			this->quitButton->Size = System::Drawing::Size(132, 50);
			this->quitButton->TabIndex = 2;
			this->quitButton->Text = L"Close";
			this->quitButton->UseVisualStyleBackColor = true;
			this->quitButton->Click += gcnew System::EventHandler(this, &ProjectForm::onClickQuit);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Cooper Black", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(9, 748);
			this->button1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(132, 50);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Create Image";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &ProjectForm::onClickCreateButton);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(9, 11);
			this->textBox1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(883, 20);
			this->textBox1->TabIndex = 6;
			// 
			// ProjectForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1185, 846);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->quitButton);
			this->Controls->Add(this->displayBox);
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"ProjectForm";
			this->Text = L"ProjectForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->displayBox))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
	
#pragma endregion
	
		
	private: System::Void onClickQuit(System::Object^ sender, System::EventArgs^ e) {
		Close();
	}
		   
	private: System::Void onClickCreateButton(System::Object^ sender, System::EventArgs^ e) {
		char* projectName = (char*)("Project.png");
		std::string path = GetCurrentDirectory();
		path = path.substr(0, path.length() - 9); // remove execution directory

		displayBox->Image;
		displayBox->Image = nullptr;
		displayBox->Refresh();
		createImage();
		


		displayBox->Load(L"Project.png");
		
		
		textBox1->Text = gcnew String((path + "Project.png").substr().c_str());
		displayBox->SizeMode = PictureBoxSizeMode::Zoom;
	}

private: System::Void onClickDisplay(System::Object^ sender, System::EventArgs^ e) {
	// define an object to get file name
	OpenFileDialog^ ofd;
	ofd = gcnew OpenFileDialog;

	// Types of files to be displayed
	ofd->Filter = "PNG Files (*png)|*.png|" "All files (*.*)|*.*";

	//set the filter for the preferred file type
	ofd->FilterIndex = 1;

	// Caption for the OpenFile dialog
	ofd->Title = "Select PNG file";

	// Caption for OpenFileDialog
	ofd->Title = "Select PNG file";

	// Display the dialog
	ofd->ShowDialog(); 

	if (ofd->FileName)
	{
		// copy file's name to textbox
		// this->textbox->Text = ofd->FileName;

		// put image in pictureBox
		displayBox->Load(ofd->FileName);

		// Format the image in pictureBox1
		displayBox->SizeMode = PictureBoxSizeMode::Zoom;
	}
}
};
}
