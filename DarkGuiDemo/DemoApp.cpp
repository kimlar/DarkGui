#include "DemoApp.h"

#include <SDL.h>
#include <vector>
#include "PointerBag.h"
#include "FilePath.h"
#include "Window.h"
#include "Texture.h"
#include "Font.h"
#include "Text.h"
#include "TextBox.h"
#include "Button.h"
#include "CheckBox.h"
#include "OptionBox.h"
#include "Image.h"
#include "ProgressBar.h"

void DemoApp::Run()
{
	PointerBag* pointerBag = new PointerBag();

	FilePath* filePath = new FilePath();
	filePath->Initialize();
	pointerBag->SetFilePath(filePath);
	
	Window* window = new Window(pointerBag);
	window->Create("DarkGui Demo");

	Font* font = new Font();
	font->Load("C:/Windows/Fonts/segoeui.ttf", 12);
	pointerBag->SetAppFont(font);

	Text* text = new Text(pointerBag);
	text->Create(font, "Hello world!", 40, 40);

	TextBox* textBox = new TextBox(pointerBag);
	textBox->Create("My project folder", 40, 70, 200);

	Button* button = new Button(pointerBag);
	button->Create("Hello", 40, 100, 200);

	CheckBox* checkBox = new CheckBox(pointerBag);
	checkBox->Create("SDL_image", 40, 130);

	// Group 1
	std::vector<OptionBox*> optionBoxesGroup1;
	// Item 1
	optionBoxesGroup1.push_back(new OptionBox(pointerBag));
	optionBoxesGroup1.back()->Create("SDL drawing", 40, 160, true);
	// Item 2
	optionBoxesGroup1.push_back(new OptionBox(pointerBag));
	optionBoxesGroup1.back()->Create("OpenGL drawing", 40, 190);
	// Item 3
	optionBoxesGroup1.push_back(new OptionBox(pointerBag));
	optionBoxesGroup1.back()->Create("Vulcan drawing", 40, 220);

	// Group 2
	std::vector<OptionBox*> optionBoxesGroup2;
	// Item 1
	optionBoxesGroup2.push_back(new OptionBox(pointerBag));
	optionBoxesGroup2.back()->Create("Dirt", 40, 280, true);
	// Item 2
	optionBoxesGroup2.push_back(new OptionBox(pointerBag));
	optionBoxesGroup2.back()->Create("Sand", 40, 310);
	// Item 3
	optionBoxesGroup2.push_back(new OptionBox(pointerBag));
	optionBoxesGroup2.back()->Create("Stone", 40, 340);

	// Collection of groups
	std::vector<std::vector<OptionBox*>> optionBoxes;
	optionBoxes.push_back(optionBoxesGroup1);
	optionBoxes.push_back(optionBoxesGroup2);

	Image* image = new Image(pointerBag);
	image->Create("Moon.png", 40, 370);

	ProgressBar* progressBar = new ProgressBar(pointerBag);
	progressBar->Create(1, 3, 300, 40, 200);
	
	// Enable text input (TextBox support)
	SDL_StartTextInput();

	SDL_Event e;
	while (window->run)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			window->HandleEvent(e);
			textBox->HandleEvent(e);
			button->HandleEvent(e);
			checkBox->HandleEvent(e);
			for (auto const& i : optionBoxes)
				for (auto const& j : i)
					j->HandleEvent(e);
		}

		// Pre app stuff
		for (auto const& i : optionBoxes)
		{
			bool hasBeenClicked = false;
			for (auto const& j : i)
				if (j->isClicked)
					hasBeenClicked = true;
			if (hasBeenClicked)
				for (auto& j : i)
					j->isChecked = false;
			for (auto& j : i)
				if (j->isClicked)
					j->isChecked = true;
		}

		// App stuff
		if (button->isClicked)
		{
			printf("Project directory is: %s\n", textBox->GetText().c_str());
			if (checkBox->isChecked)
				printf("SDL_image is included\n");

			// Group 1
			if (optionBoxes[0][0]->isChecked)
				printf("SDL drawing selected\n");
			else if (optionBoxes[0][1]->isChecked)
				printf("OpenGL drawing selected\n");
			else if (optionBoxes[0][2]->isChecked)
				printf("Vulcan drawing selected\n");

			// Group 2
			if (optionBoxes[1][0]->isChecked)
				printf("Dirt\n");
			else if (optionBoxes[1][1]->isChecked)
				printf("Sand\n");
			else if (optionBoxes[1][2]->isChecked)
				printf("Stone\n");
		}

		// Only draw when not minimized
		if (!window->isMinimized())
		{
			// Render
			window->ClearScreen();
			//...
			text->Render();
			textBox->Render();
			button->Render();
			checkBox->Render();
			for (auto const& i : optionBoxes)
				for (auto const& j : i)
					j->Render();
			image->Render();
			progressBar->Render();
			window->UpdateScreen();
		}
		else
			SDL_Delay(1);
	}

	// Disable text input (TextBox support)
	SDL_StopTextInput();

	progressBar->Destroy();
	delete progressBar;
	progressBar = nullptr;

	image->Destroy();
	delete image;
	image = nullptr;

	for (auto& i : optionBoxes)
	{
		for (auto& j : i)
		{
			j->Destroy();
			delete j;
			j = nullptr;
		}
		i.clear();
	}

	checkBox->Destroy();
	delete checkBox;
	checkBox = nullptr;

	button->Destroy();
	delete button;
	button = nullptr;

	textBox->Destroy();
	delete textBox;
	textBox = nullptr;

	text->Destroy();
	delete text;
	text = nullptr;

	font->Unload();
	delete font;
	font = nullptr;

	window->Destroy();
	delete window;
	window = nullptr;

	delete filePath;
	filePath = nullptr;

	delete pointerBag;
	pointerBag = nullptr;
}
