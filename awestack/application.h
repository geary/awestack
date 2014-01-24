#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_opengl.h"
#include <Awesomium/WebCore.h>

// Some constants that configure certain aspects of the animation:
#define SPREADIMAGE         0.1     // The amount of spread between WebTiles
#define FLANKSPREAD         0.4     // How much a WebTile moves way from center
#define FRICTION            10.0    // Friction while "flowing" through WebTiles
#define MAXSPEED            7.0     // Throttle maximum speed to this value
#define ZOOMTIME            0.3     // Speed to zoom in/out of a WebTile
#define TRANSPARENT         1       // Whether or not we should use transparency

// Forward declaration, actually declared in WebTile.h
struct WebTile;

class MethodDispatcher;

// Our main Application class is responsible for setting up the WebCore, the
// OpenGL scene, handling input, animating "WebTiles", and all other logic.
class Application :
	public Awesomium::WebViewListener::View,
	public Awesomium::WebViewListener::Process {
 public:
	Application();
	~Application();

	WebTile* addWebTile(
		const Awesomium::WebString id,
		const Awesomium::WebString url,
		int left, int top,
		int width, int height
	);

	void loadWebTile(
		const Awesomium::WebString id,
		const Awesomium::WebString url
	);

	void removeWebTile(
		const Awesomium::WebString id
	);

	int getWebTileIndex(
		const Awesomium::WebString id
	);

	WebTile* getWebTile(
		const Awesomium::WebString id
	);

	void update();

	void draw();

	void drawOne( WebTile* tile );

	void drawTile(int index, double off, double zoom);

	void updateWebTiles();

	void updateAnimationAtTime(double elapsed);

	void endAnimation();

	void driveAnimation();

	void startAnimation(double speed);

	void animateTo(int index);

	void handleInput();

	void handleDragBegin(int x, int y);

	void handleDragMove(int x, int y);

	void handleDragEnd(int x, int y);

	bool isReadyToQuit() const;

	void bindMethods( Awesomium::WebView* webView, const Awesomium::WebString& id );

	void CallJavaScript( Awesomium::WebView* view, const Awesomium::WebString& object, const Awesomium::WebString& function );

	void JS_open( Awesomium::WebView* caller, const Awesomium::JSArray& args );

	void JS_close( Awesomium::WebView* caller, const Awesomium::JSArray& args );

	void JS_focus( Awesomium::WebView* caller, const Awesomium::JSArray& args );

	void JS_order( Awesomium::WebView* caller, const Awesomium::JSArray& args );

	void JS_postMessage( Awesomium::WebView* caller, const Awesomium::JSArray& args );

	virtual void OnChangeTitle(Awesomium::WebView* caller,
														 const Awesomium::WebString& title);

	virtual void OnChangeAddressBar(Awesomium::WebView* caller,
																	const Awesomium::WebURL& url);

	virtual void OnChangeTooltip(Awesomium::WebView* caller,
															 const Awesomium::WebString& tooltip);

	virtual void OnChangeTargetURL(Awesomium::WebView* caller,
																 const Awesomium::WebURL& url);

	virtual void OnChangeCursor(Awesomium::WebView* caller,
															Awesomium::Cursor cursor);

	virtual void OnChangeFocus(Awesomium::WebView* caller,
																Awesomium::FocusedElementType focus_type);

	virtual void OnAddConsoleMessage(Awesomium::WebView* caller,
																	 const Awesomium::WebString& message,
																	 int line_number,
																	 const Awesomium::WebString& source);

	virtual void OnShowCreatedWebView(Awesomium::WebView* caller,
																		Awesomium::WebView* new_view,
																		const Awesomium::WebURL& opener_url,
																		const Awesomium::WebURL& target_url,
																		const Awesomium::Rect& initial_pos,
																		bool is_popup);

	virtual void OnUnresponsive(Awesomium::WebView* caller);

	virtual void OnResponsive(Awesomium::WebView* caller);

	virtual void OnCrashed(Awesomium::WebView* caller,
												 Awesomium::TerminationStatus status);

 protected:
	bool shouldQuit, isAnimating, isDragging, isActiveWebTileFocused,
			 zoomDirection;
	double offset, startTime, startOff, startPos, startSpeed, runDelta, lastPos,
				 zoomStart, zoomEnd;
	int numTiles;
	std::vector<WebTile*> webTiles;
	GLfloat customColor[16];
	int activeWebTile;
	Awesomium::WebCore* webCore;
	int WIDTH, HEIGHT;
	MethodDispatcher* m_methodDispatcher;
	Awesomium::JSArray m_order;
};

#endif
