#include "Input.h"
#include <string>

namespace Input {

std::string to_string(ID id) {
    switch(id) {
        case A : return "A";
        case B : return "B";
        case C : return "C";
        case D : return "D";
        case E : return "E";
        case F : return "F";
        case G : return "G";
        case H : return "H";
        case I : return "I";
        case J : return "J";
        case K : return "K";
        case L : return "L";
        case M : return "M";
        case N : return "N";
        case O : return "O";
        case P : return "P";
        case Q : return "Q";
        case R : return "R";
        case S : return "S";
        case T : return "T";
        case U : return "U";
        case V : return "V";
        case W : return "W";
        case X : return "X";
        case Y : return "Y";
        case Z : return "Z";
        case Num0 : return "Num0";
        case Num1 : return "Num1";
        case Num2 : return "Num2";
        case Num3 : return "Num3";
        case Num4 : return "Num4";
        case Num5 : return "Num5";
        case Num6 : return "Num6";
        case Num7 : return "Num7";
        case Num8 : return "Num8";
        case Num9 : return "Num9";
        case Escape : return "Escape";
        case LControl : return "LControl";
        case LShift : return "LShift";
        case LAlt : return "LAlt";
        case LSystem : return "LSystem";
        case RControl : return "RControl";
        case RShift : return "RShift";
        case RAlt : return "RAlt";
        case RSystem : return "RSystem";
        case Menu : return "Menu";
        case LBracket : return "LBracket";
        case RBracket : return "RBracket";
        case SemiColon : return "SemiColon";
        case Comma : return "Comma";
        case Period : return "Period";
        case Quote : return "Quote";
        case Slash : return "Slash";
        case BackSlash : return "BackSlash";
        case Tilde : return "Tilde";
        case Equal : return "Equal";
        case Dash : return "Dash";
        case Space : return "Space";
        case Return : return "Return";
        case BackSpace : return "BackSpace";
        case Tab : return "Tab";
        case PageUp : return "PageUp";
        case PageDown : return "PageDown";
        case End : return "End";
        case Home : return "Home";
        case Insert : return "Insert";
        case Delete : return "Delete";
        case Add : return "Add";
        case Subtract : return "Subtract";
        case Multiply : return "Multiply";
        case Divide : return "Divide";
        case Left : return "Left";
        case Right : return "Right";
        case Up : return "Up";
        case Down : return "Down";
        case Numpad0 : return "Numpad0";
        case Numpad1 : return "Numpad1";
        case Numpad2 : return "Numpad2";
        case Numpad3 : return "Numpad3";
        case Numpad4 : return "Numpad4";
        case Numpad5 : return "Numpad5";
        case Numpad6 : return "Numpad6";
        case Numpad7 : return "Numpad7";
        case Numpad8 : return "Numpad8";
        case Numpad9 : return "Numpad9";
        case F1 : return "F1";
        case F2 : return "F2";
        case F3 : return "F3";
        case F4 : return "F4";
        case F5 : return "F5";
        case F6 : return "F6";
        case F7 : return "F7";
        case F8 : return "F8";
        case F9 : return "F9";
        case F10 : return "F10";
        case F11 : return "F11";
        case F12 : return "F12";
        case F13 : return "F13";
        case F14 : return "F14";
        case F15 : return "F15";
        case Pause : return "Pause";
        default : return "Unknown";
    };
}

}


