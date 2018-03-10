#include "client.h"
#include "keycodes.h"

namespace WarzoneGUI {
	void MenuOpenEvent(qboolean open);
	void KeyEvent(int key, qboolean down);
	void MouseEvent(int x, int y);
	void SendKeyboardStatusToRenderer(void);
}
