#include "elineedit.h"

eLineEdit::eLineEdit(eMainWindow* const window) :
    eLabel(window) {
    setTextAlignment(eAlignment::left | eAlignment::vcenter);
}

bool eLineEdit::keyPressEvent(const eKeyPressEvent& e) {
    const auto k = e.key();
    auto txt = text();
    if(k == SDL_Scancode::SDL_SCANCODE_BACKSPACE) {
        if(txt.empty()) return true;
        txt.pop_back();
        setText(txt);
        return true;
    }
    std::string add;
    if(k == SDL_Scancode::SDL_SCANCODE_0) {
        add = "0";
    } else if(k == SDL_Scancode::SDL_SCANCODE_1) {
        add = "1";
    } else if(k == SDL_Scancode::SDL_SCANCODE_2) {
        add = "2";
    } else if(k == SDL_Scancode::SDL_SCANCODE_3) {
        add = "3";
    } else if(k == SDL_Scancode::SDL_SCANCODE_4) {
        add = "4";
    } else if(k == SDL_Scancode::SDL_SCANCODE_5) {
        add = "5";
    } else if(k == SDL_Scancode::SDL_SCANCODE_6) {
        add = "6";
    } else if(k == SDL_Scancode::SDL_SCANCODE_7) {
        add = "7";
    } else if(k == SDL_Scancode::SDL_SCANCODE_8) {
        add = "8";
    } else if(k == SDL_Scancode::SDL_SCANCODE_9) {
        add = "9";
    } else if(k == SDL_Scancode::SDL_SCANCODE_A) {
        add = "a";
    } else if(k == SDL_Scancode::SDL_SCANCODE_B) {
        add = "b";
    } else if(k == SDL_Scancode::SDL_SCANCODE_C) {
        add = "c";
    } else if(k == SDL_Scancode::SDL_SCANCODE_D) {
        add = "d";
    } else if(k == SDL_Scancode::SDL_SCANCODE_E) {
        add = "e";
    } else if(k == SDL_Scancode::SDL_SCANCODE_F) {
        add = "f";
    } else if(k == SDL_Scancode::SDL_SCANCODE_G) {
        add = "g";
    } else if(k == SDL_Scancode::SDL_SCANCODE_H) {
        add = "h";
    } else if(k == SDL_Scancode::SDL_SCANCODE_I) {
        add = "i";
    } else if(k == SDL_Scancode::SDL_SCANCODE_J) {
        add = "j";
    } else if(k == SDL_Scancode::SDL_SCANCODE_K) {
        add = "k";
    } else if(k == SDL_Scancode::SDL_SCANCODE_L) {
        add = "l";
    } else if(k == SDL_Scancode::SDL_SCANCODE_M) {
        add = "m";
    } else if(k == SDL_Scancode::SDL_SCANCODE_N) {
        add = "n";
    } else if(k == SDL_Scancode::SDL_SCANCODE_O) {
        add = "o";
    } else if(k == SDL_Scancode::SDL_SCANCODE_P) {
        add = "p";
    } else if(k == SDL_Scancode::SDL_SCANCODE_R) {
        add = "r";
    } else if(k == SDL_Scancode::SDL_SCANCODE_S) {
        add = "s";
    } else if(k == SDL_Scancode::SDL_SCANCODE_T) {
        add = "t";
    } else if(k == SDL_Scancode::SDL_SCANCODE_U) {
        add = "u";
    } else if(k == SDL_Scancode::SDL_SCANCODE_W) {
        add = "w";
    } else if(k == SDL_Scancode::SDL_SCANCODE_X) {
        add = "x";
    } else if(k == SDL_Scancode::SDL_SCANCODE_Y) {
        add = "y";
    } else if(k == SDL_Scancode::SDL_SCANCODE_Z) {
        add = "z";
    } else if(k == SDL_Scancode::SDL_SCANCODE_MINUS) {
        add = "-";
    } else if(k == SDL_Scancode::SDL_SCANCODE_SPACE) {
        add = " ";
    } else {
        return false;
    }
    if(e.shiftPressed()) {
        std::transform(add.begin(), add.end(), add.begin(), ::toupper);
    }
    setText(txt + add);
    return true;
}

void eLineEdit::paintEvent(ePainter& p) {
    eLabel::paintEvent(p);
    mTime++;
    if(mTime > 30) {
        if(mTime > 60) {
            mTime = 0;
        }
        return;
    }
    const auto& tex = texture();
    int texw;
    int texh;
    const int fs = fontSize();
    if(tex) {
        texw = tex->width();
        texh = tex->height();
    } else {
        texw = 0;
        texh = fs;
    }
    const int lh = 2*texh/3;
    const int x = texw + fs/4;
    const int y = (height() - lh)/2;
    const int w = lineWidth();
    const int h = lh;
    SDL_Color col1;
    SDL_Color col2;
    eFontColorHelpers::colors(fontColor(), col1, col2);
    p.fillRect({x, y, w, h}, col1);
}
