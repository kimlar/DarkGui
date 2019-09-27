#include "TextBox.h"
#include "Error.h"

void TextBox::Create(std::string text, int x, int y, int w)
{
	this->text = new Text(pointerBag);
	this->text->Create(pointerBag->GetAppFont(), "", textAdjustX, textAdjustY, 0, textColor);

	SetPosition(x, y);
	SetSize(w + backAdjustX, 20 + backAdjustY);

	textCursorCX = 0;
	UpdateCursorLocation();
	CreateEditTexture(rect.w - backAdjustX, rect.h - backAdjustY);

	this->text->SetText("");
	InsertText(text);
}

void TextBox::Destroy()
{
	text->Destroy();
	delete text;
	text = nullptr;
}

void TextBox::HandleEvent(SDL_Event& e)
{
	if (e.type == SDL_MOUSEMOTION)
	{
		int mx = e.motion.x;
		int my = e.motion.y;
		
		isHover = false;
		if (mx >= rect.x && mx < (rect.x + rect.w))
			if (my >= rect.y && my < (rect.y + rect.h))
				isHover = true;
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		int mx = e.motion.x;
		int my = e.motion.y;

		isActive = false;
		if (mx >= rect.x && mx < (rect.x + rect.w))
			if (my >= rect.y && my < (rect.y + rect.h))
				isActive = true;

		if (isActive)
		{
			MouseSetTextCursorX(mx);
		}
	}
	else if (e.type == SDL_KEYDOWN) // Special key input
	{
		// Only receive input if active
		if (!isActive)
			return;

		// Handle backspace
		if (e.key.keysym.sym == SDLK_BACKSPACE && text->GetText().length() > 0)
		{
			RemoveText(textCursorCX);
		}
		// Handle delete
		else if (e.key.keysym.sym == SDLK_DELETE)
		{
			textCursorCX++;
			if (textCursorCX > text->GetTextSize())
			{
				textCursorCX = text->GetTextSize();
				return;
			}

			RemoveText(textCursorCX);
		}
		// Handle enter
		else if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER)
		{
			isActive = false;
		}
		// Handle copy (CTRL+C)
		else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
		{
			std::string tempStr = text->GetText();

			// TODO: Text selection need fixing here!!!
			int selectStart = 2;
			int selectSize = 4;
			tempStr = tempStr.substr(selectStart, selectSize);
			SDL_SetClipboardText(tempStr.c_str());
		}
		// Move arrow left
		else if (e.key.keysym.sym == SDLK_LEFT)
		{
			textCursorCX--;
			if (textCursorCX < 0)
				textCursorCX = 0;
			UpdateCursorLocation();
		}
		// Move arrow right
		else if (e.key.keysym.sym == SDLK_RIGHT)
		{
			textCursorCX++;
			if (textCursorCX > text->GetTextSize())
				textCursorCX = text->GetTextSize();
			UpdateCursorLocation();
		}
		// Handle paste (CTRL+V)
		else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
		{
			// TODO: Text cursor need fixing here!!!
			// TODO: Create a text insert function in Text class
			int cursorPosition = 8;
			std::string tempStr = text->GetText();
			tempStr.insert(cursorPosition, SDL_GetClipboardText());
			text->SetText(tempStr);
		}
		// Handle paste (CTRL+X)
		else if (e.key.keysym.sym == SDLK_x && SDL_GetModState() & KMOD_CTRL)
		{
			std::string tempStr = text->GetText();

			// TODO: Text selection need fixing here!!!
			int selectStart = 2;
			int selectSize = 4;
			tempStr = tempStr.substr(selectStart, selectSize);
			SDL_SetClipboardText(tempStr.c_str());

			std::string tempStr2 = text->GetText();
			tempStr2.erase(selectStart, selectSize);
			text->SetText(tempStr2);
		}
	}
	else if (e.type == SDL_TEXTINPUT) // Special text input event
	{
		// Only receive input if active
		if (!isActive)
			return;

		// Not copy, pasting or cutting (therefore it is not clipboard)
		if (!((e.text.text[0] == 'c' || e.text.text[0] == 'C') && (e.text.text[0] == 'v' || e.text.text[0] == 'V') && (e.text.text[0] == 'x' || e.text.text[0] == 'X') && SDL_GetModState() & KMOD_CTRL))
		{
			InsertText(e.text.text);
		}
	}
}

void TextBox::Render()
{
	if (isActive || isHover)
		SDL_SetRenderDrawColor(&pointerBag->GetRenderer(), activeColor.r, activeColor.g, activeColor.b, activeColor.a);
	else
		SDL_SetRenderDrawColor(&pointerBag->GetRenderer(), borderColor.r, borderColor.g, borderColor.b, borderColor.a);
	SDL_RenderFillRect(&pointerBag->GetRenderer(), &rect);

	SDL_Rect frontRect = { rect.x + 1, rect.y + 1, rect.w - 2, rect.h - 2 };
	RenderTargetEditTexture();
	SDL_RenderCopy(&pointerBag->GetRenderer(), editTexture, nullptr, &frontRect);
}

void TextBox::SetPosition(int x, int y)
{
	rect.x = x;
	rect.y = y;
	//text->SetPosition(x, y);
}

void TextBox::SetSize(int w, int h)
{
	rect.w = w;
	rect.h = h;
}

void TextBox::SetTextWrap(bool wrap)
{
	this->useTextWrap = wrap;

	if (wrap)
		text->SetWrapWidth(rect.w);
	else
		text->SetWrapWidth(0); // reset to no wrap width
}

void TextBox::CreateEditTexture(int w, int h)
{
	editTexture = SDL_CreateTexture(&pointerBag->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
	if (editTexture == nullptr)
	{
		std::string texError = "Unable to create blank texture! SDL Error: ";
		texError.append(SDL_GetError());
		Error(texError);
		return;
	}

	editRect = { 0,0,w,h };
	return;
}

void TextBox::RenderTargetEditTexture()
{
	SDL_SetRenderTarget(&pointerBag->GetRenderer(), editTexture);

	SDL_SetRenderDrawColor(&pointerBag->GetRenderer(), backColor.r, backColor.g, backColor.b, backColor.a);
	SDL_RenderClear(&pointerBag->GetRenderer());

	text->Render();

	if (isActive)
	{
		SDL_SetRenderDrawColor(&pointerBag->GetRenderer(), textColor.r, textColor.g, textColor.b, textColor.a);
		SDL_RenderDrawLine(&pointerBag->GetRenderer(), editCursor.x, editCursor.y, editCursor.x, editCursor.y + 14);
	}

	SDL_SetRenderTarget(&pointerBag->GetRenderer(), nullptr);
}

void TextBox::UpdateCursorLocation()
{
	editCursor = { textAdjustX, textAdjustY + 1 };
	if (!text->GetText().empty())
	{
		for (int i = 0; i < textCursorCX; i++)
			editCursor.x += textCharsLocPX[i];
	}
}

void TextBox::MouseSetTextCursorX(int mx)
{
	int curW = 0;
	int size = text->GetTextSize();
	for (int i = 0; i < size; i++)
	{
		curW += textCharsLocPX[i];
		if (curW > (mx - rect.x))
		{
			textCursorCX = i;
			if (textCursorCX < 0)
				textCursorCX = 0;
			break;
		}
	}
	
	int totW = 0;
	for (int i = 0; i < size; i++)
		totW += textCharsLocPX[i];
	if (totW < (mx - rect.x))
		textCursorCX = size;

	UpdateCursorLocation();
}

void TextBox::InsertText(std::string insert)
{
	for (int i = 0; i < insert.size(); i++)
	{
		int oldSizeX = text->GetSize().x;
		std::string tempStr = insert.substr(i,1);
		text->InsertText(textCursorCX, tempStr);

		textCharsLocPX.insert(textCharsLocPX.begin() + textCursorCX, text->GetSize().x - oldSizeX);
		textCursorCX++;
	}
	UpdateCursorLocation();
}

void TextBox::RemoveText(int startCX, int lenCX)
{
	if (text->GetText().size() > 0 && startCX > 0)
	{
		text->RemoveText(startCX - 1, lenCX);
		
		for (int i = 0; i < lenCX; i++)
		{
			textCharsLocPX.erase(textCharsLocPX.begin() + textCursorCX - 1);
			textCursorCX--;
		}

		UpdateCursorLocation();
	}
}
